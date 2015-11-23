project( HlslParser )

set( PROJECT_DESC "Hlsl ShaderParser plug-in" )
set( ${PROJECT_NAME}_VERSION_MAJOR	0 )
set( ${PROJECT_NAME}_VERSION_MINOR	1 )
set( ${PROJECT_NAME}_VERSION_BUILD	0 )

# Include directories
include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/Src 
	${SHADER_PARSER}_SOURCE_DIR}/Interface/Src
)

set( DefaultTarget HlslParser )

add_target(
	HlslParser
	plugin
	"ShaderParser"
	"ShaderParser;${MinLibraries}"
	"HlslParserPch.h"
	"HlslParserPch.cpp"
)

set_property( TARGET HlslParser PROPERTY FOLDER "Plugin/HLSL" )
add_target_astyle( HlslParser ".h;.hpp;.inl;.cpp" )
set( Build "yes" PARENT_SCOPE )
