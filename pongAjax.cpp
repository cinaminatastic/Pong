/*************************************************************/
/* Pong CGI program                                          */
/*************************************************************/

#include <iostream>
// Stuff for AJAX
#include "cgicc/Cgicc.h"
#include "cgicc/HTTPHTMLHeader.h"
#include "cgicc/HTMLClasses.h"

//Stuff for pipes
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include "fifo.h"

using namespace std;
using namespace cgicc; // Needed for AJAX functions.

int main()
{
	string nameRec_fifo = "receivename";
	string nameSend_fifo = "sendname";

	Cgicc cgi;    // Ajax object
	
	string name = cgi.getElement("name");
	
	nameSend_fifo.openwrite();
	nameSend_fifo.send(name);
	nameSend_fifo.fifoclose();
	
	nameRec_fifo.openread();
	string recName = nameRec_fifo.recv();
	nameRec_fifo.fifoclose();
	
	cout << recName;
	
	
	return 0;
}
