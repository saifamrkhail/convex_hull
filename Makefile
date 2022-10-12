CXX = g++
CXXFLAGS = -g -Wall -I /usr/local/include/opencv4 
LIBS = /usr/local/lib64/libopencv*
LFLAGS += -lpthread -ljpeg -lrt 

SRCDIR = .
INCDIR = .

SOURCES = $(SRCDIR)/*.cpp


all: convex_hull
convex_hull:
	$(CXX) $(SOURCES) $(CXXFLAGS) -o $@ $(LIBS) $(LFLAGS)
clean:
	rm convex_hull


