# LINUX_VERSION = 2.6.18-6
LINUX_VERSION = 2.6.17-9
# KERNEL_ABI = 2.6.18-3
KERNEL_ABI = 2.6.17-2

all: toolchain linux-image-${KERNEL_ABI}-ixp4xx_${LINUX_VERSION}_arm.deb

DEBIAN_POOL = http://debian.planetmirror.com/debian/pool

.PHONY: toolchain
toolchain:
	${MAKE} -C toolchain all

clean-kernel:
	( cd linux-${LINUX_VERSION} ; fakeroot debian/rules clean )
	rm -f linux-image-*-ixp4xx_${LINUX_VERSION}_arm.deb

linux-image-${KERNEL_ABI}-ixp4xx_${LINUX_VERSION}_arm.deb: linux-${LINUX_VERSION}/debian/rules
	( cd linux-${LINUX_VERSION} ; \
	  fakeroot debian/rules debian/build debian/stamps ; \
	  fakeroot make -f debian/rules.gen binary-arch-arm-none-ixp4xx )

linux-${LINUX_VERSION}/debian/rules: downloads/linux-2.6_${LINUX_VERSION}.dsc patches/kernel/${LINUX_VERSION}/series
	dpkg-source -x downloads/linux-2.6_${LINUX_VERSION}.dsc linux-${LINUX_VERSION}
	rm -f linux-2.6_*.orig.tar.gz
	( cd linux-${LINUX_VERSION} ; \
	  ln -s ../patches/kernel/${LINUX_VERSION} patches ; \
	  quilt push -a )

downloads/linux-2.6_${LINUX_VERSION}.dsc:
	( cd downloads ; \
	  wget ${DEBIAN_POOL}/main/l/linux-2.6/linux-2.6_${LINUX_VERSION}.dsc ; \
	  for f in `grep -A 2 "^Files:" linux-2.6_${LINUX_VERSION}.dsc | tail -2 | awk '{ print $$3; }'` ; do \
	    wget ${DEBIAN_POOL}/main/l/linux-2.6/$$f ; \
	  done )

update:
	( cd kernel ; svn up )
	( cd d-i ; svn up)
	( cd nslu2-utils ; svn up )

clobber:
	rm -rf linux-${LINUX_VERSION} linux-2.6_*.orig.tar.gz
	rm -f linux-{image,headers}-*-ixp4xx_${LINUX_VERSION}_arm.deb
