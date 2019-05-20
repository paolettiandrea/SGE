//
// Created by andrea on 5/13/19.
//

#include "TestTransform.hpp"
#include <cmath>

TestTransform::TestTransform()
    : m_translation_vector(0.f,0.f)
    , m_rotation_matrix(2,2)
    , m_scale_matrix(2,2) {

    // Every internal matrix set to identity
    m_rotation_matrix.make_identity();
    m_scale_matrix.make_identity();
}

void TestTransform::set_translation(float x, float y) {
    m_translation_vector.x = x;
    m_translation_vector.y = y;
    m_dirty_flag = true;
}

void TestTransform::set_rotation(float rads) {
    float sin = std::sin(rads);
    float cos = std::cos(rads);
    m_rotation_matrix[0][0] = cos;
    m_rotation_matrix[1][1] = cos;
    m_rotation_matrix[0][1] = -sin;
    m_rotation_matrix[1][0] = sin;
    m_dirty_flag = true;
}

void TestTransform::set_scale(float scale_x, float scale_y) {
    m_scale_matrix[0][0] = scale_x;
    m_scale_matrix[1][1] = scale_y;
    m_dirty_flag = true;
}


sge::Vec2<float> TestTransform::transform_point(const sge::Vec2<float>& point) {
    // This seems to be world_to_local, probably for local_to_world we need the inverse
    Matrix2D<float> point_matrix(2,1);
    point_matrix[0][0] = point.x;
    point_matrix[1][0] = point.y;
    auto yo = m_rotation_matrix*(m_scale_matrix*point_matrix);
    return sge::Vec2<float>(yo[0][0]+m_translation_vector.x, yo[1][0]+m_translation_vector.y);
}




