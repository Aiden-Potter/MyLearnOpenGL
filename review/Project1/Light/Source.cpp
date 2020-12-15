#include <glad/glad.h>
#include <glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Material.h"
#include "learnopengl/Shader.h"
#include "Camera.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "Mesh.h"
#include "Model.h"
#include "LightDirecional.h"
#include "LightPoint.h"
#include "LightSpot.h"
#pragma region LightDeclare

//LightDirecional light = LightDirecional(glm::vec3(10.0f,10.0f,-5.0f),glm::vec3(glm::radians(45.0f),0,0));
LightSpot light = LightSpot(glm::vec3(0.0f, 2.0f, 5.0f),
	glm::vec3(glm::radians(180.0f), 0, 0),
	glm::vec3(1.0f, 1.0f, 1.0f));
#pragma endregion 

#pragma region Model
const float ScreenWidth = 800;
const float ScreenHeight = 600;
float mixValue = 0.2f;
float vertices[] = {
	// positions          // normals           // texture coords
	   -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

	   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

	   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	   -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	   -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

	   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
};


float texCoords[] = {
0.0f, 0.0f, // 左下角
1.0f, 0.0f, // 右下角
0.5f, 1.0f // 上中
};

glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(1.0f,  2.0f, -1.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-1.8f, -2.0f, -2.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -1.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
};

#pragma endregion

#pragma region Input Declare
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
float deltaTime = 0.0f; // 当前帧与上一帧的时间差
float lastFrame = 0.0f; // 上一帧的时间
bool firstMouse = true;
float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch = 0.0f;
float lastX = 800.0f / 2.0;
float lastY = 600.0 / 2.0;
float fov = 45.0f;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
};
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		mixValue += 0.001f;
		if (mixValue >= 1.0f)
			mixValue = 1.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		mixValue -= 0.001f;
		if (mixValue <= 0.0f)
			mixValue = 0.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		camera.ProcessKeyboard(UP, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		camera.ProcessKeyboard(DOWN, deltaTime);
};
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse) // 这个bool变量初始时是设定为true的
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}
	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // 注意这里是相反的，因为y坐标是从底部往顶部依次增大的
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.5f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;
	camera.ProcessMouseMovement(xoffset, yoffset);

};
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
#pragma endregion

#pragma region Tool
unsigned int LoadImageToGPU(const char* imagePath, GLint internalFormat, GLenum format, int textureSlot) {
	unsigned int textureBuffer;
	glGenTextures(1, &textureBuffer);
	glActiveTexture(GL_TEXTURE0 + textureSlot);
	glBindTexture(GL_TEXTURE_2D, textureBuffer);

	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(imagePath, &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
	return textureBuffer;
}
#pragma endregion




int main(int argc,char*argv[])
{
	std::cout << argv[0] << std::endl;
	std::string exePath = argv[0];
	std::string objPath = exePath.substr(0, exePath.find_last_of("\\")) + "\\model\\nanosuit.obj";
	std::cout << objPath  << std::endl;
#pragma region OpenWindows
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	//callback
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


	//glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	glViewport(0.5, 0, 800, 600);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
#pragma endregion	


#pragma region VAO VBO

	

	//unsigned int VBOs[3];
	//glGenBuffers(3, VBOs);


	//unsigned int VAOs[3];
	//glGenVertexArrays(3, VAOs);
	//// Bind VAO
	//glBindVertexArray(VAOs[0]);

	//// Operating Buffer
	//glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);



	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(1);

	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	//glEnableVertexAttribArray(2);


	//glBindBuffer(GL_ARRAY_BUFFER, 0);

#pragma endregion


#pragma region 材质
	//unsigned int texture1;
	//texture1 = LoadImageToGPU("container.jpg", GL_RGB, GL_RGB, 0);

	//// 为当前绑定的纹理对象设置环绕、过滤方式
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//unsigned int texture2;
	//texture2 = LoadImageToGPU("awesomeface.png", GL_RGBA, GL_RGBA, 1);

	//// 为当前绑定的纹理对象设置环绕、过滤方式
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);



#pragma endregion
	//Mesh mesh(vertices);
	Model objModel(objPath);

#pragma region InitShader

	Shader* ourShader = new Shader("LightVert.glsl", "LightFrag.glsl");
	ourShader->use();


	ourShader->setVec3("ambientColor", 0.6f,0.6f ,0.6f );
	ourShader->setVec3("objectColor", 1.0f, 1.0f, 1.0f);



	Material * mat = new Material(ourShader,
		glm::vec3(0.3f, 0.3f, 0.3f),
		LoadImageToGPU("container2.png", GL_RGBA, GL_RGBA, 0),
		LoadImageToGPU("container2_specular.png", GL_RGBA, GL_RGBA, 1),
		LoadImageToGPU("matrix.jpg", GL_RGB, GL_RGB, 2),
		64.0f);
	ourShader->setVec3("material.ambient", mat->ambient);
	//ourShader->setVec3("material.diffuse", mat->diffuse);
	ourShader->setInt("material.diffuse", 0); 
	ourShader->setInt("material.specular", 1);
	ourShader->setInt("material.emission", 2);
	ourShader->setFloat("material.shininess", mat->shiness);

	ourShader->setVec3("lightColor", light.color);

	ourShader->setFloat("lightS.cosPhyInner", light.cosPhyInner);
	ourShader->setFloat("lightS.cosPhyOutter", light.cosPhyOutter);
	//ourShader->setFloat("lightPoint.constant", light.constant);
	//ourShader->setFloat("lightPoint.linear", light.linear);
	//ourShader->setFloat("lightPoint.quadratic", light.quadratic);
	


#pragma endregion 


	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		//ourShader->setVec3("lightPos", light.position);
		ourShader->setVec3("cameraPos", camera.Position.x, camera.Position.y, camera.Position.z);

		ourShader->use();
		glm::mat4 model;
		ourShader->setMat4("model", model);
		glm::mat4 view;
		view = camera.GetViewMatrix();
		ourShader->setMat4("view", view);
		glm::mat4 projection;
		projection = glm::perspective(glm::radians(camera.Zoom), 800.0f / 600.0f, 0.1f, 100.0f);
		ourShader->setMat4("projection", projection);

		ourShader->setVec3("lightPosUniform", light.position);
		ourShader->setVec3("lightDirection", light.direction);
		objModel.Draw(mat->shader);
		//mesh.Draw(ourShader);
		//glBindVertexArray(VAOs[0]);
		//glDrawArrays(GL_TRIANGLES, 0, 36);
		//for (unsigned int i = 0; i < 10; i++)
		//{
		//	glm::mat4 model;
		//	model = glm::translate(model, cubePositions[i]);
		//	//float angle = 20.0f * i;
		//	//model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
		//	ourShader->setMat4("model", model);

		//	glDrawArrays(GL_TRIANGLES, 0, 36);
		//}

		

		glfwSwapBuffers(window);
		glfwPollEvents();

	}
	//glDeleteVertexArrays(3, VAOs);
	//glDeleteBuffers(3, VBOs);
	delete ourShader;

	glfwTerminate();

	return 0;
}
