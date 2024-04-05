
#include <iostream>
#include <vector>

const int N = 7;

class Disk {
private:
  int size; // 1 <= size <= N
public:
  Disk(int);
  int get_size() const { return size; }
  std::string to_string() const;
};

Disk::Disk(int s) {
  if (s < 1 || s > N)
    throw std::domain_error("invalid disk size");
  size = s;
}

std::string Disk::to_string() const {
  return std::string(N - size, ' ') +
         std::string(2 * size + 1, '#') +
         std::string(N - size, ' ');
}

class Tower {
private:
  std::vector<Disk> disks;
  // 0 <= i < j < disks.size() => disks[i].get_size() > disks[j].get_size()
  void push(const Disk&);
  Disk pop();
  const Disk& top() const;
public:
  Tower(int = 0);
  void move_to(Tower&);
  std::string to_string(int) const;
};

Tower::Tower(int n) {
  for (int i = n; i > 0; i--)
    push(Disk(i));
}

const Disk& Tower::top() const {
  if (disks.empty())
    throw std::domain_error("empty tower");
  return disks.back();
}

void Tower::push(const Disk& d) {
  if (disks.size() > 0 && top().get_size() <= d.get_size())
    throw std::domain_error("illegal move");
  disks.push_back(d);
}

Disk Tower::pop() {
  Disk d = top();
  disks.pop_back();
  return d;
}

void Tower::move_to(Tower& tower) {
  tower.push(pop());
}

std::string Tower::to_string(int level) const {
  if (level < 0)
    throw std::domain_error("invalid level");
  if (level < disks.size())
    return disks[level].to_string();
  else
    return std::string(N, ' ') + "|" + std::string(N, ' ');
}

class Hanoi {
private:
  int moves;                 // moves >= 0
  std::vector<Tower> towers; // towers.size() == 3
  void play(int, int, int);
  void print() const;
public:
  Hanoi();
  void play();
};

Hanoi::Hanoi() {
  moves = 0;
  towers.push_back(Tower(N));
  towers.push_back(Tower());
  towers.push_back(Tower());
}

void Hanoi::play() {
  play(N, 1, 3);
}

void Hanoi::play(int n, int from, int to) {
  if (from < 1 || from > 3 || to < 1 || to > 3 || from == to)
    throw std::domain_error("invalid towers");
  if (n > 0) {
    int help = 6 - from - to;
    play(n - 1, from, help);
    towers[from - 1].move_to(towers[to - 1]);
    std::cout << "Move " << ++moves << ": " << from << " -> " << to << std::endl;
    play(n - 1, help, to);
  } else print();
}

void Hanoi::print() const {
  std::cout << std::endl;
  for (int level = N - 1; level >= 0; level--) {
    for (int i = 0; i < 3; i++)
      std::cout << towers[i].to_string(level);
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

int main() {
  Hanoi hanoi;
  hanoi.play();
}
