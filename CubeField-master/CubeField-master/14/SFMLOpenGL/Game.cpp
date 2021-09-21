#include <Game.h>
#include <Cube.h>
#include <Easing.h>

// Helper to convert Number to String for HUD
template <typename T>
string toString(T number)
{
	ostringstream oss;
	oss << number;
	return oss.str();
}

GLuint	vsid,		// Vertex Shader ID
		fsid,		// Fragment Shader ID
		progID,		// Program ID
		vao = 0,	// Vertex Array ID
		vbo,		// Vertex Buffer ID
		vib,		// Vertex Index Buffer
		to[1];		// Texture ID
GLint	positionID,	// Position ID
		colorID,	// Color ID
		textureID,	// Texture ID
		uvID,		// UV ID
		mvpID,		// Model View Projection ID
		x_offsetID, // X offset ID
		y_offsetID,	// Y offset ID
		z_offsetID;	// Z offset ID

GLenum	error;		// OpenGL Error Code


//Please see .//Assets//Textures// for more textures
const string filename = ".//Assets//Textures//texture_2.tga";

int width;						// Width of texture
int height;						// Height of texture
int comp_count;					// Component of texture

unsigned char* img_data;		// image data

mat4 mvp, projection, 
		view, model;			// Model View Projection

Font font;						// Game font

float x_offset, y_offset, z_offset; // offset on screen (Vertex Shader)

Game::Game() : 
	window(VideoMode(800, 600), 
	"Introduction to OpenGL Texturing")
{
}

Game::Game(sf::ContextSettings settings) : 
	window(VideoMode(800, 600), 
	"Introduction to OpenGL Texturing", 
	sf::Style::Default, 
	settings)
{
	
	game_object[0] = new GameObject();
	game_object[0]->setPosition(vec3(-1.0f, 0.5f, -7.0f));

	game_object[1] = new GameObject();
	game_object[1]->setPosition(vec3(6.0f, 3.0f, -7.0f));

	game_object[2] = new GameObject();
	game_object[2]->setPosition(vec3(-3.0f, -3.0f, -7.0f));

	game_object[3] = new GameObject();
	game_object[3]->setPosition(vec3(-5.0f, -5.0f, -7.0f));

	game_object[4] = new GameObject();
	game_object[4]->setPosition(vec3(-7.0f, -7.0f, -7.0f));

	game_object[5] = new GameObject();
	game_object[5]->setPosition(vec3(-9.0f, -7.0f, -7.0f));

	game_object[6] = new GameObject();
	game_object[6]->setPosition(vec3(2.0f, 3.0f, -7.0f));

	game_object[7] = new GameObject();
	game_object[7]->setPosition(vec3(-3.0f, 3.0f, -7.0f));

	game_object[8] = new GameObject();
	game_object[8]->setPosition(vec3(-7.0f, 3.0f, -7.0f));

	game_object[9] = new GameObject();
	game_object[9]->setPosition(vec3(5.0f, 0.5f, -7.0f));

	game_object[10] = new GameObject();
	game_object[10]->setPosition(vec3(5.0f, 0.5f, -7.0f));

	game_object[11] = new GameObject();
	game_object[11]->setPosition(vec3(7.0f, 0.5f, -7.0f));

	game_object[12] = new GameObject();
	game_object[12]->setPosition(vec3(9.0f, 0.5f, -7.0f));

	game_object[13] = new GameObject();
	game_object[13]->setPosition(vec3(7.0f, 5.5f, -8.0f));

	game_object[14] = new GameObject();
	game_object[14]->setPosition(vec3(5.0f, 5.5f, -12.0f));

	game_object[15] = new GameObject();
	game_object[15]->setPosition(vec3(-5.0f, 7.5f, -15.0f));

	game_object[16] = new GameObject();
	game_object[16]->setPosition(vec3(-5.0f, 7.5f, -20.0f));

	game_object[17] = new GameObject();
	game_object[17]->setPosition(vec3(-5.0f, 5.5f, -25.0f));

	game_object[18] = new GameObject();
	game_object[18]->setPosition(vec3(-5.0f, 5.5f, -30.0f));

	game_object[19] = new GameObject();
	game_object[19]->setPosition(vec3(-5.0f, 5.5f, -35.0f));

	game_object[20] = new GameObject();
	game_object[20]->setPosition(vec3(-5.0f, 5.5f, -35.0f));

	game_object[21] = new GameObject();
	game_object[21]->setPosition(vec3(-5.0f, 5.5f, -35.0f));

	game_object[22] = new GameObject();
	game_object[22]->setPosition(vec3(-5.0f, 5.5f, -35.0f));

	game_object[23] = new GameObject();
	game_object[23]->setPosition(vec3(-5.0f, 5.5f, -35.0f));

	game_object[24] = new GameObject();
	game_object[24]->setPosition(vec3(-5.0f, 5.5f, -35.0f));

	game_object[25] = new GameObject();
	game_object[25]->setPosition(vec3(-5.0f, 5.5f, -35.0f));

	game_object[26] = new GameObject();
	game_object[26]->setPosition(vec3(-5.0f, 5.5f, -35.0f));

	game_object[27] = new GameObject();
	game_object[27]->setPosition(vec3(-5.0f, 5.5f, -35.0f));

	game_object[28] = new GameObject();
	game_object[28]->setPosition(vec3(-5.0f, 5.5f, -35.0f));

	game_object[29] = new GameObject();
	game_object[29]->setPosition(vec3(-5.0f, 5.5f, -35.0f));

	game_object[30] = new GameObject();
	game_object[30]->setPosition(vec3(-5.0f, 5.5f, -35.0f));

	game_object[31] = new GameObject();
	game_object[31]->setPosition(vec3(-5.0f, 5.5f, -35.0f));

	game_object[32] = new GameObject();
	game_object[32]->setPosition(vec3(-5.0f, 5.5f, -35.0f));

	game_object[33] = new GameObject();
	game_object[33]->setPosition(vec3(-5.0f, 5.5f, -35.0f));

	game_object[34] = new GameObject();
	game_object[34]->setPosition(vec3(-5.0f, 5.5f, -35.0f));

	game_object[35] = new GameObject();
	game_object[35]->setPosition(vec3(-5.0f, 5.5f, -35.0f));

	game_object[36] = new GameObject();
	game_object[36]->setPosition(vec3(-5.0f, 5.5f, -35.0f));

	game_object[37] = new GameObject();
	game_object[37]->setPosition(vec3(-5.0f, 5.5f, -35.0f));

	game_object[38] = new GameObject();
	game_object[38]->setPosition(vec3(-5.0f, 5.5f, -35.0f));

	game_object[39] = new GameObject();
	game_object[39]->setPosition(vec3(-5.0f, 5.5f, -35.0f));

	playerCube = new GameObject();
	playerCube->setPosition(vec3(0.5f, 0.5f, 0.0f));

	goalCube = new GameObject();
	goalCube->setPosition(vec3(2.5f, 0.5f, -80.0f));

}

