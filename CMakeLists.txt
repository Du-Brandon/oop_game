cmake_minimum_required(VERSION 3.16)
project(PracticalToolsForSimpleDesign)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
if (MSVC)
    set(TARGET_COMPILE_OPTIONS
        /W4 /Zi 
    )
    set(CMAKE_EXE_LINKER_FLAGS "/DEBUG /INCREMENTAL:NO")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/build)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/build)
else()
    set(TARGET_COMPILE_OPTIONS
        -Wall -Wextra -pedantic
    )
endif()

if (WIN32 AND CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    # see https://github.com/ntut-open-source-club/practical-tools-for-simple-design/issues/22
    set(CMAKE_RC_FLAGS="-C 1252")
endif()

option(PTSD_ENABLE_PCH "Turn on PCH to increase compilation speed" OFF)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Dependencies.cmake)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(SRC_FILES
    ${SRC_DIR}/config.cpp

    ${SRC_DIR}/Core/Context.cpp
    ${SRC_DIR}/Core/DebugMessageCallback.cpp
    ${SRC_DIR}/Core/VertexArray.cpp
    ${SRC_DIR}/Core/VertexBuffer.cpp
    ${SRC_DIR}/Core/IndexBuffer.cpp
    ${SRC_DIR}/Core/Shader.cpp
    ${SRC_DIR}/Core/Program.cpp
    ${SRC_DIR}/Core/Texture.cpp
    ${SRC_DIR}/Core/TextureUtils.cpp

    ${SRC_DIR}/Util/LoadTextFile.cpp
    ${SRC_DIR}/Util/Logger.cpp
    ${SRC_DIR}/Util/Time.cpp
    ${SRC_DIR}/Util/Input.cpp
    ${SRC_DIR}/Util/SFX.cpp
    ${SRC_DIR}/Util/BGM.cpp
    ${SRC_DIR}/Util/Image.cpp
    ${SRC_DIR}/Util/Text.cpp
    ${SRC_DIR}/Util/TransformUtils.cpp
    ${SRC_DIR}/Util/GameObject.cpp
    ${SRC_DIR}/Util/Renderer.cpp
    ${SRC_DIR}/Util/Color.cpp
    ${SRC_DIR}/Util/Animation.cpp
    ${SRC_DIR}/Util/MissingTexture.cpp
    ${SRC_DIR}/Util/Position.cpp
)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(INCLUDE_FILES
    ${INCLUDE_DIR}/pch.hpp
    ${INCLUDE_DIR}/config.hpp

    ${INCLUDE_DIR}/Core/Context.hpp
    ${INCLUDE_DIR}/Core/DebugMessageCallback.hpp
    ${INCLUDE_DIR}/Core/VertexArray.hpp
    ${INCLUDE_DIR}/Core/VertexBuffer.hpp
    ${INCLUDE_DIR}/Core/UniformBuffer.hpp
    ${INCLUDE_DIR}/Core/UniformBuffer.inl
    ${INCLUDE_DIR}/Core/IndexBuffer.hpp
    ${INCLUDE_DIR}/Core/Shader.hpp
    ${INCLUDE_DIR}/Core/Program.hpp
    ${INCLUDE_DIR}/Core/Texture.hpp
    ${INCLUDE_DIR}/Core/TextureUtils.hpp
    ${INCLUDE_DIR}/Core/Drawable.hpp
    ${INCLUDE_DIR}/Core/MissingFontTextureBase64.hpp
    ${INCLUDE_DIR}/Core/MissingImageTextureBase64.hpp

    ${INCLUDE_DIR}/Util/LoadTextFile.hpp
    ${INCLUDE_DIR}/Util/Logger.hpp
    ${INCLUDE_DIR}/Util/Time.hpp
    ${INCLUDE_DIR}/Util/Input.hpp
    ${INCLUDE_DIR}/Util/Keycode.hpp
    ${INCLUDE_DIR}/Util/SFX.hpp
    ${INCLUDE_DIR}/Util/BGM.hpp
    ${INCLUDE_DIR}/Util/Image.hpp
    ${INCLUDE_DIR}/Util/Text.hpp
    ${INCLUDE_DIR}/Util/Transform.hpp
    ${INCLUDE_DIR}/Util/TransformUtils.hpp
    ${INCLUDE_DIR}/Util/GameObject.hpp
    ${INCLUDE_DIR}/Util/Renderer.hpp
    ${INCLUDE_DIR}/Util/Color.hpp
    ${INCLUDE_DIR}/Util/MissingTexture.hpp
    ${INCLUDE_DIR}/Util/Base64.hpp
    ${INCLUDE_DIR}/Util/Animation.hpp
    ${INCLUDE_DIR}/Util/Position.hpp
)
set(EXAMPLE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/example)
set(EXAMPLE_FILES
    ${EXAMPLE_DIR}/src/Angel.cpp
    ${EXAMPLE_DIR}/src/App.cpp
    ${EXAMPLE_DIR}/src/App_otherfunc.cpp
    ${EXAMPLE_DIR}/src/Arrow.cpp
    ${EXAMPLE_DIR}/src/Background.cpp
    ${EXAMPLE_DIR}/src/Boss_1_1.cpp
    ${EXAMPLE_DIR}/src/Boss_1_2.cpp
    ${EXAMPLE_DIR}/src/Boss_1_3.cpp
    ${EXAMPLE_DIR}/src/Boss_1_4.cpp
    ${EXAMPLE_DIR}/src/Boss_2.cpp
    ${EXAMPLE_DIR}/src/Boss_3.cpp
    ${EXAMPLE_DIR}/src/Button.cpp
    ${EXAMPLE_DIR}/src/Cat.cpp
    ${EXAMPLE_DIR}/src/Enemy.cpp
    ${EXAMPLE_DIR}/src/Enemy_1.cpp
    ${EXAMPLE_DIR}/src/Enemy_2.cpp
    ${EXAMPLE_DIR}/src/Enemy_3.cpp
    ${EXAMPLE_DIR}/src/Enemy_4.cpp
    ${EXAMPLE_DIR}/src/Enemy_5.cpp
    ${EXAMPLE_DIR}/src/Enemy_6.cpp
    ${EXAMPLE_DIR}/src/Enemy_7.cpp
    ${EXAMPLE_DIR}/src/EnemyArrow.cpp
    ${EXAMPLE_DIR}/src/Exp.cpp
    ${EXAMPLE_DIR}/src/Giraffe.cpp
    ${EXAMPLE_DIR}/src/Giraffe_other_func.cpp
    ${EXAMPLE_DIR}/src/Ground_Spikes.cpp
    ${EXAMPLE_DIR}/src/Hp.cpp
    ${EXAMPLE_DIR}/src/Skill.cpp
    ${EXAMPLE_DIR}/src/Wall.cpp
    ${EXAMPLE_DIR}/src/main.cpp 
    # ../public/TracyClient.cpp
    
    ${EXAMPLE_DIR}/include/Angel.hpp
    ${EXAMPLE_DIR}/include/App.hpp
    ${EXAMPLE_DIR}/include/Arrow.hpp
    ${EXAMPLE_DIR}/include/Background.hpp
    ${EXAMPLE_DIR}/include/Boss.hpp
    ${EXAMPLE_DIR}/include/Button.hpp
    ${EXAMPLE_DIR}/include/Cat.hpp
    ${EXAMPLE_DIR}/include/Enemy.hpp
    ${EXAMPLE_DIR}/include/Enemy_1.hpp
    ${EXAMPLE_DIR}/include/Enemy_2.hpp
    ${EXAMPLE_DIR}/include/Enemy_3.hpp
    ${EXAMPLE_DIR}/include/Enemy_4.hpp
    ${EXAMPLE_DIR}/include/Enemy_5.hpp
    ${EXAMPLE_DIR}/include/Enemy_6.hpp
    ${EXAMPLE_DIR}/include/Enemy_7.hpp
    ${EXAMPLE_DIR}/include/EnemyArrow.hpp
    ${EXAMPLE_DIR}/include/Exp.hpp
    ${EXAMPLE_DIR}/include/Giraffe.hpp
    ${EXAMPLE_DIR}/include/Ground_Spikes.hpp
    ${EXAMPLE_DIR}/include/Hp.hpp
    ${EXAMPLE_DIR}/include/log_my.hpp
    ${EXAMPLE_DIR}/include/Skill.hpp
    ${EXAMPLE_DIR}/include/Wall.hpp
    # ../public/tracy/Tracy.hpp

)
set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test)
set(TEST_FILES
    ${TEST_DIR}/SimpleTest.cpp
    ${TEST_DIR}/NotSimpleTest.cpp
    ${TEST_DIR}/TransformTest.cpp
    ${TEST_DIR}/PositionTest.cpp
)

