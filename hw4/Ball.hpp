#pragma once
#include "Painter.hpp"
#include "Point.hpp"
#include "Velocity.hpp"

class Ball {
private:
    Velocity _velocity;
    Point _center;
    double _radius;
    double _mass;
    Color _color;
    bool  _isCollidable;

public:
    Ball(Point center, Velocity velocity, Color color, double radius, bool isCollidable);
    
    void setVelocity(const Velocity& velocity);
    Velocity getVelocity() const;
    void draw(Painter& painter) const;
    void setCenter(const Point& center);
    Point getCenter() const;
    double getRadius() const;
    double getMass() const;
};
