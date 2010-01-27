export CPLUS_INCLUDE_PATH=$CPLUS_INCLUDE_PATH:/opt/local/include
#export LIBRARY_PATH=/opt/local/lib

sources = load.cpp index.cpp main.cpp
objects = load.o index.o main.o

build_flags = -O3 -g

all: main

main: $(objects)
	g++ $(build_flags) -o main $(objects) 

%.o: %.cpp
	g++ $(build_flags) -c -o"$@" "$<"

%.d: %.cpp
	g++ -MM -MT $(subst .d,.o,$@) -MF "$@" "$<"

clean:
	$(RM) *.o
	$(RM) *.d

include $(sources:.cpp=.d)