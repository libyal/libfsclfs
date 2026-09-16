#!/bin/sh
# Script to run tests
#
# Version: 20260714

if [ -f "${PWD}/libfsclfs/.libs/libfsclfs.1.dylib" ] && [ -f ./pyfsclfs/.libs/pyfsclfs.so ]
then
    install_name_tool -change /usr/local/lib/libfsclfs.1.dylib "${PWD}/libfsclfs/.libs/libfsclfs.1.dylib" ./pyfsclfs/.libs/pyfsclfs.so
fi

make check-build > /dev/null

# shellcheck disable=SC2068
make check $@
RESULT=$?

if [ ${RESULT} -ne 0 ]
then
    find . -name \*.log -path \*.dir/\*/\*.log -print -exec cat {} \;
fi
exit ${RESULT}

