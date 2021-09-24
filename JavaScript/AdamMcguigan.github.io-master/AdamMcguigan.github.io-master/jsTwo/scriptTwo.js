var canvas = document.getElementById("game");
var context = canvas.getContext("2d");
var playerHealth = 110;
var npcHealth = 100;
var score = 0;



var background = new Image();
background.src = './imgTwo/background.jpg';

var gunImage = new Image();
gunImage.src = './imgTwo/gun.jpg';

var longSword = new Image();
longSword.src = './imgTwo/w_longsword_cold.png';

var magicStaff = new Image();
magicStaff.src = './imgTwo/$Staff.png';

var healingPotion = new Image();
healingPotion.src = './imgTwo/mana.png';

var fireball = new Image();
fireball.src ='./imgTwo/fireballSpriteSheetwizard.png';

var fireballEnemy = new Image();
fireballEnemy.src = './imgTwo/fireballSpriteSheet.png';

var dragonClaw = new Image();
dragonClaw.src = './imgTwo/dragonClaw.png';

var healingSprite = new Image();
healingSprite.src = './imgTwo/HealingSpriteSheet.png';

var helpScreen = new Image();
helpScreen.src = './imgTwo/HelpScreen.png';

var meleeAttackCalled = false;
var rangedAttackCalled = false;
var rangedAttackCalledNPC = false;
var healPlayerCalled = false;
var meleeAttackCalledNpc = false;
var healNpcCalled = false;
var helpScreenCalled = false;

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
var username = string2;

	

//The GameObjects
function GameObject(name, img, health) 
{
    this.name = name;
    this.img = img;
    this.health = health;
    this.x = 0;
    this.y = 0;
	var nextMovePositionX = 0;
	var nextMovePositionY = 0;
}

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




function drawHealthbarNPC() 
{
  var width = 100;
  var height = 20;
  var max = 100;
  var val = npcHealth;

  // Draw the background
  context.fillStyle = "#000000";
  context.clearRect(canvas.width - 105, 0, width, height);
  context.fillRect(canvas.width - 105, 0, width, height);

  // Draw the fill
  context.fillStyle = "#00FF00";
  var fillVal = Math.min(Math.max(val / max, 0), 1);
  context.fillRect(canvas.width - 105, 0, fillVal * width, height);
}

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

var gameOverSprite = new Image();
gameOverSprite.src = "./imgTwo/winner.jpg";

var loseScreen = new Image();
loseScreen.src = "./imgTwo/you lose.jpg";


// Sprite for the player
var playerSprite = new Image();
playerSprite.src = "./imgTwo/odin.png"; 


//Sprite for the enemy
var enemySprite = new Image();
enemySprite.src = "./imgTwo/leviathan.png";

////////////////////////////////////////////////////AUDIO LOADING BELOW//////////////////////////////////////
var audio = new Audio('buttonSound2.mp3');
var cyberpunk = new Audio('Cyberpunk 2077 Hype.mp3');
var minecraft = new Audio('C418 - Sweden - Minecraft Volume Alpha.mp3');
var undertale = new Audio('Undertale - Megalovania.mp3');
var swordAudio = new Audio('SwordSound.mp3');
var fireballAudio = new Audio('FireballSoundEffect.mp3');
var healingAudio = new Audio('HealingSoundEffect.mp3');
var movementAudio = new Audio('GallopingSoundEffect.mp3');
var dragonAudio = new Audio('FireBallDragon.mp3');
var dragonRoarAudio = new Audio('DragonRoar.mp3');
var healingEffect = new Audio('healingSoundEffectDragon.mp3');
var winScreenAudio = new Audio('winScreenMusicTrimmed.mp3');
var loseScreenAudio = new Audio('loseScreenMusic.mp3');

function GamerInput(input) 
{
    this.action = input;
}

var gamerInput = new GamerInput("None"); //No Input

// Default Player
var Player = new GameObject("player", playerSprite ,100);

//Default Enemy
var Npc = new GameObject("NPC", enemySprite, 100); // change the img to a new variable

