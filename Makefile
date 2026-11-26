EMACS ?= emacs

.PHONY: build clean serve

build:
	$(EMACS) --batch -Q -l publish.el -f site-build

clean:
	find _build -mindepth 1 -not -name '.gitkeep' -delete

serve: build
	python3 -m http.server 8000 -d _build
