#include "Renderer.hpp"
#include "Camera.hpp"


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
	window = glfwCreateWindow(screenX, screenY, "Title Goes here", NULL, NULL);


	if (window == NULL)
	{
		cout << "Window creation failed" << endl;
		exit(-1);
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);

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

	

	return true;
}