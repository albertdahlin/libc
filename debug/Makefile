APP = test

.ifmake dist
  CFLAGS += -DNDEBUG
.else
  CFLAGS +=-g -Wall -Wextra
.endif

all: clean $(APP)

dev: all
dist: all

clean:
	rm -f $(APP)
