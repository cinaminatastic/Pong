/*************************************************************/
/* Authors: Alex Seaver and Coire Gavin-Hanner               */
/* Date Created: 2-17-17					                 */
/*                                                           */
/* Variables:
		ballx, bally
		pad1y, pad1x, pad2y, pad2x
		padw, padh (same for both paddles)
		height
		*/



#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <sstream>
#include "fifo.h"
using namespace std;


int main()
{
	string p1Name, p2Name;
	string nameRec_fifo = "name_request";
	string nameSend_fifo = "name_reply";
	
	// create the FIFOs for communication
	Fifo nameRecfifo(nameRec_fifo);
	Fifo nameSendfifo(nameSend_fifo);
	
	
	while(1) {
		nameRecfifo.openread();
		p1Name = nameRecfifo.recv();
		nameRecfifo.fifoclose();
		cout << "Name: " << p1Name << endl;

		nameSendfifo.openwrite();
		nameSendfifo.send(p1Name);
		nameSendfifo.fifoclose();
	}
	
	return 0;
}
