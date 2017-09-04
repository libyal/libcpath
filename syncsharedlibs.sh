#!/bin/sh
# Script that synchronizes the shared library dependencies
#
# Version: 20170904

GIT_URL_PREFIX="https://github.com/libyal";
SHARED_LIBS="libcerror libclocale libcsplit libuna";

if test ${TRAVIS_OS_NAME} != "linux";
then
	echo "ERROR: This script is intended to be run on Travis CI.";

	exit 1;
fi

OLDIFS=$IFS;
IFS=" ";

for SHARED_LIB in ${SHARED_LIBS};
do
	git clone ${GIT_URL_PREFIX}/${SHARED_LIB}.git ${SHARED_LIB}-$$;

	if ! test -d ${SHARED_LIB}-$$;
	then
		continue
	fi

	(cd ${SHARED_LIB}-$$ && ./synclibs.sh && ./autogen.sh);

	CONFIGURE_OPTIONS="";

	(cd ${SHARED_LIB}-$$ && CONFIGURE_HELP=`./configure --help`);

	echo "${CONFIGURE_HELP}" | grep -- '--enable-wide-character-type' > /dev/null;

	if test $? -eq 0;
	then
		CONFIGURE_OPTIONS="${CONFIGURE_OPTIONS} --enable-wide-character-type";
	fi

	(cd ${SHARED_LIB}-$$ && ./configure --prefix=/usr ${CONFIGURE_OPTIONS} && make && sudo make install);

	rm -rf ${SHARED_LIB}-$$;
done

IFS=$OLDIFS;

