#include<GL/glew.h>
#include <GLFW/glfw3.h>
#include<iostream>

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtx/transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include<string>
#include<fstream>
#include<sstream>

#include"../include/Error.h"
#include"../include/Shader.h"
#include"../include/Cube.h"


GLFWwindow* window;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const unsigned int TOTAL_CUBES = 4;

void initOpenGL()
{
    /* Initialize the library */
    if (!glfwInit())
    {
        fatalError("GLFW could not be initialized");
    }

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "3D Cube", NULL, NULL);
    if (!window)
    {
        fatalError("GLFW Window could not be created!");
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        fatalError("Error loading GLEW extensions!");
    }

    glEnable(GL_DEPTH_TEST);


}


int main()
{
    initOpenGL();

    Shader shader("shaders/Main.vert", "shaders/Main.frag");

    shader.CreateShaders();

    Cube cube(TOTAL_CUBES);
    cube.Create();
   
    float aspectRatio = static_cast<float>(WINDOW_WIDTH) / WINDOW_HEIGHT;
    glm::mat4 projection = glm::perspective(glm::radians(45.f), aspectRatio, 0.1f, 500.f);

    shader.Bind();
    shader.SendUniformData("projection", projection);

    float startTime = glfwGetTime();

    glm::mat4 model[TOTAL_CUBES] = {};

    // Position Matrix
    glm::mat4 posMatrix[TOTAL_CUBES] =
    {
      glm::translate(glm::vec3(-2.5f, -2.5f, -15.f)),
      glm::translate(glm::vec3(+2.5f, -2.5f, -15.f)),
      glm::translate(glm::vec3(-5.5f, 5.f, -20.f)),
      glm::translate(glm::vec3(+5.5f, 5.f, -20.f))
    };

    //Angular Speed - Axis X, Y and Z
    glm::vec3 angSpeed[TOTAL_CUBES] =
    {
        glm::vec3(-1.75f, +0.75f, -2.75f),
        glm::vec3(+0.75f, -3.75f, +1.75f),
        glm::vec3(+1.50f, +0.50f, +2.35f),
        glm::vec3(-1.75f, +0.75f, -3.75f)
    };

    unsigned int modelVBO = cube.GetModelVBO();

    while (!glfwWindowShouldClose(window))
    {

        float currentTime = glfwGetTime();
        float dt = currentTime - startTime;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for (unsigned int i = 0; i < TOTAL_CUBES; i++)
        {
            model[i] = glm::rotate(angSpeed[i].x * dt, glm::vec3(1.f, 0.f, 0.f));
            model[i] = glm::rotate(model[i], angSpeed[i].y * dt, glm::vec3(0.f, 1.f, 0.f));
            model[i] = posMatrix[i] * glm::rotate(model[i], angSpeed[i].z * dt, glm::vec3(0.f, 0.f, 1.f));
        }
        
        // Update Matrix Buffer
        glBindBuffer(GL_ARRAY_BUFFER, modelVBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(model), model);

        //Cube 
        {
            cube.Draw();
        }

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}