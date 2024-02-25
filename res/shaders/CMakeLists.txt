#res/shaders/CMakeLists.txt

set(SHADER_FILES res/shaders/vSprite.txt res/shaders/fSprite.txt)

foreach(SHADER_FILE ${SHADER_FILES})
	configure_file(${CMAKE_SOURCE_DIR}/${SHADER_FILE} ${CMAKE_BINARY_DIR}/${SHADER_FILE} COPYONLY)
endforeach()