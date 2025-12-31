add_library(core STATIC src/core.cpp src/word_loader.cpp src/record_manager.cpp)

target_include_directories(core PUBLIC include)
