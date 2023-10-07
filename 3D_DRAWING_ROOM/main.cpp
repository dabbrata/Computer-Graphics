//
//  main.cpp
//  3D Object Drawing
//
//  Created by Nazirul Hasan on 4/9/23.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "camera.h"
#include "basic_camera.h"

#include <iostream>

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
void drawBookself(unsigned int VAO, Shader ourShader, glm::mat4 matr);
void drawTable(unsigned int VAO, Shader ourShader, glm::mat4 matr);
void drawChair(unsigned int VAO, Shader ourShader, glm::mat4 matr);
void drawCup(unsigned int VAO, Shader ourShader, glm::mat4 matr);
void drawSofa(unsigned int VAO, Shader ourShader);
void drawTelevision(unsigned int VAO, Shader ourShader, glm::mat4 matr);
void drawFan(unsigned int VAO, Shader ourShader, glm::mat4 matr, float r);
void drawOuterWall(unsigned int VAO, Shader ourShader);
void drawFrame(unsigned int VAO, Shader ourShader, glm::mat4 matr);
void drawWindow(unsigned int VAO, Shader ourShader);
void drawFloor(unsigned int VAO, Shader ourShader, glm::mat4 matr);


// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// modelling transform
float rotateAngle_X = 45.0;
float rotateAngle_Y = 45.0;
float rotateAngle_Z = 45.0;
float rotateAxis_X = 0.0;
float rotateAxis_Y = 0.0;
float rotateAxis_Z = 1.0;
float translate_X = 0.0;
float translate_Y = 0.0;
float translate_Z = 0.0;
float scale_X = 1.0;
float scale_Y = 1.0;
float scale_Z = 1.0;

//global var for fan
float r = 0.0f;
bool fanOn = false;

