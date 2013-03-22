#! /bin/bash

# perform the bootstrap passing arguments to autoconf

if [ "$1" == "noconf" ]
then

	mkdir -p build-scripts && \
		aclocal && \
		autoheader && \
		automake --add-missing && \
		autoconf
else

	mkdir -p build-scripts && \
		aclocal && \
		autoheader && \
		automake --add-missing && \
		autoconf && \
		./configure "$@"
fi


