#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <print>
#include "loadshader.h"
#include "buffers.h"
#include "stb_image.h"

#define VERTEX_PATH "./shaders/vert.glsl"
#define FRAGMENT_PATH "./shaders/frag.glsl"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);  


// for bocchi
float aspect = 1.0f;  // default, will be updated after loading
GLfloat vertices[] = {
    // pos                        // color            // tex
    -0.5f * aspect, -0.5f, 0.0f,   1.0f,0.0f,0.0f,    0.0f,0.0f, // bottom-left
    0.5f * aspect, -0.5f, 0.0f,   0.0f,1.0f,0.0f,    1.0f,0.0f, // bottom-right
    -0.5f * aspect,  0.5f, 0.0f,   1.0f,1.0f,1.0f,    0.0f,1.0f, // top-left
    0.5f * aspect,  0.5f, 0.0f,   0.0f,0.0f,1.0f,    1.0f,1.0f  // top-right
};

// GLfloat vertices[] = {
//     // Coordinates          // Colors
// //     -0.5f, -0.5f, 0.0f,     0.08f, 0.03f, 0.02f,
// //     0.5f, -0.5f, 0.0f,      0.08f, 0.03f, 0.02f,
// //     0.0f, 0.5f, 0.0f,       1.0f, 0.6f, 0.32f,
// //     -0.5f / 2, 0.0f, 0.0f,  0.9f, 0.45f, 0.17f,   // Inner Left
// //     0.5f / 2, 0.0f, 0.0f,   0.9f, 0.45f, 0.17f,   // Inner Right
// //     0.0f, -0.5f, 0.0f,      0.8f, 0.3f, 0.2f,     // Inner Down
//     -0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,  0.0f, 0.0f,  // 0 bottom-left
//      0.5f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f,  1.0f, 0.0f,  // 1 bottom-right
//     -0.5f,  0.5f, 0.0f,     1.0f, 1.0f, 1.0f,  0.0f, 1.0f,  // 2 top-left
//      0.5f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f,  1.0f, 1.0f   // 3 top-right
// };


GLuint indices[] = {
    // 0, 3, 5,
    // 3, 2, 4,
    // 5, 4, 1,
    0, 1, 2,   // bottom-left, bottom-right, top-left
    1, 3, 2    // bottom-right, top-right, top-left
};

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(900, 600, "Spinnin ahh", NULL, NULL);
    if(window == nullptr){
        std::printf("[ERROR] Failed Creating Window\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }    
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  
    
    GLuint shaderProgram = createShaderProgram(VERTEX_PATH, FRAGMENT_PATH);
    //glLinkProgram(shaderProgram);

    // Getting Data from Cpu to Gpu
    // !! You should Generate VAO first before VBO
    // !! Ordering is very important
    VAO vao; VBO vbo; EBO ebo;
    VAO_Create(vao);
    VAO_Bind(vao);

    VBO_Create(vbo, vertices, sizeof(vertices));
    EBO_Create(ebo, indices, sizeof(indices));
    VAO_LinkAttrib(vao, vbo, 0, 3, GL_FLOAT, 8 * sizeof(float));
    VAO_LinkAttrib(vao, vbo, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    VAO_LinkAttrib(vao, vbo, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);

    // Texture
    int imgwidth, imgheight, numColCh;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* bytes = stbi_load("Literally_me_I_am_him.jpg", &imgwidth, &imgheight, &numColCh, STBI_rgb);
    if (!bytes) {
        std::cerr << "[ERROR] Failed to load image!" << std::endl;
    }
    // After stbi_load
    aspect = (float)imgwidth / (float)imgheight;

    // Patch X coordinates
    vertices[0] *= aspect;  // bottom-left X
    vertices[8] *= aspect;  // bottom-right X
    vertices[16] *= aspect; // top-left X
    vertices[24] *= aspect; // top-right X

    GLenum format = GL_RGB;
    if (numColCh == 1) format = GL_RED;
    else if (numColCh == 3) format = GL_RGB;
    else if (numColCh == 4) format = GL_RGBA;
    GLenum internalFormat = (numColCh == 4) ? GL_RGBA : GL_RGB;

    GLuint texture;
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Replace GL_RGB with internalFormat and format for other images
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgwidth, imgheight, 0, GL_RGB, GL_UNSIGNED_BYTE, bytes);
    glGenerateMipmap(GL_TEXTURE_2D);
    
    stbi_image_free(bytes);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    GLuint tex0Uni = glGetUniformLocation(shaderProgram, "tex0");
    glUseProgram(shaderProgram);
    glUniform1i(tex0Uni, 0);

    while(!glfwWindowShouldClose(window))
    {
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindTexture(GL_TEXTURE_2D, texture);
        VAO_Bind(vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    // Clean up
    VAO_Delete(vao);
    VBO_Delete(vbo);
    EBO_Delete(ebo);
    glDeleteTextures(1, &texture);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}  