// camera
Camera camera(glm::vec3(-3.5f, 2.5f, 1.5f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

float eyeX = -5.0, eyeY = 3.5, eyeZ = 3.0;
float lookAtX = 0.0, lookAtY = 0.0, lookAtZ = 0.0;
glm::vec3 V = glm::vec3(0.0f, 1.0f, 0.0f);
BasicCamera basic_camera(eyeX, eyeY, eyeZ, lookAtX, lookAtY, lookAtZ, V);

// timing
float deltaTime = 0.0f;    // time between current frame and last frame
float lastFrame = 0.0f;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "CSE 4208: Computer Graphics Laboratory", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader zprogram
    // ------------------------------------
    Shader ourShader("vertexShader.vs", "fragmentShader.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    /*float cube_vertices[] = {
        0.0f, 0.0f, 0.0f, 0.3f, 0.8f, 0.5f,
        0.5f, 0.0f, 0.0f, 0.5f, 0.4f, 0.3f,
        0.5f, 0.5f, 0.0f, 0.2f, 0.7f, 0.3f,
        0.0f, 0.5f, 0.0f, 0.6f, 0.2f, 0.8f,
        0.0f, 0.0f, 0.5f, 0.8f, 0.3f, 0.6f,
        0.5f, 0.0f, 0.5f, 0.4f, 0.4f, 0.8f,
        0.5f, 0.5f, 0.5f, 0.2f, 0.3f, 0.6f,
        0.0f, 0.5f, 0.5f, 0.7f, 0.5f, 0.4f
    };*/
    /*float cube_vertices[] = {
        0.0f, 0.0f, 0.0f,
        0.5f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.0f,
        0.0f, 0.5f, 0.0f,
        0.0f, 0.0f, 0.5f,
        0.5f, 0.0f, 0.5f,
        0.5f, 0.5f, 0.5f,
        0.0f, 0.5f, 0.5f
    };*/
    float cube_vertices[] = {
        0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,

        0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.0f, 0.5f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,

        0.0f, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f,
        0.5f, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
        0.0f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,

        0.0f, 0.0f, 0.5f, 1.0f, 1.0f, 0.0f,
        0.0f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f,
        0.0f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,

        0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.5f, 0.5f, 0.0f, 1.0f, 1.0f,

        0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        0.5f, 0.0f, 0.5f, 1.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 0.5f, 1.0f, 0.0f, 1.0f
    };
    unsigned int cube_indices[] = {
        0, 3, 2,
        2, 1, 0,

        4, 5, 7,
        7, 6, 4,

        8, 9, 10,
        10, 11, 8,

        12, 13, 14,
        14, 15, 12,

        16, 17, 18,
        18, 19, 16,

        20, 21, 22,
        22, 23, 20
    };
    /*unsigned int cube_indices[] = {
        0, 3, 2,
        2, 1, 0,

        1, 2, 6,
        6, 5, 1,

        5, 6, 7,
        7 ,4, 5,

        4, 7, 3,
        3, 0, 4,

        6, 2, 3,
        3, 7, 6,

        1, 5, 4,
        4, 0, 1
    };*/
    /*float cube_vertices[] = {
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,

        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,

        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
    };*/
    // world space positions of our cubes
    /*glm::vec3 cubePositions[] = {
        glm::vec3(0.0f,  0.0f,  0.0f),
        glm::vec3(2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f,  2.0f, -2.5f),
        glm::vec3(1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };*/
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);

    // position attribute
   // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    //glEnableVertexAttribArray(0);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)12);
    glEnableVertexAttribArray(1);


    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);



    //ourShader.use();

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        // activate shader
        ourShader.use();

        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        //glm::mat4 projection = glm::ortho(-2.0f, +2.0f, -1.5f, +1.5f, 0.1f, 100.0f);
        ourShader.setMat4("projection", projection);

        // camera/view transformation
        glm::mat4 view = camera.GetViewMatrix();
        //glm::mat4 view = basic_camera.createViewMatrix();
        ourShader.setMat4("view", view);

        glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
        
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, -0.3f));
        drawBookself(VAO, ourShader, translateMatrix);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.4f));
        drawTable(VAO, ourShader, translateMatrix);


        translateMatrix = glm::translate(identityMatrix, glm::vec3(2.0f, 0.0f, 2.2f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.8f, 1.0f, 0.7f));
        drawTable(VAO, ourShader, translateMatrix * scaleMatrix);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(2.0f, 0.0f, 2.0f));
        drawCup(VAO, ourShader, translateMatrix);

        //drawCup(VAO, ourShader, identityMatrix);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.3f));
        drawCup(VAO, ourShader, translateMatrix);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.5f));
        drawCup(VAO, ourShader, translateMatrix);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.7f));
        drawCup(VAO, ourShader, translateMatrix);

        drawSofa(VAO, ourShader);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 1.5f));
        drawChair(VAO, ourShader, translateMatrix);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(1.5f, 0.0f,-0.3f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(12.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 1.3f, 1.2f));
        drawTelevision(VAO, ourShader, rotateYMatrix*scaleMatrix*translateMatrix);

        if (fanOn) {
            rotateYMatrix = glm::rotate(identityMatrix, glm::radians(r), glm::vec3(0.0f, 1.0f, 0.0f));
            drawFan(VAO, ourShader, rotateYMatrix, r);
            /*rotateYMatrix = glm::rotate(identityMatrix, glm::radians(r+90), glm::vec3(0.0f, 1.0f, 0.0f));
            drawFan(VAO, ourShader, rotateYMatrix);*/
            r += 2.0;
        }
        else {
            drawFan(VAO, ourShader, identityMatrix, r);
        }



        drawOuterWall(VAO, ourShader);
        drawFloor(VAO, ourShader, identityMatrix);
        drawWindow(VAO, ourShader);
        drawFrame(VAO, ourShader,identityMatrix);
        
        




        // render boxes
        //for (unsigned int i = 0; i < 10; i++)
        //{
        //    // calculate the model matrix for each object and pass it to shader before drawing
        //    glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //    model = glm::translate(model, cubePositions[i]);
        //    float angle = 20.0f * i;
        //    model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        //    ourShader.setMat4("model", model);

        //    glDrawArrays(GL_TRIANGLES, 0, 36);
        //}

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}
void drawBookself(unsigned int VAO, Shader ourShader, glm::mat4 matr) {
    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
    /*translateMatrix = glm::translate(identityMatrix, glm::vec3(translate_X, translate_Y, translate_Z));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(scale_X, scale_Y, scale_Z));
    model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;*/

    //translateMatrix = glm::translate(identityMatrix, glm::vec3(translate_X, translate_Y, translate_Z));
    //rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
    //rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
    //rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
    //scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.0f, 0.2f, 2.0f));
    //model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
    //ourShader.setMat4("model", model);
    ////ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));

    //glBindVertexArray(VAO);
    //glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


    scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.0f, 0.2f, 0.4f));
    model = matr * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
    //ourShader.setVec4("color", glm::vec4(0.145f, 0.271f, 0.078f, 1.0f));
    //ourShader.setVec4("color", glm::vec4(0.067f, 0.388f, 0.098f, 1.0f));
    ourShader.setVec4("color", glm::vec4(0.071f, 0.098f, 0.173f, 1.0f));

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, 2.5f, 0.4f));
    model = matr * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
    //ourShader.setVec4("color", glm::vec4(0.102f, 0.188f, 0.051f, 1.0f));

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.9f, 0.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, 2.5f, 0.4f));
    model = matr * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
    //ourShader.setVec4("color", glm::vec4(0.173f, 0.278f, 0.11f, 1.0f));

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 1.15f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.0f, 0.2f, 0.4f));
    model = matr * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));


    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.1f, 0.8325f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.6f, 0.1f, 0.4f));
    model = matr * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
    ourShader.setVec4("color", glm::vec4(0.192f, 0.459f, 0.22f, 1.0f));

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.1f, 0.515f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.6f, 0.1f, 0.4f));
    model = matr * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
    //ourShader.setVec4("color", glm::vec4(0.192f, 0.459f, 0.22f, 1.0f));
    //ourShader.setVec4("color", glm::vec4(0.196f, 0.361f, 0.11f, 1.0f));
    //ourShader.setVec4("color", glm::vec4(0.122f, 0.165f, 0.29f, 1.0f));
    ourShader.setVec4("color", glm::vec4(0.192f, 0.459f, 0.22f, 1.0f));

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.45f, 0.1f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, 0.83f, 0.4f));
    model = matr * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
    ourShader.setVec4("color", glm::vec4(0.122f, 0.165f, 0.29f, 1.0f));
    
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //for book
    //rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.15f, 0.1f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 0.60f, 0.4f));
    model = matr * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
    ourShader.setVec4("color", glm::vec4(0.071f, 0.18f, 0.024f, 1.0f));
    
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.22f, 0.1f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 0.60f, 0.4f));
    model = matr * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
    ourShader.setVec4("color", glm::vec4(0.196f, 0.043f, 0.439f, 1.0f));
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.29f, 0.1f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 0.60f, 0.4f));
    model = matr * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
    ourShader.setVec4("color", glm::vec4(0.496f, 0.73f, 0.439f, 1.0f));
    
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.36f, 0.1f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 0.60f, 0.4f));
    model = matr * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
    ourShader.setVec4("color", glm::vec4(0.612f, 0.404f, 0.098f, 1.0f));
    
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(9.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.28f, 0.835f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 0.50f, 0.4f));
    model = matr * rotateZMatrix * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
    ourShader.setVec4("color", glm::vec4(0.776f, 0.859f, 0.027f, 1.0f));
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(9.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.36f, 0.830f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 0.50f, 0.4f));
    model = matr * rotateZMatrix * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
    ourShader.setVec4("color", glm::vec4(0.58f, 0.102f, 0.184f, 1.0f));
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(9.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.44f, 0.825f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 0.50f, 0.4f));
    model = matr * rotateZMatrix * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
    ourShader.setVec4("color", glm::vec4(0.58f, 0.102f, 0.184f, 1.0f));
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void drawTable(unsigned int VAO, Shader ourShader, glm::mat4 matr) {
    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
    /*translateMatrix = glm::translate(identityMatrix, glm::vec3(translate_X, translate_Y, translate_Z));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(scale_X, scale_Y, scale_Z));
    model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;*/

    //translateMatrix = glm::translate(identityMatrix, glm::vec3(translate_X, translate_Y, translate_Z));
    //rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
    //rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
    //rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
    //scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.0f, 0.2f, 2.0f));
    //model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
    //ourShader.setMat4("model", model);
    ////ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));

    //glBindVertexArray(VAO);
    //glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.4f, 0.4f, 0.8f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 0.15f, 1.5f));
    model = matr * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
    ourShader.setVec4("color", glm::vec4(0.404f, 0.337f, 0.298f, 1.0f));
    
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //draw leg of table

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.4f, 0.4f, 0.8f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.15f, -1.0f, 0.15f));
    model = matr * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
    ourShader.setVec4("color", glm::vec4(0.251f, 0.227f, 0.216f, 1.0f));

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.825f, 0.4f, 0.8f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.15f, -1.0f, 0.15f));
    model = matr * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
    ourShader.setVec4("color", glm::vec4(0.251f, 0.227f, 0.216f, 1.0f));

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.825f, 0.4f, 1.475f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.15f, -1.0f, 0.15f));
    model = matr * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
    ourShader.setVec4("color", glm::vec4(0.251f, 0.227f, 0.216f, 1.0f));

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.4f, 0.4f, 1.475f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.15f, -1.0f, 0.15f));
    model = matr * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
    ourShader.setVec4("color", glm::vec4(0.251f, 0.227f, 0.216f, 1.0f));

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
   
}

