set(TESTFILES
    # Common Source Files
    ${CMAKE_CURRENT_LIST_DIR}/../src/common/load/load.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/common/load/loadState.cpp
    # Service Source Files
    ${CMAKE_CURRENT_LIST_DIR}/../src/services/fileOperations/fileOperations.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/services/eventManager/eventManager.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/services/json/json.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/services/logger/logger.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/services/network/client/client.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/services/network/server/server.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/services/scheduler/scheduler.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/services/timer/timer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/services/messaging/messaging.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/services/messaging/messageParser.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/services/model/model.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/services/model/modelContainer.cpp
    # Model Source Files
    ${CMAKE_CURRENT_LIST_DIR}/../src/models/pcs/pcs.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/models/sampleModel/sampleModel.cpp
    # Common Test Files
    ${CMAKE_CURRENT_LIST_DIR}/../tests/common/loadTest.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../tests/common/dataFlowTest.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../tests/common/failureTest.cpp
    # Service Test Files
    ${CMAKE_CURRENT_LIST_DIR}/../tests/services/network/networkTest.cpp
    # ${CMAKE_CURRENT_LIST_DIR}/../tests/services/eventManagerTest.cpp      # TODO(renda): Fix tests
    ${CMAKE_CURRENT_LIST_DIR}/../tests/services/fileOperationsTest.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../tests/services/jsonTest.cpp
    # ${CMAKE_CURRENT_LIST_DIR}/../tests/services/loggerTest.cpp
    # ${CMAKE_CURRENT_LIST_DIR}/../tests/services/schedulerTest.cpp         # TODO(renda): Fix tests
    # Model Test Files ${CMAKE_CURRENT_LIST_DIR}/../tests/models/pcsTest.cpp
    # TODO(renda): Add test
)

set(INCLUDEDIRS
    ${CMAKE_CURRENT_LIST_DIR}/../src/ ${CMAKE_CURRENT_LIST_DIR}/../src/models/
    ${CMAKE_CURRENT_LIST_DIR}/../tests/ ${CMAKE_SOURCE_DIR}/deps/cppzmq-4.10.0)
