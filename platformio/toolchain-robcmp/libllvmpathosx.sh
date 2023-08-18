#find libLLVM and some of its dependencies in OSX
libLLVM=`DYLD_PRINT_LIBRARIES=1 $1 -v 2>&1|grep libLLVM|sed "s/.*> //"`
libz3=`DYLD_PRINT_LIBRARIES=1 $1 -v 2>&1|grep libz3|sed "s/.*> //"`
libzstd=`DYLD_PRINT_LIBRARIES=1 $1 -v 2>&1|grep libzstd|sed "s/.*> //"`
echo $libLLVM $libz3 $libzstd
