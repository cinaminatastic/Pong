var x = 120; //positions of the ball
var y = 100;
var dx = 2; //can set these to random numbers in the beginning
var dy = 8;
var ctx;
var width;
var height;
var paddlex;
var paddlew = 75;
var paddleh = 10;
var intervalId = 0;


var XMLHttp;

function createAjax() { //this function is called at least

	if(navigator.appName == "Microsoft Internet Explorer") {
		XMLHttp = new ActiveXObject("Microsoft.XMLHTTP");
	} else {
		XMLHttp = new XMLHttpRequest(); //this else part is entered using chrome
	}

}

function getWord() { //function is called when submit is pressed

    var name = document.getElementById('name').value; //works	     

    if (name.length < 1) return;

    XMLHttp.open("GET", "/cgi-bin/gavinhannerc_pongAjax.cgi?" + "&name=" + name, true);

    XMLHttp.onreadystatechange=function() {
    	//document.getElementById('response_area').innerHTML = name;
	document.getElementById('response_area').innerHTML = XMLHttp.responseText;;
	}
    XMLHttp.send(null);
}
	

/*function init() {
    ctx = $("#canvas")[0].getContext("2d");
    width = $("#canvas").width();
    height = $("#canvas").height();
    paddlex = width / 2;
    intervalId = setInterval(draw, 20);
    return intervalId;
}

function circle(x, y, r) {
    ctx.beginPath();
    ctx.arc(x, y, r, 0, Math.PI * 2, true);
    ctx.closePath();
    ctx.fill();
}

function rect(x, y, w, h) {
    ctx.beginPath();
    ctx.rect(x, y, w, h); 
    ctx.closePath();
    ctx.fill();
}

 * 	x: x-coord of upper left corner
 *	y: y-coord of upper left corner
 *	w: width of the rectangle
 *	h: height of the rectangle
 

function clear() {
    ctx.clearRect(0, 0, width, height);
}

var leftDown = false;
var rightDown = false;

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
