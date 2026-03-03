CC = gcc
CFLAGS = -ansi -Wall -pedantic
TARGET = Shani_Peled_remove_blanks

$(TARGET).exe: $(TARGET).o
	$(CC) $(CFLAGS) -o $(TARGET).exe $(TARGET).o

$(TARGET).o: $(TARGET).c $(TARGET).h
	$(CC) $(CFLAGS) -c $(TARGET).c

clean:
	del /f *.o $(TARGET).exe