void drawChair(unsigned int VAO, Shader ourShader, glm::mat4 matr) {
    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
    /*translateMatrix = glm::translate(identityMatrix, glm::vec3(translate_X, translate_Y, translate_Z));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(scale_X, scale_Y, scale_Z));
    model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;*/

    //translateMatrix = glm::translate(identityMatrix, glm::vec3(translate_X, translate_Y, translate_Z));
    //rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
    //rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
    //rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
    //scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.0f, 0.2f, 2.0f));
    //model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
    //ourShader.setMat4("model", model);
    ////ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));

    //glBindVertexArray(VAO);
    //glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.4f, 0.4f, 0.8f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 0.15f, 1.0f));
    model = matr * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
    //ourShader.setVec4("color", glm::vec4(0.404f, 0.337f, 0.298f, 1.0f));
    ourShader.setVec4("color", glm::vec4(0.549f, 0.255f, 0.11f, 1.0f));

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.4f, 0.4f, 1.28f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 1.5f, 0.15f));
    model = matr * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
    //ourShader.setVec4("color", glm::vec4(0.404f, 0.337f, 0.298f, 1.0f));
    ourShader.setVec4("color", glm::vec4(0.682f, 0.333f, 0.153f, 1.0f));

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //draw leg of chair

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.4f, 0.4f, 0.8f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.15f, -1.0f, 0.15f));
    model = matr * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
    ourShader.setVec4("color", glm::vec4(0.157f, 0.075f, 0.035f, 1.0f));

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.825f, 0.4f, 0.8f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.15f, -1.0f, 0.15f));
    model = matr * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
    ourShader.setVec4("color", glm::vec4(0.157f, 0.075f, 0.035f, 1.0f));

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.825f, 0.4f, 1.28f));
    ourShader.setVec4("color", glm::vec4(0.157f, 0.075f, 0.035f, 1.0f));
    model = matr * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
    ourShader.setVec4("color", glm::vec4(0.157f, 0.075f, 0.035f, 1.0f));

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.4f, 0.4f, 1.28f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.15f, -1.0f, 0.15f));
    model = matr * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
    ourShader.setVec4("color", glm::vec4(0.157f, 0.075f, 0.035f, 1.0f));

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    //handle of cahir

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.40f, 0.8f, 2.40f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.10f, -0.65f, 0.1f));
    model = translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("color", glm::vec4(0.157f, 0.075f, 0.035f, 1.0f));

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.45f, 0.8f, 2.45f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(-0.1f, -0.1f, 0.70f));
    model = translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("color", glm::vec4(0.157f, 0.075f, 0.035f, 1.0f));

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.85f, 0.8f, 2.40f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.10f, -0.65f, 0.1f));
    model = translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("color", glm::vec4(0.157f, 0.075f, 0.035f, 1.0f));

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.90f, 0.8f, 2.45f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(-0.1f, -0.1f, 0.70f));
    model = translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("color", glm::vec4(0.157f, 0.075f, 0.035f, 1.0f));

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

}

