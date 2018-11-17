#include "VertexArray.h"
#include "VertexBuffer.h"

#include <fstream>
#include <iostream>

void VertexArray::splitStringWhitespace(std::string& input, std::vector<std::string>& output)
{
  std::string curr;

  output.clear();

  for(size_t i = 0; i < input.length(); i++)
  {
    if(input.at(i) == ' ' ||
      input.at(i) == '\r' ||
      input.at(i) == '\n' ||
      input.at(i) == '\t')
    {
      if(curr.length() > 0)
      {
        output.push_back(curr);
        curr = "";
      }
    }
    else
    {
      curr += input.at(i);
    }
  }

  if(curr.length() > 0)
  {
    output.push_back(curr);
  }
}

void VertexArray::splitString(std::string& input, char splitter, std::vector<std::string>& output)
{
  std::string curr;

  output.clear();

  for(size_t i = 0; i < input.length(); i++)
  {
    if(input.at(i) == splitter)
    {
      output.push_back(curr);
      curr = "";
    }
    else
    {
      curr += input.at(i);
    }
  }

  if(curr.length() > 0)
  {
    output.push_back(curr);
  }
}

VertexArray::VertexArray(std::string path) : dirty(false)
{
  glGenVertexArrays(1, &id);

  if(!id)
  {
    throw std::exception();
  }

  buffers.resize(10);
  std::ifstream file(path.c_str());

  if(!file.is_open())
  {
    throw std::exception();
  }

  std::string line;
  std::vector<std::string> splitLine;
  std::vector<glm::vec3> positions;
  std::vector<glm::vec2> texCoords;
  std::vector<glm::vec3> normals;

  VertexBuffer *positionBuffer = NULL;
  VertexBuffer *texCoordBuffer = NULL;
  VertexBuffer *normalBuffer = NULL;

  while(!file.eof())
  {
    std::getline(file, line);
    if(line.length() < 1) continue;
    splitStringWhitespace(line, splitLine);
    if(splitLine.size() < 1) continue;

    if(splitLine.at(0) == "v")
    {
      if(!positionBuffer) positionBuffer = new VertexBuffer();

      positions.push_back(glm::vec3(
        atof(splitLine.at(1).c_str()),
        atof(splitLine.at(2).c_str()),
        atof(splitLine.at(3).c_str())));
    }
    else if(splitLine.at(0) == "vt")
    {
      if(!texCoordBuffer) texCoordBuffer = new VertexBuffer();

      texCoords.push_back(glm::vec2(
        atof(splitLine.at(1).c_str()),
        1.0f - atof(splitLine.at(2).c_str())));
    }
    else if(splitLine.at(0) == "vn")
    {
      if(!normalBuffer) normalBuffer = new VertexBuffer();

      normals.push_back(glm::vec3(
        atof(splitLine.at(1).c_str()),
        atof(splitLine.at(2).c_str()),
        atof(splitLine.at(3).c_str())));
    }
    else if(splitLine.at(0) == "f")
    {
      std::vector<std::string> subsplit;
      splitString(splitLine.at(1), '/', subsplit);

      positionBuffer->add(positions.at(atoi(subsplit.at(0).c_str()) - 1));
      if(texCoordBuffer) texCoordBuffer->add(texCoords.at(atoi(subsplit.at(1).c_str()) - 1));
      if(normalBuffer) normalBuffer->add(normals.at(atoi(subsplit.at(2).c_str()) - 1));
      splitString(splitLine.at(2), '/', subsplit);
      positionBuffer->add(positions.at(atoi(subsplit.at(0).c_str()) - 1));
      if(texCoordBuffer) texCoordBuffer->add(texCoords.at(atoi(subsplit.at(1).c_str()) - 1));
      if(normalBuffer) normalBuffer->add(normals.at(atoi(subsplit.at(2).c_str()) - 1));
      splitString(splitLine.at(3), '/', subsplit);
      positionBuffer->add(positions.at(atoi(subsplit.at(0).c_str()) - 1));
      if(texCoordBuffer) texCoordBuffer->add(texCoords.at(atoi(subsplit.at(1).c_str()) - 1));
      if(normalBuffer) normalBuffer->add(normals.at(atoi(subsplit.at(2).c_str()) - 1));

      if(splitLine.size() < 5) continue;
      splitString(splitLine.at(3), '/', subsplit);

      positionBuffer->add(positions.at(atoi(subsplit.at(0).c_str()) - 1));
      if(texCoordBuffer) texCoordBuffer->add(texCoords.at(atoi(subsplit.at(1).c_str()) - 1));
      if(normalBuffer) normalBuffer->add(normals.at(atoi(subsplit.at(2).c_str()) - 1));
      splitString(splitLine.at(4), '/', subsplit);
      positionBuffer->add(positions.at(atoi(subsplit.at(0).c_str()) - 1));
      if(texCoordBuffer) texCoordBuffer->add(texCoords.at(atoi(subsplit.at(1).c_str()) - 1));
      if(normalBuffer) normalBuffer->add(normals.at(atoi(subsplit.at(2).c_str()) - 1));
      splitString(splitLine.at(1), '/', subsplit);
      positionBuffer->add(positions.at(atoi(subsplit.at(0).c_str()) - 1));
      if(texCoordBuffer) texCoordBuffer->add(texCoords.at(atoi(subsplit.at(1).c_str()) - 1));
      if(normalBuffer) normalBuffer->add(normals.at(atoi(subsplit.at(2).c_str()) - 1));
    }
  }

  setBuffer("in_Position", positionBuffer);
  if(texCoordBuffer) setBuffer("in_TexCoord", texCoordBuffer);
  if(normalBuffer) setBuffer("in_Normal", normalBuffer);
}

VertexArray::VertexArray() : dirty(false)
{
  glGenVertexArrays(1, &id);

  if(!id)
  {
    throw std::exception();
  }

  buffers.resize(10);
}

void VertexArray::setBuffer(std::string attribute, VertexBuffer *buffer)
{
  if(attribute == "in_Position")
  {
    buffers.at(0) = buffer;
  }
  else if(attribute == "in_Color")
  {
    buffers.at(1) = buffer;
  }
  else if(attribute == "in_TexCoord")
  {
    buffers.at(2) = buffer;
  }
  else if(attribute == "in_Normal")
  {
    buffers.at(3) = buffer;
  }
  else
  {
    throw std::exception();
  }

  dirty = true;
}

int VertexArray::getVertexCount()
{
  if(!buffers.at(0))
  {
    throw std::exception();
  }

  return buffers.at(0)->getDataSize() / buffers.at(0)->getComponents();
}

GLuint VertexArray::getId()
{
  if(dirty)
  {
    glBindVertexArray(id);

    for(size_t i = 0; i < buffers.size(); i++)
    {
      if(buffers.at(i))
      {
        glBindBuffer(GL_ARRAY_BUFFER, buffers.at(i)->getId());

        glVertexAttribPointer(i, buffers.at(i)->getComponents(), GL_FLOAT, GL_FALSE,
          buffers.at(i)->getComponents() * sizeof(GLfloat), (void *)0);

        glEnableVertexAttribArray(i);
      }
      else
      {
        glDisableVertexAttribArray(i);
      }
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    dirty = false;
  }

  return id;
}
