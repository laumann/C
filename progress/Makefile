#### Definitions ####
# (using := means immediate binding)
CC      := gcc
CFLAGS  := -Wall -g
RM      := rm -rfv
MKDIR   := mkdir -v

BINDIR  := bin
BIN     := $(BINDIR)/use_progress

OBJDIR  := obj
OBJECTS := $(addprefix $(OBJDIR)/,\
		progress.o use_progress.o)

# Phony targets
.PHONY: clean help run compile

#### Target section ####
compile: $(BIN)

help:
	@echo "This progress bar is taken directly from git -- because I like it, and it serves"
	@echo "as a good exercise to see how some C code works. Run:"
	@echo ""
	@echo "  'make run'"
	@echo ""
	@echo "or"
	@echo ""
	@echo "  'make compile'  (default)"
	@echo ""
	@echo "to see an example program."


run: $(BIN)
	$<

$(BIN): $(OBJECTS) | $(BINDIR)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS)

$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJECTS): progress.h git-compat-util.h bswap.h | $(OBJDIR)
$(OBJDIR) $(BINDIR): ; @$(MKDIR) $@

# Dependencies - difficult to express in this form
# progress.o: progress.h git-compat-util.h bswap.h
# use_progress.o: progress.h

clean:
	@$(RM) $(OBJDIR) $(BINDIR)
