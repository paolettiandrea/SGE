#include <fstream>
#include "SGE/components/graphics/VertArray.hpp"
#include "GameObject.hpp"
#include "Scene.hpp"

sge::cmp::VertArray::VertArray(const utils::Handle<sge::GameObject> &_gameobject)
    : Component(_gameobject, "VertArray") {

    // Subscribing to the dirty_transform_event
    dirty_transform_handler = [&](){
        this->is_dirty = true;
    };

    gameobject()->transform()->world_transform_changed_event+= dirty_transform_handler;
}

void sge::cmp::VertArray::append_local_point(const sge::Vec2<float>& new_local_point) {
    m_local_points.push_back(new_local_point);
    auto new_world_point = Vec2<float>(0,0);
    m_vertex_array.append(sf::Vertex(sf::Vector2f(new_world_point.x, new_world_point.y)));
    is_dirty = true;
}

void sge::cmp::VertArray::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(m_vertex_array, states);
}

void sge::cmp::VertArray::destruction_callback() {
    IComponent::destruction_callback();
    if ( !gameobject()->get_scene()->env()->is_shutting_down())
        gameobject()->transform()->world_transform_changed_event -= dirty_transform_handler;
}

void sge::cmp::VertArray::clean_if_dirty() {
    if (is_dirty) {
        for (int i = 0; i < m_local_points.size(); ++i) {
            auto res_vec = gameobject()->transform()->local_to_world_point(m_local_points[i]);
            m_vertex_array[i].position = sf::Vector2f(res_vec.x, -res_vec.y);       // sge to sfml y-conversion
        }
        is_dirty = false;
    }
}

void sge::cmp::VertArray::set_primitive(sf::PrimitiveType primitive_type) {
    m_vertex_array.setPrimitiveType(primitive_type);
}

void sge::cmp::VertArray::set_color(sf::Color color) {
    for (int i = 0; i < m_vertex_array.getVertexCount(); ++i) {
        m_vertex_array[i].color = color;
    }
}

void sge::cmp::VertArray::import_smesh(const std::string &filename) {
    std::string line;
    std::ifstream mesh_file (filename);
    if (mesh_file.is_open())
    {
        m_vertex_array.clear();
        set_primitive(sf::PrimitiveType::Triangles);

        bool empty_line_encounter = false;
        std::vector<sge::Vec2<float>> temp_vertices;
        while ( getline (mesh_file, line) )
        {
            if (!empty_line_encounter){
                // Phase 1: for every line two float values expected (x,y), build the vertex vector
                std::stringstream iss(line);
                float x,y;
                if (!(iss >> x >> y)) {
                    empty_line_encounter = true;
                }
                else {
                    temp_vertices.emplace_back(x,y);
                }

            } else {
                // Phase 2: for every line 3 int values are expected, the indices for the built vertex vector
                std::stringstream iss(line);
                int a,b,c;
                if (!(iss >> a >> b >> c)) {
                    break;
                }
                else {
                    append_local_point(temp_vertices[a]);
                    append_local_point(temp_vertices[b]);
                    append_local_point(temp_vertices[c]);

                }
            }
        }
        mesh_file.close();
    }
    else {
        LOG_ERROR << "Unable to open the file during smesh import [" + filename + "]";
    }
}

void sge::cmp::VertArray::set_vertex_position(unsigned int index, float x, float y) {
    if (m_vertex_array.getVertexCount()>index) {
        m_local_points[index] = sge::Vec2<float>(x,y);
        is_dirty = true;
    } else {
        LOG_ERROR << "Index given in set_vertex_position [" << index << "] is out of bounds";
    }
}

void sge::cmp::VertArray::set_vertex_color(unsigned int index, sf::Color color) {
    if (m_vertex_array.getVertexCount()>index) {
        m_vertex_array[index].color = color;
    } else {
        LOG_ERROR << "Index given in set_vertex_position [" << index << "] is out of bounds";
    }
}