void drawFrame(unsigned int VAO, Shader ourShader, glm::mat4 matr) {
    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
    /*translateMatrix = glm::translate(identityMatrix, glm::vec3(translate_X, translate_Y, translate_Z));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(scale_X, scale_Y, scale_Z));
    model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;*/

    //translateMatrix = glm::translate(identityMatrix, glm::vec3(translate_X, translate_Y, translate_Z));
    //rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
    //rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
    //rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
    //scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.0f, 0.2f, 2.0f));
    //model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
    //ourShader.setMat4("model", model);
    ////ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));

    //glBindVertexArray(VAO);
    //glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

   

    /*translateMatrix = glm::translate(identityMatrix, glm::vec3(0.85f, 2.5f, 3.4f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.60f, -0.65f, 0.6f));
    model = translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("color", glm::vec4(0.157f, 0.075f, 0.035f, 1.0f));

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.90f, 0.8f, 2.45f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(-0.1f, -0.1f, 0.70f));
    model = translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("color", glm::vec4(0.157f, 0.075f, 0.035f, 1.0f));

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);*/

}

void drawCup(unsigned int VAO, Shader ourShader, glm::mat4 matr) {

    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;

    //draw cup on table
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.5f, 0.47f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.03f, 0.3f, 0.15f));
    model = matr * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
    //ourShader.setVec4("color", glm::vec4(0.447f, 0.451f, 0.443f, 1.0f));
    ourShader.setVec4("color", glm::vec4(0.863f, 0.871f, 0.131f, 1.0f));
    
    
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.5f, 0.47f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.15f, 0.3f, 0.03f));
    model = matr * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
    //ourShader.setVec4("color", glm::vec4(0.863f, 0.871f, 0.831f, 1.0f));
    ourShader.setVec4("color", glm::vec4(0.863f, 0.871f, 0.831f, 1.0f));
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.5f, 0.47f, 1.07f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.15f, 0.3f, 0.03f));
    model = matr * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
    //ourShader.setVec4("color", glm::vec4(0.863f, 0.871f, 0.831f, 1.0f));
    ourShader.setVec4("color", glm::vec4(0.863f, 0.871f, 0.831f, 1.0f));

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.56f, 0.47f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.03f, 0.3f, 0.15f));
    model = matr * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
    //ourShader.setVec4("color", glm::vec4(0.447f, 0.451f, 0.443f, 1.0f));
    ourShader.setVec4("color", glm::vec4(0.863f, 0.871f, 0.831f, 1.0f));
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //handle of cup
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.535f, 0.5f, 1.07f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.02f, 0.02f, 0.14f));
    model = matr * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
    ourShader.setVec4("color", glm::vec4(0.149f, 0.149f, 0.145f, 1.0f));

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.535f, 0.5f, 1.13f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.02f, 0.14f, 0.02f));
    model = matr * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.535f, 0.57f, 1.07f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.02f, 0.02f, 0.14f));
    model = matr * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}


