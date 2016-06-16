all:

		gcc -shared -fPIC  -o libshared.so sharedlib.c -lrt -pthread
		g++ -o writer writer.cpp  -L. -lshared
		g++ -o reader reader.cpp  -L. -lshared
		export LD_LIBRARY_PATH=.
		
clean:
		rm -rf *o *so *out
		rm -rf /run/shm/*txt