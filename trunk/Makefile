LINUX_VERSION = 2.6.18-6

all: toolchain linux-image-2.6.18-3-ixp4xx_${LINUX_VERSION}_arm.deb

DEBIAN_POOL = http://debian.planetmirror.com/debian/pool

.PHONY: toolchain
toolchain:
	${MAKE} -C toolchain all

clean-kernel:
	( cd linux-2.6-2.6.18 ; fakeroot debian/rules clean )
	rm -f linux-image-2.6.18-3-ixp4xx_${LINUX_VERSION}_arm.deb

linux-image-2.6.18-3-ixp4xx_${LINUX_VERSION}_arm.deb: linux-2.6-2.6.18/debian/rules
	( cd linux-2.6-2.6.18 ; \
	  fakeroot debian/rules debian/build debian/stamps ; \
	  fakeroot make -f debian/rules.gen binary-arch-arm-none-ixp4xx )

linux-2.6-2.6.18/debian/rules: downloads/linux-2.6_${LINUX_VERSION}.dsc patches/kernel/series
	dpkg-source -x downloads/linux-2.6_${LINUX_VERSION}.dsc 
	( cd linux-2.6-2.6.18 ; \
	  ln -s ../patches/kernel patches ; \
	  quilt push -a )

downloads/linux-2.6_${LINUX_VERSION}.dsc:
	( cd downloads ; \
	  wget ${DEBIAN_POOL}/main/l/linux-2.6/linux-2.6_${LINUX_VERSION}.dsc ; \
	  for f in `grep -A 2 "^Files:" linux-2.6_${LINUX_VERSION}.dsc | tail -2 | awk '{ print $$3; }'` ; do \
	    wget ${DEBIAN_POOL}/main/l/linux-2.6/$$f ; \
	  done )

clobber:
	rm -rf linux-2.6-2.6.18* linux-2.6_2.6.18*
	rm -f linux-{image,headers}-2.6.18-3-ixp4xx_${LINUX_VERSION}_arm.deb