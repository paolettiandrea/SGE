#include <fstream>
#include "SGE/components/graphics/VertArray.hpp"
#include "GameObject.hpp"
#include "Scene.hpp"

sge::cmp::VertArray::VertArray(const GameObject_H &_gameobject)
    : Component(_gameobject, "VertArray") {

    // Subscribing to the dirty_transform_event
    auto handle = get_handle();
    dirty_transform_handler = [=](){
        handle->is_dirty = true;
    };

    gameobject()->transform()->world_transform_changed_event+= dirty_transform_handler;
}

void sge::cmp::VertArray::append_local_point(const sge::Vec2<float>& new_local_point, sf::Color color) {
    m_local_points.push_back(new_local_point);
    auto new_world_point = gameobject()->transform()->local_to_world_point(new_local_point);
    m_vertex_array.append(sf::Vertex(sf::Vector2f(new_world_point.x, -new_world_point.y), color));
}

void sge::cmp::VertArray::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(m_vertex_array, states);
}

void sge::cmp::VertArray::destruction_callback() {
    IComponent::destruction_callback();
    if ( !gameobject()->get_scene()->is_doomed())
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

void sge::cmp::VertArray::clean_layer_index_if_dirty(std::map<std::string, unsigned int> &layer_map) {
    if (dirty_layer_index) {
        if (layer_id.empty()) {
            layer_index = 0;
            dirty_layer_index = false;
        } else {
            if (layer_map.count(layer_id) == 1) {
                layer_index = layer_map[layer_id];
                dirty_layer_index = false;
            } else {
                LOG_ERROR << "The layer id [" << layer_id << "] isn't valid";
            }
        }
    }
}

void sge::cmp::VertArray::set_layer(const std::string &layer_id) {
    this->layer_id = layer_id;
    dirty_layer_index = true;
}

const std::string& sge::cmp::VertArray::get_layer_id() {
    return layer_id;
}

const sf::VertexArray &sge::cmp::VertArray::get_vert_array() const {
    return m_vertex_array;
}

sf::PrimitiveType sge::cmp::VertArray::get_primitive_type() const {
    return m_vertex_array.getPrimitiveType();
}

void sge::cmp::VertArray::append_vertex_as_local(const sf::Vertex &local_vertex) {
    m_local_points.emplace_back(local_vertex.position.x, -local_vertex.position.y);
    auto new_world_point = gameobject()->transform()->local_to_world_point(m_local_points.back());
    m_vertex_array.append(sf::Vertex(sf::Vector2f(new_world_point.x, -new_world_point.y), local_vertex.color));
}

void sge::cmp::VertArray::append_vertex_as_world(const sf::Vertex &world_vertex) {
    m_local_points.push_back(gameobject()->transform()->world_to_local_point(
            sge::Vec2<float>(world_vertex.position.x, -world_vertex.position.y)));
    m_vertex_array.append(world_vertex);
}

void sge::cmp::VertArray::set_vertex_array(const sf::VertexArray &vertex_array) {
    m_vertex_array.clear();
    m_vertex_array.setPrimitiveType(vertex_array.getPrimitiveType());
    for (int i = 0; i < vertex_array.getVertexCount(); ++i) {
        m_vertex_array.append(vertex_array[i]);
    }
    is_dirty = true;
}

const std::vector<sge::Vec2<float>> &sge::cmp::VertArray::get_local_points() const {
    return m_local_points;
}

std::string sge::cmp::VertArray::get_debug_string() {
    auto s =  IComponent::get_debug_string();

    s += "Type: ";
    switch (m_vertex_array.getPrimitiveType()) {

        case sf::Points:
            s += "POINTS\n";
            break;
        case sf::Lines:
            s += "LINES\n";
            break;
        case sf::LineStrip:
            s += "LINESTRIP\n";
            break;
        case sf::Triangles:
            s += "TRIANGLES\n";
            break;
        case sf::TriangleStrip:
            s += "TRIANGLESTRIP\n";
            break;
        case sf::TriangleFan:
            s += "TRIANGLEFAN\n";
            break;
        case sf::Quads:
            s += "QUADS\n";
            break;
    }

    s += "Vert count: " + std::to_string(m_vertex_array.getVertexCount()) + "";

    return s;
}

float sge::cmp::VertArray::get_alpha() {
    auto found_alpha = m_vertex_array[0].color.a;
    for (int i = 0; i < m_vertex_array.getVertexCount(); ++i) {
        if (m_vertex_array[i].color.a != found_alpha) {
            LOG_ERROR << "The alpha of this VertArray isn't unifom";
        }
    }
    return found_alpha;
}

void sge::cmp::VertArray::set_alpha(float alpha) {
    for (int i = 0; i < m_vertex_array.getVertexCount(); ++i) {
        auto col = m_vertex_array[i].color;
        m_vertex_array[i].color = sf::Color(col.r, col.g, col.b, alpha);
    }
}

void sge::cmp::VertArray::clear() {
    m_vertex_array.clear();
    m_local_points.clear();
    is_dirty = true;
}




