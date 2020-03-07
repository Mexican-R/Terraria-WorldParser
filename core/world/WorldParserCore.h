#ifndef WORLDPARSERCORE_H
#define WORLDPARSERCORE_H

#include <iostream>
#include <fstream>
#include <vector>
#include "Python.h"
#include "tile.h"
#include "block.h"
#include "wall.h"
#include "liquid.h"

namespace FileReader {
    template <class T>
    T read(std::ifstream &File) {
        T data = 0;
        File.read((char*)&data, sizeof data);
        return data;
    }
}

#define read_bool(stream) ::FileReader::read<bool>(stream)
#define read_int8(stream) ::FileReader::read<char>(stream)
#define read_uint8(stream) ::FileReader::read<unsigned char>(stream)
#define read_int16(stream) ::FileReader::read<short>(stream)
#define read_uint16(stream) ::FileReader::read<unsigned short>(stream)
#define read_int32(stream) ::FileReader::read<int>(stream)
#define read_uint32(stream) ::FileReader::read<unsigned int>(stream)
#define read_float(stream) ::FileReader::read<float>(stream)
#define read_double(stream) ::FileReader::read<double>(stream)
#define read_int64(stream) ::FileReader::read<long long>(stream)
#define read_uint64(stream) ::FileReader::read<unsigned long long>(stream)

int *read_bits(std::ifstream &tiles_data) {
    int data = (int)read_int8(tiles_data);
    int *bits = new int[8];
    bits[0] = bool(data & 0b00000001);
    bits[1] = bool(data & 0b00000010);
    bits[2] = bool(data & 0b00000100);
    bits[3] = bool(data & 0b00001000);
    bits[4] = bool(data & 0b00010000);
    bits[5] = bool(data & 0b00100000);
    bits[6] = bool(data & 0b01000000);
    bits[7] = bool(data & 0b10000000);
    return bits;
}

int tileframeimportant[424] = {0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0};

#endif