.PHONY: pretty clean

all:
	@echo "clean - remove built files"
	@echo "json_unit - create single-file test executable"
	@echo "pedantic_clang - run Clang with maximal warning flags"
	@echo "pedantic_gcc - run GCC with maximal warning flags"
	@echo "pretty - beautify code with Artistic Style"


##########################################################################
# unit tests
##########################################################################

# build unit tests
json_unit:
	@$(MAKE) json_unit -C test

# clean up
clean:
	rm -fr json_unit *.dSYM test/*.dSYM
	$(MAKE) clean -Ctest


##########################################################################
# warning detector
##########################################################################

# calling Clang with all warnings, except:
# -Wno-documentation-unknown-command: code uses user-defined commands like @complexity
# -Wno-exit-time-destructors: warning in Catch code
# -Wno-keyword-macro: unit-tests use "#define private public"
# -Wno-deprecated-declarations: the library deprecated some functions
# -Wno-weak-vtables: exception class is defined inline, but has virtual method
# -Wno-range-loop-analysis: iterator_wrapper tests "for(const auto i...)"
# -Wno-float-equal: not all comparisons in the tests can be replaced by Approx
# -Wno-switch-enum -Wno-covered-switch-default: pedantic/contradicting warnings about switches
# -Wno-padded: padding is nothing to warn about
pedantic_clang:
	$(MAKE) json_unit CXXFLAGS="\
		-std=c++11 -Wno-c++98-compat -Wno-c++98-compat-pedantic \
		-Werror \
		-Weverything \
		-Wno-documentation-unknown-command \
		-Wno-exit-time-destructors \
		-Wno-keyword-macro \
		-Wno-deprecated-declarations \
		-Wno-weak-vtables \
		-Wno-range-loop-analysis \
		-Wno-float-equal \
		-Wno-switch-enum -Wno-covered-switch-default \
		-Wno-padded"

# calling GCC with most warnings
pedantic_gcc:
	$(MAKE) json_unit CXX=g++ CXXFLAGS="\
		-std=c++11 \
		-Wno-deprecated-declarations \
		-Werror \
		-Wall -Wpedantic -Wextra \
		-Walloca \
		-Warray-bounds=2 \
		-Wcast-qual -Wcast-align \
		-Wchar-subscripts \
		-Wconditionally-supported \
		-Wconversion \
		-Wdate-time \
		-Wdeprecated \
		-Wdisabled-optimization \
		-Wdouble-promotion \
		-Wduplicated-branches \
		-Wduplicated-cond \
		-Wformat-overflow=2 \
		-Wformat-signedness \
		-Wformat-truncation=2 \
		-Wformat=2 \
		-Wno-ignored-qualifiers \
		-Wimplicit-fallthrough=5 \
		-Wlogical-op \
		-Wmissing-declarations \
		-Wmissing-format-attribute \
		-Wmissing-include-dirs \
		-Wnoexcept \
		-Wnonnull \
		-Wnull-dereference \
		-Wold-style-cast \
		-Woverloaded-virtual \
		-Wparentheses \
		-Wplacement-new=2 \
		-Wredundant-decls \
		-Wreorder \
		-Wrestrict \
		-Wshadow=global \
		-Wshift-overflow=2 \
		-Wsign-conversion \
		-Wsign-promo \
		-Wsized-deallocation \
		-Wstrict-overflow=5 \
		-Wsuggest-attribute=const \
		-Wsuggest-attribute=format \
		-Wsuggest-attribute=noreturn \
		-Wsuggest-attribute=pure \
		-Wsuggest-final-methods \
		-Wsuggest-final-types \
		-Wsuggest-override \
		-Wtrigraphs \
		-Wundef \
		-Wuninitialized -Wunknown-pragmas \
		-Wunused \
		-Wunused-const-variable=2 \
		-Wunused-macros \
		-Wunused-parameter \
		-Wuseless-cast \
		-Wvariadic-macros"

##########################################################################
# maintainer targets
##########################################################################

# pretty printer
pretty:
	echo astyle --style=allman --indent=spaces=4 --indent-modifiers \
	   --indent-switches --indent-preproc-block --indent-preproc-define \
	   --indent-col1-comments --pad-oper --pad-header --align-pointer=type \
	   --align-reference=type --add-brackets --convert-tabs --close-templates \
	   --lineend=linux --preserve-date --suffix=none --formatted \
	   lodash.hpp 

