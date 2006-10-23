OSAL_INC = /usr/include/ixp4xx/osal
CSR_INC =  /usr/include/ixp4xx/csr

obj-m := ixp400_eth.o

CFLAGS_ixp400_eth.o = -DWall \
	-I$(CSR_INC) \
	-I$(OSAL_INC) \
	-I$(OSAL_INC)/os/linux \
	-I$(OSAL_INC)/os/linux/modules \
	-I$(OSAL_INC)/os/linux/modules/ioMem \
	-I$(OSAL_INC)/os/linux/modules/core \
	-I$(OSAL_INC)/os/linux/modules/bufferMgt \
	-I$(OSAL_INC)/os/linux/core/  \
	-I$(OSAL_INC)/os/linux/platforms \
	-I$(OSAL_INC)/os/linux/platforms/ixp400 \
	-I$(OSAL_INC)/os/linux/platforms/ixp400/ixp425 \
	-I$(OSAL_INC)/modules \
	-I$(OSAL_INC)/modules/bufferMgt \
	-I$(OSAL_INC)/modules/ioMem \
	-I$(OSAL_INC)/modules/core \
	-I$(OSAL_INC)/platforms \
	-I$(OSAL_INC)/platforms/ixp400 \
	-DCONFIG_IXP400_ETH_NPEB_ONLY=1 \
	-DIX_COMPONENT_NAME=-1 -DIX_UTOPIAMODE=0 -DIX_MPHYSINGLEPORT=1

clean::
	rm -f ixp400_eth.o ixp400_eth.ko
