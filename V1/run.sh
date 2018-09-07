read -p "Enter Image File_Name: " img

#echo Compiling filter...
#javac filter.java
#echo Running filter...
#java filter $img

#echo Converting Image
#convert $img ip.pgm

echo Compiling core...
gcc pi.c
echo Running core...
./a.out $img
echo Deleting core...
rm a.out
echo Done
