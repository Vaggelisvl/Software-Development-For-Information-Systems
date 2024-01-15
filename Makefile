CXX = g++
CXXFLAGS = -std=c++11 -fPIC
LIBS = -lgtest -lgtest_main -pthread
INCLUDES = -Iheaders
SRCDIR = src
TESTDIR = tests/unit_tests
TESTDIRINT = tests/integration_tests
TESTFOLDERPOINT = structures/point
TESTFOLDERGRAPH = structures/graph
TESTFOLDERMAP= structures/unorderedMap
TESTFOLDERVECTOR= structures/vector
TESTFOLDERDATASET = structures/dataset
TESTFOLDERDATASETINT= structures/dataset
TESTFOLDEROPTIMAZATION= structures/graph/optimization
OUTDIR = bin
MKDIR_P = mkdir -p
SCRIPTS_DIR = scripts
INSTALL_GPP_SCRIPT = $(SCRIPTS_DIR)/gplusplus_install.sh
INSTALL_GTEST_SCRIPT = $(SCRIPTS_DIR)/install_gtest.sh
INSTALL_CMAKE_COMMAND = sudo apt-get update && sudo apt-get install -y cmake

# Source files for the library
LIB_SRCS = $(SRCDIR)/structures/point/Point.cpp \
           $(SRCDIR)/structures/point/PointInfo.cpp \
           $(SRCDIR)/structures/point/Neighbors.cpp \
           $(SRCDIR)/structures/scheduler/job/KNNJob.cpp \
           $(SRCDIR)/structures/scheduler/job/Job.cpp \
           $(SRCDIR)/structures/scheduler/job/NormCalculationJob.cpp \
           $(SRCDIR)/structures/scheduler/job/RandomProjectionTreeJob.cpp \
           $(SRCDIR)/structures/scheduler/job/CalculateDistanceJob.cpp \
           $(SRCDIR)/structures/scheduler/job/FindKNearestNeighborsForPointJob.cpp \
           $(SRCDIR)/structures/scheduler/JobQueue.cpp \
           $(SRCDIR)/structures/scheduler/JobDependency.cpp	\
           $(SRCDIR)/structures/scheduler/JobScheduler.cpp	\
           $(SRCDIR)/structures/Dataset.cpp \
           $(SRCDIR)/structures/graph/GraphInitialization.cpp \
           $(SRCDIR)/structures/graph/Optimizations.cpp \
           $(SRCDIR)/structures/randomProjectionTrees/RandomProjectionTrees.cpp \
           $(SRCDIR)/utils/Metrics.cpp \
           $(SRCDIR)/utils/Statistics.cpp \
           $(SRCDIR)/utils/StatisticInfo.cpp \
           $(SRCDIR)/config/Logger.cpp

# Shared library (SO) and Static library (A) names
LIB_NAME = dataforge
LIB_SHARED = $(OUTDIR)/lib$(LIB_NAME).so
LIB_STATIC = $(OUTDIR)/lib$(LIB_NAME).a

# Source files for unit tests
TEST_SRCS = $(TESTDIR)/structures/point/PointTest.cpp \
            $(TESTDIR)/structures/graph/GraphInitializationTest.cpp \
            $(TESTDIR)/structures/graph/OptimizationsTest.cpp \
            $(TESTDIR)/structures/graph/RandomProjectionTreesTest.cpp \
            $(TESTDIR)/structures/dataset/DatasetTest.cpp \
            $(TESTDIR)/structures/vector/VectorTestFloat.cpp \
            $(TESTDIR)/structures/vector/VectorTestNeighbor.cpp \
            $(TESTDIR)/structures/point/NeighborTest.cpp \
            $(TESTDIR)/structures/vector/VectorTestPoint.cpp \
            $(TESTDIR)/structures/unorderedMap/UnorderedMapTest.cpp


# Test executables
TESTS = $(patsubst $(TESTDIR)/%.cpp,$(OUTDIR)/%,$(TEST_SRCS))

.PHONY: all clean test

all: install_dependencies  shared_library static_library export_library_path main_executable
install_dependencies:
	$(MKDIR_P) $(OUTDIR)
	@$(INSTALL_CMAKE_COMMAND)
	@$(INSTALL_CMAKE_COMMAND)
	@chmod +x $(INSTALL_GPP_SCRIPT)
	@$(SHELL) $(INSTALL_GPP_SCRIPT)
	@chmod +x $(INSTALL_GTEST_SCRIPT)
	@$(SHELL) $(INSTALL_GTEST_SCRIPT)

shared_library: $(LIB_SHARED)

static_library: $(LIB_STATIC)

$(LIB_SHARED): $(LIB_SRCS)
	$(CXX) $(CXXFLAGS) -shared -o $@ $^ $(INCLUDES) -lpthread

$(LIB_STATIC): $(LIB_SRCS)
	ar rcs $@ $^

all_skip_dependencies: shared_library static_library export_library_path main_executable

test: export_library_path create_outdir $(TESTS)
	@for test in $(TESTS); do \
		./$$test; \
	done

$(OUTDIR)/%: $(TESTDIR)/%.cpp
	$(MKDIR_P) $(OUTDIR)
	$(MKDIR_P) $(OUTDIR)/$(TESTFOLDERPOINT)
	$(MKDIR_P) $(OUTDIR)/$(TESTFOLDERGRAPH)
	$(MKDIR_P) $(OUTDIR)/$(TESTFOLDERMAP)
	$(MKDIR_P) $(OUTDIR)/$(TESTFOLDERVECTOR)
	$(MKDIR_P) $(OUTDIR)/$(TESTFOLDEROPTIMAZATION)
	$(MKDIR_P) $(OUTDIR)/$(TESTFOLDERDATASET)
	$(CXX) $(CXXFLAGS) -o $@ $< $(LIB_SRCS) $(INCLUDES) $(LIBS)

export_library_path:
	export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$(OUTDIR)

main_executable: create_outdir
	$(CXX) -o main $(SRCDIR)/library.cpp -L$(OUTDIR) -Wl,-rpath,'$$ORIGIN/$(OUTDIR)' -ldataforge
ARGS ?= src/input1.bin 100 20 5 1 0.01 euclidean 3 10 5

run:
	./main $(or $(filter-out $@,$(MAKECMDGOALS)),$(ARGS))
%:
	@:
clean:
	rm -f $(LIB_SHARED) $(LIB_STATIC) $(TESTS) main

create_outdir:
	@mkdir -p $(OUTDIR)
