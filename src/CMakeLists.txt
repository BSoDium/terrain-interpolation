
aux_source_directory(. CPP_FILES)

add_executable(main ${CPP_FILES})

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

if(APPLE)
  add_definitions(-Wno-deprecated-declarations)
endif()

target_link_libraries(main OpenGL::GL OpenGL::GLU GLEW::glew glfw)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    target_compile_options(main PRIVATE -Wall -Wextra -pedantic -Wno-comment)
endif()
if(MSVC)
    target_compile_definitions(main PUBLIC -DNOMINMAX)
endif()
