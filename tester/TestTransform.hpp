//
// Created by andrea on 5/13/19.
//

#ifndef FACTORY_EXPERIMENTS_TESTTRANSFORM_HPP
#define FACTORY_EXPERIMENTS_TESTTRANSFORM_HPP

#include "SGE/utils/Matrix2D.hpp"
#include <vector>
#include "SGE/Vec2.hpp"
#include "SGE/utils/handles/Handle.hpp"
/*!
\file
\brief ${BRIEF_FILE_DESCRIPTION}
*/

class TestTransform {
public:
    TestTransform();

    void set_translation(float x, float y);
    void set_rotation(float rads);
    void set_scale(float scale_x, float scale_y);

    sge::Vec2<float> transform_point(const sge::Vec2<float>& point);


private:

    sge::Vec2<float> m_translation_vector;
    Matrix2D<float> m_rotation_matrix;
    Matrix2D<float> m_scale_matrix;


    utils::Handle<TestTransform> parent;
    std::vector<utils::Handle<TestTransform>> children;

    /*!
     * \brief Signals that the m_transform_matrix needs an update (because some underlying matrix has been changed)
     */
    bool m_dirty_flag = true;
};


#endif //FACTORY_EXPERIMENTS_TESTTRANSFORM_HPP
