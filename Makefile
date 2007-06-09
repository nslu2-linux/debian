LINUX_REVISION = 2.6.22~rc4-1~experimental.1
LINUX_VERSION = 2.6.22~rc4
LINUX_DIR = 2.6.22~rc4
KERNEL_ABI = 2.6.22-rc4

# LINUX_VERSION = 2.6.20~rc5
# LINUX_DIR = 2.6.20~rc5
# KERNEL_ABI = 2.6.20-1

# LINUX_VERSION = 2.6.19
# LINUX_DIR = 2.6.19
# KERNEL_ABI = 2.6.19-1

# LINUX_VERSION = 2.6.18-6
# LINUX_DIR = 2.6.18-3
# KERNEL_ABI = 2.6.18-3

# LINUX_VERSION = 2.6.17-9
# LINUX_DIR = 2.6.17-2
# KERNEL_ABI = 2.6.17-2

all: linux-image-${KERNEL_ABI}-ixp4xx_${LINUX_REVISION}_arm.deb

DEBIAN_POOL = http://debian.planetmirror.com/debian/pool

KERNEL_POOL = http://kernel-archive.buildserver.net/debian-kernel/pool

.PHONY: toolchain
toolchain:
	${MAKE} -C toolchain all

packages:
	( cd d-i/packages ; \
	  for f in `find * -type d -prune -print | grep -v '^arch$$'` ; do \
	    ( sudo apt-get -y build-dep $$f ) ; \
	    ( cd $$f ; fakeroot debian/rules binary-arch ) ; \
	  done \
	)

clean-kernel:
	( cd linux-2.6-${LINUX_DIR} ; fakeroot debian/rules clean )
	rm -f linux-image-*-ixp4xx_${LINUX_REVISION}_arm.deb

linux-image-${KERNEL_ABI}-ixp4xx_${LINUX_REVISION}_arm.deb: linux-2.6-${LINUX_DIR}/debian/rules
	( cd linux-2.6-${LINUX_DIR} ; \
	  fakeroot debian/rules debian/build debian/stamps debian/control ; \
	  fakeroot make -f debian/rules.gen binary-arch-arm-none-ixp4xx ; \
	  fakeroot make -f debian/rules.gen binary-indep )

ifeq (${LINUX_VERSION},2.6.22~rc4)

linux-2.6-${LINUX_DIR}/debian/rules: downloads/linux-2.6_${LINUX_VERSION}.orig.tar.gz patches/kernel/${LINUX_VERSION}/series
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
	  quilt push -a )
	touch $@

downloads/linux-2.6_${LINUX_VERSION}.orig.tar.gz:
	[ -e downloads ] || [ mkdir -p downloads
	( cd downloads ; \
	  wget ${KERNEL_POOL}/main/l/linux-2.6/linux-2.6_${LINUX_VERSION}.orig.tar.gz )

else

linux-2.6-${LINUX_DIR}/debian/rules: downloads/linux-2.6_${LINUX_VERSION}.dsc patches/kernel/${LINUX_VERSION}/series
	dpkg-source -x downloads/linux-2.6_${LINUX_VERSION}.dsc linux-2.6-${LINUX_DIR}
	rm -f linux-2.6_*.orig.tar.gz
	( cd linux-2.6-${LINUX_DIR} ; \
	  ln -s ../patches/kernel/${LINUX_VERSION} patches ; \
	  quilt push -a )

downloads/linux-2.6_${LINUX_VERSION}.dsc:
	[ -e downloads ] || mkdir -p downloads
	( cd downloads ; \
	  wget ${DEBIAN_POOL}/main/l/linux-2.6/linux-2.6_${LINUX_VERSION}.dsc ; \
	  for f in `grep -A 2 "^Files:" linux-2.6_${LINUX_VERSION}.dsc | tail -2 | awk '{ print $$3; }'` ; do \
	    wget ${DEBIAN_POOL}/main/l/linux-2.6/$$f ; \
	  done )

endif

update:
	( cd kernel ; svn up )
	( cd d-i ; svn up)
	( cd nslu2-utils ; svn up )

clobber:
	rm -rf linux-2.6-${LINUX_DIR} linux-2.6_*.orig.tar.gz
	rm -f linux-{image,headers}-*-ixp4xx_${LINUX_REVISION}_arm.deb
