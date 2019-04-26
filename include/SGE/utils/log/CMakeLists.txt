target_include_directories(factory_experiments PRIVATE .)

target_sources(factory_experiments PUBLIC
        Log.hpp
        Loggable.hpp)




if (CMAKE_BUILD_TYPE MATCHES Debug)
    target_compile_definitions(factory_experiments PUBLIC DEBUG=1)
    # if the debug verbosity hasn't been manually defined get it from the cache
    if (NOT DEBUG_LOG_VERBOSITY)
        set(DEBUG_LOG_VERBOSITY "1" CACHE STRING "If your build type id Debug this will define the max debug log level that will be compiled. ")
    endif()


    target_compile_definitions(factory_experiments PUBLIC LOG_MAX_LEVEL=${DEBUG_LOG_VERBOSITY})

else()
    target_compile_definitions(factory_experiments PUBLIC RELEASE=1)
    target_compile_definitions(factory_experiments PUBLIC LOG_MAX_LEVEL=2)
endif()

if (NOT LOG_HEADER)
    set(LOG_HEADER true CACHE BOOL "Allows a header line to be printed before every log, containing some relevant information.")
endif()
target_compile_definitions(factory_experiments PUBLIC LOG_PRINT_HEADER=${LOG_HEADER})

