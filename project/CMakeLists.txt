CMAKE_MINIMUM_REQUIRED(VERSION 3.1)

#[PROJECT_NAME]
PROJECT(DCPP)

#[BUILD_TYPE]
SET(CMAKE_BUILD_TYPE Debug)

# Set the output folders where the program will be created
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/../cmake_modules)
SET(CMAKE_INCLUDE_PATH ${PROJECT_SOURCE_DIR}/../cmake_include)
SET(EXTERNALS_PATH ${PROJECT_SOURCE_DIR}/../externals)

INCLUDE(${CMAKE_INCLUDE_PATH}/CMake-Include.txt)

# FindSDL2.cmake
FIND_PACKAGE(SDL2 REQUIRED)
INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIR})

FIND_PACKAGE(OpenGL REQUIRED)
INCLUDE_DIRECTORIES(${OPENGL_INCLUDE_DIR})

#[PRJ_INCLUDE]
INCLUDE_DIRECTORIES(include)
INCLUDE_DIRECTORIES(include/assets)
INCLUDE_DIRECTORIES(include/component)
INCLUDE_DIRECTORIES(include/containers)
INCLUDE_DIRECTORIES(include/dir)
INCLUDE_DIRECTORIES(include/help)
INCLUDE_DIRECTORIES(include/input)
INCLUDE_DIRECTORIES(include/material)
INCLUDE_DIRECTORIES(include/mesh)
INCLUDE_DIRECTORIES(include/nodes)
INCLUDE_DIRECTORIES(include/persist)
INCLUDE_DIRECTORIES(include/physics)
INCLUDE_DIRECTORIES(include/renderer)
INCLUDE_DIRECTORIES(include/scenes)
INCLUDE_DIRECTORIES(include/structures)
INCLUDE_DIRECTORIES(include/subsystem)
INCLUDE_DIRECTORIES(include/types)
INCLUDE_DIRECTORIES(include/window)
INCLUDE_DIRECTORIES(include/persist/assets)
INCLUDE_DIRECTORIES(include/persist/md3)
INCLUDE_DIRECTORIES(include/persist/obj)
INCLUDE_DIRECTORIES(include/persist/shader)
INCLUDE_DIRECTORIES(include/persist/texture)

#[PRJ_HEADER_FILES]
SET(HEADERS
	include/app.h
	include/assets/assetmanager.h
	include/component/camera.h
	include/component/component.h
	include/component/gameobject.h
	include/component/modelcomponent.h
	include/component/renderercomponent.h
	include/component/transform.h
	include/containers/array.h
	include/containers/forwardlist.h
	include/containers/proxy.h
	include/dir/directory.h
	include/help/callbacks.h
	include/help/deletehelp.h
	include/help/filemanager.h
	include/help/functor.h
	include/help/utils.h
	include/input/inputdefs.h
	include/input/inputmanagerfactory.h
	include/input/keyinputmanager.h
	include/input/mouseinputmanager.h
	include/input/sdlkeyinputmanager.h
	include/material/material.h
	include/material/property.h
	include/material/shader.h
	include/material/shadermanager.h
	include/material/texture.h
	include/material/texturemanager.h
	include/mesh/mesh.h
	include/mesh/meshmanager.h
	include/mesh/model.h
	include/mesh/vertices.h
	include/nodes/graphicnode.h
	include/persist/meshloader.h
	include/persist/assets/assetloader.h
	include/persist/md3/animationloader.h
	include/persist/md3/md3loader.h
	include/persist/md3/md3model.h
	include/persist/md3/md3structs.h
	include/persist/md3/skinloader.h
	include/persist/obj/objloader.h
	include/persist/shader/shaderloader.h
	include/persist/texture/textureloader.h
	include/physics/boundingbox.h
	include/renderer/glwraps.h
	include/renderer/renderbatch.h
	include/renderer/renderer.h
	include/renderer/renderlayer.h
	include/renderer/renderlayermanager.h
	include/renderer/vao.h
	include/renderer/vbo.h
	include/renderer/vertexproperty.h
	include/scenes/scene.h
	include/scenes/scenemanager.h
	include/structures/composedstate.h
	include/structures/node.h
	include/structures/proxy.h
	include/structures/singleton.h
	include/structures/state.h
	include/subsystem/appsubsystem.h
	include/subsystem/hfsmsubsystem.h
	include/subsystem/inputsubsystem.h
	include/subsystem/rendersubsystem.h
	include/subsystem/runnablesubsystem.h
	include/subsystem/scenesubsystem.h
	include/subsystem/subsystem.h
	include/subsystem/subsystemmanager.h
	include/subsystem/windowsubsystem.h
	include/types/rtti.h
	include/window/sdlwindow.h
	include/window/window.h
	include/window/windowfactory.h
)

