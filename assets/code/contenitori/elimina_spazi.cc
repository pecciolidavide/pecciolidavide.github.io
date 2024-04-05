
#include <iostream>
#include <string>
#include <cctype>

void elimina_spazi_inefficiente(std::string& s) {
  int i = 0;
  while (i < s.length())
    if (isspace(s[i])) s.erase(i, 1);
    else i++;
}

std::string elimina_spazi(const std::string& s) {
  std::string r;
  for (int i = 0; i < s.length(); i++)
    if (!isspace(s[i])) r.push_back(s[i]);
  return r;
}

int main() {
  std::string s = "Qui troppi spazi";
  std::cout << "s                             = " << s << std::endl;
  std::cout << "elimina_spazi(s)              = " << elimina_spazi(s) << std::endl;
  std::cout << "s                             = " << s << std::endl;
  std::cout << "elimina_spazi_inefficiente(s)" << std::endl;
  elimina_spazi_inefficiente(s);
  std::cout << "s                             = " << s << std::endl;
}
