target_include_directories(factory_experiments PRIVATE .)

target_sources(factory_experiments PUBLIC
        Logic.hpp
        ILogic.hpp
        ILogicCallbacks.hpp
        DummyLogic.hpp
        )