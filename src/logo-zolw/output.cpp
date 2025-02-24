#include "output.h"
#include <fstream>

void makeTXTDrawing(const Drawing& drawing, const std::string& fname) {
	std::ofstream file(removeExtension(fname) + ".txt");

	if (!file.is_open())
		return;


	for (int i = (int)drawing.size() - 1; i >= 0; i--) {
		for (int j = 0; j < drawing[0].size(); j++) {
			if (drawing[i][j])
				file << "x";
			else
				file << " ";
		}
		file << std::endl;
	}

	file.close();
}

void makeBMPDrawing(const Drawing& drawing, const std::string& fname) {
    std::ofstream file(removeExtension(fname) + ".bmp", std::ios::binary);

    unsigned int width = (unsigned int)drawing[0].size();
    unsigned int height = (unsigned int)drawing.size();

    char zero = 0;
    char BM[] = { 'B', 'M' };
    unsigned int offset = 54;
    unsigned int dibSize = 40;
    unsigned short planes = 1;
    unsigned short bitsPerPixel = 24;
    unsigned int printResolution = 2835;

    unsigned int paddingSize = 4 - (width * 3) % 4;
    if (paddingSize == 4)
        paddingSize = 0;
    
    unsigned int bitmapSize = width * height * 3 + height * paddingSize;
    unsigned int fileSize = bitmapSize + offset;


    file.write(BM, sizeof(BM));
    file.write((char*)&fileSize, sizeof(fileSize));
    file.write(&zero, sizeof(char));
    file.write(&zero, sizeof(char));
    file.write(&zero, sizeof(char));
    file.write(&zero, sizeof(char));
    file.write((char*)&offset, sizeof(offset));

    file.write((char*)&dibSize, sizeof(dibSize));
    file.write((char*)&width, sizeof(width));
    file.write((char*)&height, sizeof(height));
    file.write((char*)&planes, sizeof(planes));
    file.write((char*)&bitsPerPixel, sizeof(bitsPerPixel));
    file.write(&zero, sizeof(char));
    file.write(&zero, sizeof(char));
    file.write(&zero, sizeof(char));
    file.write(&zero, sizeof(char));
    file.write((char*)&bitmapSize, sizeof(bitmapSize));
    file.write((char*)&printResolution, sizeof(printResolution));
    file.write((char*)&printResolution, sizeof(printResolution));
    file.write(&zero, sizeof(char));
    file.write(&zero, sizeof(char));
    file.write(&zero, sizeof(char));
    file.write(&zero, sizeof(char));
    file.write(&zero, sizeof(char));
    file.write(&zero, sizeof(char));
    file.write(&zero, sizeof(char));
    file.write(&zero, sizeof(char));

    unsigned char black = 0x00;
    unsigned char white = 0xff;
    for (int i = 0; i < drawing.size(); i++) {
        for (int j = 0; j < drawing[0].size(); j++) {
            if (drawing[i][j]) {
                file.write((char*)&black, sizeof(black));
                file.write((char*)&black, sizeof(black));
                file.write((char*)&black, sizeof(black));
            }
            else {
                file.write((char*)&white, sizeof(black));
                file.write((char*)&white, sizeof(black));
                file.write((char*)&white, sizeof(black));
            }
        }

        for (size_t i = 0; i < paddingSize; i++) {
            file.write(&zero, sizeof(char));
        }
    }

    file.close();
}

std::string removeExtension(std::string fname) {
    auto dot = fname.find_last_of('.');
    return fname.substr(0, dot);
}
