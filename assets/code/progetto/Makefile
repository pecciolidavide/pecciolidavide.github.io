
TARGETS = test_svg0.exe test_svg1.exe test_svg2.exe labirinto.exe

all: $(TARGETS)

test_svg0.exe: svg.hh svg.cc test_svg0.cc
	g++ -o $@ svg.cc test_svg0.cc

test_svg1.exe: svg.hh svg.cc test_svg1.cc
	g++ -o $@ svg.cc test_svg1.cc

test_svg2.exe: svg.hh svg.cc test_svg2.cc
	g++ -o $@ svg.cc test_svg2.cc

labirinto.exe: svg.hh svg.cc labirinto.cc
	g++ -o $@ svg.cc labirinto.cc

clean:
	rm -f $(TARGETS)
	rm -f *.o
