#ifndef SGE_VEC2_HPP
#define SGE_VEC2_HPP

#include <algorithm>
#include <string>
#include <cmath>

namespace sge {
    template <class T>
    class Vec2 {
    public:
        Vec2() : x(0), y(0) {}
        Vec2(T x, T y) : x(x), y(y) {}
        Vec2(const Vec2<T>& that) {
            x = that.x;
            y = that.y;
        }

        bool operator==(const Vec2 &that) const {
            return x == that.x &&
                   y == that.y;
        }

        bool operator!=(const Vec2 &that) const {
            return !(that == *this);
        }

        Vec2 operator+(const Vec2& that) {
            return Vec2<T>(this->x+that.x, this->y+that.y);
        }
        Vec2 operator+(const Vec2& that) const {
            return Vec2<T>(this->x+that.x, this->y+that.y);
        }
        Vec2 operator-(const Vec2& that) {
            return Vec2<T>(this->x-that.x, this->y-that.y);
        }
        Vec2 operator-(const Vec2& that) const {
            return Vec2<T>(this->x-that.x, this->y-that.y);
        }
        Vec2 operator*(const T& that) {
            return Vec2<T>(this->x*that, this->y*that);
        }
        Vec2 operator/(const T& that) {
            return Vec2<T>(this->x/that, this->y/that);
        }

        static Vec2<T> rotate(const Vec2<T>& vec, const T& radians) {
            Vec2<T> temp (cos(radians)*vec.x-sin(radians)*vec.y, sin(radians)*vec.x+cos(radians)*vec.y);
            return temp;
        }

        static T get_signed_angle(const Vec2<T>& vec1, const Vec2<T>& vec2) {
            return atan2f(vec1.x*vec2.y-vec1.y*vec2.x,
                          vec1.x*vec2.x+vec1.y*vec2.y);
        }

        Vec2<T> normalize() {
            this->set_magnitude(1.0f);
            return *this;
        }

        void set_magnitude(const T& new_magnitude) {
            T angle = atan2(y,x);
            x = cos(angle)*new_magnitude;
            y = sin(angle)*new_magnitude;
        }
        T get_magnitude() {
            return sqrt(powf(x,2) + powf(y,2));
        }

        const T get_magnitude() const {
            return sqrt(powf(x,2) + powf(y,2));
        }

        Vec2 operator*(const double& that) {
            return Vec2<T>(this->x*that, this->y*that);
        }

        Vec2& operator=(const Vec2<T>& that) {
            this->x = that.x;
            this->y = that.y;
            return *this;
        }

        void set(T _x, T _y);

        std::string to_string();


        static bool intersection(const Vec2<T>& A,const Vec2<T>& B, const Vec2<T>& C, const Vec2<T>& D, Vec2<T>& out, bool treat_as_segments = false, float epsilon=1e-6) {
// Store the values for fast access and easy
// equations-to-code conversion
            float x1 = A.x, x2 = B.x, x3 = C.x, x4 = D.x;
            float y1 = A.y, y2 = B.y, y3 = C.y, y4 = D.y;
            out.x=NAN; out.y=NAN;

            float d = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
            // If d is zero, there is no intersection
            if (fabsf(d) < epsilon) return false;

            // Get the x and y
            float pre = (x1*y2 - y1*x2), post = (x3*y4 - y3*x4);
            float x = ( pre * (x3 - x4) - (x1 - x2) * post ) / d;
            float y = ( pre * (y3 - y4) - (y1 - y2) * post ) / d;

            if (treat_as_segments) {
                // Check if the x and y coordinates are within both lines
                if ( x < fminf(x1, x2) || x > fmaxf(x1, x2) ||
                     x < fminf(x3, x4) || x > fmaxf(x3, x4) ) return false;
                if ( y < fminf(y1, y2) || y > fmaxf(y1, y2) ||
                     y < fminf(y3, y4) || y > fmaxf(y3, y4) ) return false;
            }

            out.x = x;
            out.y = y;
            return true;
        }


        T x;
        T y;
    };

    template<class T>
    void Vec2<T>::set(T _x, T _y) {
        y = _y;
        x = _x;
    }

    template<class T>
    std::string Vec2<T>::to_string() {
        return std::string("("+std::to_string(x)+ "," + std::to_string(y)+")");
    }


}



#endif //SGE_VEC2_HPP
