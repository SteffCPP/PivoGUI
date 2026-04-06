CXX = g++

SRC_DIR = src
INC_DIR = inc
LIB_DIR = lib
BIN_DIR = bin
BUILD_DIR = build

TARGET = EasyGUI
EXE = $(BIN_DIR)/main.exe

CXXFLAGS = -I$(INC_DIR) -I$(LIB_DIR) -O2 -Wall -MMD -MP
LDFLAGS_DLL = -L$(LIB_DIR) -lSDL3 -shared -Wl,--out-implib,$(BIN_DIR)/$(TARGET).lib
LDFLAGS_EXE = -L$(BIN_DIR) -lSDL3 -l$(TARGET)

# ===================== Source files =====================

SRC = $(wildcard $(SRC_DIR)/*.cpp)
HEADERS = $(wildcard $(INC_DIR)/*.hpp)

# Library source files (exclude main.cpp)
LIB_SRC = $(filter-out $(SRC_DIR)/main.cpp,$(SRC))
LIB_OBJ = $(LIB_SRC:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Main object
MAIN_SRC = $(SRC_DIR)/main.cpp
MAIN_OBJ = $(BUILD_DIR)/main.o

# DLL output
DLL = $(BIN_DIR)/$(TARGET).dll

# ===================== Rules =====================

all: $(DLL) $(EXE)

# Create folders if they don't exist
$(BUILD_DIR):
	if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)

$(BIN_DIR):
	if not exist $(BIN_DIR) mkdir $(BIN_DIR)

# Compile library objects
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS) | $(BUILD_DIR)
	$(CXX) -c $< -o $@ $(CXXFLAGS)

# Build DLL + LIB
$(DLL): $(LIB_OBJ) | $(BIN_DIR)
	$(CXX) $(LIB_OBJ) $(LDFLAGS_DLL) -o $@

# Compile main.cpp
$(MAIN_OBJ): $(MAIN_SRC) $(HEADERS) | $(BUILD_DIR)
	$(CXX) -c $< -o $@ $(CXXFLAGS)

# Build executable linked against DLL
$(EXE): $(MAIN_OBJ) $(DLL) | $(BIN_DIR)
	$(CXX) $(MAIN_OBJ) $(LDFLAGS_EXE) -o $@

# ===================== Utilities =====================

clean:
	@if exist $(BUILD_DIR) rmdir /S /Q $(BUILD_DIR)
	@if exist $(BIN_DIR)\$(TARGET).dll del /Q $(BIN_DIR)\$(TARGET).dll
	@if exist $(BIN_DIR)\$(TARGET).lib del /Q $(BIN_DIR)\$(TARGET).lib
	@if exist $(EXE) del /Q $(EXE)

run: all
	@echo Running $(EXE)...
	@$(EXE)

-include $(BUILD_DIR)/*.d

.PHONY: all clean run