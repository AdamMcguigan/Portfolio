// Each time this function is called a GameObject
// is create based on the arguments
// In JavaScript you can consider everything an Object
// including functions

//Create 5 new functions then go do it on button up

var canvas = document.getElementById("game");
var context = canvas.getContext("2d");
var playerHealth = 110;
var score = 0;

var xPositionPlayer;
var yPositionPlayer;
// var playerXPosition
//The GameObjects
function GameObject(name, img, health) 
{
    this.name = name;
    this.img = img;
    this.health = health;
    this.x = 0;
    this.y = 0;
}

context.font = "30px Arial";
var url = document.location.href;
var gamertag;

//Function to split a string and output the players gamertag
function splitFunction() 
{
  
  var result = url.split("="); // Splits string based on =
 gamertag = result[1];
 
}

splitFunction();

var string1 = "Hello ";
var string2 = gamertag;
var username = string1.concat(string2);

///////////////////////////////////////////////////////////////////////////////////////////
function buttonOnClick() 
{
  // alert("Booooommmmmm!!!");
  console.log("Button Pressed");
  updateScore();
  
// function onPage() {
  // Using JSON and Local Storage for
  // GameState Management
  var gameObj = 
  {
    'w': 1,

  };
}
function onPageLoad() {
  // Using JSON and Local Storage for
  // GameState Management

	gameobjects[0].x = xPositionPlayer;
	gameobjects[0].y = yPositionPlayer;

  var gameObjects = {
    'pawn': 1,
    'worker': 2,
    'boss': 3
  };



  // Game objects as JSON
  localStorage.setItem('gameObjects', JSON.stringify(gameObjects));

  // Retrieve Games object as from storage
  var npcObjects = localStorage.getItem('gameObjects');

  console.log('npcObjects: ', JSON.parse(npcObjects));

  // Reading Level Information from a file
  var readJSONFromURL = function (url, callback) {
    var xhr = new XMLHttpRequest();
    xhr.open('GET', url, true);
    xhr.responseType = 'json';

    xhr.onload = function () {
      var status = xhr.status;
      if (status == 200) {
        callback(null, xhr.response);
      } else {
        callback(status);
      }
    };

    xhr.send();
  };

  readJSONFromURL('./data/level.json', function (err, data) 
  {
    if (err != null) 
	{
      console.error(err);
    } 
	else 
	{
      xPositionPlayer = data["xPosition"];
      console.log(xPositionPlayer);
      yPositionPlayer = data["yPosition"];
      console.log(yPositionPlayer);
      playerHealth = data["Health"]; 
      console.log(playerHealth);
    }
  });

/*   // Reading File from a Server
  var xmlhttp = new XMLHttpRequest();
  xmlhttp.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {
      var data = JSON.parse(this.responseText);
      document.getElementById("NPC").innerHTML = data[0];
    }
  };
  
  xmlhttp.open("GET", "./data/level.json", true);
  xmlhttp.send();



  updateScore();

} */
}

// Update the player score
function updateScore() 
{
  var current_score = localStorage.getItem('score');

  if (isNaN(current_score)) 
  {
    localStorage.setItem('score');
    document.getElementById("SCORE").innerHTML = " [ " + current_score + " ] ";
  } 
  
  else 
  {
    localStorage.setItem('score', parseInt(current_score) + 1);
    document.getElementById("SCORE").innerHTML = " [ " + current_score + " ] ";
  }

} 

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//function to draw the players health bar
function drawHealthbar() 
{
  var width = 100;
  var height = 20;
  var max = 100;
  var val = playerHealth;

  // Draw the background
  context.fillStyle = "#000000";
  context.clearRect(0, 0, width, height);
  context.fillRect(0, 0, width, height);

  // Draw the fill
  context.fillStyle = "#00FF00";
  var fillVal = Math.min(Math.max(val / max, 0), 1);
  context.fillRect(0, 0, fillVal * width, height);
}

//Function to draw the music selection box and setup the drop down boxes
function musicSelection() {
  var selection = document.getElementById("songs").value;
  var active = document.getElementById("active");
  if (active.checked == true) 
  {
    document.getElementById("HUD").innerHTML = selection + " active ";
    console.log("Audio Active");
	
	if(selection === "Cyberpunk 2077 Hype.mp3")
	{
		cyberpunk.play();
	}
	if(selection === "C418 - Sweden - Minecraft Volume Alpha.mp3")
	{
		minecraft.play();
	}
	if(selection === "Undertale - Megalovania.mp3")
	{
		undertale.play();
	}
	
  } 
  
  else 
  {
    document.getElementById("HUD").innerHTML = selection + " selected ";
    console.log("audio Selected");
	
	cyberpunk.pause();
	cyberpunk.currentTime = 0;
	
	minecraft.pause();
	minecraft.currentTime = 0;
	
	undertale.pause();
	undertale.currentTime = 0;
	
  }
}

