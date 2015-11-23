project( GlslParser )

set( PROJECT_DESC "Glsl ShaderParser plug-in" )
set( ${PROJECT_NAME}_VERSION_MAJOR	0 )
set( ${PROJECT_NAME}_VERSION_MINOR	1 )
set( ${PROJECT_NAME}_VERSION_BUILD	0 )

# Include directories
include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/Src 
	${SHADER_PARSER}_SOURCE_DIR}/Interface/Src
)

set( DefaultTarget GlslParser )

add_target(
	GlslParser
	plugin
	"ShaderParser"
	"ShaderParser;${MinLibraries}"
	"GlslParserPch.h"
	"GlslParserPch.cpp"
)

set_property( TARGET GlslParser PROPERTY FOLDER "Plugin/GLSL" )
add_target_astyle( GlslParser ".h;.hpp;.inl;.cpp" )
set( Build "yes" PARENT_SCOPE )
