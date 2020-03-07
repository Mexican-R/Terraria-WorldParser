#ifndef WALL_H
#define WALL_H

class Wall {
public:
    Wall(int wall_id, int wall_paint) {
        this->wall_id = wall_id;
        this->wall_paint = wall_paint;
    }
    int wall_id;
    int wall_paint;
};

#endif