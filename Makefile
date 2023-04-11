DIR = `basename $(CURDIR)`

MAIN = main
HEAD = wielomiany

EXEC1 = $(MAIN).out

OBJMAIN = $(MAIN).o
OBJHEAD = $(HEAD).o

HEADS = $(HEAD).h

CFLAGS = -Wall -std=c++11

CO = g++

%.o : %.cpp $(HEADS)
	$(CO) $(CFLAGS) -c  $< -o $@


%.cpp:
.PHONY: all
all: clean $(EXEC1)

$(EXEC1): $(OBJMAIN) $(HEADS)
	$(CO) $(CFLAGS) $(OBJMAIN) -o $@

.PHONY: run
run: $(EXEC1)
	./$(EXEC1)

.PHONY: clean tar
clean:
	$(RM) -f *.o *.out core


tar: clean
	@(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )
