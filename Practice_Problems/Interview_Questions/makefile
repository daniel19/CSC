app.out: FileIO.cpp FileIO.h ctc.cpp
	g++ -g -Wall FileIO.cpp ctc.cpp -o app.out

clean:
	rm *.o *.out app

debug:
	lldb app.out
run:
	./app.out
