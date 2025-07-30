CXX ?= g++
STD ?= c++17
CWARNINGS := -Wall -Wextra -Wpedantic -Wshadow
# CXXFLAGS := -std=$(STD) $(CWARNINGS) $(OPENGL_INCLUDE) -I./$(SRC_DIR)
CXXFLAGS := -std=$(STD) $(CWARNINGS) -I./$(SRC_DIR)
LDFLAGS := $(OPENGL_LIBS)

# OPENGL_INCLUDE := -I/usr/include/GL -I/usr/include/GLFW
# OPENGL_LIBS := -lglfw -lGLEW -lGL -lX11 -lpthread

BUILD_DIR = build
SRC_DIR = src

SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))
DEPS := $(OBJS:.o=.d)

TARGET = $(BUILD_DIR)/miniphysics

$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -MMD -MP -MT '$@' -c $< -o $@

$(BUILD_DIR):
	@mkdir -p $@

-include $(DEPS)

# BUILD

.PHONY: build
build: $(TARGET)

# DEBUG

.PHONY: debug
debug: CXXFLAGS += -g -O0
debug: $(TARGET)

# RELEASE

.PHONY: release
release: CXXFLAGS += -O2
release: $(TARGET)

# CLEAR

.PHONY: clear
clear:
	rm -rf $(BUILD_DIR)/*