Game::~Game()
{
}


void Game::run()
{

	initialize();

	Event event;

	float rotation = 0.01f;
	float start_value = 0.0f;
	float end_value = 1.0f;

	while (isRunning){

#if (DEBUG >= 2)
		DEBUG_MSG("Game running...");
#endif

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				isRunning = false;
			}

			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				// Set Model Rotation
				if (!animate)
				{
					animate = true;
					if (rotation < 0)
						rotation *= -1; // Set Positive
					animation = glm::vec3(0, 1, 0); //Rotate Y
				}
			}

			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				// Set Model Rotation
				if (!animate)
				{
					animate = true;
					if (rotation >= 0)
						rotation *= -1; // Set Negative
					animation = glm::vec3(0, -1, 0); //Rotate Y
				}

				// https://www.sfml-dev.org/documentation/2.0/classsf_1_1Clock.php
				// https://github.com/acron0/Easings
				// http://robotacid.com/documents/code/Easing.cs
				// http://st33d.tumblr.com/post/94243475686/easing-equations-for-unity-c
				// http://easings.net/
				// http://upshots.org/actionscript/jsas-understanding-easing
				// https://www.kirupa.com/html5/animating_with_easing_functions_in_javascript.htm
				// https://medium.com/motion-in-interaction/animation-principles-in-ui-design-understanding-easing-bea05243fe3#.svh4gczav
				// http://thednp.github.io/kute.js/easing.html
				// http://gizma.com/easing/#quad1
				// https://github.com/warrenm/AHEasing

				// VR
				// https://www.sfml-dev.org/documentation/2.4.2/classsf_1_1Sensor.php
				// http://en.sfml-dev.org/forums/index.php?topic=9412.msg65594
				// https://github.com/SFML/SFML/wiki/Tutorial:-Building-SFML-for-Android-on-Windows
				// https://github.com/SFML/SFML/wiki/Tutorial:-Building-SFML-for-Android
				// https://www.youtube.com/watch?v=n_JSi6ihDFs
				// http://en.sfml-dev.org/forums/index.php?topic=8010.0
				// 

				/*
				// Set Model Rotation
				// t = time, b = startvalue, c = change in value, d = duration:

				time = clock.getElapsedTime();
				std::cout << time.asSeconds() << std::endl;
				float original = 0.001f;
				float destination = 0.05f;

				float factor, temp;

				for (int t = 0; t < 5.0f; t++)
				{
				factor = gpp::Easing::easeIn(t, original, 0.00001f, 5.0f);
				cout << "Factor : " << factor << endl;
				}


				factor = gpp::Easing::easeIn(time.asMilliseconds(), original, 0.00001f, 5.0f);
				cout << "Factor : " << factor << endl;
				temp = original + ((destination - original) * factor);
				cout << "Temp : " << factor << endl;
				model = rotate(model, temp, glm::vec3(0, 1, 0)); // Rotate
				*/
			}

			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				// Set Model Rotation
				model = rotate(model, -0.01f, glm::vec3(1, 0, 0)); // Rotate
			}

			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				// Set Model Rotation
				model = rotate(model, 0.01f, glm::vec3(1, 0, 0)); // Rotate
			}

			//rotating on the Z axis
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
			{
				model = rotate(model, 0.01f, glm::vec3(0, 0, 1));
			}

			if (animate)
			{
				rotation += (1.0f * rotation) + 0.05f;
				model = rotate(model, 0.01f, animation); // Rotate
				rotation = 0.0f;
				animate = false;
			}


		}

		update();
		render();
	}

#if (DEBUG >= 2)
	DEBUG_MSG("Calling Cleanup...");
#endif
	unload();

}

