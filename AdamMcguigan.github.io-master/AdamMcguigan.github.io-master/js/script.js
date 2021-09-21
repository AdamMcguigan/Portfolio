var canvas = document.getElementById('game')
var context = canvas.getContext('2d');

function buttonOnClick() {
  // alert("Booooommmmmm!!!");
  console.log("Button Pressed");
}

// Update Heads Up Display with Weapon Information
function weaponSelection() {
  var selection = document.getElementById("equipment").value;
  var active = document.getElementById("active");
  if (active.checked == true) {
    document.getElementById("HUD").innerHTML = selection + " active ";
    console.log("Weapon Active");
  } else {
    document.getElementById("HUD").innerHTML = selection + " selected ";
    console.log("Weapon Selected");
  }
}

// Draw a HealthBar on Canvas, can be used to indicate players health
function drawHealthbar() {
  var width = 100;
  var height = 20;
  var max = 100;
  var val = 10;

  // Draw the background
  context.fillStyle = "#000000";
  context.clearRect(0, 0, canvas.width, canvas.height);
  context.fillRect(0, 0, width, height);

  // Draw the fill
  context.fillStyle = "#00FF00";
  var fillVal = Math.min(Math.max(val / max, 0), 1);
  context.fillRect(0, 0, fillVal * width, height);
}

//example of how to declare an array in JavaScript
//var selectionBox = [{"key":  "value"},{},{}];
//var student = [{"name:""joe", "grade":100},{"name":"jane", "grade":100}];


// Array of Weapon Options
var options = [{
    "text": "Select a Weapon",
    "value": "No Weapon",
    "selected": true
  },
  {
    "text": "Spear",
    "value": "Javelin"
  },
  {
    "text": "Sword",
    "value": "Longsword"
  },
  {
    "text": "Crossbow",
    "value": "Pistol crossbow"
  }
];

var selectBox = document.getElementById('equipment');

for (var i = 0; i < options.length; i++) {
  var option = options[i];
  selectBox.options.add(new Option(option.text, option.value, option.selected));
}

drawHealthbar();