//FIXME still some problems when the angle is really close to 0

#define PATH_RENDERER_MIN_FALLBACK_ANGLE 0.0001

#include "PathRenderer.hpp"
#include "GameObject.hpp"
#include "SGE/Scene.hpp"
#include "SGE/debug/PointDebugShape.hpp"

using sge::cmp::PathRenderer;
using sge::Vec2;


PathRenderer::PathRenderer(const utils::Handle<sge::GameObject> &_gameobject)
        : Component(_gameobject, "PathRenderer") {

    m_vert_array.setPrimitiveType(sf::PrimitiveType::TrianglesStrip);
    utils::Handle<PathRenderer> handle = get_handle();
    transform_changed_evhandler = [=]{
        for (int i = 0; i < handle->m_dirty_vertarray_chunk_flags.size(); ++i) {
            handle->m_dirty_world_flags[i] = true;
        }
    };

    gameobject()->transform()->transform_changed_event += transform_changed_evhandler;
}

void PathRenderer::elaborate_inner_point(Vec2<float> target_point, Vec2<float> prev_point, Vec2<float> next_point,
                                                sf::Vertex vert_chunck[]) {
    float inner_tick_away_ratio = 0.5;

    auto forward_dir = next_point - target_point;
    auto backward_dir = prev_point - target_point;

    auto min_dist = std::min(forward_dir.get_magnitude(), backward_dir.get_magnitude());

    forward_dir.normalize();        // Necessary?
    backward_dir.normalize();

    float angle = Vec2<float>::get_signed_angle(forward_dir,backward_dir);

    // Prev
    Vec2<float> backward_outer_perpendicular = backward_dir.normalize();
    if (angle>0) backward_outer_perpendicular = Vec2<float>::rotate(backward_outer_perpendicular,M_PI/2);
    else backward_outer_perpendicular = Vec2<float>::rotate(backward_outer_perpendicular,-M_PI/2);
    backward_outer_perpendicular.set_magnitude(m_thickness/2);

    auto outer_prev_point_a = target_point + backward_outer_perpendicular;
    auto outer_prev_point_b = prev_point + backward_outer_perpendicular;
    auto inner_prev_point_a = target_point - backward_outer_perpendicular;
    auto inner_prev_point_b = prev_point - backward_outer_perpendicular;

    // Next
    Vec2<float> forward_outer_perpendicular = forward_dir.normalize();
    if (angle<0) forward_outer_perpendicular = Vec2<float>::rotate(forward_outer_perpendicular,M_PI/2);
    else forward_outer_perpendicular = Vec2<float>::rotate(forward_outer_perpendicular,-M_PI/2);
    forward_outer_perpendicular.set_magnitude(m_thickness/2);

    auto outer_next_point_a = target_point + forward_outer_perpendicular;
    auto outer_next_point_b = next_point + forward_outer_perpendicular;
    auto inner_next_point_a = target_point - forward_outer_perpendicular;
    auto inner_next_point_b = next_point - forward_outer_perpendicular;


    //Vec2<float> outer_intersection;
    //Vec2<float>::intersection(outer_prev_point_a, outer_prev_point_b, outer_next_point_a, outer_next_point_b,
                              //outer_intersection);



    // Outer
    Vec2<float> bisettrice = forward_dir+backward_dir;
    float angle_ratio = fabsf((float)(angle/M_PI));
    bisettrice.set_magnitude(m_thickness/2*angle_ratio);
    auto outer_truncator_a = target_point - bisettrice;
    auto outer_truncator_b = outer_truncator_a + Vec2<float>::rotate(bisettrice, M_PI/2);

    bool failed_intersection_flag = false;
    Vec2<float> outer_prev_intersection, outer_next_intersection;
    if (!Vec2<float>::intersection(outer_truncator_a, outer_truncator_b, outer_prev_point_a, outer_prev_point_b, outer_prev_intersection)) failed_intersection_flag=true;
    if (!Vec2<float>::intersection(outer_truncator_a, outer_truncator_b, outer_next_point_a, outer_next_point_b, outer_next_intersection)) failed_intersection_flag = true;


    if (failed_intersection_flag) {
        outer_prev_intersection = target_point;
        outer_next_intersection = target_point;
    }


    // Inner
    Vec2<float> inner_intersection;
    if (!Vec2<float>::intersection(inner_prev_point_a, inner_prev_point_b, inner_next_point_a, inner_next_point_b,
                              inner_intersection)) failed_intersection_flag=true;

    Vec2<float> inner_next_intersection, inner_prev_intersection;

    if (failed_intersection_flag || fabsf(angle)<PATH_RENDERER_MIN_FALLBACK_ANGLE || (inner_intersection-target_point).get_magnitude()>min_dist) {
        // If the intersection is going to infinity just clamp it to a close enough point
        auto prev_dist = (target_point - prev_point).get_magnitude();
        auto next_dist = (target_point - next_point).get_magnitude();
        Vec2<float> point;
        if (prev_dist<next_dist) {
            forward_outer_perpendicular.set_magnitude(m_thickness/2);
            forward_dir.set_magnitude(prev_dist);
            point = target_point + forward_dir -forward_outer_perpendicular;
        } else {
            backward_outer_perpendicular.set_magnitude(m_thickness/2);
            backward_dir.set_magnitude(next_dist);
            point = target_point + backward_dir -backward_outer_perpendicular;
        }
        inner_next_intersection = point;
        inner_prev_intersection = point;

    } else {
        // The inner intersection is in normal bounds (the angle is large enough relative to the thickness)
        bisettrice.set_magnitude((m_thickness*inner_tick_away_ratio) * (1-fabsf(angle/m_inner_rounding_max_angle)));
        auto inner_truncator_a = inner_intersection + bisettrice;
        auto inner_truncator_b = inner_truncator_a + Vec2<float>::rotate(bisettrice, M_PI/2);
        if (fabsf(angle)<m_inner_rounding_max_angle) {
            Vec2<float>::intersection(inner_truncator_a, inner_truncator_b, inner_next_point_a, inner_next_point_b, inner_next_intersection);
            Vec2<float>::intersection(inner_truncator_a, inner_truncator_b, inner_prev_point_a, inner_prev_point_b, inner_prev_intersection);
        } else {
            inner_next_intersection = inner_intersection;
            inner_prev_intersection = inner_intersection;
        }
    }


    //gameobject()->get_scene()->env()->debug_draw(new debug::PointDebugShape(outer_prev_intersection.x, outer_prev_intersection.y,0,"outer prev inters"));
    //gameobject()->get_scene()->env()->debug_draw(new debug::PointDebugShape(outer_next_intersection.x, outer_next_intersection.y,0,"outer next inters"));

    if (angle<0) {
        vert_chunck[0].position = sf::Vector2f(outer_prev_intersection.x, -outer_prev_intersection.y);
        vert_chunck[1].position = sf::Vector2f(inner_prev_intersection.x, -inner_prev_intersection.y);
        vert_chunck[2].position = sf::Vector2f(outer_next_intersection.x, -outer_next_intersection.y);
        vert_chunck[3].position = sf::Vector2f(inner_next_intersection.x, -inner_next_intersection.y);
    } else {
        vert_chunck[0].position = sf::Vector2f(inner_prev_intersection.x, -inner_prev_intersection.y);
        vert_chunck[1].position = sf::Vector2f(outer_prev_intersection.x, -outer_prev_intersection.y);
        vert_chunck[2].position = sf::Vector2f(inner_next_intersection.x, -inner_next_intersection.y);
        vert_chunck[3].position = sf::Vector2f(outer_next_intersection.x, -outer_next_intersection.y);
    }
}

