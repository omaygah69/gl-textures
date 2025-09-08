#pragma once
#include <glad/glad.h>

// VBO
struct VBO {
    GLuint ID;
};
void VBO_Create(VBO& vbo, GLfloat* vertices, GLsizeiptr size);
void VBO_Bind(const VBO& vbo);
void VBO_Unbind();
void VBO_Delete(VBO& vbo);

// EBO
struct EBO {
    GLuint ID;
};
void EBO_Create(EBO& ebo, GLuint* indices, GLsizeiptr size);
void EBO_Bind(const EBO& ebo);
void EBO_Unbind();
void EBO_Delete(EBO& ebo);

// VAO
struct VAO {
    GLuint ID;
};
void VAO_Create(VAO& vao);
void VAO_Bind(const VAO& vao);
void VAO_Unbind();
void VAO_Delete(VAO& vao);
void VAO_LinkAttrib(const VAO& vao, const VBO& vbo, GLuint layout,
                 GLint components , GLenum type, GLsizei stride, const void* offset = (void*)0);

