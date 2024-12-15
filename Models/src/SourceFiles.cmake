set(SOURCEFILES
    ${CMAKE_CURRENT_LIST_DIR}/root.cpp
    # Common Source Files
    ${CMAKE_CURRENT_LIST_DIR}/common/load/load.cpp
    ${CMAKE_CURRENT_LIST_DIR}/common/load/loadState.cpp
    # Model Source Files
    ${CMAKE_CURRENT_LIST_DIR}/pcs/pcs.cpp
    ${CMAKE_CURRENT_LIST_DIR}/sampleModel/sampleModel.cpp)

set(INCLUDEDIRS ${CMAKE_CURRENT_LIST_DIR}/
                ${CMAKE_CURRENT_LIST_DIR}/../../Engine/include/)
