/*
 * test.cpp
 *
 *  Created on: Mar 21, 2016
 *      Author: sumanth
 */

#include <iostream>
#include <cstring>
#include <string>
#ifdef __cplusplus
extern "C" {
#endif

void memsh_init();
size_t memsh_write(char *msg);
#ifdef __cplusplus
}
#endif

using namespace std;

int main(int argc, char* argv[]) {
	string message;
	memsh_init();
	while (1) {
		cout << "enter the string to be sent:" << endl;
		getline(cin, message);
		cout << "DATA BEING WRITTEN! Wait until previous data is read!! "
				<< endl;
		int length;
		length = message.length();

		char *buf = new char[length]();
		strcpy(buf, message.c_str());
		int bytes_done = memsh_write(buf);
		cout << bytes_done << " bytes were written successfully" << endl;

	}
	return 0;

}
