target_include_directories(factory_experiments PRIVATE .)

target_sources(factory_experiments PUBLIC
        Log.cpp
        Loggable.cpp
        Terminal.cpp
        Time.cpp
        )