set(TESTFILES
    # Engine Source Files
    ${CMAKE_CURRENT_LIST_DIR}/../src/eventManager/eventManager.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/logger/logger.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/scheduler/scheduler.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/timer/timer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/messaging/messaging.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/messaging/messageParser.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/model/model.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/model/modelContainer.cpp
    # Engine Test Files
    ${CMAKE_CURRENT_LIST_DIR}/../tests/eventManagerTest.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../tests/fileOperationsTest.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../tests/schedulerTest.cpp)

set(INCLUDEDIRS
    ${CMAKE_CURRENT_LIST_DIR}/../src/ ${CMAKE_CURRENT_LIST_DIR}/../src/models/
    ${CMAKE_CURRENT_LIST_DIR}/../tests/)
