#include "Path.hpp"

#include <iostream>
#include <fstream>

using namespace sge;

//region Constructors and operators

Path& Path::operator=(const Path &that) {
    m_points.resize(that.m_points.size());
    for (int i = 0; i < that.m_points.size(); ++i) {
        m_points[i] = that.m_points[i];
    }
    m_is_closed = that.m_is_closed;
    return *this;
}

Vec2<float>& Path::operator[](unsigned int index) {
    if (index>=m_points.size()) {           // TODO EXCLUDE FROM RELEASE
        std::cout << "Error, tried to access an invalid index in Path: " << index << ", this path size is: " << m_points.size() <<  std::endl;
        exit(1);
    }
    return m_points[index];
}

Vec2<float> Path::operator[](unsigned int index) const {
    if (index>=m_points.size()) {
        std::cout << "Error, tried to access an invalid index in Path" << std::endl;
        exit(1);
    }
    return m_points[index];
}

Path::Path() {

}

Path::Path(const Path &that) {
    m_points.resize(that.m_points.size());
    for (int i = 0; i < that.m_points.size(); ++i) {
        m_points[i] = (that.m_points[i]);
    }
    m_is_closed = that.m_is_closed;
}
//endregion


void Path::append_point(sge::Vec2<float> new_point) {
    m_points.push_back(new_point);

}

unsigned int Path::get_size() const {
    return  m_points.size();
}

void Path::set_size(unsigned int size) {
    m_points.resize(size);
}

Vec2<float> &Path::get_relative(unsigned int base_index, int offset) {
    auto res_index = base_index + offset;
    if (0 <= res_index < m_points.size()) return m_points[res_index];
    else {
        if (is_closed()) {
            res_index = res_index % m_points.size();
            if (res_index>0) return m_points[res_index];
            else return m_points[m_points.size()+res_index];
        } else {
            std::cout<< "Tried to use an invalid offset in an open Path, got out of bounds!" << std::endl;
            exit(1);
        }
    }

}

void Path::print() {
    std::cout << "Path: ";
    for (int i = 0; i < m_points.size(); ++i) {
        std::cout << m_points[i].to_string();
    }
    std::cout << std::endl;
}

void Path::load_from_file(std::string path) {
    std::string line;
    std::ifstream myfile (path);
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            std::stringstream iss(line);
            float x,y;
            if (!(iss >> x >> y)) {
                break;
            }
            else {
                m_points.emplace_back(x,y);
            }
        }
        myfile.close();

        if (m_points[0]==m_points.back()) {
            m_points.pop_back();
            set_closed(true);
        }
    } else {
        std::cout << "Unable to open the file at the path: " << path << std::endl;
        exit(1);
    }
}

void Path::clear() {
    m_points.clear();
    m_is_closed = false;
}

unsigned int Path::get_closed_size() const {
    unsigned int size = get_size();
    if (this->is_closed()) size++;
    return size;
}
