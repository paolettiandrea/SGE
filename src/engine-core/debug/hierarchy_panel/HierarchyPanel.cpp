#include <SGE/SceneConstructionData.hpp>
#include <SGE/components/graphics/VertArray.hpp>
#include <SGE/components/physics/Rigidbody.hpp>
#include <SGE/components/physics/Collider.hpp>
#include <SGE/components/graphics/ui/UI.hpp>
#include "HierarchyPanel.hpp"
#include "SGE/logic/Logic.hpp"


void sge::core::debug::HierarchyPanel::reset() {
    focused_object = get_root_transforms(m_scene_transform_vector)[0];
}

void sge::core::debug::HierarchyPanel::update_state(std::vector<Transform_H> scene_transform_vector, std::vector<cd::SceneConstructionData>& scene_cds) {

    m_scene_transform_vector.clear();
    for (int i = 0; i < scene_transform_vector.size(); ++i) {
        m_scene_transform_vector.emplace_back(scene_transform_vector[i]);
    }

    // Check if the pointed object is still valid
    if (!focused_object.is_valid() || focused_object->gameobject()->get_scene() != scene_transform_vector[0]->gameobject()->get_scene()) {
        reset();
    }
    this->scene_cds = &scene_cds;
}


std::vector<Transform_H> sge::core::debug::HierarchyPanel::get_root_transforms(
        std::vector<Transform_H> transform_vector) {

    std::vector<Transform_H> vec;
    for (auto transform : transform_vector) {
        if (transform->get_parent().is_null()) vec.emplace_back(transform);
    }
    return vec;
}

void sge::core::debug::HierarchyPanel::draw(sf::RenderTarget &target, sf::RenderStates states) const {

    int vertical_anchor = SGE_DEBUG_HIERARCHY_TOP_PADDING;
    int hotizontal_anchor = SGE_DEBUG_HIERARCHY_LEFT_PADDING;

    for (int k = 0; k < scene_cds->size(); ++k) {
        sf::Color fill;
        if (k == scene_cds->size()-1) fill = SGE_DEBUG_SCENE_STACK_ACTIVE_COLOR;
        else fill = SGE_DEBUG_SCENE_STACK_INACTIVE_COLOR;
        auto scene_text = make_text((*scene_cds)[k].name, SGE_DEBUG_SCENE_STACK_CHAR_SIZE, fill);
        scene_text.setPosition(hotizontal_anchor, vertical_anchor);
        target.draw(scene_text, states);
        vertical_anchor += SGE_DEBUG_SCENE_STACK_CHAR_SIZE + SGE_DEBUG_HIERARCHY_SCENE_PADDING;

    }

    vertical_anchor += SGE_DEBUG_HIERARCHY_SCENE_STACK_TRAILING_SPACE;

    // Draw UPSTREAM HIERARCHY from root of the top scene to pointed object
    auto temp_point = focused_object;
    std::vector<Transform_H> parents;
    while (!temp_point->is_root()) {
        parents.emplace_back(temp_point->get_parent());
        temp_point = temp_point->get_parent();
    }

    for (int i = parents.size()-1; i >= 0; --i) {
        auto text = make_text(parents[i]->gameobject()->get_log_id(), SGE_DEBUG_SCENE_POINTED_CHAR_SIZE, SGE_DEBUG_HIERARCHY_UPSTREAM_COLOR);
        text.setPosition(hotizontal_anchor, vertical_anchor);
        target.draw(text, states);

        vertical_anchor += SGE_DEBUG_SCENE_POINTED_CHAR_SIZE;
        hotizontal_anchor += SGE_DEBUG_HIERARCHY_CHILD_INDENT;
    }

    // Draw the pointed object name
    draw_sibling(target, states, focused_object, &vertical_anchor, hotizontal_anchor, 0, SGE_DEBUG_HIERARCHY_FOCUSED_COLOR);
    vertical_anchor += SGE_DEBUG_HIERARCHY_SIBLINGS_PADDING;

    // Create a vector of the Transforms on the pointed level (pointed included, keeping track of its index)

    auto siblings = get_siblings(m_scene_transform_vector, focused_object);
    int pointed_index = -1;
    for (int i = 0; i < siblings.size(); ++i) {
        if (siblings[i] == focused_object) {
            pointed_index = i;
            break;
        }
    }

    if (pointed_index==-1) {
        std::cerr << "Couldn't find the focused object in the sibling vector" << std::endl;
        exit(1);
    }



    // Draw the siblings of the pointed object (from the one after the pointed to end, and from beginning to one before)
    for (int j = pointed_index+1; j < siblings.size(); ++j) {
        if (vertical_anchor < SGE_DEBUG_HIERARCHY_MAX_VERTICAL_ANCHOR) {
            draw_sibling(target, states, siblings[j], &vertical_anchor, hotizontal_anchor, 0, SGE_DEBUG_HIERARCHY_NOT_FOCUSED_COLOR);
            vertical_anchor += SGE_DEBUG_HIERARCHY_SIBLINGS_PADDING;
        }
    }
    for (int j = 0; j < pointed_index; ++j) {
        if (vertical_anchor < SGE_DEBUG_HIERARCHY_MAX_VERTICAL_ANCHOR) {
            draw_sibling(target, states, siblings[j], &vertical_anchor, hotizontal_anchor, 0, SGE_DEBUG_HIERARCHY_NOT_FOCUSED_COLOR);
            vertical_anchor += SGE_DEBUG_HIERARCHY_SIBLINGS_PADDING;
        }
    }
}





