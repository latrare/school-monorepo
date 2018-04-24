(TeX-add-style-hook
 "paper"
 (lambda ()
   (TeX-add-to-alist 'LaTeX-provided-class-options
                     '(("IEEEtran" "10pt" "journal" "compsoc")))
   (TeX-add-to-alist 'LaTeX-provided-package-options
                     '(("cite" "nocompress") ("subfig" "caption=false" "font=footnotesize" "labelfont=sf" "textfont=sf")))
   (TeX-run-style-hooks
    "latex2e"
    "abstract"
    "keywords"
    "introduction"
    "IEEEtran"
    "IEEEtran10"
    "array"
    "cite"
    "subfig"
    "hyperref")
   (LaTeX-add-bibliographies
    "IEEEabrv"
    "references"))
 :latex)

