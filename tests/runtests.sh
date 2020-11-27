#!/bin/sh
# Script to run tests
#
# Version: 20201121

if test -f ${PWD}/libfsclfs/.libs/libfsclfs.1.dylib && test -f ./pyfsclfs/.libs/pyfsclfs.so;
then
	install_name_tool -change /usr/local/lib/libfsclfs.1.dylib ${PWD}/libfsclfs/.libs/libfsclfs.1.dylib ./pyfsclfs/.libs/pyfsclfs.so;
fi

make check CHECK_WITH_STDERR=1;
RESULT=$?;

if test ${RESULT} -ne 0 && test -f tests/test-suite.log;
then
	cat tests/test-suite.log;
fi
exit ${RESULT};