void Game::initialize()
{
	isRunning = true;
	GLint isCompiled = 0;
	GLint isLinked = 0;

	if (!(!glewInit())) { DEBUG_MSG("glewInit() failed"); }

	// Copy UV's to all faces
	for (int i = 1; i < 6; i++)
		memcpy(&uvs[i * 4 * 2], &uvs[0], 2 * 4 * sizeof(GLfloat));

	DEBUG_MSG(glGetString(GL_VENDOR));
	DEBUG_MSG(glGetString(GL_RENDERER));
	DEBUG_MSG(glGetString(GL_VERSION));

	// Vertex Array Buffer
	glGenBuffers(1, &vbo);		// Generate Vertex Buffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	// Vertices (3) x,y,z , Colors (4) RGBA, UV/ST (2)

	int countVERTICES = game_object[0]->getVertexCount();
	int countCOLORS = game_object[0]->getColorCount();
	int countUVS = game_object[0]->getUVCount();

	glBufferData(GL_ARRAY_BUFFER, ((3 * VERTICES) + (4 * COLORS) + (2 * UVS)) * sizeof(GLfloat), NULL, GL_STATIC_DRAW);
	//glBufferData(GL_ARRAY_BUFFER, ((3 * VERTICES2) + (4 * COLORS2) + (2 * UVS2)) * sizeof(GLfloat), NULL, GL_STATIC_DRAW);

	glGenBuffers(1, &vib); //Generate Vertex Index Buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vib);


	int countINDICES = game_object[0]->getIndexCount();
	// Indices to be drawn
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * INDICES * sizeof(GLuint), indices, GL_STATIC_DRAW);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * INDICES2 * sizeof(GLuint), indices, GL_STATIC_DRAW);


	// NOTE: uniforms values must be used within Shader so that they 
	// can be retreived
	const char* vs_src =
		"#version 400\n\r"
		""
		"in vec3 sv_position;"
		"in vec4 sv_color;"
		"in vec2 sv_uv;"
		""
		"out vec4 color;"
		"out vec2 uv;"
		""
		"uniform mat4 sv_mvp;"
		"uniform float sv_x_offset;"
		"uniform float sv_y_offset;"
		"uniform float sv_z_offset;"
		""
		"void main() {"
		"	color = sv_color;"
		"	uv = sv_uv;"
		//"	gl_Position = vec4(sv_position, 1);"
		"	gl_Position = sv_mvp * vec4(sv_position.x + sv_x_offset, sv_position.y + sv_y_offset, sv_position.z + sv_z_offset, 1 );"
		"}"; //Vertex Shader Src

	DEBUG_MSG("Setting Up Vertex Shader");

	vsid = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vsid, 1, (const GLchar**)&vs_src, NULL);
	glCompileShader(vsid);

	// Check is Shader Compiled
	glGetShaderiv(vsid, GL_COMPILE_STATUS, &isCompiled);

	if (isCompiled == GL_TRUE) {
		DEBUG_MSG("Vertex Shader Compiled");
		isCompiled = GL_FALSE;
	}
	else
	{
		DEBUG_MSG("ERROR: Vertex Shader Compilation Error");
	}

	const char* fs_src =
		"#version 400\n\r"
		""
		"uniform sampler2D f_texture;"
		""
		"in vec4 color;"
		"in vec2 uv;"
		""
		"out vec4 fColor;"
		""
		"void main() {"
		"	fColor = color - texture2D(f_texture, uv);"
		""
		"}"; //Fragment Shader Src

	DEBUG_MSG("Setting Up Fragment Shader");

	fsid = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fsid, 1, (const GLchar**)&fs_src, NULL);
	glCompileShader(fsid);

	// Check is Shader Compiled
	glGetShaderiv(fsid, GL_COMPILE_STATUS, &isCompiled);

	if (isCompiled == GL_TRUE) {
		DEBUG_MSG("Fragment Shader Compiled");
		isCompiled = GL_FALSE;
	}
	else
	{
		DEBUG_MSG("ERROR: Fragment Shader Compilation Error");
	}

	DEBUG_MSG("Setting Up and Linking Shader");
	progID = glCreateProgram();
	glAttachShader(progID, vsid);
	glAttachShader(progID, fsid);
	glLinkProgram(progID);

	// Check is Shader Linked
	glGetProgramiv(progID, GL_LINK_STATUS, &isLinked);

	if (isLinked == 1) {
		DEBUG_MSG("Shader Linked");
	}
	else
	{
		DEBUG_MSG("ERROR: Shader Link Error");
	}

	// Set image data
	// https://github.com/nothings/stb/blob/master/stb_image.h
	img_data = stbi_load(filename.c_str(), &width, &height, &comp_count, 4);

	if (img_data == NULL)
	{
		DEBUG_MSG("ERROR: Texture not loaded");
	}

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &to[0]);
	glBindTexture(GL_TEXTURE_2D, to[0]);

	// Wrap around
	// https://www.khronos.org/opengles/sdk/docs/man/xhtml/glTexParameter.xml
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	// Filtering
	// https://www.khronos.org/opengles/sdk/docs/man/xhtml/glTexParameter.xml
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Bind to OpenGL
	// https://www.khronos.org/opengles/sdk/docs/man/xhtml/glTexImage2D.xml
	glTexImage2D(
		GL_TEXTURE_2D,			// 2D Texture Image
		0,						// Mipmapping Level 
		GL_RGBA,				// GL_RED, GL_GREEN, GL_BLUE, GL_ALPHA, GL_RGB, GL_BGR, GL_RGBA 
		width,					// Width
		height,					// Height
		0,						// Border
		GL_RGBA,				// Bitmap
		GL_UNSIGNED_BYTE,		// Specifies Data type of image data
		img_data				// Image Data
		);

	// Projection Matrix 
	projection = perspective(
		45.0f,					// Field of View 45 degrees
		4.0f / 3.0f,			// Aspect ratio
		5.0f,					// Display Range Min : 0.1f unit
		100.0f					// Display Range Max : 100.0f unit
		);

	// Camera Matrix
	view = lookAt(
		vec3(0.0f, 4.0f, 10.0f),	// Camera (x,y,z), in World Space
		vec3(0.0f, 0.0f, 0.0f),		// Camera looking at origin
		vec3(0.0f, 1.0f, 0.0f)		// 0.0f, 1.0f, 0.0f Look Down and 0.0f, -1.0f, 0.0f Look Up
		);

	// Model matrix
	model = mat4(
		1.0f					// Identity Matrix
		);

	// Enable Depth Test
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);

	// Load Font
	font.loadFromFile(".//Assets//Fonts//BBrick.ttf");
}

