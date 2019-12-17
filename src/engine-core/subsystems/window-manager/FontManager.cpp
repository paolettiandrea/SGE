#include "FontManager.hpp"
#include <iostream>
#include <dirent.h>
#include <cstring>

void sge::core::FontManager::load_fonts() {
    struct dirent *de;  // Pointer for directory entry

    DIR *dr = opendir(SGE_FONT_MANAGER_LOAD_PATH);

    if (dr == NULL)  // opendir returns NULL if couldn't open directory
    {
        printf("Could not open current directory" );
        exit(1);
    }

    while ((de = readdir(dr)) != NULL) {
        auto len = std::strlen(de->d_name);
        if (len > 4) {
            if (std::strcmp(de->d_name + len - 4,  ".ttf") || std::strcmp(de->d_name + len - 4,  ".TTF")) {
                std::string s(SGE_FONT_MANAGER_LOAD_PATH );
                s += "/";
                s += de->d_name;

                std::cout << s << std::endl;
                load_font(s, std::string(de->d_name, 0, len-4));
            }
        }
    }
    closedir(dr);
}

sf::Font *sge::core::FontManager::get_font(std::string font_name) {
    if (loaded_fonts.count(font_name)>0) {
        return loaded_fonts[font_name];
    } else {
        LOG_ERROR << "Couln't find a loaded font named: " << font_name;
        exit(1);
    }

}

void sge::core::FontManager::load_font(const std::string &font_path, const std::string &id) {
    auto font = new sf::Font();
    if (!font->loadFromFile(font_path)) {
        LOG_ERROR << "Failed to load font at path: " << font_path;
        exit(1);
    }

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
