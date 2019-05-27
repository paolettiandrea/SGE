//
// Created by andrea on 5/24/19.
//

#ifndef FACTORY_EXPERIMENTS_PATH_HPP
#define FACTORY_EXPERIMENTS_PATH_HPP

#include "SGE/Vec2.hpp"
#include <vector>
#include <ostream>
#include "SGE/components/Transform.hpp"

/*!
\file
\brief ${BRIEF_FILE_DESCRIPTION}
*/
namespace sge {
    /*!
     * \brief A simple path
     */
    class Path {
    public:
        Path();
        Path(const Path& that);

        Path& operator=(const Path& that);
        Vec2<float>& operator[](unsigned int index);
        Vec2<float> operator[](unsigned int index) const;

        void append_point(Vec2<float> new_point);

        bool is_closed() { return m_is_closed; }
        void set_closed(bool closed) { m_is_closed = closed; }

        void set_size(unsigned int size);
        unsigned int get_size() const;

        Vec2<float>& get_relative(unsigned int base_index, int offset);

        void load_from_file(std::string path);

        void print();
    private:
        std::vector<Vec2<float>> m_points;
        bool m_is_closed = false;

    };
}



#endif //FACTORY_EXPERIMENTS_PATH_HPP
