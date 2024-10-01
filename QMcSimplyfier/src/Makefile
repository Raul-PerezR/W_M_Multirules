OBJS = domain_t.o example_set.o fuzzy_t.o variable_t.o vectordouble.o VectorVar.o prueba.o patrones.o


all: $(OBJS)
	g++ -std=c++14 -w -fopenmp -fpermissive -O2 -o QMcSimplyfier $(OBJS)

%.o : %.cpp
	g++ -std=c++14 -w -fopenmp -fpermissive -O2 -c $< -o $@

domain_t.o: domain_t.cpp
example_set.o: example_set.cpp
fuzzy_t.o: fuzzy_t.cpp
variable_t.o: variable_t.cpp
vectordouble.o: vectordouble.cpp
VectorVar.o: VectorVar.cpp
prueba.o: prueba.cpp
patrones.o: patrones.cpp

clean:
	 rm -f $(OBJS) QMcSimplyfier
