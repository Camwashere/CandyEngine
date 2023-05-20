#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "portaudio" for configuration "Release"
set_property(TARGET portaudio APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(portaudio PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/portaudio.lib"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "winmm;dsound;ole32;uuid;ole32;uuid;setupapi;ole32;uuid"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/portaudio.dll"
  )

list(APPEND _cmake_import_check_targets portaudio )
list(APPEND _cmake_import_check_files_for_portaudio "${_IMPORT_PREFIX}/lib/portaudio.lib" "${_IMPORT_PREFIX}/bin/portaudio.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
