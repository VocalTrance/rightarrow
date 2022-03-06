exec = ra
objects = reader.o main.o lexer.o token.o ast.o treenode.o parser.o visitor.o builtin.o
sources = $(wildcard src/*.c) 
headers = $(wildcard src/include/*.h)
flags = -g

rightarrow: $(objects)
	gcc -o $(exec).out $(flags) $(objects)

$(objects): $(sources) $(headers)
	gcc -c $(sources) $(flags)

clean: 
	-rm $(objects)
	-rm $(exec).out
