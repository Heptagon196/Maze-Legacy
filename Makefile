Compile:
	g++ ./Editor.cpp -o Editor -DLINUX
	g++ ./Maze.cpp -o Maze -DLINUX
dev:
	git add --all
	git commit -a -m "Commit"
	git push origin master
