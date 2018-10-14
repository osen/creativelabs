#include <iostream>
#include <string>
#include <vector>

class Bomb;

std::vector<Bomb> bombs;

class Bomb
{
  std::string name;

public:
  Bomb(std::string name)
  {
    this->name = name;
  }

  void touch()
  {
    if(rand() % 100 > 30)
    {
      /* Simulate everything being exploded! */
      bombs.clear();

      /* An error: "this" is no longer valid */
      std::cout << "Crickey! The bomb was set off by " << name << std::endl;
    }
  }
};

int main()
{
  bombs.push_back(Bomb("Freddy"));
  bombs.push_back(Bomb("Charlie"));
  bombs.push_back(Bomb("Teddy"));
  bombs.push_back(Bomb("Trudy"));

  for(size_t i = 0; i < bombs.size(); i++)
  {
    bombs.at(i).touch();
  }

  return 0;
}
