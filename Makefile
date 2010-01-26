export CPLUS_INCLUDE_PATH=$CPLUS_INCLUDE_PATH:/opt/local/include
#export LIBRARY_PATH=/opt/local/lib

sources = load.cpp main.cpp
objects = load.o main.o

build_flags = -O0 -g2

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