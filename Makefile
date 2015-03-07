all: reaper

reaper: reaper.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LIBS)
