#include "buffers.h"

// VBO 
void VBO_Create(VBO& vbo, GLfloat* vertices, GLsizeiptr size) {
    glGenBuffers(1, &vbo.ID);
    glBindBuffer(GL_ARRAY_BUFFER, vbo.ID);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void VBO_Bind(const VBO& vbo) {
    glBindBuffer(GL_ARRAY_BUFFER, vbo.ID);
}

void VBO_Unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO_Delete(VBO& vbo) {
    glDeleteBuffers(1, &vbo.ID);
}

// EBO
void EBO_Create(EBO& ebo, GLuint* indices, GLsizeiptr size) {
    glGenBuffers(1, &ebo.ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo.ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

void EBO_Bind(const EBO& ebo) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo.ID);
}

void EBO_Unbind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO_Delete(EBO& ebo) {
    glDeleteBuffers(1, &ebo.ID);
}

// VAO 
void VAO_Create(VAO& vao) {
    glGenVertexArrays(1, &vao.ID);
}

void VAO_Bind(const VAO& vao) {
    glBindVertexArray(vao.ID);
}

void VAO_Unbind() {
    glBindVertexArray(0);
}

void VAO_Delete(VAO& vao) {
    glDeleteVertexArrays(1, &vao.ID);
}

void VAO_LinkAttrib(const VAO& vao, const VBO& vbo, GLuint layout,
                 GLint components, GLenum type, GLsizei stride, const void* offset) {
    VAO_Bind(vao);
    VBO_Bind(vbo);
    glVertexAttribPointer(layout, components, type, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(layout);
    // VBO_Unbind();
    VAO_Unbind();
}
