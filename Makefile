CC := clang
CFLAGS := -Wall -pipe -O2
CXX := clang++
CXXFLAGS := -Wall -pipe -O2
LDFLAGS := 

OBJS =

EXES = bisctn cmpx eval trapezoidal vec-mat
all: $(EXES)

clean:
	$(RM) $(OBJS)
dist-clean:
	$(RM) $(EXES)
.PHONY: all clean dist-clean
