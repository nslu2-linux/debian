LINUX_VERSION = 2.6.18-6

all: linux-image-2.6.18-3-ixp4xx_${LINUX_VERSION}_arm.deb

DEBIAN_POOL = http://debian.planetmirror.com/debian/pool

linux-image-2.6.18-3-ixp4xx_${LINUX_VERSION}_arm.deb: linux-2.6_${LINUX_VERSION}.dsc
	dpkg-source -x linux-2.6_${LINUX_VERSION}.dsc 
	( cd linux-2.6-2.6.18 ; \
	  fakeroot debian/rules debian/build debian/stamps ; \
	  fakeroot make -f debian/rules.gen binary-arch-arm-none-ixp4xx )

linux-2.6_${LINUX_VERSION}.dsc:
	wget ${DEBIAN_POOL}/main/l/linux-2.6/linux-2.6_${LINUX_VERSION}.dsc
	for f in `grep -A 2 "^Files:" linux-2.6_${LINUX_VERSION}.dsc | tail -2 | awk '{ print $$3; }'` ; do \
	  wget ${DEBIAN_POOL}/main/l/linux-2.6/$$f ; \
	done

