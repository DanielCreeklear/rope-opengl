cmake_minimum_required(VERSION 3.16)
project(rope_opengl LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(OpenGL REQUIRED)
if(MSVC AND EXISTS "${CMAKE_SOURCE_DIR}/lib/x64/freeglut.lib")
    set(GLUT_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include" CACHE PATH "Bundled FreeGLUT headers" FORCE)
    set(GLUT_glut_LIBRARY_RELEASE "${CMAKE_SOURCE_DIR}/lib/x64/freeglut.lib" CACHE FILEPATH "Bundled x64 FreeGLUT" FORCE)
    set(GLUT_glut_LIBRARY_DEBUG "${CMAKE_SOURCE_DIR}/lib/x64/freeglut.lib" CACHE FILEPATH "Bundled x64 FreeGLUT" FORCE)
endif()
find_package(GLUT REQUIRED)

file(GLOB PROJECT_SOURCES CONFIGURE_DEPENDS "src/*.cpp")
add_executable(rope-opengl ${PROJECT_SOURCES})
set_target_properties(rope-opengl PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}"
    RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_BINARY_DIR}"
    RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_BINARY_DIR}"
)
target_include_directories(rope-opengl PRIVATE include src)

if(TARGET OpenGL::GL)
    target_link_libraries(rope-opengl PRIVATE OpenGL::GL)
else()
    target_link_libraries(rope-opengl PRIVATE ${OPENGL_gl_LIBRARY})
endif()
if(TARGET OpenGL::GLU)
    target_link_libraries(rope-opengl PRIVATE OpenGL::GLU)
elseif(OPENGL_glu_LIBRARY)
    target_link_libraries(rope-opengl PRIVATE ${OPENGL_glu_LIBRARY})
endif()
if(TARGET GLUT::GLUT)
    target_link_libraries(rope-opengl PRIVATE GLUT::GLUT)
else()
    target_include_directories(rope-opengl PRIVATE ${GLUT_INCLUDE_DIRS})
    target_link_libraries(rope-opengl PRIVATE ${GLUT_LIBRARIES})
endif()

if(MSVC)
    target_compile_options(rope-opengl PRIVATE /W4)
else()
    target_compile_options(rope-opengl PRIVATE -Wall -Wextra -Wpedantic)
    # stb_image is vendored third-party code and is kept out of project warning output.
    set_source_files_properties(src/stb_image_impl.cpp PROPERTIES COMPILE_OPTIONS "-w")
endif()

include(CTest)
if(BUILD_TESTING)
    add_executable(physics_movement_tests
        tests/physics_movement_tests.cpp
        src/Physics.cpp
        src/Terrain.cpp
        src/Block.cpp
        src/Movement.cpp
    )
    target_include_directories(physics_movement_tests PRIVATE include src)
    if(TARGET OpenGL::GL)
        target_link_libraries(physics_movement_tests PRIVATE OpenGL::GL)
    else()
        target_link_libraries(physics_movement_tests PRIVATE ${OPENGL_gl_LIBRARY})
    endif()
    if(TARGET GLUT::GLUT)
        target_link_libraries(physics_movement_tests PRIVATE GLUT::GLUT)
    else()
        target_include_directories(physics_movement_tests PRIVATE ${GLUT_INCLUDE_DIRS})
        target_link_libraries(physics_movement_tests PRIVATE ${GLUT_LIBRARIES})
    endif()
    add_test(NAME physics_and_movement COMMAND physics_movement_tests)
endif()

# Texture paths in the original project are relative to the repository root.
set_property(TARGET rope-opengl PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")
