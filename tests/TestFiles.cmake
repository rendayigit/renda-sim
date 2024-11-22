set(TESTFILES
    ${CMAKE_SOURCE_DIR}/src/services/scheduler/scheduler.cpp
    ${CMAKE_SOURCE_DIR}/src/services/eventManager/eventManager.cpp
    ${CMAKE_SOURCE_DIR}/src/services/logger/logger.cpp
    ${CMAKE_SOURCE_DIR}/src/services/network/client/client.cpp
    ${CMAKE_SOURCE_DIR}/src/services/network/server/server.cpp
    ${CMAKE_SOURCE_DIR}/src/pcs/pcs.cpp
    ${CMAKE_SOURCE_DIR}/src/services/json/json.cpp
    ${CMAKE_SOURCE_DIR}/tests/services/json/jsonTest.cpp
    ${CMAKE_SOURCE_DIR}/tests/sampleTest.cpp
    ${CMAKE_SOURCE_DIR}/tests/eventManagerTest.cpp)

set(INCLUDEDIRS
    ${CMAKE_SOURCE_DIR}/src/)
