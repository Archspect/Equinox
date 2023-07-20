cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED on)
project(equinox VERSION 0.1.0)
add_executable(equinox 

Source/main.cpp
Source/Apparatus/Window.cpp
Source/Apparatus/Renderer.cpp
)
add_compile_definitions(BX_CONFIG_DEBUG)

target_include_directories(equinox 
	PRIVATE
	Vendor/bgfx/include
	Vendor/bx/include
	Vendor/bimg/include
	Vendor/bgfx/3rdparty/
	Vendor/bgfx/examples/common
)

target_include_directories(equinox 
	PRIVATE 
	Vendor/entt/src/
	Vendor/FastNoiseLite/Cpp/
	Vendor/fmt/include
	Vendor/glm/
	Vendor/SDL/include/
	Vendor/tinyphysicsengine/
	Vendor/cereal/
)

target_link_libraries(equinox GL X11 ${CMAKE_DL_LIBS} pthread)

target_link_directories(equinox PRIVATE 
./Vendor/bgfx/.build/linux64_gcc/bin/
./Vendor/fmt/build/
./Vendor/SDL/build/)

add_subdirectory(Vendor/flecs)

if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
	target_link_libraries(equinox 
		bgfxDebug
		bimgDebug
		bxDebug
		example-glueDebug
		example-commonDebug
		bimg_decodeDebug
	)
  elseif("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
	target_link_libraries(equinox
		example-glueRelease
		example-commonRelease
		bimg_decodeRelease
		bgfxRelease
		bimgRelease 
		bxRelease
	)
  endif()


file (COPY ${CMAKE_SOURCE_DIR}/Vendor/bgfx/examples/runtime/ DESTINATION ${CMAKE_BINARY_DIR})

target_link_libraries(${PROJECT_NAME} flecs::flecs_static)
target_link_libraries(equinox SDL2 fmt )
