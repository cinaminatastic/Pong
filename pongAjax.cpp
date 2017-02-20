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
	
	string test = "Test worked";
	
	
	// create the FIFOs for communication
	Fifo nameRec_fifo(nameRec);
	Fifo nameSend_fifo(nameSend);

	Cgicc cgi;    // Ajax object
	
	form_iterator name = cgi.getElement("name");
	string message = **name;
	
	
	//cout << message;
	
	nameSend_fifo.openwrite();
	nameSend_fifo.send(message);
	
	
	/*nameRec_fifo.openread();
	string recName = nameRec_fifo.recv();
	nameRec_fifo.fifoclose();*/
	
	cout << "Content-Type: text/html\n\n";
	cout << message;
	nameSend_fifo.fifoclose();	
	
	return 0;
}
