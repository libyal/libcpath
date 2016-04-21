#!/bin/bash
# Library path testing script
#
# Version: 20160420

EXIT_SUCCESS=0;
EXIT_FAILURE=1;
EXIT_IGNORE=77;

TEST_PREFIX=`dirname ${PWD}`;
TEST_PREFIX=`basename ${TEST_PREFIX} | sed 's/^lib\([^-]*\)/\1/'`;

TEST_PROFILE="lib${TEST_PREFIX}";
TEST_DESCRIPTION="path";
OPTION_SETS="";

TEST_TOOL_DIRECTORY=".";
TEST_TOOL="${TEST_PREFIX}_test_path";

run_test()
{ 
	local TEST_EXECUTABLE=$1;
	local FILENAME=$2;
	local FULLPATH=$3;

	local TMPDIR="tmp$$";

	rm -rf ${TMPDIR};
	mkdir ${TMPDIR};

	echo -n ${FULLPATH} > ${TMPDIR}/input;

	run_test_with_arguments "${TEST_EXECUTABLE}" ${FILENAME} > ${TMPDIR}/output;
	local RESULT=$?;

	if test ${RESULT} -eq ${EXIT_SUCCESS};
	then
		if ! cmp -s ${TMPDIR}/input ${TMPDIR}/output;
		then
			RESULT=${EXIT_FAILURE};
		fi
	fi

	rm -rf ${TMPDIR};

	echo -n "Testing full path: ${FILENAME} ";

	if test ${RESULT} -ne ${EXIT_SUCCESS};
	then
		echo " (FAIL)";
	else
		echo " (PASS)";
	fi
	return ${RESULT};
}

