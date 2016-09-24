SRC_DIR ?= .
SOURCES := $(abspath $(wildcard $(SRC_DIR)/*.cpp))
INCLUDES ?= -I .
ifdef INC_OOTEST
	INCLUDES += -I $(INC_OOTEST)
else
	INCLUDES += -I OOTest
endif
CC = g++
CFLAGS = -g3 -O0 -std=c++11
LIBS = -ldl -lrt
OBJS = $(SOURCES:.cpp=.o)
TEAMNO ?= 00
PBNO ?= 01
MAIN = PB$(TEAMNO)$(PBNO)
.PHONY: depend clean
all:	RUN
	@echo $(SOURCES)
	
$(MAIN): $(OBJS) 
	@echo $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)
RUN: $(MAIN)
	./$(MAIN)
	cppcheck $(INCLUDES)/ --enable=all $(SRC_DIR) 
	pmccabe -v $(SOURCES)
	#valgrind --leak-check=full ./$(MAIN)
		
.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

clean:
	$(RM) *.o *~ $(MAIN)

depend: $(SRCS)
	makedepend $(INCLUDES) $^

# DO NOT DELETE THIS LINE -- make depend needs it
