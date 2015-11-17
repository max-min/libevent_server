TOP :=.

INC := $(TOP)/include
LIB := $(TOP)/lib
SRC_PATH += $(TOP)/src


#LIVE555_INC += -I$(INC)/liveMedia
#LIVE555_INC += -I$(INC)/BasicUsageEnvironment 
#LIVE555_INC += -I$(INC)/groupsock
#LIVE555_INC += -I$(INC)/UsageEnvironment
#
CFLAGS += -I$(INC)

LIVEEVENT_LIB += $(LIB)/libevent.a
LIVEEVENT_LIB += $(LIB)/libevent_core.a
LIVEEVENT_LIB += $(LIB)/libevent_extra.a
LIVEEVENT_LIB += $(LIB)/libevent_pthreads.a

LDFLAGS += $(LIVEEVENT_LIB)
LDFLAGS += -ldl -pthread  -g

OBJS :=$(TOP)/obj

SRC += $(wildcard $(SRC_PATH)/*.cpp)
OBJECT_FILE:=$(addprefix $(OBJS)/, $(addsuffix .o, $(basename $(notdir $(SRC)))))

CC := g++ 
EXE:=Event_SRV
DEPFILE:=$(TOP)/deps

.PHONY:all
all:$(DEPFILE) $(EXE)

$(DEPFILE): $(SRC) Makefile
	@echo "Live555 Generating new dependency file...";
	@-rm -f $(DEPFILE)
	@for f in $(SRC); do \
		OBJ=$(OBJS)/`basename $$f|sed -e 's/\.cpp/\.o/' -e 's/\.c/\.o/'`; \
		echo $$OBJ: $$f>> $(DEPFILE); \
		echo '	$(CC) $$(CFLAGS)  -c -o $$@ $$^'>> $(DEPFILE); \
		done

-include $(DEPFILE)

############################################
$(EXE): $(OBJECT_FILE)
	$(CC) $(CFLAGS) $(OBJECT_FILE) -o "$@" $(LDFLAGS)

.PHONY:clean
clean:
	rm -rf $(EXE)
	rm -rf $(DEPFILE)
	rm -rf $(OBJS)/*.o
