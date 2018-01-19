CXX=g++
CXXFLAGS=-Wall -std=c++11

BUILD_DIR ?= ./build
SRC_DIR ?= ./src
PARSER_DIR ?= ./parser
INC_DIRS ?= ./include
MKDIR_P ?= mkdir -p

INC_FLAGS := $(addprefix -I,$(INC_DIRS))

SOURCES=And.cpp Atom.cpp AtomicFormula.cpp BaseFormula.cpp BinaryConnective.cpp False.cpp Iff.cpp Imp.cpp LogicConstant.cpp Not.cpp Or.cpp ProofTree.cpp Sequent.cpp True.cpp UnaryConnective.cpp OptionParser.cpp
SRCS:=$(SOURCES:%=$(SRC_DIR)/%)
OBJS:=$(SOURCES:%.cpp=$(BUILD_DIR)/%.o)

.PHONY: directories all clean mingw mingw_flags default

all: directories prover

default: all

#windows MinGW option
mingw: mingw_flags directories prover

mingw_flags:
	$(eval CXXFLAGS=-Wall -std=gnu++11)

#build directory
directories : ${BUILD_DIR}

${BUILD_DIR}:
	${MKDIR_P} ${BUILD_DIR}

#prover tool build
prover : $(BUILD_DIR)/main.o $(BUILD_DIR)/parser.o $(BUILD_DIR)/lexer.o $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

#main build
$(BUILD_DIR)/main.o : main.cpp
	$(CXX) $(CXXFLAGS) -c -o $(BUILD_DIR)/main.o main.cpp $(INC_FLAGS)

$(OBJS): $(BUILD_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $^ $(INC_FLAGS)

#parser build
$(BUILD_DIR)/parser.o: $(PARSER_DIR)/parser.cpp
	$(CXX) $(CXXFLAGS) -c -o $(BUILD_DIR)/parser.o $(PARSER_DIR)/parser.cpp $(INC_FLAGS)

$(BUILD_DIR)/lexer.o: $(PARSER_DIR)/lexer.cpp $(PARSER_DIR)/parser.hpp
	$(CXX) $(CXXFLAGS) -c -o $(BUILD_DIR)/lexer.o $(PARSER_DIR)/lexer.cpp $(INC_FLAGS)

$(PARSER_DIR)/parser.cpp $(PARSER_DIR)/parser.hpp: $(PARSER_DIR)/parser.ypp
	bison -d -o $(PARSER_DIR)/parser.cpp $(PARSER_DIR)/parser.ypp

$(PARSER_DIR)/lexer.cpp: $(PARSER_DIR)/lexer.lpp
	flex -o $(PARSER_DIR)/lexer.cpp $(PARSER_DIR)/lexer.lpp

#other
clean:
	rm -f $(BUILD_DIR)/*.o
	rm -r -f $(BUILD_DIR)
	rm -f *~
	rm -f $(PARSER_DIR)/parser.cpp
	rm -f $(PARSER_DIR)/lexer.cpp
	rm -f $(PARSER_DIR)/parser.hpp
	rm -f prover
	rm -f prover.exe
