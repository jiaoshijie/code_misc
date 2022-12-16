all: tree

resources = BBT_tree.h main.cpp

tree: $(resources)
	g++ -W -Wall -IBBT_tree.h main.cpp -o tree

debug: $(resources)
	g++ -W -Wall -IBBT_tree.h main.cpp -o tree -g

clean: 
	rm tree