// Gameobjects is a collection of the Actors within the game
var gameobjects = [Player, Npc];
gameobjects[0].x = 100;
gameobjects[0].y = 500;

gameobjects[1].x = 1200;
gameobjects[1].y = 500;


var xPositionPlayer = gameobjects[0].x = 100;
var yPositionPlayer = gameobjects[0].y = 500;

var random;
// Process keyboard input event
function input(event) {
    // Take Input from the Player
     //console.log("Input");
     //console.log("Event type: " + event.type);

}


var fireballPosX = gameobjects[0].x;
var fireballNPCPosX = gameobjects[1].x;

function update()
{
	
	while(rangedAttackCalled == true)
		{
			fireballAudio.play();
			fireballPosX += 10;
			if(fireballPosX >= gameobjects[1].x + 30 )
			{
				fireballPosX = gameobjects[0].x;
				rangedAttackCalled = false;
			}
			return fireballPosX;
			
		}
		
		while(rangedAttackCalledNPC == true)
		{
			dragonAudio.play();
			fireballNPCPosX -= 10;
			if(fireballNPCPosX <= gameobjects[0].x - 30)
			{
				fireballNPCPosX = gameobjects[1].x;
				rangedAttackCalledNPC = false;
			}
			return fireballNPCPosX;
			
		}
		
		if(npcHealth <= 0)
		{
			fireballEnemy.x = 10000;
			fireballEnemy.y = 10000;
		}
	
		
		
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
		context.fillText(score, 100,200);
		context.drawImage(background,0,0,canvas.width,canvas.height);
		context.fillText(username, gameobjects[0].x,gameobjects[0].y);
		
		
			
		for(i = 0; i < gameobjects.length; i++)
		{
			context.drawImage(gameobjects[0].img, (gameobjects[0].img.width / frames) * currentFrame, 160 ,80, 80, gameobjects[0].x, gameobjects[0].y, 100, 100);//(gameobjects[0].img.width / frames) * currentFrame, 0 ,40, 55, gameobjects[0].x, gameobjects[0].y, 190, 190); //change the values just after current frame to change whats drawn for the sprites
			context.drawImage(gameobjects[1].img, (gameobjects[1].img.width / frames) * currentFrame, 96 ,96, 96, gameobjects[1].x, gameobjects[0].y, 100, 100);//(gameobjects[1].img.width / frames) * currentFrame, 0 ,42, 62, gameobjects[1].x, gameobjects[0].y, 100, 100); //150,600,1000
		}
			
			
			
			if(npcHealth <= 0)
			{
				winScreenAudio.play();
				cyberpunk.pause();
				undertale.pause();
				minecraft.pause();
				context.clearRect(0,0, canvas.width, canvas.height);
				gameobjects[0].x = 5000;
				gameobjects[0].y = 5000;
				gameobjects[1].x = -5000;
				gameobjects[1].y = -5000;
				context.drawImage(gameOverSprite,0,0,canvas.width,canvas.height);
				fireballEnemy.x = 10000;
				fireballEnemy.y = 10000;
				console.log("Drawing the game over sprite");
				
			}
			
			if(playerHealth <= 0)
			{
				loseScreenAudio.play();
				cyberpunk.pause();
				undertale.pause();
				minecraft.pause();
				context.clearRect(0,0, canvas.width, canvas.height);
				gameobjects[0].x = 5000;
				gameobjects[0].y = 5000;
				gameobjects[1].x = 10000;
				gameobjects[1].y = 10000;
				context.drawImage(loseScreen,0,0, canvas.width,canvas.height);
				console.log("Drawing the game over sprite");
			}
			
			if(helpScreenCalled == true)
			{
				gamerInput = new GamerInput("Helpbutton");
				console.log("drawing the helpScreen sprite");
				//gamerInput = new GamerInput("Helpbutton");
				context.clearRect(0,0, canvas.width, canvas.height);
				context.drawImage(helpScreen,0,0,canvas.width,canvas.height);
				document.onkeydown = function(evt)
				{
				 // var x = event.keyCode;
				  evt = evt || window.event;
				  if(evt.keyCode == 27)
				  {  // 27 is the ESC key
					context.clearRect(0,0, canvas.width, canvas.height);
					context.drawImage(background,0,0,canvas.width, canvas.height);
					helpScreenCalled = false;
				  }
				}
				//helpScreenCalled = false;
				return helpScreenCalled;
			}
				
		drawHealthbar();
		drawHealthbarNPC();
		
		if(meleeAttackCalled == true)
		{
			var longSwordPosX = gameobjects[0].x;
			var longSwordPosY = gameobjects[0].y;
			context.drawImage(longSword,longSwordPosX + 30,longSwordPosY,50,50);
	        console.log("drawing the sword Sprite");
		}
		
		
		if(rangedAttackCalled == true)
		{
			var magicStaffPosX = gameobjects[0].x;
		    var magicStaffPosY = gameobjects[0].y; 
			context.drawImage(magicStaff,magicStaffPosX + 20,magicStaffPosY,200,200);
			context.drawImage(fireball, (fireball.width / frames) * currentFrame, 256 ,64, 80, fireballPosX, magicStaffPosY, 100, 100);
			if(fireballPosX >= gameobjects[1].x)
			{
				npcHealth -= 5;
			}
			console.log("drawing the magic staff Sprite");
		}
		
		if(healPlayerCalled == true)
		{
			var healingPotionPosX = gameobjects[0].x;
			var healingPotionPosY = gameobjects[0].y;
			context.drawImage(healingPotion,healingPotionPosX + 40,healingPotionPosY + 25,30,30);
			console.log("drawing the healing Potion");
		}
		
		if(rangedAttackCalledNPC == true)
		{
			var enemyPosX = gameobjects[1].x;
			var enemyPosY = gameobjects[1].y; 
			//context.drawImage(magicStaff,magicStaffPosX + 20,magicStaffPosY,200,200);
			context.drawImage(fireballEnemy, (fireballEnemy.width / frames) * currentFrame, 0 ,64, 80, fireballNPCPosX - 20, enemyPosY, 100, 100);
			if(fireballNPCPosX <= gameobjects[0].x)
			{
				playerHealth -= 0.5;
			}
			console.log("drawing the fireball Sprite");
		}
		
		if(meleeAttackCalledNpc == true)
		{
			var scratchPosX = gameobjects[0].x;
			var scratchPosY = gameobjects[0].y
			
			context.drawImage(dragonClaw,scratchPosX + 25,scratchPosY,50,50);
			console.log('drawing the npc melee attack');
		}
		
		if(healNpcCalled == true)
		{
			var healingPosX = gameobjects[1].x;
			var healingPosY = gameobjects[1].y;
			var frames2 = 25;
			context.drawImage(healingSprite, (healingSprite.width / frames) * currentFrame, 192 ,192, 192, healingPosX, healingPosY - 20, 100, 100);
			console.log("drawing the healing SpriteSheet");
		}
				
}

