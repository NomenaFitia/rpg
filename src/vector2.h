#ifndef VECTOR2_H
#define VECTOR2_H
#include <math.h>


struct Vector2 {
    int x;
    int y;

    Vector2(int x_ = 0, int y_ = 0) : x(x_), y(y_) {}

    bool operator==(const Vector2& other) const {
        return x == other.x && y == other.y;
    }

    Vector2 operator+(const Vector2& other) const {
        return Vector2(x + other.x, y + other.y);
    }

    Vector2 operator-(const Vector2& other) const {
        return Vector2(x - other.x, y - other.y);
    }

    double distanceTo(const Vector2& other) const {
        return sqrt((other.x - x) * (other.x - x) + (other.y - y) * (other.y - y) );
    }

    bool isInRange(const Vector2& other, int range) const {
        return abs(x - other.x) <= range && abs(y - other.y) <= range;
    }

    Vector2& operator+=(const Vector2& other) {
        x += other.x;
        y += other.y;

        return *this;
    }

    Vector2 wrapPosition(const Vector2& position, int width, int height) {
        int newX = (position.x % width + width) % width;
        int newY = (position.y % height + height) % height;

        return Vector2(newX, newY);
    }
};

#endif

