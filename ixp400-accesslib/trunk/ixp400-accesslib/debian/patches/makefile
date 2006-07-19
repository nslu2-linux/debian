Index: ixp400_xscale_sw/Makefile
===================================================================
--- ixp400_xscale_sw/Makefile.orig	2006-07-19 15:18:44.000000000 +0200
+++ ixp400_xscale_sw/Makefile	2006-07-19 15:45:59.000000000 +0200
@@ -54,7 +54,7 @@
 # Components that work only for a subset of platforms
 # should be added to the relevant *_COMPONENTS lists.
 #
-BI_ENDIAN_COMPONENTS := atmdAcc atmm atmsch qmgr npeMh npeDl ethAcc ethDB ethMii hssAcc uartAcc usb featureCtrl ossl osServices 
+BI_ENDIAN_COMPONENTS := qmgr npeMh npeDl ethAcc ethDB ethMii featureCtrl osServices
 
 
 #Components only applicable to ixp46x
@@ -69,6 +69,11 @@
 else
 linuxbe_COMPONENTS := $(BI_ENDIAN_COMPONENTS) dmaAcc oslinux perfProfAcc
 endif
+ifeq ($(IX_LINUXVER),2.6)
+linuxle_COMPONENTS := $(BI_ENDIAN_COMPONENTS) oslinux
+else
+linuxle_COMPONENTS := $(BI_ENDIAN_COMPONENTS) oslinux perfProfAcc
+endif
 
 #The lists below contain the set of components available for each target platform
 # specific to the ixp46X device
@@ -164,7 +169,7 @@
 ################################################################
 # Linux kernel source
 
-LINUX_SRC := $($(IX_TARGET)_KERNEL_DIR)
+LINUX_SRC := $(KERNEL_DIR)
 
 ################################################################
 # Inclusion of common Makefile
@@ -188,20 +193,6 @@
 OSAL_MODULE := ../ixp_osal/lib/$(IX_TGT_DEVICE)/$(IX_TARGET_OS)/$(IX_TARGET)/ixp_osal.o
 endif 
 
-.PHONY: osal_build
-osal_build :
-	echo cd into $(OSAL_DIR)
-	cd $(OSAL_DIR) $(CMD_SEP) $(MAKE) libosal IX_TARGET=$(IX_TARGET)
-
-$(OSAL_IMAGE) : osal_build
-
-.PHONY: osal_module
-osal_module :
-	echo cd into $(OSAL_DIR)
-	cd $(OSAL_DIR) $(CMD_SEP) $(MAKE) module IX_TARGET=$(IX_TARGET)
-
-$(OSAL_MODULE) : osal_module
-
 ################################################################
 # Compiler & linker commands
 #
@@ -264,11 +255,12 @@
 else # IX_TARGET_OS == vxworks
 
 # Linux tool names
-ifeq ($(IX_TARGET), linuxbe)
-LINUX_CROSS_COMPILE := $(HARDHAT_BASE)/devkit/arm/xscale_be/bin/xscale_be-
-else
-LINUX_CROSS_COMPILE := $(HARDHAT_BASE)/devkit/arm/xscale_le/bin/xscale_le-
-endif
+#ifeq ($(IX_TARGET), linuxbe)
+#LINUX_CROSS_COMPILE := $(HARDHAT_BASE)/devkit/arm/xscale_be/bin/xscale_be-
+#else
+#LINUX_CROSS_COMPILE := $(HARDHAT_BASE)/devkit/arm/xscale_le/bin/xscale_le-
+#endif
+LINUX_CROSS_COMPILE := $(CROSS_COMPILE)
 
 LD := $(LINUX_CROSS_COMPILE)ld
 CC := $(LINUX_CROSS_COMPILE)gcc
@@ -329,6 +321,8 @@
 CFLAGS += -DIX_NPEDL_READ_MICROCODE_FROM_FILE
 
 
+CFLAGS += -DIX_UTOPIAMODE=0 -DIX_MPHY=1 -DIX_MPHYSINGLEPORT
+
 # Linux linker flags
 LDFLAGS := -r
 
@@ -404,7 +398,7 @@
   ifeq ($(IX_TARGET_OS),vxworks)
     LDFLAGS += -Wl
     CFLAGS += -DCPU=XSCALE -DCPU_XSCALE -DARMMMU=ARMMMU_XSCALE \
-      	-DARMCACHE=ARMCACHE_XSCALE
+	-DARMCACHE=ARMCACHE_XSCALE
     GNU_CFLAGS += -mcpu=xscale -mapcs-32 -mno-sched-prolog
     ifeq ($(IX_TARGET),vxle)
       CFLAGS += -DARMEL -D__ARMEL__ -DLITTLE_ENDIAN_MODE
