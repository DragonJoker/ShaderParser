option( BUILD_GLSL_PLUGIN "Build GLSL plugin" TRUE )
option( BUILD_HLSL_PLUGIN "Build HLSL plugin" TRUE )

function( PluginInit )
	set( Glsl "no (Not wanted)" PARENT_SCOPE )
	set( Hlsl "no (Not wanted)" PARENT_SCOPE )
endfunction( PluginInit )

function( PluginBuild )
	if( ${BUILD_GLSL_PLUGIN} )
		set( Build ${Glsl} )
		add_subdirectory( Plugin/Glsl )
		set( Glsl ${Build} PARENT_SCOPE )
	endif ()
	if( ${BUILD_HLSL_PLUGIN} )
		set( Build ${Hlsl} )
		add_subdirectory( Plugin/Hlsl )
		set( Hlsl ${Build} PARENT_SCOPE )
	endif ()
endfunction( PluginBuild )

function( PluginSummary msg )
	set( msg_tmp "\n\nPlugins :" )
	set( msg_tmp "${msg_tmp}\n    GLSL                  ${Glsl}" )
	set( msg_tmp "${msg_tmp}\n    HLSL                  ${Hlsl}" )
	SET( msg "${msg}${msg_tmp}" PARENT_SCOPE )
endfunction( PluginSummary )

function( PluginSetup )
	if( ${BUILD_GLSL_PLUGIN} )
		cpack_add_component( GlslParser
			DISPLAY_NAME "GLSL plugin"
			DESCRIPTION "GLSL plugin to use with ${MAIN_PROJECT_NAME}"
			REQUIRED
			GROUP ParserPlugins
			INSTALL_TYPES Minimal Full
		)
	endif ()

	if( ${BUILD_HLSL_PLUGIN} )
		cpack_add_component( HlslParser
			DISPLAY_NAME "HLSL plugin"
			DESCRIPTION "HLSL plugin to use with ${MAIN_PROJECT_NAME}"
			REQUIRED
			GROUP ParserPlugins
			INSTALL_TYPES Minimal Full
		)
	endif ()
endfunction( PluginSetup )
