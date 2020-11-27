#include "Renderer.hpp"
#include "Camera.hpp"
#include "glm/gtx/string_cast.hpp"
#include "HBS.hpp"


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
	window = glfwCreateWindow(x, y, "Title Goes here", NULL, NULL);
	cam = Camera(vec3(0, 3, 0), vec3(0, 1, 0), 0, 0, 10, 1, 1);
}

Renderer::~Renderer()
{
}


void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
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
	//int width, height;
	//glfwGetWindowSize(this->window, &width, &height);
	//this->player->camera.changeWindowSize(vec2(width, height));
	this->addThing(this->player);


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
	printf("######%#@%@#%@#new window size\n");
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

	glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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



		processInput(this->window);
		shader.use();

		for (auto t : things) //Everything else
		{
			t->draw(shader); //the order of these two infuriates me, but it doesn't work
			t->tick(deltaTime, this->window); //the other way around :|
			handleHits(things, t);
		}

		mat4 view = this->cam.getView(mat4(1.0));
		//mat4 view = lookAt(vec3(32 + sin(glfwGetTime()/10)*20, 85, 32+cos(glfwGetTime()/10)*20), vec3(32, 60, 32), vec3(0.0f, 1.0f, 0.0f));
		shader.setMatFour("view", view);
		mat4 projection = perspective(radians(70.0f), (float)screenX / (float)screenY, 0.1f, 256.0f);
		shader.setMatFour("projection", projection);


		glfwSwapBuffers(this->window);
		glfwPollEvents();
	}
	glfwTerminate();
}