var options = [{
    "text": "Select a Audio",
    "value": "No Audio",
    "selected": true
  },
  {
    "text": "Cyberpunk 2077",
    "value": "Cyberpunk 2077 Hype.mp3"
  },
  {
    "text": "Minecraft - Theme",
    "value": "C418 - Sweden - Minecraft Volume Alpha.mp3"
  },
  {
    "text": "Undertale - Megalovania",
    "value": "Undertale - Megalovania.mp3"
  }
];


var selectBox = document.getElementById('songs');

for (var i = 0; i < options.length; i++) 
{
  var option = options[i];
  selectBox.options.add(new Option(option.text, option.value, option.selected));
  
}

function drawHealthbar() {
  var width = 100;
  var height = 20;
  var max = 100;
  var val = playerHealth;

  // Draw the background
  context.fillStyle = "#000000";
  context.clearRect(0, 0, width, height);
  context.fillRect(0, 0, width, height);

  // Draw the fill
  context.fillStyle = "#00FF00";
  var fillVal = Math.min(Math.max(val / max, 0), 1);
  context.fillRect(0, 0, fillVal * width, height);
}


var gameOverSprite = new Image();
gameOverSprite.src = "./img/gameOver.jpg";

// Sprite for the player
var playerSprite = new Image();
playerSprite.src = "./img/hulk.png"; 


//Sprite for the enemy
var enemySprite = new Image();
enemySprite.src = "./img/ryuk.png";

var audio = new Audio('rightFinalOne.mp3');
// var audio = new Audio('buttonsound2.mp3');
var cyberpunk = new Audio('Cyberpunk 2077 Hype.mp3');
var minecraft = new Audio('C418 - Sweden - Minecraft Volume Alpha.mp3');
var undertale = new Audio('Undertale - Megalovania.mp3');

// The GamerInput is an Object that holds the Current
// GamerInput (Left, Right, Up, Down)
function GamerInput(input) 
{
    this.action = input;
}

// Default GamerInput is set to None
var gamerInput = new GamerInput("None"); //No Input

// Default Player
var Player = new GameObject("player", playerSprite ,100);

//Default Enemy
var Npc = new GameObject("NPC", enemySprite, 100); // change the img to a new variable

// Gameobjects is a collection of the Actors within the game
var gameobjects = [Player, Npc];
gameobjects[0].x = 100;
gameobjects[0].y = 100;

gameobjects[1].x = 1200;
gameobjects[1].y = 650;

// Process keyboard input event
function input(event) {
    // Take Input from the Player
     //console.log("Input");
     //console.log("Event type: " + event.type);

    if (event.type === "keydown") {
        switch (event.keyCode) {
            case 37:
                gamerInput = new GamerInput("Left");
                break; //Left key
            case 38:
                gamerInput = new GamerInput("Up");
                break; //Up key
            case 39:
                gamerInput = new GamerInput("Right");
                break; //Right key
            case 40:
                gamerInput = new GamerInput("Down");
                break; //Down key
            default:
                gamerInput = new GamerInput("None"); //No Input
        }
    } else {
        gamerInput = new GamerInput("None"); //No Input
    }
     console.log("Gamer Input :" + gamerInput.action);
}

// Total Frames
var frames = 4;

// Current Frame
var currentFrame = 0;

// X axis to Draw from
var sprite_x = 0;

// Initial time set
var initial = new Date().getTime();
var current; // current time

function animate() 
{
	
    current = new Date().getTime(); // update current
    if (current - initial >= 500) 
	{ // check is greater that 500 ms
        currentFrame = (currentFrame + 1) % frames; // update frame
        initial = current; // reset initial
    } 
		context.clearRect(0,0, canvas.width, canvas.height);
		context.fillText(username, 100,100);
		context.fillText(score, 100,200);
		
			for(i = 0; i < gameobjects.length; i++)
			{
				context.drawImage(gameobjects[0].img, (gameobjects[0].img.width / frames) * currentFrame, 0 ,40, 55, gameobjects[0].x, gameobjects[0].y, 190, 190); //change the values just after current frame to change whats drawn for the sprites
				context.drawImage(gameobjects[1].img, (gameobjects[1].img.width / frames) * currentFrame, 0 ,42, 62, gameobjects[1].x, gameobjects[0].y, 190, 190); //150,600,1000
			}
			
			drawHealthbar();
			
			if(gameobjects[1].health <= 0)
			{
				context.clearRect(0,0, canvas.width, canvas.height);
				gameobjects[0].x = 5000;
				gameobjects[0].y = 5000;
				gameobjects[1].x = 10000;
				gameobjects[1].y = 10000;
				context.drawImage(gameOverSprite,0,0,1600,700);
				console.log("Drawing the game over sprite");
				
			}
				
}

