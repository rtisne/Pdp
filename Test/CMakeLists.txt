cmake_minimum_required(VERSION 3.0)
set (CMAKE_CXX_STANDARD 11)

project(Unit_test)
find_package( OpenCV REQUIRED )

set(SRCS
    main.cpp
     ../server/src/ConnectedComponent.cpp
     ../server/src/Font.cpp
     ../server/src/Character.cpp
     ../server/src/Line.cpp
     ../server/src/Image.cpp
     ../server/src/Session.cpp
     ../server/src/Binarization.cpp
    )
    
set(HEADERS
     ../server/headers/json.hpp
     ../server/headers/ConnectedComponent.hpp
     ../server/headers/Font.hpp
     ../server/headers/Character.hpp
     ../server/headers/Line.hpp
     ../server/headers/Image.hpp
     ../server/headers/Session.hpp
     ../server/headers/Binarization.hpp
    )

add_executable(Unit_test ${SRCS} ${HEADERS})
target_link_libraries( Unit_test ${OpenCV_LIBS} )

