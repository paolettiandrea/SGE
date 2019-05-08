//
// Created by andrea on 5/5/19.
//

#ifndef FACTORY_EXPERIMENTS_VEC2_HPP
#define FACTORY_EXPERIMENTS_VEC2_HPP


/*!
\file
\brief ${BRIEF_FILE_DESCRIPTION}
*/
#include <string>

namespace sge {
    template <class T>
    class Vec2 {
    public:
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
        Vec2 operator-(const Vec2& that) {
            return Vec2<T>(this->x-that.x, this->y-that.y);
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



#endif //FACTORY_EXPERIMENTS_VEC2_HPP
