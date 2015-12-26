
CXXFLAGS += -w -fPIC -I../libBoard/include

objects := chdrawer.o canvas.o chBlock.o chCentromere.o chromosome.o chromosomeElement.o chromosomeMark.o chromosomeSign.o color.o colorPalette.o ideogram.o karyotype.o markSign.o parameters.o

all: ../libchrdrawer.dll ../libchrdrawer.so

../libchrdrawer.dll: $(objects) 
	$(CXX) -shared -o ../libchrdrawer.dll $(CXXFLAGS) $(objects)
../libchrdrawer.so: $(objects) 
	$(CXX) -shared -o ../libchrdrawer.so $(CXXFLAGS) $(objects)
	
	
