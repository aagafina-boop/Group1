CXX      := g++
CXXFLAGS := -Wall -Wextra -std=c++17 -Iinclude

BUILD    := build
TARGET   := kch_phase1
TEST_BIN := test_phase1

MODULE_OBJS := $(BUILD)/module1_staff.o $(BUILD)/module2_triage.o

.PHONY: all test clean

all: $(TARGET)

$(TARGET): $(MODULE_OBJS) $(BUILD)/main_phase1.o
	$(CXX) $(CXXFLAGS) $^ -o $@

$(TEST_BIN): $(MODULE_OBJS) $(BUILD)/test_phase1.o
	$(CXX) $(CXXFLAGS) $^ -o $@

test: $(TEST_BIN)
	./$(TEST_BIN)

$(BUILD)/%.o: src/%.cpp | $(BUILD)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD)/%.o: tests/%.cpp | $(BUILD)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD)/module1_staff.o $(BUILD)/main_phase1.o $(BUILD)/test_phase1.o: include/module1_staff.h
$(BUILD)/module2_triage.o $(BUILD)/main_phase1.o $(BUILD)/test_phase1.o: include/module2_triage.h

$(BUILD):
	mkdir -p $(BUILD)

clean:
	rm -rf $(BUILD) $(TARGET) $(TEST_BIN)