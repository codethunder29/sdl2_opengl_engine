cmake_minimum_required(VERSION 3.10)

project(project VERSION 1.0)

if(UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif()

if(LINUX)
    # setting flags for release, O2 optimization and pthread implemention for threads
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -pthread")
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS} -O0")

    # adding engine files
    file(GLOB HEADERS *.hpp engine/*.hpp engine/core/*.hpp engine/components/*.hpp objects/*.hpp engine/rendering/*.hpp)
    file(GLOB SOURCES *.cpp engine/*.cpp engine/core/*.cpp engine/components/*.cpp objects/*.cpp engine/rendering/*.cpp)

    # adding renderer files (seperating them because renderer could change)
    file(GLOB HEADERS ${HEADERS} engine/rendering/*.hpp engine/rendering/lib/stb_image/*.h)
    file(GLOB SOURCES ${SOURCES} engine/rendering/*.cpp engine/rendering/lib/stb_image/*.c)
    
    add_executable(project ${SOURCES} ${HEADERS})
    INCLUDE(FindPkgConfig)

    # searching for lib's packages (SDL and GLEW)
    PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
    PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
    PKG_SEARCH_MODULE(GLM REQUIRED glm)
    find_package(GLEW REQUIRED)

    # engine include dirs
    target_include_directories(project PUBLIC ${PROJECT_BINARY_DIR} ${PROJECT_SOURCE_DIR}/engine ${PROJECT_SOURCE_DIR}/engine/core ${PROJECT_SOURCE_DIR}/engine/components ${PROJECT_SOURCE_DIR}/objects)
    # renderer include dirs
    target_include_directories(project PUBLIC ${PROJECT_SOURCE_DIR}/engine/rendering ${PROJECT_SOURCE_DIR}/engine/rendering/lib/stb_image)
    # libs (like SDL and GLEW) include dirs and linking
    target_include_directories(project PUBLIC SDL2 ${GLEW_INCLUDE_DIRS} GLM SDL2IMAGE)
    target_link_libraries(project SDL2 GL ${GLEW_LIBRARIES} ${SDL2IMAGE_LIBRARIES} )

elseif(APPLE)

elseif(WIN32)

endif()