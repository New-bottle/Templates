compile_tex:
	@xelatex --shell-escape main.tex
	evince main.pdf
