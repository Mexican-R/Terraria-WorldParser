#ifndef BLOCK_H
#define BLOCK_H

class Block {
public:
    Block(int block_type, int frame_x, int frame_y, int block_paint, int is_block_active, int block_shape) {
        this->block_type = block_type;
        this->frame_x = frame_x;
        this->frame_y = frame_y;
        this->block_paint = block_paint;
        this->is_block_active = is_block_active;
        this->block_shape = block_shape;
    }
    int block_type;
    int frame_x;
    int frame_y;
    int block_paint;
    int is_block_active;
    int block_shape;
};

#endif