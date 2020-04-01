#First check if the sysroot is defined.
# Run Target:
#   hw  - Compile for hardware
#   emu - Compile for emulation (Default)
#   cpu_emu - Quick compile for cpu emulation trating all HW functions as CPU functions
TARGET := emu

#ifndef SYSROOT
#ifeq ($(TARGET), hw)
#	$(error SYSROOT is not set)
#endif
#endif


DSA_PATH := ./DSA/ultra.dsa
OVERLAY := nw_nw
BOARD := ZCU102
PROC := psu_cortexa53
TARGET_OS := linux

#Head definition
TOP_FUNCTION = needwun
TOP_FILE = nw.c

#-----------------
# 0 -> 75
# 1 -> 100
# 2 -> 150
# 3-> 200
# 4-> 300
CLKID = 1


HW_FLAGS := 
ifneq ($(TARGET), cpu_emu)
	HW_FLAGS += -sds-hw $(TOP_FUNCTION) $(CURDIR)/$(TOP_FILE) -clkid $(CLKID) -sds-end 
endif

BUILD_DIR := $(CURDIR)/build
TEST_DIR := $(BUILD_DIR)/$(BOARD)-$(OVERLAY)

# Emulation Mode:
#     debug     - Include debug data
#     optimized - Exclude debug data (Default)
EMU_MODE := optimized



EMU_FLAGS := 
ifneq ($(TARGET), hw)
	EMU_FLAGS := -mno-bitstream -mno-boot-files -emulation $(EMU_MODE)
endif


#CFLAGS = -g -Wall -O3 -c -I$(CURDIR)/inc/ -fno-builtin -D__HW__ -Wno-unused-label #-D__DEBUG__ -D__CHECK_REULTS_PER_LAYER__
CFLAGS = -Wall -O3 -c -I$(CURDIR)/../../common -I$(CURDIR)/ -fno-builtin -Wno-unused-label
CFLAGS += -MT"$@" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)"
LFLAGS = "$@" "$<"
#SDSFLAGS := -sds-pf $(CURDIR)/$(BOARD)/platforms/$(OVERLAY) -target-os linux
SDSFLAGS := -sds-pf zcu102 -target-os $(TARGET_OS)

LDFLAGS :=
#ifeq ($(TARGET), hw)
#	LDFLAGS += --sysroot=$(SYSROOT) -Wl,-rpath-link=$(SYSROOT)/lib/aarch64-linux-gnu/,-rpath-link=$(SYSROOT)/usr/lib/aarch64-linux-gnu/,-rpath-link=$(SYSROOT)/usr/lib/
#	LDFLAGS += -lopencv_core -lopencv_highgui -lopencv_imgproc -lGL -lGLU -lglut
#endif

C_COMP := sdscc $(SDSFLAGS)
OBJECTS = $(TEST_DIR)/nw.o 
OBJECTS += $(TEST_DIR)/local_support.o
LOGFILE = $(TEST_DIR)/_sds/reports/sds.log

# Check Rule Builds the Sources and Executes on Specified Target
check: all
ifneq ($(TARGET), hw)
ifeq ($(TARGET_OS), linux)
ifeq ($(EMU_MODE), optimized)
	cp $(CURDIR)/../../utility/emu_run_no_gui.sh $(TEST_DIR)/emu_run.sh
else
	cp $(CURDIR)/../../utility/emu_run.sh $(TEST_DIR)/emu_run.sh
endif
	cd $(TEST_DIR) ; ./emu_run.sh $(OVERLAY)
endif
else
	$(info "This Release Doesn't Support Automated Hardware Execution")
endif

all: clean help host exec


help:
	@echo "usage: make"
	@echo
	@echo "options:"
	@echo "--------"
	@echo "help:       show help message."
	@echo "all:        make the SDx platform, and test it."
	@echo "platform:   make the SDx platform based on the input arguments."
	@echo "test:       do a simple test after a given platform is made."
	@echo "cleantest:  clean the test folder."
	@echo "clean:      clean the test and SDx platforms for the given board."
	@echo "cleanall:   clean all the platforms for a fresh start."
	@echo
	@echo "arguments:"
	@echo "----------"
	@echo "DSA_PATH:   path to the dsa file"
	@echo "            e.g., ./platform/hw/hdmi.dsa"
	@echo "PROC:       name of the processor that can be targeted"
	@echo "            e.g., psu_cortexa53"
	@echo
	@echo "current configuration:"
	@echo "----------------------"
	@echo "make DSA_PATH=$(DSA_PATH)"
	@echo "     OVERLAY=$(OVERLAY)"
	@echo "     BOARD=$(BOARD)"
	@echo "     PROC=$(PROC)"
#	@echo "     SYSROOT=$(SYSROOT)"
	@echo

host:
	$(MAKE) -C $(CURDIR)/../../common

exec: cleantest $(OBJECTS)
	@mkdir -p $(TEST_DIR)
	@echo 'Building Target: $@'
	@echo 'Trigerring: SDS++ Linker'
	cd $(TEST_DIR) ; $(C_COMP) -Wall  $(CURDIR)/../../common/build/support.o $(CURDIR)/../../common/build/harness.o $(LDFLAGS) -o $(OVERLAY) $(OBJECTS) $(EMU_FLAGS)
	@echo 'SDx Completed Building Target: $@'
	@echo
	@tput setaf 2; \
	echo "PASS: Platform successfully tested."; \
	tput sgr0;
	@echo


$(TEST_DIR)/%.o: $(CURDIR)/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: SDSCC Compiler'
	@mkdir -p $(TEST_DIR)
	cd $(TEST_DIR) ; $(C_COMP) $(CFLAGS) -o $(LFLAGS) $(HW_FLAGS)
	@echo 'Finished building: $<'
	@echo ' '
ifeq ($(TARGET), cpu_emu) 
	@echo 'Ignore the warning which states that hw function is not a HW accelerator but has pragma applied for cpu_emu mode'
	@echo ' '
endif


cleantest:
	@rm -rf $(BUILD_DIR)

clean: cleantest
	rm -rf .build
	rm -rf $(BOARD)/platforms
	rm -rf ./$(BOARD)/hw

cleanall: clean
	rm -rf ./*/platforms
	rm -rf ./*/hw