test_path()
{
	local TEST_EXECUTABLE=$1;

	local RESULT=${EXIT_IGNORE};

	# Note that not all version of uname support the -o option
	# so we cannot use: `uname -o` = "Msys"
	UNAME=`uname -s | sed 's/-[^-]*$//'`;

	if test ${UNAME} = "MINGW32_NT";
	then
		WINPWD=`pwd -W | tr '/' '\\'`;
		DRIVE=`echo ${WINPWD} | cut -c 1`;

		run_test "${TEST_EXECUTABLE}" "user\\test.txt" "\\\\?\\${WINPWD}\\user\\test.txt";
		RESULT=$?;

		if test ${RESULT} -ne ${EXIT_SUCCESS};
		then
			return ${RESULT};
		fi
		RESULT=$?;

		if test ${RESULT} -ne ${EXIT_SUCCESS};
		then
			return ${RESULT};
		fi

		run_test "${TEST_EXECUTABLE}" "username\\..\\user\\test.txt" "\\\\?\\${WINPWD}\\user\\test.txt";
		RESULT=$?;

		if test ${RESULT} -ne ${EXIT_SUCCESS};
		then
			return ${RESULT};
		fi

		run_test "${TEST_EXECUTABLE}" "\\home\\user\\test.txt" "\\\\?\\${DRIVE}:\\home\\user\\test.txt";
		RESULT=$?;

		if test ${RESULT} -ne ${EXIT_SUCCESS};
		then
			return ${RESULT};
		fi

		run_test "${TEST_EXECUTABLE}" "c:\\home\\user\\test.txt" "\\\\?\\c:\\home\\user\\test.txt";
		RESULT=$?;

		if test ${RESULT} -ne ${EXIT_SUCCESS};
		then
			return ${RESULT};
		fi

		run_test "${TEST_EXECUTABLE}" "c:\\home\\user\\\\test.txt" "\\\\?\\c:\\home\\user\\test.txt";
		RESULT=$?;

		if test ${RESULT} -ne ${EXIT_SUCCESS};
		then
			return ${RESULT};
		fi

		run_test "${TEST_EXECUTABLE}" "c:\\home\\username\\..\\user\\test.txt" "\\\\?\\c:\\home\\user\\test.txt";
		RESULT=$?;

		if test ${RESULT} -ne ${EXIT_SUCCESS};
		then
			return ${RESULT};
		fi

		run_test "${TEST_EXECUTABLE}" "c:\\..\\home\\user\\test.txt" "\\\\?\\c:\\home\\user\\test.txt";
		RESULT=$?;

		if test ${RESULT} -ne ${EXIT_SUCCESS};
		then
			return ${RESULT};
		fi

		run_test "${TEST_EXECUTABLE}" "c:\\..\\home\\username\\..\\user\\test.txt" "\\\\?\\c:\\home\\user\\test.txt";
		RESULT=$?;

		if test ${RESULT} -ne ${EXIT_SUCCESS};
		then
			return ${RESULT};
		fi

		run_test "${TEST_EXECUTABLE}" "\\\\.\\PhysicalDrive0" "\\\\.\\PhysicalDrive0";
		RESULT=$?;

		if test ${RESULT} -ne ${EXIT_SUCCESS};
		then
			return ${RESULT};
		fi

		run_test "${TEST_EXECUTABLE}" "\\\\?\\Volume{4c1b02c4-d990-11dc-99ae-806e6f6e6963}" "\\\\?\\Volume{4c1b02c4-d990-11dc-99ae-806e6f6e6963}";
		RESULT=$?;

		if test ${RESULT} -ne ${EXIT_SUCCESS};
		then
			return ${RESULT};
		fi

		run_test "${TEST_EXECUTABLE}" "\\\\172.0.0.1\\C$\\test.txt" "\\\\?\\UNC\\172.0.0.1\\C$\\test.txt";
		RESULT=$?;

		if test ${RESULT} -ne ${EXIT_SUCCESS};
		then
			return ${RESULT};
		fi

		run_test "${TEST_EXECUTABLE}" "\\\\?\\UNC\\172.0.0.1\\C$\\test.txt" "\\\\?\\UNC\\172.0.0.1\\C$\\test.txt";
		RESULT=$?;

		if test ${RESULT} -ne ${EXIT_SUCCESS};
		then
			return ${RESULT};
		fi
	else
		run_test "${TEST_EXECUTABLE}" "user/test.txt" "${PWD}/user/test.txt";
		RESULT=$?;

		if test ${RESULT} -ne ${EXIT_SUCCESS};
		then
			return ${RESULT};
		fi

		run_test "${TEST_EXECUTABLE}" "username/../user/test.txt" "${PWD}/user/test.txt";
		RESULT=$?;

		if test ${RESULT} -ne ${EXIT_SUCCESS};
		then
			return ${RESULT};
		fi

		run_test "${TEST_EXECUTABLE}" "/home/user/test.txt" "/home/user/test.txt";
		RESULT=$?;

		if test ${RESULT} -ne ${EXIT_SUCCESS};
		then
			return ${RESULT};
		fi

		run_test "${TEST_EXECUTABLE}" "/home/user//test.txt" "/home/user/test.txt";
		RESULT=$?;

		if test ${RESULT} -ne ${EXIT_SUCCESS};
		then
			return ${RESULT};
		fi

		run_test "${TEST_EXECUTABLE}" "/home/username/../user/test.txt" "/home/user/test.txt";
		RESULT=$?;

		if test ${RESULT} -ne ${EXIT_SUCCESS};
		then
			return ${RESULT};
		fi

		run_test "${TEST_EXECUTABLE}" "/../home/user/test.txt" "/home/user/test.txt";
		RESULT=$?;

		if test ${RESULT} -ne ${EXIT_SUCCESS};
		then
			return ${RESULT};
		fi

		run_test "${TEST_EXECUTABLE}" "/../home/username/../user/test.txt" "/home/user/test.txt";
		RESULT=$?;

		if test ${RESULT} -ne ${EXIT_SUCCESS};
		then
			return ${RESULT};
		fi
	fi
	return ${EXIT_SUCCESS};
}

if ! test -z ${SKIP_LIBRARY_TESTS};
then
	exit ${EXIT_IGNORE};
fi

TEST_EXECUTABLE="${TEST_TOOL_DIRECTORY}/${TEST_TOOL}";

if ! test -x "${TEST_EXECUTABLE}";
then
	TEST_EXECUTABLE="${TEST_TOOL_DIRECTORY}/${TEST_TOOL}.exe";
fi

if ! test -x "${TEST_EXECUTABLE}";
then
	echo "Missing test executable: ${TEST_EXECUTABLE}";

	exit ${EXIT_FAILURE};
fi

TEST_RUNNER="tests/test_runner.sh";

if ! test -f "${TEST_RUNNER}";
then
	TEST_RUNNER="./test_runner.sh";
fi

if ! test -f "${TEST_RUNNER}";
then
	echo "Missing test runner: ${TEST_RUNNER}";

	exit ${EXIT_FAILURE};
fi

source ${TEST_RUNNER};

assert_availability_binary cmp;

test_path;
RESULT=$1;

exit ${RESULT};

