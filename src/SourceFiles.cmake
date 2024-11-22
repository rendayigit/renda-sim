set(SOURCEFILES
    ${CMAKE_SOURCE_DIR}/src/main.cpp
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
    ${CMAKE_SOURCE_DIR}/src/models/sampleModel/sampleModel.cpp)

set(INCLUDEDIRS
    ${CMAKE_SOURCE_DIR}/src/
    ${CMAKE_SOURCE_DIR}/src/models/)
