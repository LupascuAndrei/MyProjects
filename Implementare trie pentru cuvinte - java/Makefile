build:
	mkdir classes
	javac src/*.java -d classes
	javac -cp classes src/*.java -d classes
clean:
	rm -rf classes
run:
	java -Xmx1024m -cp classes Main
