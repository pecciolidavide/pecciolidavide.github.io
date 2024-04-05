// Programma: Labirinto
// Autore:    Luca Padovani, luca.padovani@unito.it

#include <vector>
#include "svg.hh"
#include <ctime>

// Classe per rappresentare labirinto
// width  = larghezza del labirinto
// height = altezza del labirinto
// block  = spessore dei muri
// Row    = una riga della matrice che rappresenta il labirinto
// Data   = la matrice che rappresenta il labirinto
// maze   = il labirinto, ogni elemento è un numero compreso tra
//          0 e 3, con il seguente significato
//          0 = corridoio inesplorato
//          1 = muro
//          3 = percorso di uscita
//          2 = corridoio esplorato
class Labirinto {
private:
  int width;  // width >= 1, deve essere un numero dispari
  int height; // height >= 1, deve essere un numero dispari
  int block;  // block >= 1

  typedef std::vector<char> Row;
  typedef std::vector<Row> Data;
  Data maze;  // ogni elemento nel range [0, 3]

  void crea_stanza(int, int, int, int);
  bool posizione_valida(int, int) const;

public:
  Labirinto(int, int, int);
  bool fuga(int, int, int, int);
  void visualizza() const;
};

// genera un numero intero casuale compreso tra 0 e m - 1
int numero_casuale(int m) {
  return std::rand() % m;
}

// determina se x è pari
bool pari(int x) {
  return x % 2 == 0;
}

// crea una stanza di larghezza width e altezza height nel labirinto
// a partire dalle coordinate (x, y)
void Labirinto::crea_stanza(int x, int y, int width, int height) {
  if (pari(width) || pari(height))
    throw std::domain_error("invalid chamber size");
  if (width == 1 || height == 1) return;
  if (width > height) {
    // divido stanza verticalmente in modo che il muro sia in
    // posizione dispari
    int w = numero_casuale((width - 3) / 2 + 1) * 2 + 1;
     // faccio in modo che la porta sia in posizione pari
    int door = numero_casuale(height / 2 + 1) * 2;
    for (int i = 0; i < height; i++) maze[y + i][x + w] = 1;
    maze[y + door][x + w] = 0;
    crea_stanza(x, y, w, height);
    crea_stanza(x + w + 1, y, width - w - 1, height);
  } else {
    // divido stanza orizzontalmente in modo che il muro sia in
    // posizione dispari
    int h = numero_casuale((height - 3) / 2 + 1) * 2 + 1;
    int door = numero_casuale(width / 2 + 1) * 2;
    for (int j = 0; j < width; j++) maze[y + h][x + j] = 1;
    maze[y + h][x + door] = 0;
    crea_stanza(x, y, width, h);
    crea_stanza(x, y + h + 1, width, height - h - 1);
  }
}

// crea un labirinto di dimensione (width, height) con spessore dei
// muri pari a block e ne calcola il percorso di uscita dall'angolo
// in basso a sinistra (1, 1) all'angolo in alto a destra (width -
// 2, height - 2)
Labirinto::Labirinto(int block, int width, int height) {
  if (block < 1 || width < 0 || height < 0 || pari(width) || pari(height))
    throw std::domain_error("invalid maze");

  std::srand(std::time(nullptr));

  this->block = block;
  this->width = width;
  this->height = height;

  maze.resize(height);
  for (int i = 0; i < height; i++) maze[i].resize(width);

  // creo muri esterni
  for (int i = 0; i < height; i++)
    maze[i][0] = maze[i][width - 1] = 1;
  for (int j = 0; j < width; j++)
    maze[0][j] = maze[height - 1][j] = 1;
  crea_stanza(1, 1, width - 2, height - 2);

  fuga(1, 1, width - 2, height - 2);
}

// crea un disegno SVG che mostri il labirinto ed il percorso di
// uscita
void Labirinto::visualizza() const {
  std::vector<std::string> color;
  color.push_back("white");
  color.push_back("black");
  color.push_back("red");
  color.push_back("orange");
  SVG g(width * block, height * block, 0, 0, std::cout);
  g.set_stroke_width(0);
  for (int i = 0; i < height; i++)
    for (int j = 0; j < width; j++)
      if (maze[i][j] != 0) {
	g.set_stroke(color[maze[i][j]]);
	g.set_fill(color[maze[i][j]]);
	g.rect(j * block, i * block, block, block);
      }
}

// verifica se (x, y) è una posizione valida all'interno del
// labirinto, ovvero se (x, y) si trova in un corridoio all'interno
// del labirinto
bool Labirinto::posizione_valida(int x, int y) const {
  return x >= 0 && x < width && y >= 0 && y < height && maze[y][x] == 0;
}

// cerca un percorso di uscita dalla posizione (x, y) alla posizione
// (xe, ye), restituisce true se lo trova e false altrimenti
bool Labirinto::fuga(int x, int y, int xe, int ye) {
  maze[y][x] = 2; // mark as path
  if (x == xe && y == ye) return true;
  for (int i = 1; i >= -1; i--)
    for (int j = 1; j >= -1; j--)
      if (i * j == 0) {
	int nx = x + j;
	int ny = y + i;
	if (posizione_valida(nx, ny) && fuga(nx, ny, xe, ye))
	  return true;
      }
  maze[y][x] = 3; // mark as visited
  return false;
}

int main(int argc, char* argv[]) {
  if (argc != 4)
    std::cerr << "Usage: labirinto <wall> <width> <height>" << std::endl;
  else {
    Labirinto maze(std::stoi(argv[1]), std::stoi(argv[2]), std::stoi(argv[3]));
    maze.visualizza();
  }
}