void Game::update()
{
	window.clear(sf::Color(255, 192, 203, 255));
#if (DEBUG >= 2)
	DEBUG_MSG("Updating...");
#endif
	// Update Model View Projection
	// For mutiple objects (cubes) create multiple models
	// To alter Camera modify view & projection
	mvp = projection * view * model;

	DEBUG_MSG(model[0].x);
	DEBUG_MSG(model[0].y);
	DEBUG_MSG(model[0].z);

	for (int i = 0; i < sizeOfGameObjects;i++)
	{
		float movement = game_object[i]->getPosition().z + 0.05f;
		float currentX = game_object[i]->getPosition().x;
		float currentY = game_object[i]->getPosition().y;
		game_object[i]->setPosition((vec3(currentX, currentY, movement)));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		for (int i = 0; i < sizeOfGameObjects;i++)
		{
			float movement = game_object[i]->getPosition().z + 0.05f;
			float currentX = game_object[i]->getPosition().x + 0.05f;
			float currentY = game_object[i]->getPosition().y;
			game_object[i]->setPosition((vec3(currentX, currentY, movement)));
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		for (int i = 0; i < sizeOfGameObjects;i++)
		{
			float movement = game_object[i]->getPosition().z + 0.05f;
			float currentX = game_object[i]->getPosition().x - 0.05f;
			float currentY = game_object[i]->getPosition().y;
			game_object[i]->setPosition((vec3(currentX, currentY, movement)));
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		for (int i = 0; i < sizeOfGameObjects;i++)
		{
			float movement = game_object[i]->getPosition().z - 0.05f;
			float currentX = game_object[i]->getPosition().x;
			float currentY = game_object[i]->getPosition().y;
			game_object[i]->setPosition((vec3(currentX, currentY, movement)));
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		for (int i = 0; i < sizeOfGameObjects;i++)
		{
			float movement = game_object[i]->getPosition().z;
			float currentX = game_object[i]->getPosition().x;
			float currentY = game_object[i]->getPosition().y + 0.05f;
			game_object[i]->setPosition((vec3(currentX, currentY, movement)));
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		for (int i = 0; i < sizeOfGameObjects;i++)
		{
			float movement = game_object[i]->getPosition().z;
			float currentX = game_object[i]->getPosition().x;
			float currentY = game_object[i]->getPosition().y - 0.05f;
			game_object[i]->setPosition((vec3(currentX, currentY, movement)));
		}
	}

	for (int i = 0; i < sizeOfGameObjects;i++)
	{
		if (game_object[2]->getPosition().z >= 10)
		{
			score += 1;
		}

		if (game_object[i]->getPosition().z >= 10)
		{
			int randXNum = (rand() % 160) - 80;
			int randZNum = 0;
		
			float movement = game_object[i]->getPosition().z - 100.0f;
			float currentX = randXNum;
			float currentY = game_object[i]->getPosition().y;
			game_object[i]->setPosition((vec3(currentX, 0.5f, movement)));

			
		}
		
		goalCube->setPosition(vec3(0.5, 0.5, goalCube->getPosition().z + 0.0005f));
	}

	for (int i = 0; i < sizeOfGameObjects;i++)
	{

		if (game_object[i]->getPosition().x - 1 < playerCube->getPosition().x - 1 && game_object[i]->getPosition().x > playerCube->getPosition().x - 1
			|| game_object[i]->getPosition().x < playerCube->getPosition().x + 1 && game_object[i]->getPosition().x + 1 > playerCube->getPosition().x + 1 && collided == false)
		{
			if (game_object[i]->getPosition().z -1 < playerCube->getPosition().z - 1 && game_object[i]->getPosition().z - 1 > playerCube->getPosition().z - 2)
			{
				float movement = game_object[i]->getPosition().z - 100.0f;
				float currentX = game_object[i]->getPosition().x;
				float currentY = game_object[i]->getPosition().y;
				game_object[i]->setPosition((vec3(currentX, currentY, movement)));
				collided = true;
				lives--;
			}
		}
		else
		{
			collided = false;
		}

		if (goalCube->getPosition().z >= playerCube->getPosition().z - 2.6 && goalCube->getPosition().z <= playerCube->getPosition().z + 2.3)
		{
			goalCube->setPosition(vec3(0.5, 0.5,-100));
			collidedWithGoal = true;
			
		}
		
	}

	if (score >= 12)
	{
		window.clear(sf::Color(48, 213, 200, 255));
	}

	if (score >= 24)
	{
		window.clear(sf::Color(145, 88, 88, 255));
	}

	if (score >= 36)
	{
		window.clear(sf::Color(108, 91, 123, 255));
	}

}

void Game::render()
{

#if (DEBUG >= 2)
	DEBUG_MSG("Render Loop...");
#endif

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Save current OpenGL render states
	// https://www.sfml-dev.org/documentation/2.0/classsf_1_1RenderTarget.php#a8d1998464ccc54e789aaf990242b47f7
	window.pushGLStates();

	// Find mouse position using sf::Mouse
	int x = Mouse::getPosition(window).x;
	int y = Mouse::getPosition(window).y;

	string hud = "Heads Up Display ["
		+ string(toString(x))
		+ "]["
		+ string(toString(y))
		+ "]";

	Text text(hud, font);
	Text scoreText;
	Text winText;
	Text loseText;
	Text livesText;


	scoreText.setFont(font);
	scoreText.setFillColor(sf::Color(255, 255, 255, 170));
	scoreText.setPosition(50, 550);
	scoreText.setString("Score: " + std::to_string(score));

	livesText.setFont(font);
	livesText.setFillColor(sf::Color(255, 255, 255, 170));
	livesText.setPosition(650, 550);
	livesText.setString("Lives: " + std::to_string(lives));

	text.setFillColor(sf::Color(255, 255, 255, 170));
	text.setPosition(50.f, 50.f);

	winText.setFont(font);
	winText.setFillColor(sf::Color(255, 255, 255, 170));
	winText.setPosition(250, 250);
	winText.setString("You Win! Well done");

	loseText.setFont(font);
	loseText.setFillColor(sf::Color(255, 255, 255, 170));
	loseText.setPosition(150, 250);
	loseText.setString("You Lose, better luck next time!");

	window.draw(text);
	window.draw(scoreText);
	window.draw(livesText);

	if (score >= 40)
	{
		window.clear(sf::Color(255, 192, 203, 255));
		window.draw(winText);

		for (int i = 0;i < sizeOfGameObjects; i++)
		{
			game_object[i]->setPosition(vec3(100, 100, 100));
			playerCube->setPosition(vec3(100, 100, 100));
			goalCube->setPosition(vec3(100, 100, 100));
		}

	}

	if (lives <= 0)
	{
		window.clear(sf::Color(255, 192, 203,255));
		window.draw(loseText);

		for (int i = 0;i < sizeOfGameObjects; i++)
		{
			game_object[i]->setPosition(vec3(100, 100, 100));
			playerCube->setPosition(vec3(100, 100, 100));
			goalCube->setPosition(vec3(100, 100, 100));
		}
	}

	// Restore OpenGL render states
	// https://www.sfml-dev.org/documentation/2.0/classsf_1_1RenderTarget.php#a8d1998464ccc54e789aaf990242b47f7

	window.popGLStates();

	// Rebind Buffers and then set SubData
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vib);

	// Use Progam on GPU
	glUseProgram(progID);

	// Find variables within the shader
	// https://www.khronos.org/opengles/sdk/docs/man/xhtml/glGetAttribLocation.xml
	positionID = glGetAttribLocation(progID, "sv_position");
	if (positionID < 0) { DEBUG_MSG("positionID not found"); }

	colorID = glGetAttribLocation(progID, "sv_color");
	if (colorID < 0) { DEBUG_MSG("colorID not found"); }

	uvID = glGetAttribLocation(progID, "sv_uv");
	if (uvID < 0) { DEBUG_MSG("uvID not found"); }

	textureID = glGetUniformLocation(progID, "f_texture");
	if (textureID < 0) { DEBUG_MSG("textureID not found"); }

	mvpID = glGetUniformLocation(progID, "sv_mvp");
	if (mvpID < 0) { DEBUG_MSG("mvpID not found"); }

	x_offsetID = glGetUniformLocation(progID, "sv_x_offset");
	if (x_offsetID < 0) { DEBUG_MSG("x_offsetID not found"); }

	y_offsetID = glGetUniformLocation(progID, "sv_y_offset");
	if (y_offsetID < 0) { DEBUG_MSG("y_offsetID not found"); }

	z_offsetID = glGetUniformLocation(progID, "sv_z_offset");
	if (z_offsetID < 0) { DEBUG_MSG("z_offsetID not found"); };

	// VBO Data....vertices, colors and UV's appended
	// Add the Vertices for all your GameOjects, Colors and UVS
	
	glBufferSubData(GL_ARRAY_BUFFER, 0 * VERTICES * sizeof(GLfloat), 3 * VERTICES * sizeof(GLfloat), game_object[0]->getVertex());
	//glBufferSubData(GL_ARRAY_BUFFER, 0 * VERTICES * sizeof(GLfloat), 3 * VERTICES * sizeof(GLfloat), vertices);
	glBufferSubData(GL_ARRAY_BUFFER, 3 * VERTICES * sizeof(GLfloat), 4 * COLORS * sizeof(GLfloat), colors);
	glBufferSubData(GL_ARRAY_BUFFER, ((3 * VERTICES) + (4 * COLORS)) * sizeof(GLfloat), 2 * UVS * sizeof(GLfloat), uvs);

	// Send transformation to shader mvp uniform [0][0] is start of array
	glUniformMatrix4fv(mvpID, 1, GL_FALSE, &mvp[0][0]);

	// Set Active Texture .... 32 GL_TEXTURE0 .... GL_TEXTURE31
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(textureID, 0); // 0 .... 31

	// Set the X, Y and Z offset (this allows for multiple cubes via different shaders)
	// Experiment with these values to change screen positions

	/*glUniform1f(x_offsetID, 1.00f);
	glUniform1f(y_offsetID, 1.00f);
	glUniform1f(z_offsetID, 1.00f);*/

	// Set pointers for each parameter (with appropriate starting positions)
	// https://www.khronos.org/opengles/sdk/docs/man/xhtml/glVertexAttribPointer.xml
	glVertexAttribPointer(positionID, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(colorID, 4, GL_FLOAT, GL_FALSE, 0, (VOID*)(3 * VERTICES * sizeof(GLfloat)));
	glVertexAttribPointer(uvID, 2, GL_FLOAT, GL_FALSE, 0, (VOID*)(((3 * VERTICES) + (4 * COLORS)) * sizeof(GLfloat)));
	
	// Enable Arrays
	glEnableVertexAttribArray(positionID);
	glEnableVertexAttribArray(colorID);
	glEnableVertexAttribArray(uvID);

	glUniform1f(x_offsetID, game_object[0]->getPosition().x);
	glUniform1f(y_offsetID, game_object[0]->getPosition().y);
	glUniform1f(z_offsetID, game_object[0]->getPosition().z);

	// Draw Element Arrays
	glDrawElements(GL_TRIANGLES, 3 * INDICES, GL_UNSIGNED_INT, NULL);


	glUniform1f(x_offsetID, game_object[1]->getPosition().x);
	glUniform1f(y_offsetID, game_object[1]->getPosition().y);
	glUniform1f(z_offsetID, game_object[1]->getPosition().z);
	glDrawElements(GL_TRIANGLES, 3 * INDICES, GL_UNSIGNED_INT, NULL);


	glUniform1f(x_offsetID, game_object[2]->getPosition().x);
	glUniform1f(y_offsetID, game_object[2]->getPosition().y);
	glUniform1f(z_offsetID, game_object[2]->getPosition().z);
	glDrawElements(GL_TRIANGLES, 3 * INDICES, GL_UNSIGNED_INT, NULL);

	glUniform1f(x_offsetID, game_object[3]->getPosition().x);
	glUniform1f(y_offsetID, game_object[3]->getPosition().y);
	glUniform1f(z_offsetID, game_object[3]->getPosition().z);
	glDrawElements(GL_TRIANGLES, 3 * INDICES, GL_UNSIGNED_INT, NULL);

	glUniform1f(x_offsetID, game_object[4]->getPosition().x);
	glUniform1f(y_offsetID, game_object[4]->getPosition().y);
	glUniform1f(z_offsetID, game_object[4]->getPosition().z);
	glDrawElements(GL_TRIANGLES, 3 * INDICES, GL_UNSIGNED_INT, NULL);

	glUniform1f(x_offsetID, game_object[5]->getPosition().x);
	glUniform1f(y_offsetID, game_object[5]->getPosition().y);
	glUniform1f(z_offsetID, game_object[5]->getPosition().z);
	glDrawElements(GL_TRIANGLES, 3 * INDICES, GL_UNSIGNED_INT, NULL);

	glUniform1f(x_offsetID, game_object[6]->getPosition().x);
	glUniform1f(y_offsetID, game_object[6]->getPosition().y);
	glUniform1f(z_offsetID, game_object[6]->getPosition().z);
	glDrawElements(GL_TRIANGLES, 3 * INDICES, GL_UNSIGNED_INT, NULL);

	glUniform1f(x_offsetID, game_object[7]->getPosition().x);
	glUniform1f(y_offsetID, game_object[7]->getPosition().y);
	glUniform1f(z_offsetID, game_object[7]->getPosition().z);
	glDrawElements(GL_TRIANGLES, 3 * INDICES, GL_UNSIGNED_INT, NULL);

	glUniform1f(x_offsetID, game_object[8]->getPosition().x);
	glUniform1f(y_offsetID, game_object[8]->getPosition().y);
	glUniform1f(z_offsetID, game_object[8]->getPosition().z);
	glDrawElements(GL_TRIANGLES, 3 * INDICES, GL_UNSIGNED_INT, NULL);

	glUniform1f(x_offsetID, game_object[9]->getPosition().x);
	glUniform1f(y_offsetID, game_object[9]->getPosition().y);
	glUniform1f(z_offsetID, game_object[9]->getPosition().z);
	glDrawElements(GL_TRIANGLES, 3 * INDICES, GL_UNSIGNED_INT, NULL);

	glUniform1f(x_offsetID, game_object[10]->getPosition().x);
	glUniform1f(y_offsetID, game_object[10]->getPosition().y);
	glUniform1f(z_offsetID, game_object[10]->getPosition().z);
	glDrawElements(GL_TRIANGLES, 3 * INDICES, GL_UNSIGNED_INT, NULL);

	glUniform1f(x_offsetID, game_object[11]->getPosition().x);
	glUniform1f(y_offsetID, game_object[11]->getPosition().y);
	glUniform1f(z_offsetID, game_object[11]->getPosition().z);
	glDrawElements(GL_TRIANGLES, 3 * INDICES, GL_UNSIGNED_INT, NULL);

	glUniform1f(x_offsetID, game_object[12]->getPosition().x);
	glUniform1f(y_offsetID, game_object[12]->getPosition().y);
	glUniform1f(z_offsetID, game_object[12]->getPosition().z);
	glDrawElements(GL_TRIANGLES, 3 * INDICES, GL_UNSIGNED_INT, NULL);

	glUniform1f(x_offsetID, game_object[13]->getPosition().x);
	glUniform1f(y_offsetID, game_object[13]->getPosition().y);
	glUniform1f(z_offsetID, game_object[13]->getPosition().z);
	glDrawElements(GL_TRIANGLES, 3 * INDICES, GL_UNSIGNED_INT, NULL);

	glUniform1f(x_offsetID, game_object[14]->getPosition().x);
	glUniform1f(y_offsetID, game_object[14]->getPosition().y);
	glUniform1f(z_offsetID, game_object[14]->getPosition().z);
	glDrawElements(GL_TRIANGLES, 3 * INDICES, GL_UNSIGNED_INT, NULL);

	glUniform1f(x_offsetID, game_object[15]->getPosition().x);
	glUniform1f(y_offsetID, game_object[15]->getPosition().y);
	glUniform1f(z_offsetID, game_object[15]->getPosition().z);
	glDrawElements(GL_TRIANGLES, 3 * INDICES, GL_UNSIGNED_INT, NULL);

	glUniform1f(x_offsetID, game_object[16]->getPosition().x);
	glUniform1f(y_offsetID, game_object[16]->getPosition().y);
	glUniform1f(z_offsetID, game_object[16]->getPosition().z);
	glDrawElements(GL_TRIANGLES, 3 * INDICES, GL_UNSIGNED_INT, NULL);

	glUniform1f(x_offsetID, game_object[17]->getPosition().x);
	glUniform1f(y_offsetID, game_object[17]->getPosition().y);
	glUniform1f(z_offsetID, game_object[17]->getPosition().z);
	glDrawElements(GL_TRIANGLES, 3 * INDICES, GL_UNSIGNED_INT, NULL);

	glUniform1f(x_offsetID, game_object[18]->getPosition().x);
	glUniform1f(y_offsetID, game_object[18]->getPosition().y);
	glUniform1f(z_offsetID, game_object[18]->getPosition().z);
	glDrawElements(GL_TRIANGLES, 3 * INDICES, GL_UNSIGNED_INT, NULL);

	glUniform1f(x_offsetID, game_object[19]->getPosition().x);
	glUniform1f(y_offsetID, game_object[19]->getPosition().y);
	glUniform1f(z_offsetID, game_object[19]->getPosition().z);
	glDrawElements(GL_TRIANGLES, 3 * INDICES, GL_UNSIGNED_INT, NULL);

	glUniform1f(x_offsetID, game_object[20]->getPosition().x);
	glUniform1f(y_offsetID, game_object[20]->getPosition().y);
	glUniform1f(z_offsetID, game_object[20]->getPosition().z);
	glDrawElements(GL_TRIANGLES, 3 * INDICES, GL_UNSIGNED_INT, NULL);

	glUniform1f(x_offsetID, game_object[21]->getPosition().x);
	glUniform1f(y_offsetID, game_object[21]->getPosition().y);
	glUniform1f(z_offsetID, game_object[21]->getPosition().z);
	glDrawElements(GL_TRIANGLES, 3 * INDICES, GL_UNSIGNED_INT, NULL);

	glUniform1f(x_offsetID, game_object[22]->getPosition().x);
	glUniform1f(y_offsetID, game_object[22]->getPosition().y);
	glUniform1f(z_offsetID, game_object[22]->getPosition().z);
	glDrawElements(GL_TRIANGLES, 3 * INDICES, GL_UNSIGNED_INT, NULL);

	glUniform1f(x_offsetID, game_object[23]->getPosition().x);
	glUniform1f(y_offsetID, game_object[23]->getPosition().y);
	glUniform1f(z_offsetID, game_object[23]->getPosition().z);
	glDrawElements(GL_TRIANGLES, 3 * INDICES, GL_UNSIGNED_INT, NULL);

	glUniform1f(x_offsetID, game_object[24]->getPosition().x);
	glUniform1f(y_offsetID, game_object[24]->getPosition().y);
	glUniform1f(z_offsetID, game_object[24]->getPosition().z);
	glDrawElements(GL_TRIANGLES, 3 * INDICES, GL_UNSIGNED_INT, NULL);

	glUniform1f(x_offsetID, game_object[25]->getPosition().x);
	glUniform1f(y_offsetID, game_object[25]->getPosition().y);
	glUniform1f(z_offsetID, game_object[25]->getPosition().z);
	glDrawElements(GL_TRIANGLES, 3 * INDICES, GL_UNSIGNED_INT, NULL);

	glUniform1f(x_offsetID, game_object[26]->getPosition().x);
	glUniform1f(y_offsetID, game_object[26]->getPosition().y);
	glUniform1f(z_offsetID, game_object[26]->getPosition().z);
	glDrawElements(GL_TRIANGLES, 3 * INDICES, GL_UNSIGNED_INT, NULL);

	glUniform1f(x_offsetID, game_object[27]->getPosition().x);
	glUniform1f(y_offsetID, game_object[27]->getPosition().y);
	glUniform1f(z_offsetID, game_object[27]->getPosition().z);
	glDrawElements(GL_TRIANGLES, 3 * INDICES, GL_UNSIGNED_INT, NULL);

	glUniform1f(x_offsetID, game_object[28]->getPosition().x);
	glUniform1f(y_offsetID, game_object[28]->getPosition().y);
	glUniform1f(z_offsetID, game_object[28]->getPosition().z);
	glDrawElements(GL_TRIANGLES, 3 * INDICES, GL_UNSIGNED_INT, NULL);

	glUniform1f(x_offsetID, game_object[29]->getPosition().x);
	glUniform1f(y_offsetID, game_object[29]->getPosition().y);
	glUniform1f(z_offsetID, game_object[29]->getPosition().z);
	glDrawElements(GL_TRIANGLES, 3 * INDICES, GL_UNSIGNED_INT, NULL);

	glUniform1f(x_offsetID, game_object[30]->getPosition().x);
	glUniform1f(y_offsetID, game_object[30]->getPosition().y);
	glUniform1f(z_offsetID, game_object[30]->getPosition().z);
	glDrawElements(GL_TRIANGLES, 3 * INDICES, GL_UNSIGNED_INT, NULL);

	glUniform1f(x_offsetID, game_object[31]->getPosition().x);
	glUniform1f(y_offsetID, game_object[31]->getPosition().y);
	glUniform1f(z_offsetID, game_object[31]->getPosition().z);
	glDrawElements(GL_TRIANGLES, 3 * INDICES, GL_UNSIGNED_INT, NULL);

	glUniform1f(x_offsetID, game_object[32]->getPosition().x);
	glUniform1f(y_offsetID, game_object[32]->getPosition().y);
	glUniform1f(z_offsetID, game_object[32]->getPosition().z);
	glDrawElements(GL_TRIANGLES, 3 * INDICES, GL_UNSIGNED_INT, NULL);

	glUniform1f(x_offsetID, game_object[33]->getPosition().x);
	glUniform1f(y_offsetID, game_object[33]->getPosition().y);
	glUniform1f(z_offsetID, game_object[33]->getPosition().z);
	glDrawElements(GL_TRIANGLES, 3 * INDICES, GL_UNSIGNED_INT, NULL);

	glUniform1f(x_offsetID, game_object[34]->getPosition().x);
	glUniform1f(y_offsetID, game_object[34]->getPosition().y);
	glUniform1f(z_offsetID, game_object[34]->getPosition().z);
	glDrawElements(GL_TRIANGLES, 3 * INDICES, GL_UNSIGNED_INT, NULL);

	glUniform1f(x_offsetID, game_object[35]->getPosition().x);
	glUniform1f(y_offsetID, game_object[35]->getPosition().y);
	glUniform1f(z_offsetID, game_object[35]->getPosition().z);
	glDrawElements(GL_TRIANGLES, 3 * INDICES, GL_UNSIGNED_INT, NULL);

	glUniform1f(x_offsetID, game_object[36]->getPosition().x);
	glUniform1f(y_offsetID, game_object[36]->getPosition().y);
	glUniform1f(z_offsetID, game_object[36]->getPosition().z);
	glDrawElements(GL_TRIANGLES, 3 * INDICES, GL_UNSIGNED_INT, NULL);

	glUniform1f(x_offsetID, game_object[37]->getPosition().x);
	glUniform1f(y_offsetID, game_object[37]->getPosition().y);
	glUniform1f(z_offsetID, game_object[37]->getPosition().z);
	glDrawElements(GL_TRIANGLES, 3 * INDICES, GL_UNSIGNED_INT, NULL);

	glUniform1f(x_offsetID, game_object[38]->getPosition().x);
	glUniform1f(y_offsetID, game_object[38]->getPosition().y);
	glUniform1f(z_offsetID, game_object[38]->getPosition().z);
	glDrawElements(GL_TRIANGLES, 3 * INDICES, GL_UNSIGNED_INT, NULL);

	glUniform1f(x_offsetID, game_object[39]->getPosition().x);
	glUniform1f(y_offsetID, game_object[39]->getPosition().y);
	glUniform1f(z_offsetID, game_object[39]->getPosition().z);
	glDrawElements(GL_TRIANGLES, 3 * INDICES, GL_UNSIGNED_INT, NULL);

	glUniform1f(x_offsetID, playerCube->getPosition().x);
	glUniform1f(y_offsetID, playerCube->getPosition().y);
	glUniform1f(z_offsetID, playerCube->getPosition().z);
	glDrawElements(GL_TRIANGLES, 3 * INDICES, GL_UNSIGNED_INT, NULL);

	glUniform1f(x_offsetID, goalCube->getPosition().x);
	glUniform1f(y_offsetID, goalCube->getPosition().y);
	glUniform1f(z_offsetID, goalCube->getPosition().z);
	glDrawElements(GL_TRIANGLES, 3 * INDICES, GL_UNSIGNED_INT, NULL);

	window.display();

	// Disable Arrays
	glDisableVertexAttribArray(positionID);
	glDisableVertexAttribArray(colorID);
	glDisableVertexAttribArray(uvID);

	// Unbind Buffers with 0 (Resets OpenGL States...important step)
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// Reset the Shader Program to Use
	glUseProgram(0);

	// Check for OpenGL Error code
	error = glGetError();
	if (error != GL_NO_ERROR) {
		DEBUG_MSG(error);
	}
}

void Game::unload()
{
#if (DEBUG >= 2)
	DEBUG_MSG("Cleaning up...");
#endif
	glDetachShader(progID, vsid);	// Shader could be used with more than one progID
	glDetachShader(progID, fsid);	// ..
	glDeleteShader(vsid);			// Delete Vertex Shader
	glDeleteShader(fsid);			// Delete Fragment Shader
	glDeleteProgram(progID);		// Delete Shader
	glDeleteBuffers(1, &vbo);		// Delete Vertex Buffer
	glDeleteBuffers(1, &vib);		// Delete Vertex Index Buffer
	stbi_image_free(img_data);		// Free image stbi_image_free(..)
}

