#include "algorithms.hpp"
#include "geomutils.hpp"

#include <list>
#include <algorithm>
#include <map>
#include <math.h>

struct edge
{
  int a;
  int b;
  edge(int a, int b) : a(a), b(b) {}
  bool equals(edge e)
  {
    return (a == e.a && b == e.b) || (a == e.b && b == e.a);
  }
};

std::tuple<std::vector<vertex>, std::vector<primitive>> catmullClark(std::vector<vertex> vertices, std::vector<primitive> primitives)
{
  // Create the new vertices
  std::vector<vertex> new_vertices = vertices;
  // Create the new primitives
  std::vector<primitive> new_primitives = primitives;
  // TODO: Implement the Catmull-Clark algorithm
  return std::make_tuple(new_vertices, new_primitives);
}

std::tuple<std::vector<vertex>, std::vector<primitive>> wave(std::vector<vertex> vertices, std::vector<primitive> primitives)
{
  // Create the new vertices
  std::vector<vertex> new_vertices = vertices;
  // Create the new primitives
  std::vector<primitive> new_primitives = primitives;

  // For each vertex
  for (int i = 0; i < vertices.size(); i++)
  {
    // Apply a sine wave to the vertex's position
    new_vertices[i].y += sin(vertices[i].x * vertices[i].z) * 0.1f;
  }

  return std::make_tuple(new_vertices, new_primitives);
}

std::tuple<std::vector<vertex>, std::vector<primitive>> blur(std::vector<vertex> vertices, std::vector<primitive> primitives)
{
  // Create the new vertices
  std::vector<vertex> new_vertices = vertices;
  // Create the new primitives
  std::vector<primitive> new_primitives = primitives;

  // For each vertex
  for (int i = 0; i < vertices.size(); i++)
  {
    // Retrieve the vertex's neighbors
    std::vector<int> neighbors;
    for (primitive p : primitives)
    {
      if (p.a == i || p.b == i || p.c == i)
      {
        if (p.a != i)
        {
          neighbors.push_back(p.a);
        }
        if (p.b != i)
        {
          neighbors.push_back(p.b);
        }
        if (p.c != i)
        {
          neighbors.push_back(p.c);
        }
      }
    }

    // Compute the average position of the neighbors
    float avg_y = vertices[i].y;
    for (int neighborIndex : neighbors)
    {
      avg_y += vertices[neighborIndex].y;
    }

    // Set the new vertex's position to the average
    new_vertices[i].y = avg_y / (neighbors.size() + 1.0f);
  }

  return std::make_tuple(new_vertices, new_primitives);
}

std::tuple<std::vector<vertex>, std::vector<primitive>> loop(std::vector<vertex> vertices, std::vector<primitive> primitives)
{
  // Create the new vertices (initialize with the original vertices)
  std::vector<vertex> new_vertices;
  // Create the new primitives (initialize with the original primitives)
  std::vector<primitive> new_primitives;

  // For each primitive
  for (int i = 0; i < (int)primitives.size(); i++)
  {
    // Get the primitive's vertices
    vertex a = vertices[primitives[i].a];
    vertex b = vertices[primitives[i].b];
    vertex c = vertices[primitives[i].c];

    vertex v4 = vertex((a.x + b.x) / 2, (a.y + b.y) / 2, (a.z + b.z) / 2);
    vertex v5 = vertex((b.x + c.x) / 2, (b.y + c.y) / 2, (b.z + c.z) / 2);
    vertex v6 = vertex((a.x + c.x) / 2, (a.y + c.y) / 2, (a.z + c.z) / 2);

    // Create the new vertices
    new_vertices.push_back(a);
    new_vertices.push_back(b);
    new_vertices.push_back(c);
    new_vertices.push_back(v4);
    new_vertices.push_back(v5);
    new_vertices.push_back(v6);

    int index = new_vertices.size() - 6;
    // Create the new primitive
    new_primitives.push_back(primitive(index, index + 3, index + 5));
    new_primitives.push_back(primitive(index + 3, index + 4, index + 5));
    new_primitives.push_back(primitive(index + 3, index + 1, index + 4));
    new_primitives.push_back(primitive(index + 4, index + 2, index + 5));
  }

  return std::make_tuple(new_vertices, new_primitives);
}

std::tuple<std::vector<vertex>, std::vector<primitive>> simpleSubd(std::vector<vertex> vertices, std::vector<primitive> primitives)
{
  // Create the new vertices (initialize with the original vertices)
  std::vector<vertex> new_vertices = vertices;
  // Create the new primitives (initialize with the original primitives)
  std::vector<primitive> new_primitives = primitives;

  // For each primitive
  for (int i = 0; i < (int)primitives.size(); i++)
  {
    // Get the primitive's vertices
    vertex v1 = vertices[primitives[i].a];
    vertex v2 = vertices[primitives[i].b];
    vertex v3 = vertices[primitives[i].c];

    vertex v12 = vertex((v1.x + v2.x) / 2, (v1.y + v2.y) / 2, (v1.z + v2.z) / 2);
    vertex v23 = vertex((v2.x + v3.x) / 2, (v2.y + v3.y) / 2, (v2.z + v3.z) / 2);
    vertex v13 = vertex((v1.x + v3.x) / 2, (v1.y + v3.y) / 2, (v1.z + v3.z) / 2);

    new_vertices.push_back(v12);
    new_vertices.push_back(v23);
    new_vertices.push_back(v13);

    int index = new_vertices.size() - 3;
    // Create the new primitive
    new_primitives.push_back(primitive(primitives[i].a, index, index + 2));
    new_primitives.push_back(primitive(index, index + 1, index + 2));
    new_primitives.push_back(primitive(index, primitives[i].b, index + 1));
    new_primitives.push_back(primitive(index + 1, primitives[i].c, index + 2));
  }

  return std::make_tuple(new_vertices, new_primitives);
}