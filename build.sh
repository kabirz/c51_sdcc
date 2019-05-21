prebuild() {
    mkdir -p $1
    pushd $1
    if test "$2" = "ninja"
    then
        GEN="Ninja"
    else
        GEN="Unix Makefiles"
    fi
    cmake -DCMAKE_TOOLCHAIN_FILE=cmake/compiler.cmake -G"$GEN" .. 
    export TARGET=$1
    popd
}

build() {
    cmake --build  $TARGET
}

postbuild() {
    rm -fr $TARGET
}