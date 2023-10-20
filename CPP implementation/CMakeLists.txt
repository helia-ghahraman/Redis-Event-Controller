
cmake_minimum_required( VERSION 3.1 )
project( XBOX_manager )

set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread" )


add_executable( client client.cpp )
add_executable( server server.cpp )

# ----- start adding hiredis -----
find_path( HIREDIS_HEADER hiredis )
target_include_directories( server PUBLIC ${HIREDIS_HEADER} )
target_include_directories( client PUBLIC ${HIREDIS_HEADER} )
find_library( HIREDIS_LIB hiredis )
target_link_libraries( server ${HIREDIS_LIB} )
target_link_libraries( client ${HIREDIS_LIB} )
# ----- end adding hiredis -----

# ----- start adding redisHelper-plus-plus -----
find_path( REDIS_PLUS_PLUS_HEADER sw )
target_include_directories( server PUBLIC ${REDIS_PLUS_PLUS_HEADER} )
target_include_directories( client PUBLIC ${REDIS_PLUS_PLUS_HEADER} )

find_library( REDIS_PLUS_PLUS_LIB redis++ )
target_link_libraries( server ${REDIS_PLUS_PLUS_LIB} )
target_link_libraries( client ${REDIS_PLUS_PLUS_LIB} )
# ----- end adding redisHelper-plus-plus -----