function update() 
{
    // Iterate through all GameObjects
    // Updating position and gamestate
    // console.log("Update");
	
    for (i = 0; i < gameobjects.length; i++) 
	{
	  
        if (gamerInput.action === "Up") 
		{
            gameobjects[1].health = 100;
			gameobjects[0].y -= 5;
            console.log("Up");
        }
		if (gamerInput.action === "Down") 
			{
                gameobjects[0].y += 5;
                console.log("Down");
				console.log(gameobjects[i].name + " at x: " + gameobjects[i].x + " Y: ");
            }
			if(gamerInput.action === "Left")
			{
				gameobjects[0].x -= 5;
				console.log("Left");
			}
			if(gamerInput.action === "Right")
			{
				gameobjects[0].x += 5;
				console.log("Right");
			}
			//movement to follow the player
			if(gameobjects[0].x > gameobjects[1].x)
			{
				gameobjects[1].x +=1;
			}
			//movement to follow the player
			if(gameobjects[0].x < gameobjects[1].x)
			{
				gameobjects[1].x -=1;
			}
			//movement to follow the player
			if(gameobjects[0].y > gameobjects[1].y)
			{
				gameobjects[1].y +=1;
			}
			//movement to follow the player
			if(gameobjects[0].y < gameobjects[1].y)
			{
				gameobjects[1].y -=1;
			}
			//Boundary Checking
			if(gameobjects[0].x >= 1800 || gameobjects[0].y >= 800)
			{
				gameobjects[0].x = 50;
				gameobjects[0].y = 50;
											
			}
			//boundary checking
			if(gameobjects[0].x <= 0 || gameobjects[0].y <= 0)
			{
				gameobjects[0].x = 1200;
				gameobjects[0].y = 200;
												
			}
			if(gameobjects[0].x == gameobjects[1].x && gameobjects[0].y == gameobjects[1].y)
			{
				gameobjects[1].health -= 20;
				playerHealth -= 10;
				console.log("-20 health");
				gameobjects[1].x = 1200;
				gameobjects[1].y = 650;
														
			}
			else 
			{
				console.log(gameobjects[i].name + " at X: " + gameobjects[i].x + "  Y: " + gameobjects[i].y); 
				console.log(gameobjects[i].name + " player Health: " + gameobjects[0].health + "NPC HEALTH" + gameobjects[1].health);
			}
			
    }
	
	
}

document.getElementById("buttonUp").onmouseup = function() {ButtonUp()};
document.getElementById("buttonDown").onmouseup = function() {ButtonUp()};
document.getElementById("buttonLeft").onmouseup = function() {ButtonUp()};
document.getElementById("buttonRight").onmouseup = function() {ButtonUp()};



//Function for the left input 
function LeftbuttonOnClick()
{
	gamerInput = new GamerInput("Left");
	audio.play();
	score = score + 1;
	buttonOnClick();
	
}

//function for the right input
function RightbuttonOnClick()
{
	gamerInput = new GamerInput("Right");
	audio.play();
	score = score + 1;
	buttonOnClick();
	
}

//function for the up input
function UpbuttonOnClick()
{
	gamerInput = new GamerInput("Up");
	audio.play();
	score = score + 1;
	buttonOnClick();
	
}

//function for the down input 
function DownbuttonOnClick()
{
	gamerInput = new GamerInput("Down");
	audio.play();
	score = score + 1;
	buttonOnClick();
	
}

function ButtonUp()
{
	gamerInput = new GamerInput("None");
}

var x = 0,
    y = 1300;
	

// Draw GameObjects to Console
// Modify to Draw to Screen
function draw() 
{
   
    for (i = 0; i < gameobjects.length; i++) 
	{
		
        if (gameobjects[i].health > 0) 
		{
             console.log("Image :" + gameobjects[i].img);
			 animate();
			
        }
		
    }
	

}


function gameloop() 
{
    update();
    draw();
	animate();
    window.requestAnimationFrame(gameloop);
}

// Handle Active Browser Tag Animation
window.requestAnimationFrame(gameloop);

// Handle Keypressed
window.addEventListener('keyup', input);
window.addEventListener('keydown', input);
window.addEventListener('keyright', input);
window.addEventListener('keyleft',input);

