/*
 * reader.cpp
 *
 *  Created on: Mar 22, 2016
 *      Author: sumanth
 */

/*
 * test.cpp
 *
 *  Created on: Mar 21, 2016
 *      Author: sumanth
 */

#include <iostream>
#include <cstring>
#include <string>

#define TEMP_SIZE 10
#ifdef __cplusplus
extern "C" {
#endif

void memsh_init();
size_t memsh_read(char *msg);
#ifdef __cplusplus
}
#endif

using namespace std;

int main(int argc, char* argv[]) {

	char ch;
	memsh_init();
	char *buf = new char[TEMP_SIZE]();
	while (1) {
		cout << "Press R to read or X to exit" << endl;
		cin >> ch;
		if (ch == 'X') {
			break;
		}
		while (ch != 'R') {
			cout << "please choose the right option" << endl;
			cin >> ch;
		}
		int bytes_read;
		bytes_read = memsh_read(buf);
		cout << "DATA READ: " << buf << endl << "no. of Bytes read = "
				<< bytes_read << endl;
	}

	return 0;

}
