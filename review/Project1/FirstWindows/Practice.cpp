
#include <glad/glad.h>
#include <glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void processInput(GLFWwindow* window);

int main3()
{
	//glfw
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


	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"out vec4 vertexColor; // 为片段着色器指定一个颜色输出\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"	vertexColor = vec4(0.5, 0.0, 0.0, 1.0); // 把输出变量设置为暗红色\n"
		"}\0";
	const char* fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\n\0";
	const char* fragmentShaderSourceRed = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"in vec4 vertexColor;\n"
		"uniform vec4 ourColor; // 在OpenGL程序代码中设定这个变量\n"
		"void main()\n"
		"{\n"
		"   FragColor = ourColor;\n"
		"}\n\0";
	const char* vertexShaderSourceMix = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"layout (location = 1) in vec3 aColor;\n"
		"out vec3 ourDColor; // 为片段着色器指定一个颜色输出\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"	ourDColor = aColor; // 把输出变量设置为暗红色\n"
		"}\0";
	const char* fragmentShaderSourceMix = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"in vec3 ourDColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(ourDColor, 1.0);\n"
		"}\n\0";
	float vertices[] = {
		// 位置              // 颜色
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // 右下
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // 左下
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // 顶部
	};
	float vertices1[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};
	float vertices2[] = {
		0.5f, 0.5f, 0.0f,
		 -0.5f, 0.5f, 0.0f,
		 0.0f,  -0.5f, 0.0f
	};

	unsigned int VBOs[3];
	glGenBuffers(3, VBOs);




	unsigned int VAOs[3];
	glGenVertexArrays(3, VAOs);
	// Bind VAO
	glBindVertexArray(VAOs[0]);

	// Operating Buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	// Bind VAO
	glBindVertexArray(VAOs[1]);

	// Operating Buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Bind VAO
	glBindVertexArray(VAOs[2]);

	// Operating Buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	unsigned int fragmentShaderRed;
	fragmentShaderRed = glCreateShader(GL_FRAGMENT_SHADER);

	unsigned int vertexShaderMix;
	vertexShaderMix = glCreateShader(GL_VERTEX_SHADER);

	unsigned int fragmentShaderMix;
	fragmentShaderMix = glCreateShader(GL_FRAGMENT_SHADER);


	//compile protect
	int  success;
	char infoLog[512];


	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);//check compile res
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}


	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);//check compile res
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	glShaderSource(fragmentShaderRed, 1, &fragmentShaderSourceRed, NULL);
	glCompileShader(fragmentShaderRed);
	glGetShaderiv(fragmentShaderRed, GL_COMPILE_STATUS, &success);//check compile res
	if (!success)
	{
		glGetShaderInfoLog(fragmentShaderRed, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	glShaderSource(vertexShaderMix, 1, &vertexShaderSourceMix, NULL);
	glCompileShader(vertexShaderMix);
	glGetShaderiv(vertexShaderMix, GL_COMPILE_STATUS, &success);//check compile res
	if (!success)
	{
		glGetShaderInfoLog(vertexShaderMix, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}


	glShaderSource(fragmentShaderMix, 1, &fragmentShaderSourceMix, NULL);
	glCompileShader(fragmentShaderMix);
	glGetShaderiv(fragmentShaderMix, GL_COMPILE_STATUS, &success);//check compile res
	if (!success)
	{
		glGetShaderInfoLog(fragmentShaderMix, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//shader program
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADERPROGRAM::LINK_FAILED\n" << infoLog << std::endl;
	}
	//shader program
	unsigned int shaderProgramRed;
	shaderProgramRed = glCreateProgram();
	glAttachShader(shaderProgramRed, vertexShader);
	glAttachShader(shaderProgramRed, fragmentShaderRed);
	glLinkProgram(shaderProgramRed);
	glGetProgramiv(shaderProgramRed, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgramRed, 512, NULL, infoLog);
		std::cout << "ERROR::SHADERPROGRAM::LINK_FAILED\n" << infoLog << std::endl;
	}
	unsigned int shaderProgramMix;
	shaderProgramMix = glCreateProgram();
	glAttachShader(shaderProgramMix, vertexShaderMix);
	glAttachShader(shaderProgramMix, fragmentShaderMix);
	glLinkProgram(shaderProgramMix);
	glGetProgramiv(shaderProgramMix, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgramMix, 512, NULL, infoLog);
		std::cout << "ERROR::SHADERPROGRAM::LINK_FAILED\n" << infoLog << std::endl;
	}

	//int nrAttributes;
	//glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	//std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;
	glUseProgram(shaderProgram);
	//delete shader
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glDeleteShader(fragmentShaderRed);
	glDeleteShader(vertexShaderMix);
	glDeleteShader(fragmentShaderMix);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	while (!glfwWindowShouldClose(window))
	{

		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAOs[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		int vertexColorLocation = glGetUniformLocation(shaderProgramRed, "ourColor");
		glUseProgram(shaderProgramRed);
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);


		glBindVertexArray(VAOs[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glUseProgram(shaderProgramMix);
		glBindVertexArray(VAOs[2]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		//glBindVertexArray(0);
		processInput(window);
		glfwSwapBuffers(window);
		glfwPollEvents();

	}
	glDeleteVertexArrays(2, VAOs);
	glDeleteBuffers(2, VBOs);
	glDeleteProgram(shaderProgram);
	glDeleteProgram(shaderProgramRed);
	glfwTerminate();

	return 0;
}