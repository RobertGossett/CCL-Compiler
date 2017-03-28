#
# Define LEXEMES to be the Lex/Flex file holding the relevant lexeme rules.
#

LEXEMES = scanner.ll

#
# Define GRAMMAR to be the Yacc/Bison file holding the relevant grammar rules.
#

GRAMMAR = grammar.yy

#
# Define COMPILER to be the final executable file name
#

COMPILER = scCCL

#
# On most UNIX's use
#

CXX = g++
CXXFLAGS = -ILibrary
#CXXFLAGS = -g -DYYDEBUG
LIBS =

LEX = flex
LFLAGS = -+ -osc.yy.cc

YACC = bison
YFLAGS = -b sc
#YFLAGS = -b sc -v

# ommitted codegen.o in both lines
$(COMPILER): error.o main.o scanner.o sc.tab.o sc.yy.o simpleSymbolTable.o
	$(CXX) $(CXXFLAGS) -o $(COMPILER) error.o main.o scanner.o sc.tab.o sc.yy.o simpleSymbolTable.o $(LIBS)

# codegen.o: bareBonesNAryTree.h codegen.cpp codegen.h sc.tab.hh

error.o: error.cpp error.h scanner.h

# codegen.h ommitted
main.o: bareBonesNAryTree.h error.h main.cpp main.h simpleSymbolTable.h

sc.tab.o: bareBonesNAryTree.h error.o main.o scanner.o sc.tab.cc sc.tab.hh

sc.yy.o: bareBonesNAryTree.h sc.tab.hh sc.yy.cc

scanner.o: scanner.cpp scanner.h 

simpleSymbolTable.o: simpleSymbolTable.cpp simpleSymbolTable.h

sc.tab.cc sc.tab.hh: $(GRAMMAR)
	$(YACC) $(YFLAGS) $(GRAMMAR)
	bisonfix sc.tab.cc sc.tab.hh

sc.yy.cc: $(LEXEMES)
	$(LEX) $(LFLAGS) $(LEXEMES)

$(GRAMMAR): ;
$(LEXEMES): ;
# codegen.cpp: ;
# codegen.h: ;
error.cpp: ;
error.h: ;
main.cpp: ;
main.h: ;
scanner.cpp: ;
scanner.h: ;
simpleSymbolTable.cpp: ;
simpleSymbolTable.h: ;
bareBonesNAryTree.h: abstractNAryTree.h
	touch bareBonesNAryTree.h
abstractNAryTree.h: ;

clean:
	rm -f sc.tab.* *.output sc.yy.* *.o

realclean:
	rm -f sc.tab.* *.output sc.yy.* *.o $(COMPILER)*
