#find libLLVM and some of its dependencies
libLLVM=`ldd $1|grep libLLVM|sed "s/.*=> \([^( ]*\).*/\1/"`
libz3=`ldd $libLLVM|grep libz3|sed "s/.*=> \([^( ]*\).*/\1/"`
libedit=`ldd $libLLVM|grep libedit|sed "s/.*=> \([^( ]*\).*/\1/"`
libbsd=`ldd $libLLVM|grep libbsd|sed "s/.*=> \([^( ]*\).*/\1/"`
echo $libLLVM $libz3 $libedit $libbsd
