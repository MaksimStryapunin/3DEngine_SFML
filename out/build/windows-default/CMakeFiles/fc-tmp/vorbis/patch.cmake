cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

message(VERBOSE "Executing patch step for vorbis")

block(SCOPE_FOR VARIABLES)

cmake_language(GET_MESSAGE_LOG_LEVEL _ep_step_log_level)
if(_ep_step_log_level MATCHES "VERBOSE|DEBUG|TRACE")
  set(_ep_step_maybe_command_echo COMMAND_ECHO STDOUT)
else()
  set(_ep_step_maybe_command_echo)
endif()
execute_process(
  WORKING_DIRECTORY "C:/Users/Максим/source/repos/3DEngine_SFML/out/build/windows-default/_deps/vorbis-src"
  COMMAND_ERROR_IS_FATAL LAST
  ${_ep_step_maybe_command_echo}
  COMMAND  [====[C:/Program Files (x86)/Microsoft Visual Studio/2019/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/bin/cmake.exe]====] [====[-DVORBIS_DIR=C:/Users/Максим/source/repos/3DEngine_SFML/out/build/windows-default/_deps/vorbis-src]====] [====[-P]====] [====[C:/Users/Максим/source/repos/3DEngine_SFML/out/build/windows-default/_deps/sfml-src/tools/vorbis/PatchVorbis.cmake]====]
)

endblock()
