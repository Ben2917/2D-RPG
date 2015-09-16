
# find all of the .cpp and .h files and add their names to a list
# of all of the files in the directory to compile.

file(GLOB SRCS lua/*.c lua/*.h lua/*.hpp *.cpp *.h)

# Now define the target executable and add the files to it.

set(BIN_DIR ${game_project_SOURCE_DIR}/bin)

add_executable( game ${SRCS})

target_link_libraries(game ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY})

install(TARGETS game RUNTIME DESTINATION ${BIN_DIR})

