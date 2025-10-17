# Add this directory for internal users.
include_directories(.)
# Find sources.
file(GLOB metis_sources *.c)
# Build libmetis.
add_library(metis ${METIS_LIBRARY_TYPE} ${GKlib_sources} ${metis_sources})
set_target_properties(metis PROPERTIES OUTPUT_NAME "${BINARY_NAME}")

target_compile_definitions(metis
    PUBLIC HIGHS_METIS_THREAD_SAFE
)

if(UNIX)
  target_link_libraries(metis m)
endif()

if(WIN32)
  set(RT_DEST bin)
else()
  set(RT_DEST lib)
endif()

if(METIS_INSTALL)
  install(TARGETS metis EXPORT metisTargets
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION ${RT_DEST}
    ARCHIVE DESTINATION lib
    INCLUDES DESTINATION include)
endif()