@@ -558,6 +552,7 @@
 			$($(c)_EXPORT_OBJ:%=$(OBJ_DIR)/$(subst _,/,$(c))/%) \
 		   )
 
+export COMPONENTS
 
 ################################################################
 # Rules
@@ -1216,7 +1211,7 @@
 define VXWORKS_CALL_BSP_MAKE
 	cd $(BSP_DIR) $(CMD_SEP) \
 	$(MAKE) $(VXWORKS_IMAGE_NAME) \
-      	   LIB_EXTRA="$(VXWORKS_LIB_EXTRA:%=$(IX_XSCALE_SW)/%)" \
+	   LIB_EXTRA="$(VXWORKS_LIB_EXTRA:%=$(IX_XSCALE_SW)/%)" \
 	   IX_TARGET=$(IX_TARGET) IX_PLATFORM=$(IX_PLATFORM) IX_DEVICE=$(IX_DEVICE)
 	cp $(BSP_DIR)/$(VXWORKS_IMAGE_NAME) $@
 endef
@@ -1370,33 +1365,22 @@
 libIxp400 : $(OBJ_DIR)/libIxp400.a $(NPE_PRODUCTION_HEADER_OBJ) $(OSAL_MODULE)
 
 $(OBJ_DIR)/libIxp400.a : $(COMPONENT_OBJ) $(NPE_PRODUCTION_HEADER_OBJ) $(OSAL_MODULE) 
-	$(MAKEFILE_TRACE) Building Ixp400 library containing components $(COMPONENTS:%=\"%\")
+	$(MAKEFILE_TRACE) Building Ixp400 library containing components $(COMPONENTS:%=\"%\") #"
 	$(AR) rvs $(OBJ_DIR)/libIxp400.a $^
 else
 libIxp400 : $(OBJ_DIR)/libIxp425.a $(NPE_PRODUCTION_HEADER_OBJ) $(OSAL_MODULE)
 
 $(OBJ_DIR)/libIxp425.a : $(COMPONENT_OBJ) $(NPE_PRODUCTION_HEADER_OBJ) $(OSAL_MODULE)
-	$(MAKEFILE_TRACE) Building Ixp400 library containing components $(COMPONENTS:%=\"%\")
+	$(MAKEFILE_TRACE) Building Ixp400 library containing components $(COMPONENTS:%=\"%\") #"
 	$(AR) rvs $(OBJ_DIR)/libIxp425.a $^
 endif
 
 ################################################################
 # Loadable module containing all component code
 
+.PHONY: ixp400
 ifeq ($(IX_LINUXVER),2.6)
-ixp400 : $(OBJ_DIR)/ixp400.o
-	@echo 'EXTRA_LDFLAGS := --whole-archive' > $(OBJ_DIR)/Makefile
-	@echo ' ' >> $(OBJ_DIR)/Makefile
-	@echo 'lib-m := $(COMPONENTS:%=ixp400_%.o) $(OBJ_DIR_EXIT)/$(OSAL_MODULE)'>> $(OBJ_DIR)/Makefile
-	@echo ' ' >> $(OBJ_DIR)/Makefile
-	@echo 'obj-m := ixp400.o' >> $(OBJ_DIR)/Makefile
-	@echo ' ' >> $(OBJ_DIR)/Makefile
-	@echo 'ixp400-objs := lib.a' >> $(OBJ_DIR)/Makefile
-	@echo ' ' >> $(OBJ_DIR)/Makefile
-	@echo 'default:' >> $(OBJ_DIR)/Makefile
-	@echo -ne "\t" >> $(OBJ_DIR)/Makefile
-	@echo 'make -C $(LINUX_SRC) M=$(shell pwd)/$(OBJ_DIR) V=1 modules' >> $(OBJ_DIR)/Makefile
-	make -C $(OBJ_DIR)
+ixp400 : $(OBJ_DIR)/ixp400.ko
 else
 ixp400 : $(OBJ_DIR)/ixp400.o
 endif
@@ -1406,6 +1390,11 @@
 	$(LD) $(LDFLAGS) $^ -o $@
 endif
 
+$(OBJ_DIR)/ixp400.ko: $(OBJ_DIR)/Makefile $(COMPONENTS:%=$(OBJ_DIR)/ixp400_%.o) $(OSAL_MODULE)
+	$(MAKE) -C $(LINUX_SRC) OSAL_MODULE=$(OBJ_DIR_EXIT)/$(OSAL_MODULE) M=$(IX_XSCALE_SW)/$(OBJ_DIR) V=1
+
+$(OBJ_DIR)/Makefile: Kbuild
+	cp $^ $@
 
 
 ################################################################
