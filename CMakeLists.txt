cmake_minimum_required(VERSION 2.8)
project(SCGB)
set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/cpp)
set(DEMO_DIR ${SOURCE_DIR}/demo)
set(INCLUDE_DIRS
  "${CMAKE_SOURCE_DIR}/class"
  "${CMAKE_SOURCE_DIR}/lib"
  )
# I don't think glob is that bad guy...
# You just need to touch it every time.
file(GLOB SCGB_SOURCES ${SOURCE_DIR}/*.cpp)
include_directories(${INCLUDE_DIRS})

# Library
add_library(scgb "${SCGB_SOURCES}")
# Demo program
add_executable(demo "${DEMO_DIR}/main.cpp")
target_link_libraries(demo scgb)

# Choose actual curses implementation.
set(USE_NCURSES "ON" CACHE BOOL "ON to use ncurses, OFF to use pdcurses.")
if(USE_NCURSES)
  find_library(NCURSESW_LIB ncursesw)
  target_link_libraries(demo ${NCURSESW_LIB})
else()
  find_library(PDCURSES_LIB pdcurses HINT "${CMAKE_SOURCE_DIR}/lib")
  # When you want to use pdcurses, put the lib in {SOURCE}/lib.
  # Also, put curses.h at the same directory as pdcurses.
  if(NOT PDCURSES_LIB)
    message("Fatal error: PDCurses not found.")
  endif()
  if(UNIX)
    # In Unix like OS, I assume pdcurses uses X11
    # and static library's extension is .a.
    find_package(X11 REQUIRED)
    find_library(Xaw_LIB Xaw)
    find_library(Xpm_LIB Xpm)
    target_link_libraries(demo
      ${X11_LIBRARIES}
      ${X11_ICE_LIB}
      ${X11_Xt_LIB}
      ${X11_Xmu_LIB}
      ${X11_SM_LIB}
      ${Xaw_LIB}
      ${Xpm_LIB}
      )
    add_definitions(-DXCURSES)
  elseif(WIN32)
    
  endif()
  add_definitions(-DPDC_WIDE)
  target_link_libraries(scgb ${PDCURSES_LIB})
endif()

add_custom_command(
  TARGET demo
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy
  $<TARGET_FILE_NAME:demo> ${CMAKE_SOURCE_DIR} 
  )
