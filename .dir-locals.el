;; Directory Local Variables -*- no-byte-compile: t -*-
;; C-c c c (compile) lancia `make' nella radice della repo, da qualunque file.
((nil . ((eval . (setq-local compile-command
                             (concat "make -C "
                                     (shell-quote-argument
                                      (expand-file-name
                                       (locate-dominating-file default-directory ".dir-locals.el")))))))))
