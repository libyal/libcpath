#!/bin/sh
# Script to run tests
#
# Version: 20201121

if test -f ${PWD}/libcpath/.libs/libcpath.1.dylib && test -f ./pycpath/.libs/pycpath.so;
then
	install_name_tool -change /usr/local/lib/libcpath.1.dylib ${PWD}/libcpath/.libs/libcpath.1.dylib ./pycpath/.libs/pycpath.so;
fi

make check CHECK_WITH_STDERR=1;
RESULT=$?;

if test ${RESULT} -ne 0 && test -f tests/test-suite.log;
then
	cat tests/test-suite.log;
fi
exit ${RESULT};

