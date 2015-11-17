LDFLAGS  += -march=native -fopenmp -g
CPPFLAGS += -march=native -std=gnu99 -fopenmp -g -O0 

ifneq ($(CXX),c++)
ifneq ($(CXX),g++)
SPACE  := $(empty) $(empty)
SUFFIX := -$(subst $(SPACE),_,$(CXX))
endif
endif

TESTS := baseline$(SUFFIX) avxsimd$(SUFFIX)

all: $(TESTS)

clean:; rm -f $(TESTS) $(addsuffix .o, $(TESTS))

.SECONDARY:

%$(SUFFIX).o:: %.cc Makefile
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(CPPFLAGS)
ifeq ($(CLANG),1)
	$(CXX) -o $(@:.o=.ll) -S -emit-llvm -c $< $(CXXFLAGS) $(CPPFLAGS)
endif

%$(SUFFIX): %$(SUFFIX).o
	$(CXX) -o $@ $< $(LDFLAGS)
