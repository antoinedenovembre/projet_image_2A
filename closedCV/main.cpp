#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

#include "ImageClasse.hpp"
#include "ImageCouleur.hpp"
#include "ImageDouble.hpp"
#include "ImageNdg.hpp"

namespace fs = std::__fs::filesystem;

std::vector<std::string> get_filenames(const std::string & path)
{
    std::vector<std::string> filenames;
    for (const auto & entry : fs::directory_iterator(path))
    {
        if (entry.is_regular_file())
        {
            filenames.push_back(entry.path().filename().string());
        }
    }
    return filenames;
}

int main(void)
{
    std::string folderPath     = "img";
    std::string testFolderPath = folderPath + "/test";
    std::string gtFolderPath   = folderPath + "/gt";

	double somme = 0;
	int count = 0;

    try
    {
        // Get filenames from the test folder
        std::vector<std::string> testImages = get_filenames(testFolderPath);

        // Loop through each image name
        for (const std::string & filename : testImages)
        {
            std::string testImagePath = testFolderPath + "/" + filename;
			std::string gtFilename = filename.substr(0, filename.find_last_of(".")) + ".png"; // Change extension to .png
            std::string gtImagePath = gtFolderPath + "/" + gtFilename;

            // Load the test image
            CImageNdg testImage{testImagePath};

            // Load the ground truth image
            // CImageNdg gtImage{gtImagePath};

            // Process the test image
            CImageNdg processedImage = testImage.process();

            // Compare the processed image with the ground truth image

            // Save the processed image
            processedImage.sauvegarde("processed_" + filename);
        }

		std::cout << "Moyenne : " << somme / count << std::endl;
    }
    catch (const fs::filesystem_error & e)
    {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
    }
    catch (const std::exception & e)
    {
        std::cerr << "Standard exception: " << e.what() << std::endl;
    }
    catch (const char * e)
    {
        std::cerr << "Exception: " << e << std::endl;
    }

    return 0;
}