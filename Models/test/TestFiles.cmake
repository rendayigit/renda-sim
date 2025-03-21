set(TESTFILES
    # Common Source Files
    ${CMAKE_CURRENT_LIST_DIR}/../src/common/load/load.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/common/load/loadState.cpp
    # Model Source Files
    ${CMAKE_CURRENT_LIST_DIR}/../src/pcs/pcs.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/sampleModel/sampleModel.cpp
    # Model Test Files
    ${CMAKE_CURRENT_LIST_DIR}/../test/common/loadTest.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../test/common/dataFlowTest.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../test/common/failureTest.cpp
    # TODO(renda): Add PCS test ${CMAKE_CURRENT_LIST_DIR}/../test/pcsTest.cpp
)

set(INCLUDEDIRS
    ${CMAKE_CURRENT_LIST_DIR}/../src/
    ${CMAKE_CURRENT_LIST_DIR}/../../Engine/src/ # TODO: should not need this
    ${CMAKE_CURRENT_LIST_DIR}/../../Engine/include/ ${CMAKE_CURRENT_LIST_DIR}/)
