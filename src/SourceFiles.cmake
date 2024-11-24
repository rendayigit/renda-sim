set(SOURCEFILES
    ${CMAKE_CURRENT_LIST_DIR}/../src/main.cpp
    # UI Source Files
    ${CMAKE_CURRENT_LIST_DIR}/../ui/mainWindow.cpp
    # Common Source Files
    ${CMAKE_CURRENT_LIST_DIR}/../src/common/load/load.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/common/load/loadState.cpp
    # Service Source Files
    ${CMAKE_CURRENT_LIST_DIR}/../src/services/eventManager/eventManager.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/services/json/json.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/services/logger/logger.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/services/network/client/client.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/services/network/server/server.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/services/scheduler/scheduler.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/services/timer/timer.cpp
    # Model Source Files
    ${CMAKE_CURRENT_LIST_DIR}/../src/models/pcs/pcs.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/models/sampleModel/sampleModel.cpp)

set(INCLUDEDIRS
    ${CMAKE_CURRENT_LIST_DIR}/../
    ${CMAKE_CURRENT_LIST_DIR}/../src/
    ${CMAKE_CURRENT_LIST_DIR}/../src/models/
    ${CMAKE_CURRENT_LIST_DIR}/../deps/wxWidgets/include
    ${CMAKE_CURRENT_LIST_DIR}/../deps/wxWidgets/lib/wx/include/gtk3-unicode-3.2)
