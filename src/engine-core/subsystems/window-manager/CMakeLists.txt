target_include_directories(SGE PRIVATE .)

target_sources(SGE PRIVATE
        WindowManager.cpp
        WindowManager.hpp

        FontManager.cpp
        FontManager.hpp
        )


add_subdirectory(debug-shapes-manager)