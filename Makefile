CFLAGS?=-O3
CFLAGS+=-MMD -MP
LDFLAGS?=
LIB_SRC=array.c
TEST_SRC=main.c $(LIB_SRC)

all:test lib

test:$(patsubst %.c,%.o,$(TEST_SRC))
	$(CC) $(LDFLAGS) -o $@ $^

lib:libarray.a

libarray.a:$(patsubst %.c,%.o,$(LIB_SRC))
	$(AR) -rcs -o $@ $^

%.o:%.c
	$(CC) $(CFLAGS) -c $<

-include $(TEST_SRC:.c=.d)

clean:
	rm -f *.o *.d test libarray.a 
