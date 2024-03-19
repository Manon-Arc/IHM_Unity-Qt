# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\IHM_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\IHM_autogen.dir\\ParseCache.txt"
  "IHM_autogen"
  )
endif()
