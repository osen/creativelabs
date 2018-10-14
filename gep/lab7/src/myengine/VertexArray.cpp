#include "VertexArray.h"
#include "VertexBuffer.h"

namespace myengine
{

VertexArray::VertexArray() : dirty(false)
{
  glGenVertexArrays(1, &id);

  if(!id)
  {
    throw std::exception();
  }

  buffers.resize(10);
}

void VertexArray::setBuffer(std::string attribute, std::weak_ptr<VertexBuffer> buffer)
{
  if(attribute == "in_Position")
  {
    buffers.at(0) = buffer.lock();
  }
  else if(attribute == "in_Color")
  {
    buffers.at(1) = buffer.lock();
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

}
