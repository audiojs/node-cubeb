cmake_minimum_required(VERSION 2.8)

project(cubeb_js)
file(GLOB SOURCE_FILES "src/*.cc" "src/*.h")
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})

set(CMAKE_CXX_FAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DENABLE_DEBUG")

set_target_properties(${PROJECT_NAME} PROPERTIES
    PREFIX ""
    SUFFIX ".node"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/dist"
)

target_link_libraries(${PROJECT_NAME}
    # Node libraries
    ${CMAKE_JS_LIB}
    # Cubeb library
    "${CMAKE_SOURCE_DIR}/cubeb/build/libcubeb.a"
)

target_include_directories(${PROJECT_NAME}
    # Node.js headers
    PRIVATE ${CMAKE_JS_INC}
    PRIVATE "${CMAKE_SOURCE_DIR}/node_modules/node-addon-api"
    # Cubeb headers
    PRIVATE "${CMAKE_SOURCE_DIR}/cubeb/src"
    PRIVATE "${CMAKE_SOURCE_DIR}/cubeb/build/exports"
    PRIVATE "${CMAKE_SOURCE_DIR}/cubeb/include"
)

# ALSA library needed for Linux
if(UNIX AND NOT APPLE)
    target_link_libraries(${PROJECT_NAME} libasound.so)
endif()

# Copy the JS module that imports the binary
add_custom_command(
    TARGET cubeb_js POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_SOURCE_DIR}/src/cubeb.js
            ${CMAKE_SOURCE_DIR}/dist/cubeb.js
)