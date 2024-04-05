
// https://salsa.debian.org/salve/witalian/-/tree/master

// Copyright (C) 1997-2018 by Davide G. M. Salvetti.

// This is a (short) list of Italian words for use as a /usr/dict dictionary.

// See the file INSTALL for building and installation instructions.

// Please send all bug reports by electronic mail to:
// 	witalian@packages.debian.org

// This dictionary is free software.  See the file COPYING for copying
// conditions.

// A consistent part of the dictionary was put together from the Italian
// dictionary for ispell, by Antonio Palamà, from sources obtained from

// ftp://ftp.pluto.linux.it/pub/pluto/ildp/apps/ispell/italiano-0.03.tgz

// The Italian dictionary for ispell, by Antonio Palamà, is licensed under the
// GNU General Public License: this is a work based on that program.

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

typedef std::vector<std::string> vocabolario;

vocabolario leggi_vocabolario() {
  vocabolario d;
  std::ifstream f("italiano.txt");
  while (f.good()) {
    std::string parola;
    f >> parola;
    if (parola.find('\'') == std::string::npos) d.push_back(parola);
  }
  return d;
}

bool termina_con(const std::string& p, const std::string& s) {
  int k = p.length();
  int l = s.length();
  return k < l ? false : p.substr(k - l) == s;
}

void cerca_rime(const vocabolario& d, const std::string& s) {
  for (int i = 0; i < d.size(); i++)
    if (termina_con(d[i], s))
      std::cout << "  " << d[i] << std::endl;
}

int main() {
  vocabolario d = leggi_vocabolario();
  std::cout << "Ho " << d.size()
	    << " parole nel vocabolario " << std::endl;
  std::string suffisso;
  do {
    std::cout << "\nFa rima con (^C o Q per uscire): ";
    std::cin >> suffisso;
    if (suffisso != "Q") cerca_rime(d, suffisso);
  } while (suffisso != "Q");
}
