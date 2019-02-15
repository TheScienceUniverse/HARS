read -p "Enter Image File_Name: " img
echo Converting to pgm...
convert $img ip.pgm
echo Compiling...
gcc pi.c
echo Running...
./a.out ip.pgm
echo Converting to png...
convert op.pgm op.png
echo Deleting...
rm a.out ip.pgm op.pgm
echo Openning Output
xdg-open op.png
echo Done
