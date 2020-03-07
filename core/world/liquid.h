#ifndef LIQUID_H
#define LIQUID_H

class Liquid {
public:
    Liquid(int liquid_type, int liquid_shape) {
        this->liquid_type = liquid_type;
        this->liquid_shape = liquid_shape;
    }
    int liquid_type;
    int liquid_shape;
};

#endif