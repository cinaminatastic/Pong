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
	string nameRec = "name_reply"; //use this to identify different users
	string nameSend = "name_request";
	
	string recName = "Did not receive";
	
	
	// create the FIFOs for communication
	Fifo nameRec_fifo(nameRec);
	Fifo nameSend_fifo(nameSend);

	Cgicc cgi;    // Ajax object
	
	form_iterator name = cgi.getElement("name");
	string message = **name;
	

	nameSend_fifo.openwrite();
	nameSend_fifo.send(message);
	nameSend_fifo.fifoclose();
	
	
	nameRec_fifo.openread();
	recName = nameRec_fifo.recv();
	
	cout << "Content-Type: text/html\n\n";
	cout << recName;
	nameRec_fifo.fifoclose();	
	
	return 0;
}
