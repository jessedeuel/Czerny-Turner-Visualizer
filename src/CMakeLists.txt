find_package(Magnum REQUIRED GL Sdl2Application)

set_directory_properties(PROPERTIES CORRADE_USE_PEDANTIC_FLAGS ON)

add_executable(czerny_turner_visualizer main.cpp)
target_link_libraries(czerny_turner_visualizer PRIVATE
    Magnum::Application
    Magnum::GL
    Magnum::Magnum)