sf::Text sge::core::debug::HierarchyPanel::make_text(const std::string &string, unsigned int char_size, sf::Color fill_color) const {
    sf::Text text;
    text.setFont(*font);
    text.setString(string);
    text.setCharacterSize(char_size);
    text.setFillColor(fill_color);
    return text;
}

void sge::core::debug::HierarchyPanel::initialize(sge::core::FontManager &font_manager) {
    font = font_manager.get_font(SGE_DEBUG_HIERARCHY_FONT);
    italic_font = font_manager.get_font(SGE_DEBUG_HIERARCHY_ITALIC_FONT);
}

void sge::core::debug::HierarchyPanel::draw_sibling(sf::RenderTarget &target, sf::RenderStates states, Transform_H transform, int *vertical_anchor,
                                                    int horizontal_anchor, int level, sf::Color fill) const {
    int char_size;
    auto obj_log_id = transform->gameobject()->get_log_id();
    std::string s = obj_log_id.substr(1, obj_log_id.size()-2);
    if (level == 0) {
        char_size = SGE_DEBUG_SCENE_POINTED_CHAR_SIZE;
    }
    else {
        char_size = SGE_DEBUG_HIERARCHY_CHILD_CHAR_SIZE;
    }

    auto text = make_text(s, char_size, fill);
    text.setPosition(horizontal_anchor, *vertical_anchor);
    target.draw(text, states);

    *vertical_anchor += char_size + SGE_DEBUG_HIERARCHY_CHILD_PADDING;

    switch (display_mode) {

        case HIERARCHY:
            for (auto child : transform->get_children()) {
                draw_sibling(target, states, child, vertical_anchor, horizontal_anchor + SGE_DEBUG_HIERARCHY_CHILD_INDENT, level+1, fill);
            }
            break;
        case COMPONENT: {

            horizontal_anchor += 20;

            draw_component(target, states, "Transform",
                           transform->gameobject()->get_component<sge::cmp::Transform>("Transform").get_pointer(),
                           vertical_anchor, horizontal_anchor, fill);

            *vertical_anchor += SGE_DEBUG_COMPONENT_PADDING;

            draw_component(target, states, "LogicHub",
                           transform->gameobject()->get_component<sge::cmp::LogicHub>("LogicHub").get_pointer(),
                           vertical_anchor, horizontal_anchor, fill);

            *vertical_anchor += SGE_DEBUG_COMPONENT_PADDING;

            auto vert_array = transform->gameobject()->get_component<sge::cmp::VertArray>("VertArray");
            if (vert_array.is_valid()) {
                draw_component(target, states, "VertArray", vert_array.get_pointer(),
                               vertical_anchor, horizontal_anchor, fill);
                *vertical_anchor += SGE_DEBUG_COMPONENT_PADDING;
            }

            auto rigidbody = transform->gameobject()->get_component<sge::cmp::Rigidbody>("Rigidbody");
            if (rigidbody.is_valid()) {
                draw_component(target, states, "Rigidbody", rigidbody.get_pointer(),
                               vertical_anchor, horizontal_anchor, fill);
                *vertical_anchor += SGE_DEBUG_COMPONENT_PADDING;
            }

            auto collider = transform->gameobject()->get_component<sge::cmp::Collider>("Collider");
            if (collider.is_valid()) {
                draw_component(target, states, "Collider", collider.get_pointer(),
                               vertical_anchor, horizontal_anchor, fill);
                *vertical_anchor += SGE_DEBUG_COMPONENT_PADDING;
            }

            auto ui = transform->gameobject()->get_component<sge::cmp::UI>("UI");
            if (ui.is_valid()) {
                draw_component(target, states, "UI", ui.get_pointer(),
                               vertical_anchor, horizontal_anchor, fill);
                *vertical_anchor += SGE_DEBUG_COMPONENT_PADDING;
            }

            break;
        }
        case LOGIC:
            horizontal_anchor += SGE_DEBUG_HIERARCHY_CHILD_INDENT;
            auto logichub = transform->gameobject()->logichub();
            for (auto logic : logichub->get_attached_logic_list()) {
                auto name_text = make_text(logic->get_logic_id(), SGE_DEBUG_LOGIC_HEADER_CHAR_SIZE, fill);
                name_text.setFont(*italic_font);
                name_text.setPosition(horizontal_anchor, *vertical_anchor);
                target.draw(name_text, states);
                *vertical_anchor += SGE_DEBUG_LOGIC_HEADER_CHAR_SIZE;

                auto s = logic->debug_string();
                if (s.empty()) s = "No debug info.";

                auto logic_text = make_text(s, SGE_DEBUG_LOGIC_INFO_CHAR_SIZE, fill);
                logic_text.setPosition(horizontal_anchor + SGE_DEBUG_HIERARCHY_CHILD_INDENT, *vertical_anchor);
                target.draw(logic_text, states);
                *vertical_anchor += logic_text.getLocalBounds().height + SGE_DEBUG_LOGIC_PADDING;
            }
            break;
    }
}