//////////////////////////////////////////////////////////////////
function moveForwardPlayer()
{
	movementAudio.play();
	gamerInput = new GamerInput("right"); // this is just for the button press 
	gameobjects[0].x += 10;
	console.log("player pushed forward");
	healPlayerCalled = false;
	rangedAttackCalled = false;
	meleeAttackCalled = false;
}



function rangedAttackPlayer()
{
	gamerInput = new GamerInput("left");
	//var distance = gameobjects[0].x - gameobjects[1].x;
	console.log("player used ranged attack");
	meleeAttackCalled = false;
	rangedAttackCalled = true;
	healPlayerCalled = false;
	return rangedAttackCalled;
}

function healPlayer()
{
	healingAudio.play();
	playerHealth += 5;
	healPlayerCalled = true;
	rangedAttackCalled = false;
	meleeAttackCalled = false;
	return healPlayerCalled;
}



function meleeAttack()
{
	//var meleeDistance = 400;
	if(gameobjects[0].x >= 350 && gameobjects[1].x >= 200)
	{
		npcHealth -= 10;
		swordAudio.play();
	}
	
	rangedAttackCalled = false;
	meleeAttackCalled = true;
	healPlayerCalled = false;
	return meleeAttackCalled;
	
}
///////////////////////////////////////////////////////////////////

