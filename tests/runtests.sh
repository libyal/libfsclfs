#!/bin/sh
# Script to run tests
#
# Version: 20260609

if test -f ${PWD}/libfsclfs/.libs/libfsclfs.1.dylib && test -f ./pyfsclfs/.libs/pyfsclfs.so
then
	install_name_tool -change /usr/local/lib/libfsclfs.1.dylib ${PWD}/libfsclfs/.libs/libfsclfs.1.dylib ./pyfsclfs/.libs/pyfsclfs.so
fi

make check-build > /dev/null

make check $@
RESULT=$?

if test ${RESULT} -ne 0
then
	find . -name \*.log -path \*.dir/\*/\*.log -print -exec cat {} \;
fi
exit ${RESULT}

