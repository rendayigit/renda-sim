# TODO(renda): Fix tests
set(TESTFILES
    # Common Source Files
    ${CMAKE_CURRENT_LIST_DIR}/../src/common/load/load.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/common/load/loadState.cpp
    # Model Source Files
    ${CMAKE_CURRENT_LIST_DIR}/../src/pcs/pcs.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/sampleModel/sampleModel.cpp
    # Common Test Files
    ${CMAKE_CURRENT_LIST_DIR}/../tests/common/loadTest.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../tests/common/dataFlowTest.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../tests/common/failureTest.cpp
    # TODO(renda): Add PCS test ${CMAKE_CURRENT_LIST_DIR}/../tests/pcsTest.cpp
)

set(INCLUDEDIRS
    ${CMAKE_CURRENT_LIST_DIR}/../src/
    ${CMAKE_CURRENT_LIST_DIR}/../../Engine/src/ # TODO: should not need this
    ${CMAKE_CURRENT_LIST_DIR}/../../Engine/include/
    ${CMAKE_CURRENT_LIST_DIR}/
    ${CMAKE_SOURCE_DIR}/deps/cppzmq-4.10.0)
