#include "WorldParserCore.h"

TileData read_tiles(std::ifstream &tiles_data) {
    int *flags1 = read_bits(tiles_data);
    int has_block = flags1[1];
    int has_wall = flags1[2];
    int liquid_type = flags1[4] * 2 + flags1[3];
    int has_extended_block_id = flags1[5];
    int rle = flags1[7] * 2 + flags1[6];
    int block_shape;
    int is_block_active;
    int is_block_painted;
    int is_wall_painted;
    int multiply_by;
    Block *block;
    Wall *wall;
    Liquid *liquid;
    
    if (flags1[0]) {
        int *flags2 = read_bits(tiles_data);
        block_shape = flags2[6] * 4 + flags2[5] * 2 + flags2[4];
        if (flags2[0]) {
            int *flags3 = read_bits(tiles_data);
            if (flags3[2]) {
                is_block_active = 0;
            } else {
                is_block_active = 1;
            }
            is_block_painted = flags3[3];
            is_wall_painted = flags3[4];
            delete flags3;
        } else {
            is_block_active = 1;
            is_block_painted = 0;
            is_wall_painted = 0;
        }
        delete flags2;
    } else {
        block_shape = 0;
        is_block_active = 1;
        is_block_painted = 0;
        is_wall_painted = 0;
    }
    
    if (has_block) {
        int block_type;
        if (has_extended_block_id) {
            block_type = read_uint16(tiles_data);
        } else {
            block_type = read_uint8(tiles_data);
        }
        int frame_x;
        int frame_y;
        if (tileframeimportant[block_type]) {
            frame_x = read_uint16(tiles_data);
            frame_y = read_uint16(tiles_data);
        } else {
            frame_x = 0;
            frame_y = 0;
        }
        int block_paint;
        if (is_block_painted) {
            block_paint = read_uint8(tiles_data);
        } else {
            block_paint = 0;
        }
        block = new Block(block_type, frame_x, frame_y, block_paint, is_block_active, block_shape);
    } else {
        block = new Block(0, 0, 0, 0, 0, 0);
    }
    if (has_wall) {
        int wall_id = read_uint8(tiles_data);
        int wall_paint;
        if (is_wall_painted) {
            wall_paint = read_uint8(tiles_data);
        } else {
            wall_paint = 0;
        }
        wall = new Wall(wall_id, wall_paint);
    } else {
        wall = new Wall(0, 0);
    }
    if (liquid_type != 0) {
        liquid = new Liquid(liquid_type, read_uint8(tiles_data));
    } else {
        liquid = new Liquid(0, 0);
    }
    if (rle == 2) {           
        multiply_by = read_uint16(tiles_data) + 1;
    } else if (rle == 1) {
        multiply_by = read_uint8(tiles_data) + 1;
    } else {
        multiply_by = 1;
    }
    delete flags1;
    Tile *tile = new Tile(block, wall, liquid);
    TileData tile_data(tile, multiply_by);
    return tile_data;     
}

static PyObject *WorldParserCore_ParseTiles(PyObject *self, PyObject *args) {
    char *path;
    int world_size_x, world_size_y;
    if (!PyArg_ParseTuple(args, "sii", &path, &world_size_x, &world_size_y)) {
        return NULL;
    }
    PyObject *world_tiles = PyList_New(0);
    std::ifstream tiles_data(path);
    std::vector<std::vector<Tile *>> _tiles(world_size_x);
    _tiles.resize(world_size_x);
    for (int i = 0; i < world_size_x; i++) {
        PyObject *column = PyList_New(0);
        while ((int)_tiles[i].size() < world_size_y) {
            TileData tiles_column = read_tiles(tiles_data);
            for (int _ = 0; _ < tiles_column.RLE; _++) {
                _tiles[i].push_back(tiles_column.tile);
                PyList_Append(column, Py_BuildValue("(iii)", 
                                                    tiles_column.tile->block->block_type,
                                                    tiles_column.tile->liquid->liquid_type,
                                                    tiles_column.tile->wall->wall_id));
                delete tiles_column.tile;
            }
        }
        PyList_Append(world_tiles, column);
    }
    
    return world_tiles;
    
}
    
static PyMethodDef WorldParserCore_methods[] = {
    {"ParseTiles", (PyCFunction)WorldParserCore_ParseTiles, METH_VARARGS, "parse"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef WorldParserCore = {
    PyModuleDef_HEAD_INIT,
    "WorldParserCore",
    "Core",
    -1,
    WorldParserCore_methods
};

PyMODINIT_FUNC PyInit_WorldParserCore(void) {
    return PyModule_Create(&WorldParserCore);
}
     