void PathRenderer::elaborate_extremes() {
    if (is_closed()) {
        unsigned int last_index = m_world_path.get_size()-1;
        unsigned int vert_chunk_index = (last_index-1)*4+2;
        elaborate_inner_point(m_world_path[last_index], m_world_path[last_index-1], m_world_path[0], &m_vert_array[vert_chunk_index]);
        elaborate_inner_point(m_world_path[0], m_world_path[last_index], m_world_path[1], &m_vert_array[vert_chunk_index+4]);
        m_vert_array[0].position = m_vert_array[m_vert_array.getVertexCount()-2].position;
        m_vert_array[1].position = m_vert_array[m_vert_array.getVertexCount()-1].position;
    } else {
        auto initial_dir = m_world_path[1] - m_world_path[0];
        initial_dir.set_magnitude(m_thickness/2);
        auto point1 = m_world_path[0] + Vec2<float>::rotate(initial_dir, M_PI/2);
        auto point2 = m_world_path[0] - Vec2<float>::rotate(initial_dir, M_PI/2);

        m_vert_array[0].position = sf::Vector2f(point1.x,-point1.y);
        m_vert_array[1].position = sf::Vector2f(point2.x,-point2.y);

        auto final_dir = m_world_path[m_world_path.get_size()-1] - m_world_path[m_world_path.get_size()-2];
        final_dir.set_magnitude(m_thickness/2);
        auto point4 = m_world_path[m_world_path.get_size()-1] + Vec2<float>::rotate(final_dir, M_PI/2);
        auto point3 = m_world_path[m_world_path.get_size()-1] - Vec2<float>::rotate(final_dir, M_PI/2);

        auto vert_array_last_index = m_vert_array.getVertexCount()-1;
        m_vert_array[vert_array_last_index].position = sf::Vector2f(point3.x,-point3.y);
        m_vert_array[vert_array_last_index-1].position = sf::Vector2f(point4.x,-point4.y);
    }
}

