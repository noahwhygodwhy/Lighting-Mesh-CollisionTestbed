#include "Renderer.hpp"
#include "Camera.hpp"


float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame


//TODO: you were moving the camera from the renderer to the Player

Renderer::Renderer(int x, int y)
{
	layerCount = 0;
	EBO = 0;
	VBO = 0;
	VAO = 0;
	screenX = x;
	screenY = y;
	cam = Camera(vec3(0, 0, 0), vec3(0, 1, 0), 0, 0, 10, 1, 1);
	window = glfwCreateWindow(x, y, "Title Goes here", NULL, NULL);
}

Renderer::~Renderer()
{
}


void processInput(GLFWwindow* window, Camera& cam)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		//printf("W");
		cam.keyboardInput(Direction::FORWARD, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		//printf("S");
		cam.keyboardInput(Direction::BACKWARD, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		//printf("A");
		cam.keyboardInput(Direction::LEFT, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		//printf("D");
		cam.keyboardInput(Direction::RIGHT, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		//printf("D");
		cam.keyboardInput(Direction::DOWN, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		//printf("D");
		cam.keyboardInput(Direction::UP, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	{
		//printf("E");
		cam.keyboardInput(Direction::YAW_RIGHT, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		//printf("Q");
		cam.keyboardInput(Direction::YAW_LEFT, deltaTime);
	}
}

static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Player* p = (Player*) glfwGetWindowUserPointer(window);
	p->getController()->keyCallback(window, key, scancode, action, mods, p->getSpeed());
}
static void mouseButtCallback(GLFWwindow* window, int button, int action, int mods)
{

	Player* p = (Player*)glfwGetWindowUserPointer(window);
	p->getController()->mouseButtCallback(window, button, action, mods);
}
static void mouseMoveCallback(GLFWwindow* window, double xpos, double ypos)
{
	Player* p = (Player*)glfwGetWindowUserPointer(window);
	p->getController()->mouseMoveCallback(window, xpos, ypos);
}


void Renderer::setPlayer(Player* p)
{
	this->player = p;
	glfwSetWindowUserPointer(this->window, this->player);
	glfwSetKeyCallback(this->window, keyCallback);
	glfwSetMouseButtonCallback(this->window, mouseButtCallback);
	glfwSetCursorPosCallback(this->window, mouseMoveCallback);

}

void Renderer::addThing(Thing* th)
{
	things.push_back(th);
}
void frameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

bool Renderer::initialize()
{

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SRGB_CAPABLE, 1);
	//glfwWindowHint(GLFW_SAMPLES, 16);
	this->window = glfwCreateWindow(screenX, screenY, "Title Goes here", NULL, NULL);


	if (this->window == NULL)
	{
		cout << "Window creation failed" << endl;
		exit(-1);
	}

	glfwMakeContextCurrent(this->window);
	glfwSetFramebufferSizeCallback(this->window, frameBufferSizeCallback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "GLAD init failed" << endl;
		exit(-1);
	}

	shader = Shader("vertShader.glsl", "fragShader.glsl");

	glEnable(GL_CULL_FACE);
	glEnable(GL_FRAMEBUFFER_SRGB);
	glEnable(GL_DEPTH_TEST);
	glFrontFace(GL_CCW);

	glEnable(GL_LINE_SMOOTH);
	glLineWidth(2.0f);

	return true;
}
void Renderer::run()
{
	while (!glfwWindowShouldClose(this->window))
	{	
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);

		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;



		//processInput(this->window, cam);
		shader.use();

		
		mat4 view = cam.getView();
		//mat4 view = lookAt(vec3(32 + sin(glfwGetTime()/10)*20, 85, 32+cos(glfwGetTime()/10)*20), vec3(32, 60, 32), vec3(0.0f, 1.0f, 0.0f));
		shader.setMatFour("view", view);
		mat4 projection = perspective(radians(70.0f), (float)screenX / (float)screenY, 0.1f, 256.0f);
		shader.setMatFour("projection", projection);

		player->tick(deltaTime, this->window);
		player->draw(shader);

		for (auto t : things) //Everything else
		{
			t->tick(deltaTime);
			t->draw(shader);
		}
		glfwSwapBuffers(this->window);
		glfwPollEvents();
	}
	glfwTerminate();
}