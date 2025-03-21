set(TESTFILES
    # Engine Source Files
    ${CMAKE_CURRENT_LIST_DIR}/../src/eventManager/eventManager.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/logger/logger.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/scheduler/scheduler.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/messaging/commanding.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/messaging/commandParser.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/messaging/publisher.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/model/model.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/model/modelContainer.cpp
    # Engine Test Files
    ${CMAKE_CURRENT_LIST_DIR}/../test/eventManagerTest.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../test/fileOperationsTest.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../test/schedulerTest.cpp)

set(INCLUDEDIRS
    ${CMAKE_CURRENT_LIST_DIR}/../src/ ${CMAKE_CURRENT_LIST_DIR}/../src/models/
    ${CMAKE_CURRENT_LIST_DIR}/../test/)
