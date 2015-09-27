import random

myFile = open("inputFile.txt", "w" )

for i in range(50):
	line = str(random.randint(1, 100))
	myFile.write(line + '\n')

myFile.close()