void PathRenderer::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(m_vert_array, states);

    /*
    sf::VertexArray yo;
    yo.setPrimitiveType(sf::PrimitiveType::LineStrip);
    sf::Color col = sf::Color::Green;
    for (int i = 0; i < m_vert_array.getVertexCount(); ++i) {

        col.g -= 30;
        col.b -= 30;
        yo.append(m_vert_array[i]);
        yo[i].color = col;
    }
    target.draw(yo, states);
     */



}

void PathRenderer::set_path(const Path &new_path) {
    m_local_path = new_path;
    unsigned int new_path_size = new_path.get_size();

    m_world_path.set_size(new_path_size);

    m_world_path.set_closed(m_local_path.is_closed());
    m_dirty_world_flags.resize(new_path_size);
    m_dirty_vertarray_chunk_flags.resize(new_path_size);

    for (int i = 0; i < m_dirty_world_flags.size(); ++i) {
        m_dirty_world_flags[i] = true;
        m_dirty_vertarray_chunk_flags[i] = true;
    }
        // The size of the vertarray used to represent the path obviously depends on is_closed
    if (m_world_path.is_closed()) m_vert_array.resize(new_path_size*4+2);
    else m_vert_array.resize((new_path_size-1)*4);

    set_color_all(base_color);
}

void PathRenderer::clean_pass() {

    if (m_local_path.get_size()<3) {
        LOG_WARNING << "Path with less than three points";
        return;
    }

    // First of all clean the world_path
    for (int i = 0; i < m_world_path.get_size(); ++i) {
        if (m_dirty_world_flags[i]==true) {
            m_world_path[i] = gameobject()->transform()->local_to_world_point(m_local_path[i]);
            m_dirty_world_flags[i] = false;
            m_dirty_vertarray_chunk_flags[i] = true;
            if (i>0) m_dirty_vertarray_chunk_flags[i-1] = true;
            if (i<m_world_path.get_size()-1) m_dirty_vertarray_chunk_flags[i+1] = true;
        }
    }

    // TODO EXCLUDE NOT DIRTY

    // Then clean the inner parts of the VertexArray (so starting from index 1)
    for (int j = 1; j < m_world_path.get_size()-1; ++j) {
        if (m_dirty_vertarray_chunk_flags[j]) {
            unsigned int vert_chunk_index = (j-1)*4+2;
            elaborate_inner_point(m_world_path[j], m_world_path[j-1], m_world_path[j+1], &m_vert_array[vert_chunk_index]);
            m_dirty_vertarray_chunk_flags[j] = false;
        }
    }

    elaborate_extremes();

}

void PathRenderer::set_color_all(sf::Color color) {
    for (int i = 0; i < m_vert_array.getVertexCount(); ++i) {
        m_vert_array[i].color = color;
    }
    base_color = color;
}

void PathRenderer::set_point(unsigned int index, sge::Vec2<float> new_point) {
    if (new_point!=m_local_path[index]) {
        m_local_path[index] = new_point;
        m_dirty_world_flags[index] = true;

        m_dirty_vertarray_chunk_flags[index] = true;
        if (index>0) m_dirty_vertarray_chunk_flags[index-1] = true;
        if (index<m_dirty_vertarray_chunk_flags.size()-1) m_dirty_vertarray_chunk_flags[index+1] = true;
    }
}


void sge::cmp::PathRenderer::destruction_callback() {
    IComponent::destruction_callback();
    if ( !gameobject()->get_scene()->env()->is_shutting_down())
        gameobject()->transform()->transform_changed_event -= transform_changed_evhandler;
}

void sge::cmp::PathRenderer::set_closed(bool closed) {
    if (closed!=m_local_path.is_closed()) {
        if (closed) {
            m_vert_array.resize(m_local_path.get_size()*4+2);
        } else {
            m_vert_array.resize((m_local_path.get_size()-1)*4);
        }
        m_dirty_vertarray_chunk_flags[0] = true;
        m_dirty_vertarray_chunk_flags[m_local_path.get_size()-1] = true;
        m_local_path.set_closed(closed);
    }
}

