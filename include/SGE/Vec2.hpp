//
// Created by andrea on 5/5/19.
//

#ifndef FACTORY_EXPERIMENTS_VEC2_HPP
#define FACTORY_EXPERIMENTS_VEC2_HPP


/*!
\file
\brief ${BRIEF_FILE_DESCRIPTION}
*/
namespace sge {
    template <class T>
    class Vec2 {
    public:
        Vec2(T x, T y) : m_x(x), m_y(y) {}

        bool operator==(const Vec2 &that) const {
            return m_x == that.m_x &&
                   m_y == that.m_y;
        }

        bool operator!=(const Vec2 &that) const {
            return !(that == *this);
        }

        Vec2 operator+(const Vec2& that) {
            return Vec2<T>(this->m_x+that.m_x, this->m_y+that.m_y);
        }

    private:
        T m_x;
        T m_y;
    };
}



#endif //FACTORY_EXPERIMENTS_VEC2_HPP