add_library(PTSD STATIC
    ${SRC_FILES}
    ${INCLUDE_FILES}
)
target_link_libraries(PTSD
    ${DEPENDENCY_LINK_LIBRARIES}
)
target_include_directories(PTSD SYSTEM PRIVATE
    ${DEPENDENCY_INCLUDE_DIRS}
)
target_include_directories(PTSD PRIVATE
    ${INCLUDE_DIR}
)
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(PTSD PRIVATE PTSD_ASSETS_DIR="${CMAKE_CURRENT_SOURCE_DIR}/assets")
else()
    # TODO
    message(AUTHOR_WARNING "relative PTSD_ASSETS_DIR is WIP, Please use `-DCMAKE_BUILD_TYPE=Debug` build for now.")
    target_compile_definitions(PTSD PRIVATE PTSD_ASSETS_DIR="${CMAKE_CURRENT_SOURCE_DIR}/assets")
endif()
if (${PTSD_ENABLE_PCH})
    target_precompile_headers(PTSD PRIVATE
        include/pch.hpp
    )
endif()

target_compile_options(PTSD PRIVATE
    ${TARGET_COMPILE_OPTIONS}
)

if(NOT PROJECT_IS_TOP_LEVEL)
    set(DEPENDENCY_INCLUDE_DIRS ${DEPENDENCY_INCLUDE_DIRS} PARENT_SCOPE)
    set(DEPENDENCY_LINK_LIBRARIES ${DEPENDENCY_LINK_LIBRARIES} PARENT_SCOPE)