#[PRJ_SOURCE_FILES]
SET(SOURCES
	src/app.cpp
	src/assets/assetmanager.cpp
	src/component/camera.cpp
	src/component/component.cpp
	src/component/gameobject.cpp
	src/component/modelcomponent.cpp
	src/component/renderercomponent.cpp
	src/component/transform.cpp
	src/help/filemanager.cpp
	src/input/inputmanagerfactory.cpp
	src/input/keyinputmanager.cpp
	src/input/mouseinputmanager.cpp
	src/input/sdlkeyinputmanager.cpp
	src/material/material.cpp
	src/material/property.cpp
	src/material/shader.cpp
	src/material/texture.cpp
	src/mesh/mesh.cpp
	src/mesh/model.cpp
	src/nodes/graphicnode.cpp
	src/persist/meshloader.cpp
	src/persist/assets/assetloader.cpp
	src/persist/md3/animationloader.cpp
	src/persist/md3/md3loader.cpp
	src/persist/md3/md3model.cpp
	src/persist/md3/skinmodel.cpp
	src/persist/obj/objloader.cpp
	src/persist/shader/shaderloader.cpp
	src/persist/texture/textureloader.cpp
	src/physics/boundingbox.cpp
	src/renderer/renderbatch.cpp
	src/renderer/renderer.cpp
	src/renderer/renderlayer.cpp
	src/renderer/renderlayermanager.cpp
	src/renderer/vao.cpp
	src/renderer/vbo.cpp
	src/renderer/vertexproperty.cpp
	src/scenes/scene.cpp
	src/scenes/scenemanager.cpp
	src/subsystem/hfsmsubsystem.cpp
	src/subsystem/inputsubsystem.cpp
	src/subsystem/rendersubsystem.cpp
	src/subsystem/scenesubsystem.cpp
	src/subsystem/subsystemmanager.cpp
	src/subsystem/windowsubsystem.cpp
	src/window/sdlwindow.cpp
	src/window/windowfactory.cpp
)

# Generate the static library from the sources
ADD_LIBRARY(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})

#[ORGANIZATION]

SOURCE_GROUP_BY_FOLDER("${SOURCES}")
SOURCE_GROUP_BY_FOLDER("${HEADERS}")

#[EXTERNAL_PROJECTS]
ADD_SUBDIRECTORY(${EXTERNALS_PATH}/dcpp_signals/project ${PROJECT_BINARY_DIR}/dcpp_signals)
INCLUDE_DIRECTORIES(${EXTERNALS_PATH}/dcpp_signals/project/include)

ADD_SUBDIRECTORY(${EXTERNALS_PATH}/dcpp_math/project ${PROJECT_BINARY_DIR}/dcpp_math)
INCLUDE_DIRECTORIES(${EXTERNALS_PATH}/dcpp_math/project/include)

ADD_SUBDIRECTORY(${EXTERNALS_PATH}/stb_image/project ${PROJECT_BINARY_DIR}/stb_image)
INCLUDE_DIRECTORIES(${EXTERNALS_PATH}/stb_image/project/include)

ADD_SUBDIRECTORY(${EXTERNALS_PATH}/rapidjson/project ${PROJECT_BINARY_DIR}/rapidjson)
INCLUDE_DIRECTORIES(${EXTERNALS_PATH}/rapidjson/project/include)


TARGET_LINK_LIBRARIES(${PROJECT_NAME} 
	${SDL2_LIBRARY}
	${OPENGL_LIBRARIES}
)

SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)
 
# Set the location for library installation
# Use "sudo make install" to apply
INSTALL(TARGETS ${PROJECT_NAME} DESTINATION ${LIBRARY_OUTPUT_PATH})
INSTALL(DIRECTORY ${PROJECT_SOURCE_DIR}/include DESTINATION ${LIBRARY_OUTPUT_PATH})
