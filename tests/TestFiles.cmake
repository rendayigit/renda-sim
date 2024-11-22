set(TESTFILES
    # Common Source Files
    ${CMAKE_SOURCE_DIR}/src/common/load/load.cpp
    ${CMAKE_SOURCE_DIR}/src/common/load/loadState.cpp
    # Service Source Files
    ${CMAKE_SOURCE_DIR}/src/services/eventManager/eventManager.cpp
    ${CMAKE_SOURCE_DIR}/src/services/json/json.cpp
    ${CMAKE_SOURCE_DIR}/src/services/logger/logger.cpp
    ${CMAKE_SOURCE_DIR}/src/services/network/client/client.cpp
    ${CMAKE_SOURCE_DIR}/src/services/network/server/server.cpp
    ${CMAKE_SOURCE_DIR}/src/services/scheduler/scheduler.cpp
    # Model Source Files
    ${CMAKE_SOURCE_DIR}/src/models/pcs/pcs.cpp
    ${CMAKE_SOURCE_DIR}/src/models/sampleModel/sampleModel.cpp
    # Common Test Files
    ${CMAKE_SOURCE_DIR}/tests/common/loadTest.cpp
    ${CMAKE_SOURCE_DIR}/tests/common/dataFlowTest.cpp
    ${CMAKE_SOURCE_DIR}/tests/common/failureTest.cpp
    # Service Test Files
    ${CMAKE_SOURCE_DIR}/tests/services/eventManagerTest.cpp
    ${CMAKE_SOURCE_DIR}/tests/services/simpleEventTest.cpp
    ${CMAKE_SOURCE_DIR}/tests/services/jsonTest.cpp
    ${CMAKE_SOURCE_DIR}/tests/services/loggerTest.cpp
    ${CMAKE_SOURCE_DIR}/tests/services/fileOperationsTest.cpp
    # Model Test Files
    # ${CMAKE_SOURCE_DIR}/tests/models/pcsTest.cpp
    )

set(INCLUDEDIRS
    ${CMAKE_SOURCE_DIR}/src/
    ${CMAKE_SOURCE_DIR}/src/models/
    ${CMAKE_SOURCE_DIR}/tests/)
