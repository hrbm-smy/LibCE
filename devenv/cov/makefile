# Target
TARGET = bin/LibCE_UnitTester.exe

# Commands, options
INCLUDES += -I../../inc

CC = gcc
CFLAGS += -Wall
CFLAGS += -MD
CFLAGS += --coverage
CFLAGS += -D_UNIT_TEST

#CXX = g++	# embedded
CXXFLAGS += $(CFLAGS)

GCOV = gcov
COVFLAGS =

RM = del
RMFLAGS = /F /Q

# Sources, Objects
# $(VARIABLE:OLD_PREFIX%OLD_SUFFIX=NEW_PREFIX%NEW_SUFFIX)

# ../
SRCS_01 += ../LibCE_UnitTester.cpp
OBJS_01 = $(SRCS_01:../%.cpp=obj/%.o)
OBJS += $(OBJS_01)

obj/%.o: ../%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ -c $<

# ../../src
SRCS_02 += ../../src/Assertions.c
SRCS_02 += ../../src/AvlTree.c
SRCS_02 += ../../src/Encoders.c
SRCS_02 += ../../src/Indices.c
SRCS_02 += ../../src/Map.c
SRCS_02 += ../../src/MmIo.c
SRCS_02 += ../../src/RingedFrames.c
SRCS_02 += ../../src/SchmittTrigger.c
OBJS_02 = $(SRCS_02:../../%.c=obj/%.o)
OBJS += $(OBJS_02)

obj/src/%.o: ../../src/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

COVS_02 = $(SRCS_02:../../src/%.c=%.c.gcov)
COVS += $(COVS_02)

%.c.gcov: obj/src/%.gcda
	$(GCOV) $(COVFLAGS) -o obj/src $< > $@.log

# Targets
all: $(TARGET) gcov

.PHONY: all

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)
	$(TARGET)

gcov: $(COVS)

.PHONY: gcov

clean:
	$(RM) $(RMFLAGS) bin\*.*
	$(RM) $(RMFLAGS) obj\*.*
	$(RM) $(RMFLAGS) obj\src\*.*
	$(RM) $(RMFLAGS) *.gcov
	$(RM) $(RMFLAGS) *.log

.PHONY: clean

-include obj/*.d
-include obj/src/*.d
