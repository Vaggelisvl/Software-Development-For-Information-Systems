CXX = g++
CXXFLAGS = -std=c++11 -fPIC
LIBS = -lgtest -lgtest_main -pthread
INCLUDES = -Iheaders
SRCDIR = src
TESTDIR = tests/unit_tests
OUTDIR = bin
MKDIR_P = mkdir -p
# Source files for the library
LIB_SRCS = $(SRCDIR)/structures/point/Point.cpp \
           $(SRCDIR)/structures/point/PointInfo.cpp \
           $(SRCDIR)/structures/point/Neighbors.cpp \
           $(SRCDIR)/structures/Dataset.cpp \
           $(SRCDIR)/structures/graph/GraphInitialization.cpp \
           $(SRCDIR)/utils/Metrics.cpp \
           $(SRCDIR)/config/Logger.cpp

# Shared library (SO) and Static library (A) names
LIB_NAME = dataforge
LIB_SHARED = $(OUTDIR)/lib$(LIB_NAME).so
LIB_STATIC = $(OUTDIR)/lib$(LIB_NAME).a

# Source files for unit tests
TEST_SRCS = $(TESTDIR)/structures/point/PointTest.cpp \
            $(TESTDIR)/structures/graph/GraphInitializationTest.cpp \
            $(TESTDIR)/structures/dataset/DatasetTest.cpp \
            $(TESTDIR)/structures/vector/VectorTestFloat.cpp \
            $(TESTDIR)/structures/vector/VectorTestNeighbor.cpp \
            $(TESTDIR)/structures/vector/VectorTestPoint.cpp \
            $(TESTDIR)/structures/unorderedMap/UnorderedMapTest.cpp


# Test executables
TESTS = $(patsubst $(TESTDIR)/%.cpp,$(OUTDIR)/%,$(TEST_SRCS))

.PHONY: all clean test

all: shared_library static_library

shared_library: $(LIB_SHARED)

static_library: $(LIB_STATIC)

$(LIB_SHARED): $(LIB_SRCS)
	$(CXX) $(CXXFLAGS) -shared -o $@ $^ $(INCLUDES)

$(LIB_STATIC): $(LIB_SRCS)
	ar rcs $@ $^

test: create_outdir $(TESTS)
	@for test in $(TESTS); do \
		./$$test; \
	done

$(OUTDIR)/%: $(TESTDIR)/%.cpp
	$(MKDIR_P) $(OUTDIR)
	$(CXX) $(CXXFLAGS) -o $@ $< $(LIB_SRCS) $(INCLUDES) $(LIBS)




clean:
	rm -f $(LIB_SHARED) $(LIB_STATIC) $(TESTS)

create_outdir:
	@mkdir -p $(OUTDIR)