void drawSofa(unsigned int VAO, Shader ourShader) {
    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
    /*translateMatrix = glm::translate(identityMatrix, glm::vec3(translate_X, translate_Y, translate_Z));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(scale_X, scale_Y, scale_Z));
    model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;*/

    //translateMatrix = glm::translate(identityMatrix, glm::vec3(translate_X, translate_Y, translate_Z));
    //rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
    //rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
    //rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
    //scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.0f, 0.2f, 2.0f));
    //model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
    //ourShader.setMat4("model", model);
    ////ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));

    //glBindVertexArray(VAO);
    //glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.5f, 0.3f, 0.8f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.15f, 0.15f, 3.0f));
    model = translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("color", glm::vec4(0.549f, 0.255f, 0.11f, 1.0f));
    
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.5f, 0.3f, 0.8f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.15f, -0.75f, 0.15f));
    model = translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("color", glm::vec4(0.157f, 0.075f, 0.035f, 1.0f));

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.005f, 0.3f, 0.8f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.15f, -0.75f, 0.15f));
    model = translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("color", glm::vec4(0.157f, 0.075f, 0.035f, 1.0f));

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.005f, 0.3f, 1.5f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.15f, -0.75f, 0.15f));
    model = translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("color", glm::vec4(0.157f, 0.075f, 0.035f, 1.0f));

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


    translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.5f, 0.3f, 1.5f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.15f, -0.75f, 0.15f));
    model = translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("color", glm::vec4(0.157f, 0.075f, 0.035f, 1.0f));

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.5f, 0.3f, 2.225f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.15f, -0.75f, 0.15f));
    model = translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("color", glm::vec4(0.157f, 0.075f, 0.035f, 1.0f));

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.005f, 0.3f, 2.225f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.15f, -0.75f, 0.15f));
    model = translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("color", glm::vec4(0.157f, 0.075f, 0.035f, 1.0f));

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //backwall of sofa

    translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.5f, 0.35f, 0.8f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.15f, 1.0f, 3.0f));
    model = translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("color", glm::vec4(0.682f, 0.333f, 0.153f, 1.0f));

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //side handle of sofa

    //left hand
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.1f, 0.7f, 0.8f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.10f, -0.75f, 0.10f));
    model = translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("color", glm::vec4(0.157f, 0.075f, 0.035f, 1.0f));

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.1f, 0.7f, 0.8f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(-0.750f, -0.1f, 0.10f));
    model = translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("color", glm::vec4(0.157f, 0.075f, 0.035f, 1.0f));

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


    //right hand

    translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.1f, 0.7f, 2.225f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.10f, -0.75f, 0.10f));
    model = translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("color", glm::vec4(0.157f, 0.075f, 0.035f, 1.0f));

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.1f, 0.7f, 2.225f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(-0.750f, -0.1f, 0.10f));
    model = translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("color", glm::vec4(0.157f, 0.075f, 0.035f, 1.0f));

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


}

void drawTelevision(unsigned int VAO, Shader ourShader, glm::mat4 matr) {
    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
    /*translateMatrix = glm::translate(identityMatrix, glm::vec3(translate_X, translate_Y, translate_Z));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(scale_X, scale_Y, scale_Z));
    model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;*/

    //translateMatrix = glm::translate(identityMatrix, glm::vec3(translate_X, translate_Y, translate_Z));
    //rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
    //rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
    //rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
    //scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.0f, 0.2f, 2.0f));
    //model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
    //ourShader.setMat4("model", model);
    ////ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));

    //glBindVertexArray(VAO);
    //glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    //cells
    translateMatrix = glm::translate(identityMatrix, glm::vec3(1.5f, 0.3f, 0.8f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 0.15f, 1.0f));
    model = matr * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
    ourShader.setVec4("color", glm::vec4(0.373f, 0.412f, 0.216f, 1.0f));
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //cells
    translateMatrix = glm::translate(identityMatrix, glm::vec3(1.5f, 0.10f, 0.87f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 0.15f, 0.7f));
    model = matr * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
    ourShader.setVec4("color", glm::vec4(0.247f, 0.271f, 0.137f, 1.0f));
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(1.925f, 0.3f, 0.8f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.15f, -1.0f, 1.0f));
    model = matr * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
    ourShader.setVec4("color", glm::vec4(0.157f, 0.075f, 0.035f, 1.0f));
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(1.5f, 0.3f, 0.8f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, -1.0f, 0.15f));
    model = matr * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(1.5f, 0.3f, 1.225f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, -1.0f, 0.15f));
    model = matr * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


    //translateMatrix = glm::translate(identityMatrix, glm::vec3(0.4f, 0.4f, 1.225f));
    //scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.15f, -1.0f, 0.15f));
    //model = translateMatrix * scaleMatrix;
    //ourShader.setMat4("model", model);
    ////ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));

    //glBindVertexArray(VAO);
    //glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //television drawing.....

    translateMatrix = glm::translate(identityMatrix, glm::vec3(1.65f, 0.4f, 0.95f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.3f, 0.10f, 0.5f));
    model = matr * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
    ourShader.setVec4("color", glm::vec4(0.071f, 0.071f, 0.067f, 1.0f));
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(1.77f, 0.4f, 1.05f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.10f, 0.30f, 0.15f));
    model = matr * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
    ourShader.setVec4("color", glm::vec4(0.118f, 0.122f, 0.114f, 1.0f));
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    // pc frame...............
    translateMatrix = glm::translate(identityMatrix, glm::vec3(1.77f, 0.5f, 0.74f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.10f, 0.10f, 1.5f));
    model = matr * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
    ourShader.setVec4("color", glm::vec4(0.071f, 0.071f, 0.067f, 1.0f));
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(1.77f, 0.5f, 0.74f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.10f, 0.75f, 0.10f));
    model = matr * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(1.77f, 0.85f, 0.74f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.10f, 0.10f, 1.5f));
    model = matr * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(1.77f, 0.5f, 1.44f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.10f, 0.75f, 0.10f));
    model = matr * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //pc screen............

    translateMatrix = glm::translate(identityMatrix, glm::vec3(1.77f, 0.86f, 0.80f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.10f, -0.60f, 1.3f));
    model = matr * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
    ourShader.setVec4("color", glm::vec4(0.784f, 0.812f, 0.678f, 1.0f));
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);



}

