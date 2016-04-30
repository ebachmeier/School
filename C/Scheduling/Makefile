CC=gcc

all: comparison2 setscheduler cpuTimeWaste compare kernelinfo observer comparison1

cpuTimeWaste: cpuTimeWaste.c
	$(CC) -o $@ $^

compare: compare.c
	$(CC) -o $@ $^

kernelinfo: kernelInfo.c
	$(CC) -o $@ $^

observer: observer.c
	$(CC) -o $@ $^

comparison1: comparison1.c
	$(CC) -o $@ $^

setscheduler: setScheduler.c
	$(CC) -o $@ $^

comparison2: comparison2.c
	$(CC) -o $@ $^

clean:
	rm -f *.o comparison2 setscheduler cpuTimeWaste compare kernelinfo observer comparison1
