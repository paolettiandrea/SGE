#ifndef NON_GRAVITAR_HIERARCHYPANEL_HPP
#define NON_GRAVITAR_HIERARCHYPANEL_HPP

#include <SGE/utils/handles/Handle.hpp>
#include <SGE/components/Transform.hpp>
#include <SFML/Graphics.hpp>
#include <subsystems/input-manager/InputManager.hpp>
#include <subsystems/window-manager/FontManager.hpp>


#define SGE_DEBUG_HIERARCHY_FONT "RobotoMono-Medium"
#define SGE_DEBUG_HIERARCHY_ITALIC_FONT "RobotoMono-BoldItalic"

#define SGE_DEBUG_SCENE_STACK_INACTIVE_COLOR sf::Color(100,100,100)
#define SGE_DEBUG_SCENE_STACK_ACTIVE_COLOR sf::Color(200,200,200)

#define SGE_DEBUG_HIERARCHY_FOCUSED_COLOR sf::Color(220,220,220)
#define SGE_DEBUG_HIERARCHY_NOT_FOCUSED_COLOR sf::Color(220,220,220,150)
#define SGE_DEBUG_HIERARCHY_UPSTREAM_COLOR sf::Color(150,150,150)

#define SGE_DEBUG_HIERARCHY_LEFT_PADDING 5
#define SGE_DEBUG_HIERARCHY_TOP_PADDING 5

#define SGE_DEBUG_HIERARCHY_ROW_SPACING 20
#define SGE_DEBUG_HIERARCHY_CHILD_INDENT 10
#define SGE_DEBUG_HIERARCHY_SCENE_STACK_TRAILING_SPACE 5


#define SGE_DEBUG_SCENE_STACK_CHAR_SIZE 15
#define SGE_DEBUG_SCENE_POINTED_CHAR_SIZE 13
#define SGE_DEBUG_HIERARCHY_CHILD_CHAR_SIZE 11

#define SGE_DEBUG_HIERARCHY_SCENE_PADDING 2
#define SGE_DEBUG_HIERARCHY_SIBLINGS_PADDING 20
#define SGE_DEBUG_HIERARCHY_CHILD_PADDING 1

#define SGE_DEBUG_COMPONENT_PADDING 5
#define SGE_DEBUG_COMPONENT_HEADER_CHAR_SIZE 12
#define SGE_DEBUG_COMPONENT_INFO_CHAR_SIZE 11

#define SGE_DEBUG_LOGIC_HEADER_CHAR_SIZE 12
#define SGE_DEBUG_LOGIC_INFO_CHAR_SIZE 11
#define SGE_DEBUG_LOGIC_PADDING 3

#define SGE_DEBUG_HIERARCHY_MAX_VERTICAL_ANCHOR 4000



namespace sge::core::debug {
    enum HierarchyDisplayMode { HIERARCHY, SHALLOW_HIERARCHY, COMPONENT, LOGIC };

    class HierarchyPanel : public sf::Drawable {
    public:
        void initialize(FontManager& font_manager);

        void update_state(std::vector<Transform_H> scene_transform_vector, std::vector<cd::Scene_ConstructionData>& scene_cds);

        void reset();

        void focus_next();
        void focus_previous();
        void enter_focused();
        void return_focused();

        void next_mode();
        void prev_mode();

    private:
        Transform_H focused_object;
        std::vector<Transform_H> m_scene_transform_vector;

        sf::Font* font;
        sf::Font* italic_font;

        HierarchyDisplayMode display_mode = HIERARCHY;

        std::vector<cd::Scene_ConstructionData>* scene_cds;

        static std::vector<Transform_H> get_root_transforms(std::vector<Transform_H> transform_vector);
        static std::vector<Transform_H> get_siblings(std::vector<Transform_H> transform_vector, Transform_H target_transform);

        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

        [[nodiscard]] sf::Text make_text(const std::string &string, unsigned int char_size = 20, sf::Color fill_color = sf::Color::White) const;

        void draw_sibling(sf::RenderTarget &target, sf::RenderStates states, Transform_H transform, int *vertical_anchor, int horizontal_anchor, int level, sf::Color fill) const;

        void draw_component(sf::RenderTarget &target, sf::RenderStates states,
                            const std::string &header, sge::cmp::IComponent *component,
                            int *vertical_anchor, int horizontal_anchor, sf::Color fill) const;
    };
}



#endif //NON_GRAVITAR_HIERARCHYPANEL_HPP
