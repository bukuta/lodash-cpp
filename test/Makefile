##########################################################################
# unit tests
##########################################################################

# additional flags
# -Wall -Wextra -pedantic -Wcast-align -Wcast-qual -Wno-ctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wmissing-declarations -Wmissing-include-dirs -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-overflow=5 -Wswitch -Wundef -Wno-unused -Wnon-virtual-dtor -Wreorder -Wdeprecated -Wno-float-equal

CXXFLAGS += -std=c++17 
CPPFLAGS += 

SOURCES = test.cpp

OBJECTS = $(SOURCES:.cpp=.o)

##############################################################################
# main rules
##############################################################################

all: $(TESTCASES)

clean:
	rm -fr json_unit $(OBJECTS) $(SOURCES:.cpp=.gcno) $(SOURCES:.cpp=.gcda) 

##############################################################################
# single test file
##############################################################################

json_unit: $(OBJECTS) test.cpp json.hpp
	@echo "[CXXLD] $@"
	@$(CXX) $(CXXFLAGS) $(LDFLAGS) $(OBJECTS) -o $@

%.o: %.cpp test.cpp json.hpp
	@echo "[CXX]   $@"
	@$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@


##############################################################################
# individual test cases
##############################################################################

