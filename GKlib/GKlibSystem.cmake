# Helper modules.
include(CheckFunctionExists)
include(CheckIncludeFile)

# Add compiler flags.
if(MSVC)
  # set(GKlib_COPTS "/Ox")
  set(GKlib_COPTIONS "-DWIN32 -DMSC -D_CRT_SECURE_NO_DEPRECATE -DUSE_GKREGEX")
elseif(MINGW)
  set(GKlib_COPTS "-DUSE_GKREGEX")
else()
  # set(GKlib_COPTS "-O3")
  set(GKlib_COPTIONS "-DLINUX -D_FILE_OFFSET_BITS=64")
endif(MSVC)
if(CYGWIN)
  set(GKlib_COPTIONS "${GKlib_COPTIONS} -DCYGWIN")
endif(CYGWIN)
if(CMAKE_COMPILER_IS_GNUCC)
# GCC opts.
  set(GKlib_COPTIONS "${GKlib_COPTIONS} -std=c99 -fno-strict-aliasing")
  if(NOT MINGW)
      set(GKlib_COPTIONS "${GKlib_COPTIONS} -fPIC")
  endif(NOT MINGW)
# GCC warnings.
  set(GKlib_COPTIONS "${GKlib_COPTIONS} -Wall -pedantic -Wno-unused-but-set-variable -Wno-unused-variable -Wno-unknown-pragmas")
elseif(${CMAKE_C_COMPILER_ID} MATCHES "Sun")
# Sun insists on -xc99.
  set(GKlib_COPTIONS "${GKlib_COPTIONS} -xc99")
endif(CMAKE_COMPILER_IS_GNUCC)

# Check for features.
check_include_file(execinfo.h HAVE_EXECINFO_H)
if(HAVE_EXECINFO_H)
  set(GKlib_COPTIONS "${GKlib_COPTIONS} -DHAVE_EXECINFO_H")
endif(HAVE_EXECINFO_H)

check_function_exists(getline HAVE_GETLINE)
if(HAVE_GETLINE)
  set(GKlib_COPTIONS "${GKlib_COPTIONS} -DHAVE_GETLINE")
endif(HAVE_GETLINE)

# Finally set the official C flags.
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${GKlib_COPTIONS} ${GKlib_COPTS}")

# Find GKlib sources.
file(GLOB GKlib_sources ${GKLIB_PATH}/*.c)
file(GLOB GKlib_includes ${GKLIB_PATH}/*.h)
