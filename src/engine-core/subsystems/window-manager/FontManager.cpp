#include "FontManager.hpp"
#include <filesystem>
#include <iostream>

void sge::core::FontManager::load_fonts() {

    for (const auto& entry : std::filesystem::directory_iterator("./res/fonts")) {
        if (entry.is_regular_file()) {
            if (entry.path().extension() == ".ttf" || entry.path().extension() == ".TTF") {
                load_font(entry.path().string());
            }
        }
    }
}

sf::Font *sge::core::FontManager::get_font(std::string font_name) {
    if (loaded_fonts.count(font_name)>0) {
        return loaded_fonts[font_name];
    } else {
        LOG_ERROR << "Couln't find a loaded font named: " << font_name;
        exit(1);
    }

}

void sge::core::FontManager::load_font(const std::string &font_path) {
    auto font = new sf::Font();
    if (!font->loadFromFile(font_path)) {
        LOG_ERROR << "Failed to load font at path: " << font_path;
        exit(1);
    }

    std::filesystem::path path(font_path);
    auto id = path.stem().string();
    loaded_fonts[id] = font;
}

sge::core::FontManager::FontManager()
: Loggable("FontManager") {

}

sge::core::FontManager::~FontManager() {
    for (auto pair : loaded_fonts) {
        delete (pair.second);
    }
}