function moveForwardNPC()
{
	gameobjects[1].x -=3
	rangedAttackCalledNPC = false;
	meleeAttackCalledNpc = false;
	healNpcCalled = false;
	
}

function rangedAttackNPC()
{
	rangedAttackCalledNPC = true;
	meleeAttackCalledNpc = false;
	healNpcCalled = false;
	return rangedAttackCalledNPC;
	
	
}

function healNPC()
{
	healingEffect.play();
	npcHealth += 5;
	healNpcCalled = true;
	rangedAttackCalledNPC = false;
	meleeAttackCalledNpc = false; 	
	return healNpcCalled;
}

function meleeAttackNPC()
{
	
	if(gameobjects[0].x >= 350 && gameobjects[1].x >= 200)
	{
		dragonRoarAudio.play();
		playerHealth -= 10;
		meleeAttackCalledNpc = true;
		rangedAttackCalledNPC = false;
		healNpcCalled = false;
	}
	
	return meleeAttackCalledNpc;
}

function randomAbilityNPC()
{
	random = Math.floor(Math.random() * 4) + 1;
	if(gameobjects[1].x <= 149)
	{
		moveForwardNPC();
	}
	if(gameobjects[1].x >= 150)
	{
		
		if(random === 1)
		{
			moveForwardNPC();
			//rangedAttackNPC();
			console.log("NPC moving forward");
		}
		if(random === 2)
		{
			meleeAttackNPC();
			//rangedAttackNPC();
			console.log("NPC used melee attack");
		}
		if(random === 3)
		{
			rangedAttackNPC();
			console.log("NPC used ranged attack");
		}
		if(random === 4)
		{
			healNPC();
			//rangedAttackNPC();
			console.log("NPC healed");
		}
		
	}

}

document.getElementById("buttonUp").onmouseup = function() {ButtonUp()};
document.getElementById("buttonDown").onmouseup = function() {ButtonUp()};
document.getElementById("buttonLeft").onmouseup = function() {ButtonUp()};
document.getElementById("buttonRight").onmouseup = function() {ButtonUp()};
document.getElementById("Helpbutton").onmouseup = function() {ButtonUp()};



//Function for the left input 
function LeftbuttonOnClick()
{
	gamerInput = new GamerInput("Left");
	audio.play();
	rangedAttackPlayer();
	console.log("Player used ranged attack");
	score = score + 1;
	setTimeout(randomAbilityNPC(),5000);
}

//function for moving the player forward 
function RightbuttonOnClick()
{
	gamerInput = new GamerInput("Right");
	audio.play();
	score = score + 1;
	moveForwardPlayer();
	console.log("Moving Forward");
	setTimeout(randomAbilityNPC(),5000); //This function here tells the function to wait 5000 miliseconds before activating
	//randomAbilityNPC();
	
}

//function for the up input
function UpbuttonOnClick()
{
	gamerInput = new GamerInput("Up");
	audio.play();
	score = score + 1;
	healPlayer();
	console.log("Player Healed");
	setTimeout(randomAbilityNPC(),5000);

}

//function for the down input 
function DownbuttonOnClick()
{
	gamerInput = new GamerInput("Down");
	audio.play();
	score = score + 1;
	meleeAttack();
	console.log("Player used melee attack");
	setTimeout(randomAbilityNPC(),5000);
}



//function for the help button
function HelpbuttonOnClick()
{
	//console.log("drawing the helpScreen sprite");
	gamerInput = new GamerInput("Helpbutton");
	helpScreenCalled = true;
	return helpScreenCalled;
	//context.drawImage(helpScreen,0,0,1440,600);
	//if statement for esc to be pressed
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
   drawHealthbarNPC();
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