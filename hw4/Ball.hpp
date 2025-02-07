#pragma once
#include "Painter.hpp"
#include "Point.hpp"
#include "Velocity.hpp"
#include "corecrt_math_defines.h"

class Ball {
    public:
    
        Ball();
        Ball::Ball(double radius, Color color);
    
        void setVelocity(const Velocity& velocity);
        Velocity getVelocity() const;
        void draw(Painter& painter) const;
        void setCenter(const Point& center);
        Point getCenter() const;
        double getRadius() const;
        double getMass() const;
    
    private:
        Point center;
        Velocity velocity;
        double radius;
        Color color;
    };
    