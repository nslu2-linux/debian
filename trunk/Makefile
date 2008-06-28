LINUX_REVISION = 2.6.26~rc8-1~experimental.1
LINUX_VERSION = 2.6.26~rc8
LINUX_DIR = 2.6.26~rc8
KERNEL_ABI = 2.6.26-rc8

DEB_BUILD_ARCH = armel

all: linux-image-${KERNEL_ABI}-ixp4xx_${LINUX_REVISION}_${DEB_BUILD_ARCH}.deb

DEBIAN_POOL = http://debian.planetmirror.com/debian/pool

KERNEL_SITE = http://photon.itp.tuwien.ac.at/~mattems/

linux-image-${KERNEL_ABI}-ixp4xx_${LINUX_REVISION}_${DEB_BUILD_ARCH}.deb: linux-2.6-${LINUX_DIR}/debian/rules
	( cd linux-2.6-${LINUX_DIR} ; \
	  fakeroot debian/rules debian/build debian/stamps debian/control ; \
	  fakeroot make -f debian/rules.gen binary-arch_${DEB_BUILD_ARCH}_none_ixp4xx ; \
	  fakeroot make -f debian/rules.gen binary-indep )

ifeq (${LINUX_VERSION},2.6.26~rc8)

linux-2.6-${LINUX_DIR}/debian/rules: downloads/linux-2.6_${LINUX_VERSION}.orig.tar.gz
	rm -rf linux-2.6-${LINUX_DIR}
	tar zxf downloads/linux-2.6_${LINUX_VERSION}.orig.tar.gz
	( cd linux-2.6-${LINUX_DIR} ; \
	  rm -rf debian ; \
	  ( svn export svn://svn.debian.org/kernel/dists/trunk/linux-2.6/debian debian || \
	    cp -rip ../kernel/linux-2.6/debian debian ) )
	[ ! -e patches/kernel/${LINUX_VERSION}/series ] || \
	( cd linux-2.6-${LINUX_DIR} ; \
	  rm -f patches ; \
	  ln -s ../patches/kernel/${LINUX_VERSION} patches ; \
	  [ ! -e patches/series ] || quilt push -a )
	touch $@

downloads/linux-2.6_${LINUX_VERSION}.orig.tar.gz:
	[ -e downloads ] || mkdir -p downloads
	( cd downloads ; \
	  wget ${KERNEL_SITE}/linux-2.6_${LINUX_VERSION}.orig.tar.gz )

else

linux-2.6-${LINUX_DIR}/debian/rules: downloads/linux-2.6_${LINUX_VERSION}.dsc
	rm -rf linux-2.6-${LINUX_DIR}
	dpkg-source -x downloads/linux-2.6_${LINUX_VERSION}.dsc linux-2.6-${LINUX_DIR}
	rm -f linux-2.6_*.orig.tar.gz
	( cd linux-2.6-${LINUX_DIR} ; \
	  ln -s ../patches/kernel/${LINUX_VERSION} patches ; \
	  [ ! -e patches/series ] || quilt push -a )

downloads/linux-2.6_${LINUX_VERSION}.dsc:
	[ -e downloads ] || mkdir -p downloads
	( cd downloads ; \
	  wget ${DEBIAN_POOL}/main/l/linux-2.6/linux-2.6_${LINUX_VERSION}.dsc ; \
	  for f in `grep -A 2 "^Files:" linux-2.6_${LINUX_VERSION}.dsc | tail -2 | awk '{ print $$3; }'` ; do \
	    wget ${DEBIAN_POOL}/main/l/linux-2.6/$$f ; \
	  done )

endif

clean:
	( cd linux-2.6-${LINUX_DIR} ; fakeroot debian/rules clean )
	rm -f linux-image-*-ixp4xx_${LINUX_REVISION}_${DEB_BUILD_ARCH}.deb

clobber:
	rm -rf linux-2.6-${LINUX_DIR}
	rm -f linux-*.deb linux-*.changes
