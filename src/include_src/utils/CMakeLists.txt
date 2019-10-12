target_include_directories(SGE PRIVATE .)

target_sources(SGE PRIVATE
        Log.cpp
        Loggable.cpp
        Terminal.cpp
        Time.cpp
        Events.cpp
        EventHandler.cpp
        )