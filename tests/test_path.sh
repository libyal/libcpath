#!/bin/bash
#
# Basic File IO (CPATH) library path testing script
#
# Copyright (c) 2008-2014, Joachim Metz <joachim.metz@gmail.com>
#
# Refer to AUTHORS for acknowledgements.
#
# This software is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This software is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this software.  If not, see <http://www.gnu.org/licenses/>.
#

EXIT_SUCCESS=0;
EXIT_FAILURE=1;
EXIT_IGNORE=77;

TMP="tmp";

CMP="cmp";

test_path()
{ 
	FILENAME=$1;
	FULLPATH=$2;

	mkdir ${TMP};
	cd ${TMP};

	echo -n ${FULLPATH} > input;

	../${CPATH_TEST_PATH} ${FILENAME} > output;

	RESULT=$?;

	if test ${RESULT} -eq ${EXIT_SUCCESS};
	then
		if ! ${CMP} -s input output;
		then
			RESULT=${EXIT_FAILURE};
		fi
	fi

	cd ..;
	rm -rf ${TMP};

	echo -n "Testing full path: ${FILENAME} ";

	if test ${RESULT} -ne ${EXIT_SUCCESS};
	then
		echo " (FAIL)";
	else
		echo " (PASS)";
	fi
	return ${RESULT};
}

CPATH_TEST_PATH="cpath_test_path";

if ! test -x ${CPATH_TEST_PATH};
then
	CPATH_TEST_PATH="cpath_test_path.exe";
fi

if ! test -x ${CPATH_TEST_PATH};
then
	echo "Missing executable: ${CPATH_TEST_PATH}";

	exit ${EXIT_FAILURE};
fi

rm -rf ${TMP};

# Note that not all version of uname support the -o option
# so we cannot use: `uname -o` = "Msys"
UNAME=`uname -s | sed 's/-[^-]*$//'`;

if test ${UNAME} = "MINGW32_NT";
then
	WINPWD=`pwd -W | tr '/' '\\'`;
	DRIVE=`echo ${WINPWD} | cut -c 1`;

	if ! test_path "user\\test.txt" "\\\\?\\${WINPWD}\\tmp\\user\\test.txt"
	then
		exit ${EXIT_FAILURE};
	fi

	if ! test_path "username\\..\\user\\test.txt" "\\\\?\\${WINPWD}\\tmp\\user\\test.txt"
	then
		exit ${EXIT_FAILURE};
	fi

	if ! test_path "\\home\\user\\test.txt" "\\\\?\\${DRIVE}:\\home\\user\\test.txt"
	then
		exit ${EXIT_FAILURE};
	fi

	if ! test_path "c:\\home\\user\\test.txt" "\\\\?\\c:\\home\\user\\test.txt"
	then
		exit ${EXIT_FAILURE};
	fi

	if ! test_path "c:\\home\\user\\\\test.txt" "\\\\?\\c:\\home\\user\\test.txt"
	then
		exit ${EXIT_FAILURE};
	fi

	if ! test_path "c:\\home\\username\\..\\user\\test.txt" "\\\\?\\c:\\home\\user\\test.txt"
	then
		exit ${EXIT_FAILURE};
	fi

	if ! test_path "c:\\..\\home\\user\\test.txt" "\\\\?\\c:\\home\\user\\test.txt"
	then
		exit ${EXIT_FAILURE};
	fi

	if ! test_path "c:\\..\\home\\username\\..\\user\\test.txt" "\\\\?\\c:\\home\\user\\test.txt"
	then
		exit ${EXIT_FAILURE};
	fi

	if ! test_path "\\\\.\\PhysicalDrive0" "\\\\.\\PhysicalDrive0"
	then
		exit ${EXIT_FAILURE};
	fi

	if ! test_path "\\\\?\\Volume{4c1b02c4-d990-11dc-99ae-806e6f6e6963}" "\\\\?\\Volume{4c1b02c4-d990-11dc-99ae-806e6f6e6963}"
	then
		exit ${EXIT_FAILURE};
	fi

	if ! test_path "\\\\172.0.0.1\\C$\\test.txt" "\\\\?\\UNC\\172.0.0.1\\C$\\test.txt"
	then
		exit ${EXIT_FAILURE};
	fi

	if ! test_path "\\\\?\\UNC\\172.0.0.1\\C$\\test.txt" "\\\\?\\UNC\\172.0.0.1\\C$\\test.txt"
	then
		exit ${EXIT_FAILURE};
	fi
else
	if ! test_path "user/test.txt" "${PWD}/tmp/user/test.txt"
	then
		exit ${EXIT_FAILURE};
	fi

	if ! test_path "username/../user/test.txt" "${PWD}/tmp/user/test.txt"
	then
		exit ${EXIT_FAILURE};
	fi

	if ! test_path "/home/user/test.txt" "/home/user/test.txt"
	then
		exit ${EXIT_FAILURE};
	fi

	if ! test_path "/home/user//test.txt" "/home/user/test.txt"
	then
		exit ${EXIT_FAILURE};
	fi

	if ! test_path "/home/username/../user/test.txt" "/home/user/test.txt"
	then
		exit ${EXIT_FAILURE};
	fi

	if ! test_path "/../home/user/test.txt" "/home/user/test.txt"
	then
		exit ${EXIT_FAILURE};
	fi

	if ! test_path "/../home/username/../user/test.txt" "/home/user/test.txt"
	then
		exit ${EXIT_FAILURE};
	fi
fi

exit ${EXIT_SUCCESS};

