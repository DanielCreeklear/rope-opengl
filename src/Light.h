#ifndef LIGHT_H
#define LIGHT_H

class Light {
public:
    Light();
    void initialize();
    void applyLighting();

private:
    float position[4];
};

#endif
