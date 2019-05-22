prebuild() {
    mkdir -p $1
    pushd $1
    if test "$2" = "ninja"
    then
        GEN="Ninja"
    elif test "$2" = "ON"
    then
        export VERBOSE_MAKEFILE="ON"
        GEN="Unix Makefiles"
    else
        GEN="Unix Makefiles"
    fi
    if test "$VERBOSE_MAKEFILE" = "ON"
    then
        cmake -DCMAKE_TOOLCHAIN_FILE=cmake/compiler.cmake -G"$GEN" -DCMAKE_VERBOSE_MAKEFILE=ON .. 
    else
        cmake -DCMAKE_TOOLCHAIN_FILE=cmake/compiler.cmake -G"$GEN" .. 
    fi
    export TARGET=$1
    popd
}

build() {
    if test "$TARGET" = ""
    then
        echo "Please prebuild project"
    else
        cmake --build  $TARGET
    fi
}

postbuild() {
    rm -fr $TARGET
    unset TARGET
    unset VERBOSE
}