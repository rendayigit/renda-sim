set(SOURCEFILES
    # Engine Source Files
    # ${CMAKE_CURRENT_LIST_DIR}/eventManager/eventManager.cpp
    ${CMAKE_CURRENT_LIST_DIR}/logger/logger.cpp
    ${CMAKE_CURRENT_LIST_DIR}/scheduler/scheduler.cpp
    ${CMAKE_CURRENT_LIST_DIR}/timer/timer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/messaging/commanding.cpp
    ${CMAKE_CURRENT_LIST_DIR}/messaging/commandParser.cpp
    ${CMAKE_CURRENT_LIST_DIR}/messaging/publisher.cpp
    ${CMAKE_CURRENT_LIST_DIR}/model/model.cpp
    ${CMAKE_CURRENT_LIST_DIR}/model/modelContainer.cpp)

set(INCLUDEDIRS ${CMAKE_CURRENT_LIST_DIR}/
                ${CMAKE_CURRENT_LIST_DIR}/../deps/cppzmq-4.10.0)
