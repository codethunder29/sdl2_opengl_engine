#ifndef __DATATYPES__
#define __DATATYPES__

// used templates to not write a lot of versions of the same thing
template <typename T>
class Vec2
{
public:
    T x;
    T y;
    
    Vec2() {}  // doing this because i cant with default with templates

    Vec2(T x, T y)
    {
        this->x = x;
        this->y = y;
    }

    Vec2& operator=(const Vec2& other)
    {
        x = other.x;
        y = other.y;

        return *this;
    }

    Vec2 operator+(const Vec2& other)
    {
        Vec2<T> v(x, y);
        v.x += other.x;
        v.y += other.y;

        return v;
    }

    Vec2& operator+=(const Vec2& other)
    {
        x += other.x;
        y += other.y;

        return *this;
    }

    Vec2 operator-(const Vec2& other)
    {
        Vec2<T> v(x, y);
        v.x -= other.x;
        v.y -= other.y;

        return v;
    }

    Vec2& operator-=(const Vec2& other)
    {
        x -= other.x;
        y -= other.y;

        return *this;
    }

    Vec2 operator*(const float other)
    {
        Vec2<T> v(x, y);
        v.x *= other;
        v.y *= other;

        return v;
    }

    Vec2& operator*=(const float other)
    {
        x *= other;
        y *= other;

        return *this;
    }

    Vec2 operator/(const float other)
    {
        Vec2<T> v(x, y);
        v.x /= other;
        v.y /= other;

        return v;
    }

    Vec2& operator/=(const float other)
    {
        x /= other;
        y /= other;

        return *this;
    }
};

// struct Circle
// {
//     Vec2<float> pos;
//     float radius;
// };

// struct Line
// {
//     Vec2<float> p1;
//     Vec2<float> p2;
// };

// struct Ray
// {
//     Vec2<float> pos;
//     float angle;
//     float magnitude;
// };

#endif