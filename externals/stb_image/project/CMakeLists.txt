cmake_minimum_required(VERSION 3.1)

#[PROJECT_NAME]
PROJECT(STB_IMAGE)

#[BUILD_TYPE]
SET(CMAKE_BUILD_TYPE Debug)

# Set the output folders where the program will be created
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

#[PRJ_INCLUDE]
INCLUDE_DIRECTORIES(include)

#[PRJ_HEADER_FILES]
SET(HEADERS
	include/stb_image.h
)

# Generate the static library from the sources
ADD_LIBRARY(${PROJECT_NAME} INTERFACE)
TARGET_SOURCES(${PROJECT_NAME} INTERFACE ${HEADERS})

# From here, the target '${PROJECT_NAME}' can be customised
#TARGET_INCLUDE_DIRECTORIES(${PROJECT_NAME}) # Transitively forwarded
#INSTALL(TARGETS ${PROJECT_NAME})
# Copy the include directory where the lib is installed
INSTALL(DIRECTORY include DESTINATION ${LIBRARY_OUTPUT_PATH})

#  HACK: have the files showing in the IDE, under the name '${PROJECT_NAME}_IDE'
ADD_CUSTOM_TARGET(${PROJECT_NAME}_IDE SOURCES ${HEADERS})