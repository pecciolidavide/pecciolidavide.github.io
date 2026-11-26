;;; publish.el --- Build del sito pecciolidavide -*- lexical-binding: t; -*-

;; Uso: `make' (oppure C-c c c da Emacs).
;; Gira in `emacs --batch -Q': non dipende dalla config di Doom.
;; Sorgenti:  content/*.org  -> _build/*.html
;; Statici:   static/**      -> _build/**

(require 'ox-publish)

(defvar site-root
  (file-name-directory (or load-file-name buffer-file-name)))

(defun site-path (rel) (expand-file-name rel site-root))

(defvar site-nav
  "<nav class=\"site-nav\">
  <a class=\"site-name\" href=\"/\">Davide Peccioli's webpage</a>
  <span class=\"links\">
    <a href=\"/portfolio.html\">Portfolio</a>
    <a href=\"https://cv.pecciolidavide.it\">CV</a>
  </span>
</nav>")

(defvar site-footer
  "<footer>
  <p>Last updated %C &middot; Written in <a href=\"https://orgmode.org\">Org mode</a></p>
</footer>")

(setq org-html-doctype "html5"
      org-html-html5-fancy t
      org-html-validation-link nil
      org-html-head-include-default-style nil
      org-html-head-include-scripts nil
      org-html-htmlize-output-type nil
      org-export-with-toc nil
      org-export-with-section-numbers nil
      org-export-with-author nil
      org-export-with-date nil
      org-export-with-sub-superscripts '{}
      org-html-metadata-timestamp-format "%Y-%m-%d"
      org-publish-use-timestamps-flag nil   ; sito piccolo: ricostruisci sempre tutto
      org-publish-timestamp-directory (site-path ".org-timestamps/")
      make-backup-files nil)

(setq org-publish-project-alist
      `(("site-pages"
         :base-directory ,(site-path "content")
         :base-extension "org"
         :publishing-directory ,(site-path "_build")
         :recursive t
         :exclude "^_"                      ; content/_*.org = include/bozze, non pubblicati
         :publishing-function org-html-publish-to-html
         :html-head "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">
<link rel=\"stylesheet\" href=\"/css/style.css\">"
         :html-preamble ,site-nav
         :html-postamble ,site-footer)
        ("site-static"
         :base-directory ,(site-path "static")
         :base-extension any
         :publishing-directory ,(site-path "_build")
         :recursive t
         :publishing-function org-publish-attachment)
        ("site" :components ("site-pages" "site-static"))))

(defun site-build ()
  "Pubblica tutto il sito in _build/."
  (org-publish "site" t)
  (message "Sito pubblicato in %s" (site-path "_build")))

;;; publish.el ends here
