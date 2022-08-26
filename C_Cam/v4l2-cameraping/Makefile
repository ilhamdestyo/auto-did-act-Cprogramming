PREFIX?=/usr/local/
BINDIR?=$(PREFIX)bin/
CFLAGS:=-W -Wall -pedantic

.PHONY: all
all: v4l2-cameraping

.PHONY: clean
clean:
	$(RM) v4l2-cameraping

.PHONY: install
install:
	install -d $(BINDIR)
	install -t $(BINDIR) v4l2-cameraping
