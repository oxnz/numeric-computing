CC := clang
CFLAGS := -Wall -pipe -O2
CXX := clang++
CXXFLAGS := -Wall -pipe -O2
LDFLAGS := 

OBJS = mtx.o vtr.o vtrm.o

EXES = bisctn cmpx eval trapezoidal vec-mat vtr mtx
all: $(EXES)

mtx: mtx.o vtr.o
	$(CXX) $(CFLAGS) $(LDFLAGS) $^ -o $@
vtr: vtr.o vtrm.o
	$(CXX) $(CFLAGS) $(LDFLAGS) $^ -o $@
clean:
	$(RM) $(OBJS)
dist-clean:
	$(RM) $(EXES)
.PHONY: all clean dist-clean
