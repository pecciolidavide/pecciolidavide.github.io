
// SOLUZIONI DEGLI ESERCIZI 1 E 2 NEL CODICE

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#include <cctype>

typedef std::pair<std::string, int> WordCount;
typedef std::map<std::string, int>  WordCountMap;
typedef std::vector<WordCount>      WordCountVec;

std::string filter_alpha(const std::string& w) {
  std::string r;
  for (int i = 0; i < w.size(); i++)
    if (std::isalpha(w[i]) || w[i] == '\'')
      r.push_back(w[i]);
  return r;
}

bool valid(const std::string& w) {
  for (int i = 0; i < w.size(); i++)
    if (!std::isalpha(w[i])) return false;
  return true;
}

WordCountMap read_word_map(std::istream& is) {
  WordCountMap m;
  std::string w;
  while (is >> w)
    // SOLUZIONE ESERCIZIO 1
    if (valid(w) && std::isupper(w[0])) m[w]++;
  return m;
}

bool Compare(const WordCount& p, const WordCount& q) {
  return p.second > q.second;
}

WordCountVec sort_word_map(const WordCountMap& m) {
  WordCountVec v = WordCountVec(m.begin(), m.end());
  std::sort(v.begin(), v.end(), Compare);
  return v;
}

// INIZIO SOLUZIONE ESERCIZIO 3

// definisco una funzione di confronto tra coppie tale che (p,c) <
// (q,d) se e solo se la lunghezza di p è maggiore della lunghezza
// di q

bool CompareByLength(const WordCount& p, const WordCount& q) {
  return p.first.size() > q.first.size();
}

void print_longest_word(const WordCountMap& m) {
  WordCountVec v = WordCountVec(m.begin(), m.end());
  // ordino il vettore di coppie usando CompareByLength
  std::sort(v.begin(), v.end(), CompareByLength);
  // la parola più lunga è il primo elemento del vettore
  std::cout << "La parola più lunga è " << v.front().first
	    << " e compare " << v.front().second << " volte"
	    << std::endl;
}

// FINE SOLUZIONE ESERCIZIO 3

int main() {
  std::ifstream f("i_promessi_sposi.txt");
  WordCountMap m = read_word_map(f);
  WordCountVec v = sort_word_map(m);
  for (int i = 0; i < 10 && i < v.size(); i++)
    std::cout << v[i].second << ": " << v[i].first << std::endl;

  // SOLUZIONE ESERCIZIO 2

  // Il numero di parole diverse coincide con il numero di elementi
  // nella mappa (non ci sono mai due elementi con la stessa chiave)
  // e dunque con il numero di elementi del vettore v, per come e`
  // costruito
  std::cout << "Il testo contiene " << m.size() << " parole diverse" << std::endl;
  print_longest_word(m);
}
