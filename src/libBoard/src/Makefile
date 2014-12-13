
CXXFLAGS += -w -fPIC -I../include/

objects := Board.o Color.o Path.o PSFonts.o Rect.o ShapeList.o Shapes.o Tools.o Transforms.o

all: ../../libboard.dll ../../libboard.so

../../libboard.dll: $(objects) 
	$(CXX) -shared -o ../../libboard.dll $(CXXFLAGS) $(objects)
../../libboard.so: $(objects) 
	$(CXX) -shared -o ../../libboard.so $(CXXFLAGS) $(objects)
	
	
