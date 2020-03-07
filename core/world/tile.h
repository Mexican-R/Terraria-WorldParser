#ifndef TILE_H
#define TILE_H

#include "block.h"
#include "wall.h"
#include "liquid.h"

template <int T>
static void copy_array(int self[T], int target[T]) {
    for (int i = 0; i < T; i++) {
        target[i] = self[i];
    }
}

class Tile {
public:
    Tile(Block *block, Wall *wall, Liquid *liquid) {
       this->block = block;
       this->wall = wall;
       this->liquid = liquid;
    }
    Block *block;
    Wall *wall;
    Liquid *liquid;
};

class TileData {
public:
    TileData(Tile *tile, int RLE) {
        this->tile = tile;
        this->RLE = RLE;
    } 
    Tile *tile;
    int RLE;
};

#endif