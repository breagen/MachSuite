TARGET := hw

BOARD := ZCU102
PROC := psu_cortexa53
TARGET_OS := linux


BUILD_DIR := $(CURDIR)/build
TEST_DIR := $(BUILD_DIR)/

EMU_FLAGS := 
ifneq ($(TARGET), hw)
	EMU_FLAGS := -mno-bitstream -mno-boot-files -emulation $(EMU_MODE)
endif


#CFLAGS = -g -Wall -O3 -c -I$(CURDIR)/inc/ -fno-builtin -D__HW__ -Wno-unused-label #-D__DEBUG__ -D__CHECK_REULTS_PER_LAYER__
CFLAGS = -Wall -O3 -c -I$(CURDIR)/ -fno-builtin -Wno-unused-label
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
OBJECTS += $(TEST_DIR)/support.o
OBJECTS += $(TEST_DIR)/harness.o 
LOGFILE = $(TEST_DIR)/_sds/reports/sds.log

#all: clean help platform exec
all: cleantest $(OBJECTS)

$(TEST_DIR)/%.o: $(CURDIR)/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: SDSCC Compiler'
	@mkdir -p $(TEST_DIR)
	cd $(TEST_DIR) ; $(C_COMP) $(CFLAGS) -o $(LFLAGS)
	@echo 'Finished building: $<'
	@echo ' '
ifeq ($(TARGET), cpu_emu) 
	@echo 'Ignore the warning which states that hw function is not a HW accelerator but has pragma applied for cpu_emu mode'
	@echo ' '
endif

cleantest:
	@rm -rf $(BUILD_DIR)
