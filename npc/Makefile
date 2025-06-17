DEFAULT_VERILOG ?= top.v 
DEFAULT_CPP ?= sim_main.cpp
DEFAULT_TOP ?= top
DEFAULT_OBJ_DIR ?= obj_dir

VERILOG_SRC ?= $(DEFAULT_VERILOG)
CPP_SRC ?= $(DEFAULT_CPP)
TOP_MODULE ?= $(DEFAULT_TOP)
OBJ_DIR ?= $(DEFAULT_OBJ_DIR)
TARGET ?= sim_$(TOP_MODULE)

all:
	@echo "Write this Makefile by your self."


sim:$(TARGET)
$(TARGET): $(VERILOG_SRC) $(CPP_SRC)
	$(call git_commit, "sim RTL") # DO NOT REMOVE THIS LINE!!!
	@echo "Write this Makefile by your self."
	verilator -Wall $(VERILOG_SRC) $(CPP_SRC) --cc --trace-fst --exe \
		--build -top-module $(TOP_MODULE) --Mdir $(OBJ_DIR)\
	@ln -sf $(OBJ_DIR)/V$(TOP_MODULE) $@

clean:
	rm -rf $(OBJ_DIR) $(TARGET) *.vcd *.fst

.PHONY: sim all
