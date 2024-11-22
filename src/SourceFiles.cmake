set(SOURCEFILES
    # Model Source Files
    ${CMAKE_SOURCE_DIR}/src/main.cpp
    ${CMAKE_SOURCE_DIR}/src/services/scheduler/scheduler.cpp
    ${CMAKE_SOURCE_DIR}/src/services/eventManager/eventManager.cpp
    ${CMAKE_SOURCE_DIR}/src/services/logger/logger.cpp
    ${CMAKE_SOURCE_DIR}/src/services/json/json.cpp
    ${CMAKE_SOURCE_DIR}/src/services/network/client/client.cpp
    ${CMAKE_SOURCE_DIR}/src/services/network/server/server.cpp
    ${CMAKE_SOURCE_DIR}/src/pcs/pcs.cpp
    ${CMAKE_SOURCE_DIR}/src/sampleModel/sampleModel.cpp)

set(INCLUDEDIRS
    ${CMAKE_SOURCE_DIR}/src/)
