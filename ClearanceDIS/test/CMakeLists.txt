# Standalone tests for the ClearanceDIS module. Uses only <cassert>
# so there's no third-party test-framework dependency to vendor -
# minimises supply-chain surface for the CI job. - TripleA

add_executable(clearance_dis_selftest
    test_wire_format.cpp
)

target_link_libraries(clearance_dis_selftest
    PRIVATE ClearanceDIS
)

# Registers with ctest so `ctest --output-on-failure` runs it in CI.
# Non-zero exit code = test failed. - TripleA
add_test(
    NAME ClearanceDIS.WireFormat
    COMMAND clearance_dis_selftest
)
