
// SOLUZIONE DELL'ESERCIZIO 1

#include <iostream>
#include <string>
#include <cctype>

void inserisci_spazi_inefficiente(std::string& s) {
  int i = 0;
  while (i < s.length()) {
    if (s[i] == ',' && (i + 1 == s.length() || !isspace(s[i + 1])))
      s.insert(i + 1, 1, ' ');
    i++;
  }
}

std::string inserisci_spazi(const std::string& s) {
  std::string r;
  for (int i = 0; i < s.length(); i++) {
    r.push_back(s[i]);
    if (s[i] == ',' && (i + 1 == s.length() || !isspace(s[i + 1])))
      r.push_back(' ');
  }
  return r;
}

int main() {
  // La barra verticale | ci permette di capire se lo spazio viene
  // inserito anche dopo l'ultima virgola
  std::string s = "Qui,pochi,spazi,";
  std::cout << "s                               = " << s << "|" << std::endl;
  std::cout << "inserisci_spazi(s)              = " << inserisci_spazi(s) <<  "|" << std::endl;
  std::cout << "s                               = " << s <<  "|" << std::endl;
  std::cout << "inserisci_spazi_inefficiente(s)" << std::endl;
  inserisci_spazi_inefficiente(s);
  std::cout << "s                               = " << s <<  "|" << std::endl;
}
