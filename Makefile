# Usage:
#   make compile FILE=<filename> OUT=<outputname>
#   make go OUT=<outputname>

CXX = g++
CXXFLAGS = -std=c++11 -Wall

CODE_DIR = code
COMPILE_DIR = compile

compile:
	@if [ -z "$(FILE)" ] || [ -z "$(OUT)" ]; then \
		echo "Usage: make compile FILE=<filename> OUT=<outputname>"; \
		exit 1; \
	fi; \
	src="$(CODE_DIR)/$(FILE)"; \
	outdir="$(COMPILE_DIR)"; \
	outbin="$$outdir/$(OUT)"; \
	mkdir -p "$$outdir"; \
	if [ ! -f "$$src" ]; then \
		echo "Source file not found: $$src"; \
		exit 2; \
	fi; \
	$(CXX) $(CXXFLAGS) -o "$$outbin" "$$src" && echo "Compiled to $$outbin"

go:
	@if [ -z "$(OUT)" ]; then \
		echo "Usage: make go OUT=<outputname>"; \
		exit 1; \
	fi; \
	bin="$(COMPILE_DIR)/$(OUT)"; \
	if [ ! -x "$$bin" ]; then \
		echo "Executable not found: $$bin"; \
		exit 2; \
	fi; \
	"$$bin"

clean:
	rm -rf $(COMPILE_DIR) *.o