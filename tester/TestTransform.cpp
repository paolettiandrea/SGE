//
// Created by andrea on 5/13/19.
//

#include "TestTransform.hpp"
#include <cmath>

TestTransform::TestTransform()
    : m_translation_matrix(3,3)
    , m_rotation_matrix(3,3)
    , m_scale_matrix(3,3)
    , m_local_transform_matrix(3,3) {

    // Every internal matrix set to identity
    m_translation_matrix.make_identity();
    m_rotation_matrix.make_identity();
    m_scale_matrix.make_identity();
    this->update_transform_matrix();
}

void TestTransform::set_translation(float x, float y) {
    m_translation_matrix[0][2] = x;
    m_translation_matrix[1][2] = y;
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


void TestTransform::update_transform_matrix() {
    Matrix2D<float> temp(3,3);
    temp.multiply(m_translation_matrix, m_rotation_matrix);
    m_local_transform_matrix.multiply(temp, m_scale_matrix);
    m_dirty_flag = false;
}

sge::Vec2<float> TestTransform::transform_point(sge::Vec2<float> point) {
    if (m_dirty_flag) update_transform_matrix();

    Matrix2D<float> point_matrix(3,1);
    point_matrix[0][0] = point.x;
    point_matrix[1][0] = point.y;
    point_matrix[2][0] = 1;

    Matrix2D<float> res(3,1);
    res.multiply(m_local_transform_matrix, point_matrix);
    return sge::Vec2(res[0][0], res[1][0]);
}