void sge::core::debug::HierarchyPanel::focus_next() {
    auto siblings = get_siblings(m_scene_transform_vector, focused_object);
    if (siblings.size()>1) {
        int next_index = -1;
        for (int i = 0; i < siblings.size(); ++i) {
            if (siblings[i] == focused_object) {
                next_index = i+1;
                break;
            }
        }

        if (next_index >= siblings.size()) next_index = 0;

        focused_object = siblings[next_index];
    }
}

void sge::core::debug::HierarchyPanel::focus_previous() {
    auto siblings = get_siblings(m_scene_transform_vector, focused_object);
    if (siblings.size()>1) {
        int prev_index;
        for (int i = 0; i < siblings.size(); ++i) {
            if (siblings[i] == focused_object) {
                prev_index = i-1;
                break;
            }
        }

        if (prev_index < 0) prev_index = siblings.size()-1;

        focused_object = siblings[prev_index];
    }
}

std::vector<Transform_H>
sge::core::debug::HierarchyPanel::get_siblings(std::vector<Transform_H> transform_vector, Transform_H target_transform) {
    std::vector<Transform_H> siblings;
    if (target_transform->is_root()) {
        siblings = get_root_transforms(transform_vector);
    } else {
        auto parent_children = target_transform->get_parent()->get_children();

        for (auto child : parent_children) {
            siblings.emplace_back(child);
        }
    }
    return siblings;
}

void sge::core::debug::HierarchyPanel::enter_focused() {
    if (!focused_object->get_children().empty())
        focused_object = focused_object->get_children().front();
}

void sge::core::debug::HierarchyPanel::return_focused() {
    if (!focused_object->is_root())
        focused_object = focused_object->get_parent();
}

void sge::core::debug::HierarchyPanel::next_mode() {
    if (display_mode==LOGIC) display_mode = HIERARCHY;
    else display_mode = static_cast<HierarchyDisplayMode>(static_cast<int>(display_mode) + 1);
}

void sge::core::debug::HierarchyPanel::prev_mode() {
    if (display_mode==HIERARCHY) display_mode = LOGIC;
    else display_mode = static_cast<HierarchyDisplayMode>(static_cast<int>(display_mode) - 1);
}

void sge::core::debug::HierarchyPanel::draw_component(sf::RenderTarget &target, sf::RenderStates states,
                                                      const std::string &header, sge::cmp::IComponent *component,
                                                      int *vertical_anchor, int horizontal_anchor, sf::Color fill) const {

    auto header_text = make_text(header, SGE_DEBUG_COMPONENT_HEADER_CHAR_SIZE, fill);
    header_text.setFont(*italic_font);
    header_text.setPosition(horizontal_anchor, *vertical_anchor);
    target.draw(header_text, states);
    *vertical_anchor += SGE_DEBUG_COMPONENT_HEADER_CHAR_SIZE + 2;
    horizontal_anchor += SGE_DEBUG_HIERARCHY_CHILD_INDENT;

    auto text = make_text(component->get_debug_string(), SGE_DEBUG_COMPONENT_INFO_CHAR_SIZE, fill);
    text.setPosition(horizontal_anchor, *vertical_anchor);
    target.draw(text, states);
    *vertical_anchor += text.getLocalBounds().height;
}






