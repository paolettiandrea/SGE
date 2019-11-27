#include "SGE/components/graphics/ui/UI.hpp"
#include <SGE/GameObject.hpp>
#include <SGE/Scene.hpp>
#include <FontManager.hpp>


void sge::cmp::UI::clean_dirty_anchor_alignment(sf::FloatRect new_rect) {
    if (dirty_anchor_alignment) {

        float x = 0;
        switch (anchor_align.horizontal) {
            case LEFT:
                x = new_rect.left;
                break;
            case MIDDLE:
                x = new_rect.left + new_rect.width/2;
                break;
            case RIGHT:
                x = new_rect.left + new_rect.width;
                break;
        }

        float y = 0;
        switch (anchor_align.vertical) {
            case TOP:
                y = new_rect.top;
                break;
            case CENTER:
                y = new_rect.top + new_rect.height/2;
                break;
            case BOTTOM:
                y = new_rect.top + new_rect.height;
                break;
        }
        m_content->set_position(sf::Vector2f(x, y));

        dirty_anchor_alignment = false;
    }

}

void sge::cmp::UI::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    m_content->prepare_for_draw();
    target.draw(*m_content, states);
}

sge::cmp::UI::UI(const utils::Handle<GameObject> &gameobject) : Component(gameobject, "UI") {

}

void sge::cmp::UI::clean_dirty_origin_alignment() {
    if (m_content->m_bounds_dirty) {
        auto bounds = m_content->get_bounds();

        float x = 0;
        switch (origin_align.horizontal) {
            case LEFT:
                x = bounds.left + m_content->m_offset.x;
                break;
            case MIDDLE:
                x = bounds.left + bounds.width/2 + m_content->m_offset.x;
                break;
            case RIGHT:
                x = bounds.left + bounds.width + m_content->m_offset.x;
                break;
        }
        float y = 0;
        switch (origin_align.vertical) {
            case TOP:
                y = bounds.top + m_content->m_offset.y;
                break;
            case CENTER:
                y = bounds.top + bounds.height/2 + m_content->m_offset.y;
                break;
            case BOTTOM:
                y = bounds.top+ bounds.height + m_content->m_offset.y;
                break;
        }
        m_content->set_origin(sf::Vector2f(x, y));
        m_content->m_bounds_dirty = false;
    }

}

void sge::cmp::UI::set_anchor_alignment(sge::cmp::UI::Alignment alignment) {
    if (anchor_align.vertical != alignment.vertical) {
        anchor_align.vertical = alignment.vertical;
        dirty_origin_alignment = true;
    }
    if (anchor_align.horizontal != alignment.horizontal) {
        anchor_align.horizontal = alignment.horizontal;
        dirty_origin_alignment = true;
    }
}

void sge::cmp::UI::set_origin_alignment(sge::cmp::UI::Alignment alignment) {
    if (origin_align.vertical != alignment.vertical) {
        origin_align.vertical = alignment.vertical;
        dirty_origin_alignment = true;
    }
    if (origin_align.horizontal != alignment.horizontal) {
        origin_align.horizontal = alignment.horizontal;
        dirty_origin_alignment = true;
    }
}

void sge::cmp::UI::initialization_callback() {
    IComponent::initialization_callback();
    auto my_handle = get_handle();
    camera_ratio_changed_evhandler = [=]() {
        my_handle->dirty_anchor_alignment = true;
    };
    gameobject()->get_scene()->get_camera()->ratio_changed_event += camera_ratio_changed_evhandler;
}

void sge::cmp::UI::destruction_callback() {
    IComponent::destruction_callback();

    gameobject()->get_scene()->get_camera()->ratio_changed_event -= camera_ratio_changed_evhandler;
    delete (m_content);
}

void sge::cmp::UI::clean_font(core::FontManager &font_manager) {
    m_content->clean_font(font_manager);
}

void sge::cmp::UI::set_anchor_alignment(sge::cmp::UI::HotizontalAlignment horizontal,
                                        sge::cmp::UI::VerticalAlignment vertical_alignment) {
    anchor_align.horizontal = horizontal;
    anchor_align.vertical = vertical_alignment;
    dirty_anchor_alignment = true;
}

void sge::cmp::UI::set_origin_alignment(sge::cmp::UI::HotizontalAlignment horizontal,
                                        sge::cmp::UI::VerticalAlignment vertical_alignment) {
   origin_align.horizontal = horizontal;
    origin_align.vertical = vertical_alignment;
    dirty_origin_alignment = true;
}

void sge::cmp::UI::set_content(sge::UIContent *content) {
    if (m_content!= nullptr) {
        delete (m_content);
    }

    m_content = content;

}

void sge::cmp::UI::visual_debug_draw_ui_rectangles(sf::RenderTexture& target) {
    auto bounds = m_content->get_bounds();
}

std::string sge::cmp::UI::get_debug_string() {
    auto s = IComponent::get_debug_string();

    s+= "Horizontal anchor alignment: ";
    switch (anchor_align.horizontal) {
        case LEFT:      s+= "LEFT";     break;
        case MIDDLE:    s += "MIDDLE";  break;
        case RIGHT:     s += "RIGHT";   break;
    }
    s += "\n";

    s+= "Vertical anchor alignment: ";
    switch (anchor_align.vertical) {
        case TOP:       s+= "TOP";      break;
        case CENTER:    s += "CENTER";  break;
        case BOTTOM:    s += "BOTTOM";  break;
    }
    s += "\n";

    s+= "Horizontal origin alignment: ";
    switch (origin_align.horizontal) {
        case LEFT:      s+= "LEFT";     break;
        case MIDDLE:    s += "MIDDLE";  break;
        case RIGHT:     s += "RIGHT";   break;
    }
    s += "\n";

    s+= "Vertical anchor alignment: ";
    switch (origin_align.vertical) {
        case TOP:       s+= "TOP";      break;
        case CENTER:    s += "CENTER";  break;
        case BOTTOM:    s += "BOTTOM";  break;
    }
    s += "\n";

    return s;
}
