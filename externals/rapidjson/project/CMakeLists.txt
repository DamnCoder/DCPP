CMAKE_MINIMUM_REQUIRED(VERSION 3.1)

# MACROS
MACRO(SOURCE_GROUP_BY_FOLDER FILE_GROUP)

	SET(SOURCE_GROUP_DELIMITER "/")
	SET(last_dir "")
	SET(files "")

	FOREACH(file ${FILE_GROUP})

		#FILE(RELATIVE_PATH relative_file ${ROOT_CPP_PATH} ${file})
		#GET_FILENAME_COMPONENT(dir "${relative_file}" PATH)
		GET_FILENAME_COMPONENT(dir "${file}" PATH)
		#MESSAGE(STATUS ${dir})

		IF (NOT "${dir}" STREQUAL "${last_dir}")
			
			IF (files)
				SOURCE_GROUP("${last_dir}" FILES ${files})
			ENDIF (files)
			
			SET(files "")

		ENDIF (NOT "${dir}" STREQUAL "${last_dir}")
		
		SET(files ${files} ${file})
		SET(last_dir "${dir}")

	ENDFOREACH(file)

	IF (files)
		SOURCE_GROUP("${last_dir}" FILES ${files})
	ENDIF (files)

ENDMACRO(SOURCE_GROUP_BY_FOLDER)

#[PROJECT_NAME]
PROJECT(RapidJSON)

#[BUILD_TYPE]
SET(CMAKE_BUILD_TYPE Debug)

# Set the output folders where the program will be created
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

#[PRJ_INCLUDE]
INCLUDE_DIRECTORIES(include)
INCLUDE_DIRECTORIES(include/rapidjson)
INCLUDE_DIRECTORIES(include/rapidjson/error)
INCLUDE_DIRECTORIES(include/rapidjson/internal)
INCLUDE_DIRECTORIES(include/rapidjson/msinttypes)

#[PRJ_HEADER_FILES]
SET(HEADERS
	include/rapidjson/allocators.h
	include/rapidjson/document.h
	include/rapidjson/encodedstream.h
	include/rapidjson/encodings.h
	include/rapidjson/filereadstream.h
	include/rapidjson/filewritestream.h
	include/rapidjson/fwd.h
	include/rapidjson/istreamwrapper.h
	include/rapidjson/memorybuffer.h
	include/rapidjson/memorystream.h
	include/rapidjson/ostreamwrapper.h
	include/rapidjson/pointer.h
	include/rapidjson/prettywriter.h
	include/rapidjson/rapidjson.h
	include/rapidjson/reader.h
	include/rapidjson/schema.h
	include/rapidjson/stream.h
	include/rapidjson/stringbuffer.h
	include/rapidjson/writer.h
	include/rapidjson/error/en.h
	include/rapidjson/error/error.h
	include/rapidjson/internal/biginteger.h
	include/rapidjson/internal/diyfp.h
	include/rapidjson/internal/dtoa.h
	include/rapidjson/internal/ieee754.h
	include/rapidjson/internal/itoa.h
	include/rapidjson/internal/meta.h
	include/rapidjson/internal/pow10.h
	include/rapidjson/internal/regex.h
	include/rapidjson/internal/stack.h
	include/rapidjson/internal/strfunc.h
	include/rapidjson/internal/strtod.h
	include/rapidjson/internal/swap.h
	include/rapidjson/msinttypes/inttypes.h
	include/rapidjson/msinttypes/stdint.h
)

#[PRJ_SOURCE_FILES]
SET(SOURCES
)

# Generate the static library from the sources
ADD_LIBRARY(${PROJECT_NAME} INTERFACE)
TARGET_SOURCES(${PROJECT_NAME} INTERFACE ${HEADERS})

#[ORGANIZATION]
SOURCE_GROUP_BY_FOLDER("${HEADERS}")

#[EXTERNAL_PROJECTS]
 
#-------------------------------------------------------------------------------------------
# Installation
#-------------------------------------------------------------------------------------------
# Copy the include directory where the lib is installed
INSTALL(DIRECTORY include DESTINATION ${LIBRARY_OUTPUT_PATH})

#  HACK: have the files showing in the IDE, under the name '${PROJECT_NAME}_IDE'
ADD_CUSTOM_TARGET(${PROJECT_NAME}_IDE SOURCES ${HEADERS})
