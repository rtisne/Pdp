cmake_minimum_required(VERSION 3.0)


project(Unit_test)
find_package( OpenCV REQUIRED )

set(SRCS
    main.cpp
     ../server/BoundingBox.cpp
     ../server/ConnectedComponent.cpp
     ../server/Font.cpp
     ../server/Character.cpp
     ../server/Line.cpp
     ../server/Image.cpp
     ../server/Session.cpp
     ../server/Binarization.cpp
    )
    
set(HEADERS
     ../server/BoundingBox.hpp
     ../server/ConnectedComponent.hpp
     ../server/Font.hpp
     ../server/Character.hpp
     ../server/Line.hpp
     ../server/Image.hpp
     ../server/Session.hpp
     ../server/Binarization.hpp
    )

add_executable(Unit_test ${SRCS} ${HEADERS})
target_link_libraries( Unit_test ${OpenCV_LIBS} )

