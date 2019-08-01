add_library(BcfPass MODULE
    BogusControlFlow.cpp
    CryptoUtils.cpp
    Utils.cpp
)

# Use C++11 to compile the pass(i.e., supply -std=c++11).
target_compile_features(BcfPass PRIVATE cxx_range_for cxx_auto_type)

# LLVM is (typically) built with no C++ RTTI. We need to match that;
# otherwise, we'll get linker errors about missing RTTI data.
set_target_properties(BcfPass PROPERTIES
    COMPILE_FLAGS "-fno-rtti"
)

# Get proper shared-library
# resolved when the shared library is linked) on OS X.
if(APPLE)
    set_target_properties(BcfPass PROPERTIES
        LINK_FLAGS "-undefined dynamic_lookup"
    )
endif(APPLE)
