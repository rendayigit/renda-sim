set(SOURCEFILES
    ${CMAKE_CURRENT_LIST_DIR}/../src/engine/main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/models/root.cpp
    # Common Source Files
    ${CMAKE_CURRENT_LIST_DIR}/../src/models/common/load/load.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/models/common/load/loadState.cpp
    # Engine Source Files
    ${CMAKE_CURRENT_LIST_DIR}/../src/engine/eventManager/eventManager.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/engine/fileOperations/fileOperations.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/engine/json/json.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/engine/logger/logger.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/engine/network/client/client.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/engine/network/server/server.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/engine/scheduler/scheduler.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/engine/timer/timer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/engine/messaging/messaging.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/engine/messaging/messageParser.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/engine/model/model.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/engine/model/modelContainer.cpp
    # Model Source Files
    ${CMAKE_CURRENT_LIST_DIR}/../src/models/pcs/pcs.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/models/sampleModel/sampleModel.cpp)

set(INCLUDEDIRS
    ${CMAKE_CURRENT_LIST_DIR}/../ ${CMAKE_CURRENT_LIST_DIR}/../src/
    ${CMAKE_CURRENT_LIST_DIR}/../src/models/
    ${CMAKE_SOURCE_DIR}/deps/cppzmq-4.10.0)
