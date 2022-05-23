#define GL_GLEXT_PROTOTYPES 1
#define GL3_PROTOTYPES 1

#include "mesh.hpp"

#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>

Mesh::Mesh(int vertices, int primitives)
{
  this->vertices = std::vector<vertex>(vertices);
  this->primitives = std::vector<primitive>(primitives);
  // Create vertex buffer
  glGenBuffers(1, &vertex_buffer);
  // Create primitive buffer
  glGenBuffers(1, &primitive_buffer);
  // Update the buffers
  updateGLBuffers();
}

Mesh::~Mesh()
{
}

void Mesh::updateGLBuffers()
{
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertex), &vertices[0], GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, primitive_buffer);
  glBufferData(GL_ARRAY_BUFFER, primitives.size() * sizeof(primitive), &primitives[0], GL_STATIC_DRAW);
}

void Mesh::draw()
{
  // Bind the vertex buffer
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
  // Enable the vertex attribute arrays
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  // Set the vertex attribute pointers
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void *)0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void *)12);
  // Bind the primitive buffer
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, primitive_buffer);
  // Draw the primitives
  glDrawElements(GL_TRIANGLES, primitives.size() * 3, GL_UNSIGNED_INT, (void *)0);
  // Disable the vertex attribute arrays
  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
}

void Mesh::setVertex(int index, vertex v)
{
  vertices[index] = v;
  updateGLBuffers();
}