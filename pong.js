var x = 150; //positions of the ball
var xNew;
var dx = 2; //can set these to random numbers in the beginning
var mirrorx = 150;
var y = 150;
var ctx;
var width;
var height;
var paddley;
var paddle2y;
var paddlew = 10;
var paddleh = 75;
var intervalId = 0;
var userNumber = -1;
var padRec;
var intVar;
var waitPaddleMove = false;

var XMLHttp;
var XMLHttp2;
var upDown = false;
var downDown = false;
var name
var i = 0;

function initialize() { //this function is called at least

	if(navigator.appName == "Microsoft Internet Explorer") {
		XMLHttp = new ActiveXObject("Microsoft.XMLHTTP");
		XMLHttp2 = new ActiveXObject("Microsoft.XMLHTTP");
	} else {
		XMLHttp = new XMLHttpRequest(); //this else part is entered using chrome
		XMLHttp2 = new XMLHttpRequest();
	}
	document.getElementById("canvas").style.background = 'rgb(128, 128, 128)';
	init();
	paddley = height/2;
	paddle2y = height/2;

}

function paddleEnd() {
    clearInterval(intVar);
}
function paddle() {

    intVar = setInterval(function(){ movePaddle()}, 500);
}

function movePaddle() {
	console.log("tope of movePaddle: " + waitPaddleMove);
    if (waitPaddleMove) {
		console.log("Error - previous paddle move not complete");
		//return;
    }
    waitPaddleMove = true;
    console.log(waitPaddleMove);
    if(upDown) {
		paddley -= 10;
		
	} else if(downDown) {
		paddley +=10;
	}

    
    
    var sendStr = "/cgi-bin/seavera_pongAjax.cgi?" + "&name=" + name + "&userNumber=" + userNumber + "&paddley=" + paddley;
    console.log("Send:"+ sendStr);
    XMLHttp2.open("GET", sendStr, true);

    XMLHttp2.onreadystatechange=function() {
    	if (XMLHttp2.readyState == 4) {
    		//console.log("if (XMLHttp2.readyState == 4)");
			padRec = XMLHttp2.responseText;;
			
			paddle2y = padRec.slice(0, padRec.indexOf("*"));
			console.log(paddle2y);
			xNew = padRec.slice(padRec.indexOf("*") + 1, padRec.lastIndexOf("*"));
			console.log("First x: " + x);
			console.log("xNew: " + xNew);
			if (userNumber === "2") {
				dx = mirrorx - xNew;
				x += dx;
				console.log("Second x: " + x);
				mirrorx = xNew;
				}
			else {
				x = xNew;
				}
				
			console.log("x: " + x);
			y = padRec.slice(padRec.lastIndexOf("*") +1, padRec.length);
			console.log("y: " + y);
			
			if (padRec === undefined) {
				console.log("Null response");
    		} else {
				//console.log("else statement		Recv: " + padRec + ":" + paddle2y);
				clear(); //clears the rectangle...?
				rect(0, paddley, paddlew, paddleh);
				rect(width - paddlew, paddle2y, paddlew, paddleh); //sets the position of the paddle //sets the position of the paddle
				circle(x, y, 10); //sets the ball in motion
				waitPaddleTrue = false;
				//console.log(waitPaddleTrue);
				//i++;
				//console.log(i);
			
   		 	}
		}
	}
    
    XMLHttp2.send(null);
    
}

function getUsername() { //function is called when submit is pressed

    name = document.getElementById('name').value;	     
    console.log("getUsername");
    if (name === undefined) return;

    XMLHttp.open("GET", "/cgi-bin/gavinhannerc_pongAjax.cgi?" + "&name=" + name + "&userNumber=" + userNumber + "&paddley=" + paddley, true);
    XMLHttp.onreadystatechange=function() {	
		var tuser = XMLHttp.responseText;
		console.log("Getting user:"+tuser);
		if ((tuser !== undefined) && (tuser.length > 0)) {
			userNumber = tuser;
		}
		document.getElementById('response_area').innerHTML = userNumber;;
		console.log("setting user number: "+ userNumber);
    }
    XMLHttp.send(null);
    upDown = false;
	downDown = false;
}

function rect(x, y, w, h) {
    ctx.beginPath();
    ctx.rect(x, y, w, h); 
    ctx.closePath();
    ctx.fill();
}

function circle(x, y, r) {
    ctx.beginPath();
    ctx.arc(x, y, r, 0, Math.PI * 2, true);
    ctx.closePath();
    ctx.fill();
}

function clear() {
    ctx.clearRect(0, 0, width, height);
}

function getWord() { //function is called when submit is pressed

    var name = document.getElementById('name').value;	     

    if (name.length < 1) return;

    XMLHttp.open("GET", "/cgi-bin/gavinhannerc_pongAjax.cgi?" + "&name=" + name, true);

    XMLHttp.onreadystatechange=function() {
	document.getElementById('response_area').innerHTML = XMLHttp.responseText;;
	}
    XMLHttp.send(null);
}

$(document).keydown(function(e) { //gives the value of the key when you press down
    if(e.keyCode == 40) {
        downDown = true;
    } else if(e.keyCode = 38) {
        upDown = true;
    }
    else if(e.keycode != 40) {
    	downDown = false;
    }
    else if(e.keycode != 38) {
    	upDown = false;
    }
});
$(document).keyup(function(e) { //tells the program that you have stopped pressing the key
    if(e.keyCode == 40) {
        downDown = false;
    } else if(e.keyCode == 38) {
        upDown = false;
    }
    else if(e.keycode != 40) {
    	downDown = false;
    }
    else if(e.keycode != 38) {
    	upDown = false;
    }
});
	

function init() {
    ctx = $("#canvas")[0].getContext("2d");
    width = $("#canvas").width();
    height = $("#canvas").height();
    paddlex = width / 2;
    //intervalId = setInterval(draw, 20);
    //return intervalId;
}

/*
 * 	x: x-coord of upper left corner
 *	y: y-coord of upper left corner
 *	w: width of the rectangle
 *	h: height of the rectangle
 

function clear() {
    ctx.clearRect(0, 0, width, height);
}


$(document).keydown(function(e) { //gives the value of the key when you press down
    if(e.keyCode == 39) {
        rightDown = true;
    } else if(e.keyCode = 37) {
        leftDown = true;
    }
});
$(document).keyup(function(e) { //tells the program that you have stopped pressing the key
    if(e.keyCode == 39) {
        rightDown = false;
    } else if(e.keyCode == 37) {
        leftDown = false;
    }
});

function draw() {
    clear(); //clears the rectangle...?
    circle(x, y, 10); //sets the ball in motion
    if(leftDown) {
        paddlex -= 5; //if the user is pressing the left arrow, move to the left
    } else if(rightDown) {
        paddlex += 5; // move to the right
    }
    rect(paddlex, height - paddleh, paddlew, paddleh); //sets the position of the paddle
    if (x + dx > width || x + dx < 0) { //if the ball hits the sides of the board. [0--------width]
        dx = -dx;
    }
    if (y + dy < 0) { //if y is less than 0, reverse the direction of the ball
        dy = -dy;
    } else if (y + dy > height) { //if the ball goes farther down than it should
        if (x > paddlex && x < paddlex + paddlew) { //if the x position of the ball is along the paddle, reverse the direction
            dy = -dy;
        } else { //if not along the paddle, clear the game
            clearInterval(intervalId);
        }
    }
    x += dx; //new changes in ball position
    y += dy;
}

init();*/