endif()

add_executable(Example EXCLUDE_FROM_ALL
    ${EXAMPLE_FILES}
)
target_link_libraries(Example
    SDL2::SDL2main # IDK what happens if we don't link SDL2main
    PTSD
)
target_include_directories(Example SYSTEM PRIVATE
    ${INCLUDE_DIR}
    ${DEPENDENCY_INCLUDE_DIRS}
)
target_include_directories(Example PRIVATE
    ${EXAMPLE_DIR}/include
)

target_compile_definitions(Example PRIVATE ASSETS_DIR="${CMAKE_CURRENT_SOURCE_DIR}/assets")

enable_testing()

add_executable(Tests EXCLUDE_FROM_ALL
    ${TEST_FILES}
)
target_link_libraries(Tests
    PTSD
    GTest::gtest_main
)
target_include_directories(Tests SYSTEM PRIVATE
    ${INCLUDE_DIR}
    ${DEPENDENCY_INCLUDE_DIRS}
    lib/googletest/googletest/include
    lib/googletest/googlemock/include
)
target_compile_options(Tests PRIVATE
    ${TARGET_COMPILE_OPTIONS}
)

add_executable(AudioTest EXCLUDE_FROM_ALL
    ${TEST_DIR}/Interactive/Audio.cpp
)
target_link_libraries(AudioTest
    PTSD
    GTest::gtest_main
)
target_include_directories(AudioTest SYSTEM PRIVATE
    ${INCLUDE_DIR}
    ${DEPENDENCY_INCLUDE_DIRS}
    lib/googletest/googletest/include
    lib/googletest/googlemock/include
)
target_compile_options(AudioTest PRIVATE
    ${TARGET_COMPILE_OPTIONS}
)

include(GoogleTest)
gtest_discover_tests(Tests)
