#ifndef ANIMATED_FIGURE_H
#define ANIMATED_FIGURE_H

class AnimatedFigure
{
public:
    AnimatedFigure();
    void draw();
    void update(float delta);

private:
    float rotationAngle;
};

#endif