void drawFan(unsigned int VAO, Shader ourShader, glm::mat4 matr, float r) {
    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model,combined, translateMatrix3;
    /*translateMatrix = glm::translate(identityMatrix, glm::vec3(translate_X, translate_Y, translate_Z));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(scale_X, scale_Y, scale_Z));
    model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;*/

    //translateMatrix = glm::translate(identityMatrix, glm::vec3(translate_X, translate_Y, translate_Z));
    //rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
    //rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
    //rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
    //scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.0f, 0.2f, 2.0f));
    //model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
    //ourShader.setMat4("model", model);
    ////ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));

    //glBindVertexArray(VAO);
    //glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //translateMatrix = glm::translate(identityMatrix, glm::vec3(0.4f, 3.0f, 0.8f));
    //scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.6f, 0.10f, 0.2f));
    //rotateYMatrix = glm::rotate(identityMatrix, glm::radians(r), glm::vec3(0.0f, 1.0f, 0.0f));
    //model = translateMatrix * matr * glm::translate(identityMatrix, glm::vec3(-0.4f, -3.0f, -0.8f)) * scaleMatrix;
    //ourShader.setMat4("model", model);
    ////ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
    //glBindVertexArray(VAO);
    //glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


    //translateMatrix = glm::translate(identityMatrix, glm::vec3(0.4f, 3.0f, 0.8f));
    //scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.6f, 0.10f, 0.2f));
    //rotateYMatrix = glm::rotate(identityMatrix, glm::radians(r+90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    //model = translateMatrix * matr * glm::translate(identityMatrix, glm::vec3(-0.4f, -3.0f, -0.8f)) * scaleMatrix;
    //ourShader.setMat4("model", model);
    ////ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
    //glBindVertexArray(VAO);
    //glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 2.5f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.0f, 0.1f, 0.2f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(r), glm::vec3(0.0f, 1.0f, 0.0f));
    model = translateMatrix *  glm::translate(identityMatrix, glm::vec3(0.5f, 0.0f, 0.0f)) * rotateYMatrix * glm::translate(identityMatrix, glm::vec3(-0.5f, 0.0f, 0.0f)) * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
    ourShader.setVec4("color", glm::vec4(0.071f, 0.071f, 0.067f, 1.0f));
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 2.5f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.0f, 0.1f, 0.2f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(r + 90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = translateMatrix * glm::translate(identityMatrix, glm::vec3(0.5f, 0.0f, 0.0f)) * rotateYMatrix * glm::translate(identityMatrix, glm::vec3(-0.5f, 0.0f, 0.0f)) * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.465f, 2.54f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 0.88f, 0.1f));
    model = translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
    ourShader.setVec4("color", glm::vec4(0.259f, 0.259f, 0.251f, 1.0f));
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 3.0f, 1.0f));
    //scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.0f, 0.1f, 0.2f));
    //rotateYMatrix = glm::rotate(identityMatrix, glm::radians(r + 120.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    //model = translateMatrix * glm::translate(identityMatrix, glm::vec3(0.5f, 0.0f, 0.0f)) * rotateYMatrix * glm::translate(identityMatrix, glm::vec3(-0.5f, 0.0f, 0.0f)) * scaleMatrix;
    //ourShader.setMat4("model", model);
    ////ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
    //glBindVertexArray(VAO);
    //glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

}


