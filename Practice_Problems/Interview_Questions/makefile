app.out: ../Library/FileIO.cpp ../Library/FileIO.h ctc.cpp
	g++ -g -Wall ../Library/FileIO.cpp ctc.cpp -o app.out

clean:
	rm *.o *.out app

debug:
	lldb app.out

run:
	./app.out
