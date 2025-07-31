CXX ?= g++
STD ?= c++17

ifeq ($(OS), Windows_NT)
  CXXWARNINGS := -Wall -Wextra
  TARGET = $(BUILD_DIR)/miniphysics.exe
  OPENGL_LIBS := -lglfw3 -lopengl32 -lgdi32
else
  CXXWARNINGS := -Wall -Wextra -Wpedantic -Wshadow
  TARGET = $(BUILD_DIR)/miniphysics
  ifeq ($(shell uname -s), Linux)
    OPENGL_INCLUDE := -I/usr/include/GLFW -I/usr/include/GL
    OPENGL_LIBS := -lglfw -lGL
  else ifeq ($(shell uname -s), Darwin)
    OPENGL_LIBS := -lglfw -framework Cocoa -framework OpenGL -framework IOKit
  endif
endif

CXXFLAGS := -std=$(STD) $(CXXWARNINGS) $(OPENGL_INCLUDE) -I./$(SRC_DIR)
LDFLAGS := $(OPENGL_LIBS)

BUILD_DIR = build
SRC_DIR = src

SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))
DEPS := $(OBJS:.o=.d)

$(TARGET): $(OBJS)
	$(CXX) $^ -o $@ $(LDFLAGS)

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
