#!/bin/sh
# Script to run tests
#
# Version: 20260609

if test -f ${PWD}/libcpath/.libs/libcpath.1.dylib && test -f ./pycpath/.libs/pycpath.so
then
	install_name_tool -change /usr/local/lib/libcpath.1.dylib ${PWD}/libcpath/.libs/libcpath.1.dylib ./pycpath/.libs/pycpath.so
fi

make check-build > /dev/null

make check $@
RESULT=$?

if test ${RESULT} -ne 0
then
	find . -name \*.log -path \*.dir/\*/\*.log -print -exec cat {} \;
fi
exit ${RESULT}