void drawOuterWall(unsigned int VAO, Shader ourShader) {

    glm::mat4 identityMatrix = glm::mat4(1.0f);
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-1.0f, -0.01f, -0.5f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(8.5f, 6.0f, 8.0f));
    model = translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("color", glm::vec4(0.82f, 0.702f, 0.667f, 1.0f));
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);


    /*translateMatrix = glm::translate(identityMatrix, glm::vec3(-1.0f, 0.01f, -0.5f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.0f, 6.0f, 3.5f));
    model = translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("color", glm::vec4(1.0f, 0.8431f, 0.7019f, 1.0f));
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);*/

    translateMatrix = glm::translate(identityMatrix, glm::vec3(-1.0f, 2.98f, -0.5f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(8.5f, 0.01f, 8.0f));
    model = translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("color", glm::vec4(0.871f, 0.851f, 0.82f, 1.0f));
    
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(-1.0f, -0.3f, -0.5f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(8.5f, 0.5f, 8.0f));
    model = translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("color", glm::vec4(0.82f, 0.698f, 0.576f, 1.0f));
    //ourShader.setVec4("color", glm::vec4(0.894f, 0.902f, 0.906f, 1.0f));
    
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void drawFloor(unsigned int VAO, Shader ourShader, glm::mat4 matr) {
    glm::mat4 identityMatrix = glm::mat4(1.0f);
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;

    //translateMatrix = glm::translate(identityMatrix, glm::vec3(-1.0f, -0.02f, -0.5f));
    //scaleMatrix = glm::scale(identityMatrix, glm::vec3(8.5f, 0.01f, 8.0f));
    //model = translateMatrix * scaleMatrix;
    //ourShader.setMat4("model", model);
    ////ourShader.setVec4("color", glm::vec4(0.82f, 0.698f, 0.576f, 1.0f));
    //ourShader.setVec4("color", glm::vec4(0.894f, 0.902f, 0.906f, 1.0f));
   
    //glBindVertexArray(VAO);
    //glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    for (int i = 0; i <= 16; i++) {
        if (i % 2 == 0) {
            for (int j = 0; j < 16; j++) {
                translateMatrix = glm::translate(identityMatrix, glm::vec3(( - 1.0+0.25*i), -0.02f, (-0.5 + 0.25 * j)));
                scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 0.01f, 0.5f));
                model = translateMatrix * scaleMatrix;
                ourShader.setMat4("model", model);
                if (j % 2 == 0)
                    //ourShader.setVec4("color", glm::vec4(0.82f, 0.698f, 0.576f, 1.0f));
                    ourShader.setVec4("color", glm::vec4(0.839f, 0.725f, 0.725f, 1.0f));
                else {
                    //ourShader.setVec4("color", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
                    ourShader.setVec4("color", glm::vec4(0.439f, 0.384f, 0.384f, 1.0f));
                }
                //ourShader.setVec4("color", glm::vec4(0.894f, 0.902f, 0.906f, 1.0f));

                glBindVertexArray(VAO);
                glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
            }
        }
        else {

            for (int j = 0; j < 16; j++) {
                translateMatrix = glm::translate(identityMatrix, glm::vec3((-1.0 + 0.25 * i), -0.02f, (-0.5 + 0.25 * j)));
                scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 0.01f, 0.5f));
                model = translateMatrix * scaleMatrix;
                ourShader.setMat4("model", model);
                if (j % 2 != 0)
                    //ourShader.setVec4("color", glm::vec4(0.82f, 0.698f, 0.576f, 1.0f));
                    ourShader.setVec4("color", glm::vec4(0.839f, 0.725f, 0.725f, 1.0f));
                else {
                    //ourShader.setVec4("color", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
                    ourShader.setVec4("color", glm::vec4(0.439f, 0.384f, 0.384f, 1.0f));
                }
                //ourShader.setVec4("color", glm::vec4(0.894f, 0.902f, 0.906f, 1.0f));

                glBindVertexArray(VAO);
                glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
            }

        }
    }

}




