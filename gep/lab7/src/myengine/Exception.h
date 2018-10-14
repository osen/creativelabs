#include <exception>
#include <string>

namespace myengine
{

class Exception : public std::exception
{
public:
  Exception(std::string message);
  ~Exception() throw();

  const char *what();

private:
  std::string message;
};

}