void sge::cmp::PathRenderer::set_path_as_circle(float radius, unsigned int segments_number) {
    Path path;
    float angle = 2*M_PI/segments_number;
    for (int i = 0; i < segments_number; ++i) {
        path.append_point(Vec2<float>(cosf(i*angle), sinf(i*angle)));
    }
    path.set_closed(true);
    set_path(path);
}










/*

 void PathRenderer::append_point(const Vec2<float>& new_point) {
    // Append all the relevant data
    m_path_local_points.push_back(new_point);
    m_path_world_points.emplace_back(0,0);

    unsigned int new_vert_point_number;
    if (m_path_local_points.size()<=2)  new_vert_point_number = 2;
    else new_vert_point_number = PATH_INTERNAL_INDEX_FACTOR;
    for (int i = 0; i < new_vert_point_number; ++i) {
        m_path_vertex_array.append(sf::Vertex(sf::Vector2f(0,0)));
    }

    // Set this point and the one before as dirty
    m_dirty_points.push_back(true);
    if (m_dirty_points.size()>1) m_dirty_points[m_dirty_points.size()-2] = true;
}

void sge::cmp::PathRenderer::clean_point_by_index(unsigned int target_point_index) {
    update_world_position_at_index(target_point_index);

    // Targeted first point of the path
    if (target_point_index==0) {
        update_world_position_at_index(1);
        auto direction = m_path_world_points[1] - m_path_world_points[0];
        direction.set_magnitude(m_thickness/2);
        const Vec2<float>& rotated_vector = Vec2<float>::rotate(direction, M_PI / 2);
        auto temp_point = m_path_world_points[0] + rotated_vector;
        m_path_vertex_array[0] = sf::Vector2f(temp_point.x, -temp_point.y);
        temp_point = m_path_world_points[0] - rotated_vector;
        m_path_vertex_array[1] = sf::Vector2f(temp_point.x, -temp_point.y);
        m_dirty_points[0] = false;

        // Targeted last point of the path
    } else if (target_point_index==m_path_local_points.size()-1) {
        update_world_position_at_index(target_point_index-1);
        auto direction = m_path_world_points[m_path_local_points.size()-1] - m_path_world_points[m_path_local_points.size()-2];
        direction.set_magnitude(thickness/2);
        auto temp_point = m_path_world_points[m_path_world_points.size()-1] + Vec2<float>::rotate(direction, M_PI/2);
        m_path_vertex_array[m_path_vertex_array.getVertexCount()-2] = sf::Vector2f(temp_point.x, -temp_point.y);
        temp_point = m_path_world_points[m_path_local_points.size()-1] - Vec2<float>::rotate(direction, M_PI/2);
        m_path_vertex_array[m_path_vertex_array.getVertexCount()-1] = sf::Vector2f(temp_point.x, -temp_point.y);
        m_dirty_points[m_path_local_points.size()-1] = false;

        // Targeted a middle point of the path
    } else {
        update_world_position_at_index(target_point_index-1);
        update_world_position_at_index(target_point_index+1);

        auto forward_dir = m_path_world_points[target_point_index+1] - m_path_world_points[target_point_index];
        auto backward_dir = m_path_world_points[target_point_index-1] - m_path_world_points[target_point_index];

        forward_dir.set_magnitude(1.0);
        backward_dir.set_magnitude(1.0);

        auto bisettrice = forward_dir + backward_dir;
        auto angle = atan2f(forward_dir.x*backward_dir.y-forward_dir.y*backward_dir.x,forward_dir.x*backward_dir.x+forward_dir.y*backward_dir.y);
        auto angle_ratio = fabs(angle) / M_PI;


        auto antibisettrice = sge::Vec2(-bisettrice.x, -bisettrice.y);
        std::cout <<" Antibisettrice: " << antibisettrice.to_string() << std::endl;
        float outer_thickness = thickness/2*angle_ratio;
        antibisettrice.set_magnitude(outer_thickness);
        auto middle_point = m_path_world_points[target_point_index] + antibisettrice;


        auto yo = Vec2<float>::rotate(antibisettrice, M_PI/2);
        yo.set_magnitude(thickness/2 + (1-angle_ratio));

        auto res1 = middle_point + yo;
        auto res2 = middle_point - yo;

        sf::Vector2f outer_point1 (res1.x,-res1.y);
        sf::Vector2f outer_point2 (res2.x,-res2.y);




        bisettrice.set_magnitude(thickness/2);
        middle_point = m_path_world_points[target_point_index] + bisettrice;



        // Previous
        Vec2<float> side_perp (0,0);
        if (angle>0) side_perp = Vec2<float>::rotate(backward_dir, -M_PI/2);
        else side_perp = Vec2<float>::rotate(backward_dir, M_PI/2);
        side_perp.set_magnitude(thickness/2);
        auto next_a = m_path_world_points[target_point_index-1] + side_perp;
        auto prev_b = m_path_world_points[target_point_index] + side_perp;

        // Next
        if (angle>0) side_perp = Vec2<float>::rotate(forward_dir, M_PI/2);
        else side_perp = Vec2<float>::rotate(forward_dir, -M_PI/2);
        side_perp.set_magnitude(thickness/2); //probably not necessary
        auto next_a = m_path_world_points[target_point_index] + side_perp;
        auto next_b = m_path_world_points[target_point_index+1] + side_perp;


        /////////////////////////////////////////
        sf::Vector2f inner_point1;
        sf::Vector2f inner_point2;
        Vec2<float> inner_borders_intersection(0,0);
        if (!Vec2<float>::intersection(next_a,next_b, prev_a,prev_b, inner_borders_intersection)) {
            bisettrice.set_magnitude(thickness/2);
            sge::Vec2<float> unique_pt = m_path_world_points[target_point_index] + bisettrice;
            inner_point1.x =unique_pt.x; inner_point1.y = -unique_pt.y;
            inner_point2.x = unique_pt.x; inner_point2.y = -unique_pt.y;
        } else {
            float max_angle = M_PI - M_PI/10;
            float max_rounder_additional_thickness = 10;

            if (fabsf(angle)<max_angle) {
                forward_dir.set_magnitude(max_rounder_additional_thickness*(fabsf(1/(angle)/max_angle)));
                backward_dir.set_magnitude(max_rounder_additional_thickness*(fabsf(1/(angle)/max_angle)));
                auto offset2 = inner_borders_intersection + forward_dir;
                auto offset1 = inner_borders_intersection + backward_dir;
                inner_point1.x =offset1.x; inner_point1.y = -offset1.y;
                inner_point2.x = offset2.x; inner_point2.y = -offset2.y;

                //if ((offset1 - inner_borders_intersection).get_magnitude() > ;


            } else {
                inner_point1.x =inner_borders_intersection.x; inner_point1.y = -inner_borders_intersection.y;
                inner_point2.x = inner_borders_intersection.x; inner_point2.y = -inner_borders_intersection.y;
            }

        }



        std::cout << angle << std::endl;
        unsigned int anchor_vertarray_index = (target_point_index-1)*PATH_INTERNAL_INDEX_FACTOR+2;
        if (angle<0) {
            m_path_vertex_array[anchor_vertarray_index] = outer_point1;
            m_path_vertex_array[anchor_vertarray_index+1] = inner_point1;
            m_path_vertex_array[anchor_vertarray_index+2] = outer_point2;
            m_path_vertex_array[anchor_vertarray_index+3] = inner_point2;

        } else {
            m_path_vertex_array[anchor_vertarray_index] = inner_point1;
            m_path_vertex_array[anchor_vertarray_index+1] = outer_point2;
            m_path_vertex_array[anchor_vertarray_index+2] = inner_point2;
            m_path_vertex_array[anchor_vertarray_index+3] = outer_point1;
        }

        m_dirty_points[target_point_index] = false;
    }
}

void sge::cmp::PathRenderer::set_thickness(float new_thickness) {
    thickness = new_thickness;
    for (int i = 0; i < m_path_local_points.size(); ++i) {
        m_dirty_points[i] = true;
    }
}

void sge::cmp::PathRenderer::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(m_path_vertex_array, states);

}

void sge::cmp::PathRenderer::set_color_all(sf::Color color) {
    for (int i = 0; i < m_path_vertex_array.getVertexCount(); ++i) {
        m_path_vertex_array[i].color = color;
    }
}

void sge::cmp::PathRenderer::clean_pass() {
    for (int i = 0; i < m_dirty_points.size(); ++i) {
        if (m_dirty_points[i]==true) {
            clean_point_by_index(i);
        }
    }
}

void sge::cmp::PathRenderer::update_world_position_at_index(unsigned int index) {
    if (m_dirty_points[index])
        m_path_world_points[index] = gameobject()->transform()->local_to_world_point(m_path_local_points[index]);
}

void sge::cmp::PathRenderer::set_point(unsigned int index, const sge::Vec2<float>& new_val) {
    m_path_local_points[index] = new_val;
    m_dirty_points[index] = true;
    if (index!=0) m_dirty_points[index-1] = true;
    if (index<m_dirty_points.size()-1) m_dirty_points[index+1] = true;
}


 */
