set(TESTFILES
    # Common Source Files
    ${CMAKE_CURRENT_LIST_DIR}/../src/models/common/load/load.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/models/common/load/loadState.cpp
    # Engine Source Files
    ${CMAKE_CURRENT_LIST_DIR}/../src/engine/eventManager/eventManager.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/engine/logger/logger.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/engine/scheduler/scheduler.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/engine/timer/timer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/engine/messaging/messaging.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/engine/messaging/messageParser.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/engine/model/model.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/engine/model/modelContainer.cpp
    # Model Source Files
    ${CMAKE_CURRENT_LIST_DIR}/../src/models/pcs/pcs.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/models/sampleModel/sampleModel.cpp
    # Common Test Files
    ${CMAKE_CURRENT_LIST_DIR}/../tests/models/common/loadTest.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../tests/models/common/dataFlowTest.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../tests/models/common/failureTest.cpp
    # Engine Test Files
    ${CMAKE_CURRENT_LIST_DIR}/../tests/engine/network/networkTest.cpp
    # ${CMAKE_CURRENT_LIST_DIR}/../tests/engine/eventManagerTest.cpp
    # TODO(renda): Fix tests
    ${CMAKE_CURRENT_LIST_DIR}/../tests/engine/fileOperationsTest.cpp
    # ${CMAKE_CURRENT_LIST_DIR}/../tests/engine/loggerTest.cpp
    # ${CMAKE_CURRENT_LIST_DIR}/../tests/engine/schedulerTest.cpp
    # TODO(renda): Fix tests Model Test Files
    # ${CMAKE_CURRENT_LIST_DIR}/../tests/models/pcsTest.cpp
    # TODO(renda): Add test
)

set(INCLUDEDIRS
    ${CMAKE_CURRENT_LIST_DIR}/../src/ ${CMAKE_CURRENT_LIST_DIR}/../src/models/
    ${CMAKE_CURRENT_LIST_DIR}/../tests/ ${CMAKE_SOURCE_DIR}/deps/cppzmq-4.10.0)