void drawWindow(unsigned int VAO, Shader ourShader) {

    glm::mat4 identityMatrix = glm::mat4(1.0f);
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;

    translateMatrix = glm::translate(identityMatrix, glm::vec3(3.2f, 2.0f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.10f, -2.0f, 2.8f));
    model = translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
    
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //window frame
    //left
    translateMatrix = glm::translate(identityMatrix, glm::vec3(3.15f, 2.0f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.10f, -2.0f, 0.10f));
    model = translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
    ourShader.setVec4("color", glm::vec4(0.239f, 0.239f, 0.067f, 1.0f));
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    //top
    translateMatrix = glm::translate(identityMatrix, glm::vec3(3.15f, 2.0f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.10f, -0.1f, 2.8f));
    model = translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    //right
    translateMatrix = glm::translate(identityMatrix, glm::vec3(3.15f, 2.0f, 2.35f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.10f, -2.0f, 0.10f));
    model = translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //bottom
    translateMatrix = glm::translate(identityMatrix, glm::vec3(3.15f, 1.0f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.10f, -0.1f, 2.8f));
    model = translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


    //middle divider

    translateMatrix = glm::translate(identityMatrix, glm::vec3(3.15f, 2.0f, 1.65f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.10f, -2.0f, 0.15f));
    model = translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //right glass of the window

    translateMatrix = glm::translate(identityMatrix, glm::vec3(3.18f, 2.0f, 1.65f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.10f, -2.0f, 1.4f));
    model = translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec4("Color", glm::vec4(1.0f, 1.0f, 1.0f,1.0f));
    ourShader.setVec4("color", glm::vec4(0.941f, 0.949f, 0.886f, 1.0f));
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //left glass of the window

    translateMatrix = glm::translate(identityMatrix, glm::vec3(3.18f, 2.0f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.10f, -2.0f, 1.4f));
    model = translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec4("Color", glm::vec4(1.0f, 1.0f, 1.0f,1.0f));
    ourShader.setVec4("color", glm::vec4(0.941f, 0.949f, 0.886f, 1.0f));
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


}






// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.ProcessKeyboard(LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {
        /*eyeY -= 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);*/
        camera.ProcessKeyboard(UP, deltaTime);

    }

    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
    {
        /*if (rotateAxis_X) rotateAngle_X -= 1;
        else if (rotateAxis_Y) rotateAngle_Y -= 1;
        else rotateAngle_Z -= 1;*/
        camera.ProcessKeyboard(DOWN, deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS) {
        camera.ProcessKeyboard(WORLD_UP, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) translate_Y += 0.001;
    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) translate_Y -= 0.001;
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) translate_X += 0.001;
    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) translate_X -= 0.001;
    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) translate_Z += 0.001;
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) translate_Z -= 0.001;
    /*if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) scale_X += 0.001;*/
    if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS) scale_X -= 0.001;
    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) scale_Y += 0.001;
    if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) scale_Y -= 0.001;
    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) scale_Z += 0.001;
    if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) scale_Z -= 0.001;

    //pitch operation......
    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
    {
        /*rotateAngle_X += 0.05;
        rotateAxis_X = 0.05;
        rotateAxis_Y = 0.0;
        rotateAxis_Z = 0.0;*/

        camera.ProcessKeyboard(PITCH_A, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
        camera.ProcessKeyboard(PITCH_C, deltaTime);
    }

    //YAW operation.........
    if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
    {
        /*rotateAngle_Y += 0.05;
        rotateAxis_X = 0.05;
        rotateAxis_Y = 0.05;
        rotateAxis_Z = 0.0;*/
        camera.ProcessKeyboard(YAW_R, deltaTime);

    }
    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
    {
        /*eyeZ += 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);*/

        camera.ProcessKeyboard(YAW_L, deltaTime);
    }


    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
    {
        /*rotateAngle_Z += 0.05;
        rotateAxis_X = 0.0;
        rotateAxis_Y = 0.0;
        rotateAxis_Z = 0.05;*/
        camera.ProcessKeyboard(ROLL_L, deltaTime);
        
    }

    if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
    {
        eyeX += 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
    {
        eyeX -= 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }
    
    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
    {
        /*eyeZ -= 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);*/

        if (fanOn) {
            fanOn = false;
        }
        else {
            fanOn = true;
        }
    }

    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        eyeY += 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }
   
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
    {
        lookAtX += 2.5 * deltaTime;
        basic_camera.changeLookAt(lookAtX, lookAtY, lookAtZ);
    }
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
    {
        lookAtX -= 2.5 * deltaTime;
        basic_camera.changeLookAt(lookAtX, lookAtY, lookAtZ);
    }
    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
    {
        lookAtY += 2.5 * deltaTime;
        basic_camera.changeLookAt(lookAtX, lookAtY, lookAtZ);
    }
    if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
    {
        lookAtY -= 2.5 * deltaTime;
        basic_camera.changeLookAt(lookAtX, lookAtY, lookAtZ);
    }
    if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
    {
        lookAtZ += 2.5 * deltaTime;
        basic_camera.changeLookAt(lookAtX, lookAtY, lookAtZ);
    }
    if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
    {
        lookAtZ -= 2.5 * deltaTime;
        basic_camera.changeLookAt(lookAtX, lookAtY, lookAtZ);
    }
    if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS)
    {
        basic_camera.changeViewUpVector(glm::vec3(1.0f, 0.0f, 0.0f));
    }
    if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS)
    {
        basic_camera.changeViewUpVector(glm::vec3(0.0f, 1.0f, 0.0f));
    }
    if (glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS)
    {
        basic_camera.changeViewUpVector(glm::vec3(0.0f, 0.0f, 1.0f));
    }

   /* if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS)
    {
        
    }*/

}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}