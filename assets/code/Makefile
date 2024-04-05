
CC = clang++ -Wc++11-extensions
# CC = g++-9

NULL =
EXAMPLES = \
  funzioni/tartaglia \
  funzioni/frac \
  classi_oggetti/frac \
  classi_oggetti/complex \
  classi_oggetti/time \
  oggetti_mutabili/die_hard \
  oggetti_mutabili/word_counter \
  oggetti_mutabili/word_counter_full \
  oggetti_mutabili/conto_corrente \
  contenitori/elimina_spazi \
  contenitori/inserisci_spazi \
  contenitori/rimario \
  contenitori/vector \
  contenitori/matrix \
  liste/test_pair \
  liste/sparse_vector \
  liste/cf \
  mappe/wf \
  mappe/sparse_vector_map \
  mappe/sparse_matrix \
  template/test_template \
  template/vector_template \
  template/pair \
  template/matrix_template \
  input/somma_terminale \
  input/somma_file \
  input/somma_linea_comando \
  input/somma_file_linea_comando \
  $(NULL)

SOURCES = $(EXAMPLES:%=%.cc)
TARGETS = $(EXAMPLES:%=%.exe)

all: $(TARGETS)

%.exe: %.cc
	$(CC) -o $@ $<

clean:
	rm -f $(TARGETS)
