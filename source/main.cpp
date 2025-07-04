#define STB_IMAGE_IMPLEMENTATION
#include "../libs/stb/stb_image.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>



int main(int argc, char* argv[])
{
	std::string image_name;
	bool bflip_image = false;
	bool bbit_size = true;

	if (argc == 2)
	{
		image_name = argv[1];
		std::cout << "Using standard settings: alpha in bits and no flipping." << std::endl;
	}
	else if (argc == 3)
	{
		image_name = argv[1];
		std::string second_arg = argv[2];
		if (second_arg == "-f")
		{
			bflip_image = true;
			std::cout << "Custom settings: alpha in bits and flipping image." << std::endl;
		}
		else
		{
			bbit_size = false;
			std::cout << "Custom settings: alpha in bytes and no flipping." << std::endl;
		}
	}
	else if (argc > 3)
	{
		image_name = argv[1];
		bflip_image = true;
		bbit_size = false;
		std::cout << "Custom settings: alpha in bytes and flipping image." << std::endl;
	}
	else
	{
		std::cout << "Unexpected amount of arguments: program is confused and will shut down." << std::endl;
		return -1;
	}
	
	int32_t image_width;
	int32_t image_height;
	int32_t image_channels;
	stbi_set_flip_vertically_on_load(bflip_image);
	uint8_t* image_data = stbi_load(image_name.c_str(), &image_width, &image_height, &image_channels, STBI_rgb_alpha);
	size_t image_size = image_width * image_height * image_channels;
	std::cout << "Height: " << image_height << ", Width: " << image_width << ", Channels: " << image_channels << std::endl;
	
	if (image_channels < 4)
	{
		std::cout << "Image has no alpha channel." << std::endl;
		return -2;
	}

	std::vector<uint8_t> alpha;
	for (int32_t i = 3; i < image_size; i += 4)
	{
		alpha.push_back(image_data[i]);
	}
	std::cout << "Alpha elements: " << alpha.size() << std::endl;



	if (bbit_size)
	{
		std::ofstream testfile(".\\bitslayout.txt");
		if (testfile.is_open())
		{
			int32_t tick = 1;
			for (int32_t i = 0; i < alpha.size(); i++)
			{
				testfile << static_cast<int>(alpha[i] / 255);
				if (tick == 8)
				{
					testfile << ", ";
					tick = 0;
				}
				tick++;
			}
			testfile.close();
		}
		else
			std::cout << "Failed to create bitslayout.txt" << std::endl;

		std::cout << "Writing alpha in bits... " << std::endl;
		std::ofstream outfile(".\\array.txt");
		if (outfile.is_open())
		{
			int tick = 1;
			for (int32_t i = 0; i < alpha.size(); i += 8)
			{
				uint8_t byte = 0;
				uint8_t mask = (alpha[i + 7] / 255 << 0) |
					(alpha[i + 6] / 255 << 1) |
					(alpha[i + 5] / 255 << 2) |
					(alpha[i + 4] / 255 << 3) |
					(alpha[i + 3] / 255 << 4) |
					(alpha[i + 2] / 255 << 5) |
					(alpha[i + 1] / 255 << 6) |
					(alpha[i] / 255 << 7);
				byte = byte | mask;

				outfile << static_cast<int>(byte) << ", ";
			}
			outfile.close();
		}
		else
		{
			std::cout << "Failed to create array.txt" << std::endl;
			return -3;
		}
	}
	else if (!bbit_size)
	{
		std::cout << "Writing alpha in bytes... " << std::endl;
		std::ofstream outfile(".\\array.txt");
		if (outfile.is_open())
		{
			for (int32_t i = 0; i < alpha.size(); i ++)
			{
				outfile << static_cast<int>(alpha[i]) << ", ";
			}
			outfile.close();
		}
		else
		{
			std::cout << "Failed to create array.txt" << std::endl;
			return -3;
		}
	}
	

	return 0;
}
