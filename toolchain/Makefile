ARCH	= arm

DEBIAN_POOL = http://debian.planetmirror.com/debian/pool

BINUTILS_VERSION	:= $(shell dpkg -s binutils | grep '^Version:' | awk '{ print $$2; }')
BINUTILS_SOURCE_VERSION	:= ${BINUTILS_VERSION}
BINUTILS_DIR		:= binutils-$(shell echo ${BINUTILS_SOURCE_VERSION} | sed -e 's/-.*//')

GCC41_VERSION 		:= $(shell dpkg -s gcc-4.1 | grep '^Version:' | awk '{ print $$2; }')
GCC41_SOURCE_VERSION 	:= $(shell dpkg -s gcc-4.1 | sed -n 's/Source:.*(\(.*\))/\1/p')
GCC41_DIR		:= gcc-4.1-$(shell echo ${GCC41_SOURCE_VERSION} | sed -e 's/-.*//')

LIBC6_VERSION 		:= $(shell dpkg -s libc6 | grep '^Version:' | awk '{ print $$2; }')
LIBC6_SOURCE_VERSION 	:= ${LIBC6_VERSION}

HEADERS_VERSION		:= $(shell dpkg -s linux-kernel-headers | grep '^Version:' | awk '{ print $$2; }')
HEADERS_SOURCE_VERSION 	:= ${HEADERS_VERSION}

HOST_ARCH := $(shell dpkg-architecture -qDEB_HOST_ARCH)

all: \
	binutils-${ARCH}-linux-gnu_${BINUTILS_VERSION}_${HOST_ARCH}.deb \
	linux-kernel-headers-${ARCH}-cross_${HEADERS_VERSION}_all.deb \
	libc6-${ARCH}-cross_${LIBC6_VERSION}_all.deb \
	libc6-dev-${ARCH}-cross_${LIBC6_VERSION}_all.deb \
	gcc-4.1-${ARCH}-linux-gnu_${GCC41_VERSION}_${HOST_ARCH}.deb

gcc-4.1-${ARCH}-linux-gnu_${GCC41_VERSION}_${HOST_ARCH}.deb: gcc-4.1_${GCC41_SOURCE_VERSION}.dsc
	sudo apt-get -y build-dep gcc-4.1
	dpkg-source -x gcc-4.1_${GCC41_SOURCE_VERSION}.dsc
	( cd ${GCC41_DIR} ; \
	  export GCC_TARGET=${ARCH} ; \
	  debian/rules control ; \
	  dpkg-buildpackage -us -uc -rfakeroot -b )
	sudo dpkg -i lib{gcc1,stdc++6}*-${ARCH}-cross_${GCC41_VERSION}_all.deb \
		     {cpp,g++,gcc}-*-${ARCH}-linux-gnu_${GCC41_VERSION}_${HOST_ARCH}.deb

gcc-4.1_${GCC41_SOURCE_VERSION}.dsc:
	apt-get source gcc-4.1

libc6-${ARCH}-cross_${LIBC6_VERSION}_all.deb: libc6_${LIBC6_VERSION}_${ARCH}.deb
	dpkg-cross -a ${ARCH} -b libc6_${LIBC6_VERSION}_${ARCH}.deb
	sudo dpkg -i libc6-${ARCH}-cross_${LIBC6_VERSION}_all.deb

libc6_${LIBC6_VERSION}_${ARCH}.deb:
	wget ${DEBIAN_POOL}/main/g/glibc/libc6_${LIBC6_VERSION}_${ARCH}.deb

libc6-dev-${ARCH}-cross_${LIBC6_VERSION}_all.deb: libc6-dev_${LIBC6_VERSION}_${ARCH}.deb
	dpkg-cross -a ${ARCH} -b libc6-dev_${LIBC6_VERSION}_${ARCH}.deb
	sudo dpkg -i libc6-dev-${ARCH}-cross_${LIBC6_VERSION}_all.deb

libc6-dev_${LIBC6_VERSION}_${ARCH}.deb:
	wget ${DEBIAN_POOL}/main/g/glibc/libc6-dev_${LIBC6_VERSION}_${ARCH}.deb

linux-kernel-headers-${ARCH}-cross_${HEADERS_VERSION}_all.deb: linux-kernel-headers_${HEADERS_VERSION}_${ARCH}.deb
	dpkg-cross -a ${ARCH} -b linux-kernel-headers_${HEADERS_VERSION}_${ARCH}.deb
	sudo dpkg -i linux-kernel-headers-${ARCH}-cross_${HEADERS_VERSION}_all.deb

linux-kernel-headers_${HEADERS_VERSION}_${ARCH}.deb:
	wget ${DEBIAN_POOL}/main/l/linux-kernel-headers/linux-kernel-headers_${HEADERS_VERSION}_${ARCH}.deb

binutils-${ARCH}-linux-gnu_${BINUTILS_VERSION}_${HOST_ARCH}.deb: binutils_${BINUTILS_SOURCE_VERSION}.dsc
	sudo aptitude -y install fakeroot dpkg-cross
	sudo apt-get -y build-dep binutils
	dpkg-source -x binutils_${BINUTILS_SOURCE_VERSION}.dsc
	( cd ${BINUTILS_DIR} ; \
		TARGET=${ARCH}-linux-gnu fakeroot debian/rules binary-cross )
	sudo dpkg -i $@

binutils_${BINUTILS_SOURCE_VERSION}.dsc:
	apt-get source binutils

clean:
	rm -rf ${BINUTILS_DIR} ${GCC41_DIR}

clobber: clean
	rm binutils-${ARCH}-linux-gnu_${BINUTILS_VERSION}_${HOST_ARCH}.deb
	rm linux-kernel-headers-${ARCH}-cross_${HEADERS_VERSION}_all.deb
	rm libc6-dev-${ARCH}-cross_${LIBC6_VERSION}_all.deb
	rm libc6-${ARCH}-cross_${LIBC6_VERSION}_all.deb
	rm lib{gcc1,stdc++6}*-${ARCH}-cross_${GCC41_VERSION}_all.deb
	rm {cpp,g++,gcc}-*-${ARCH}-linux-gnu_${GCC41_VERSION}_${HOST_ARCH}.deb

distclean: clobber
	rm -rf binutils* gcc*