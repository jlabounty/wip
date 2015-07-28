echo "Converting New Geometry..."

convert -density 300 5GeV.eps -flatten 5GeV.png
	echo "***1/6***"
convert -density 300 10GeV.eps -flatten 10GeV.png
	echo "***2/6***"
convert -density 300 15GeV.eps -flatten 15GeV.png
	echo "***3/6***"
convert -density 300 20GeV.eps -flatten 20GeV.png
	echo "***4/6***"
convert -density 300 25GeV.eps -flatten 25GeV.png
	echo "***5/6***"
convert -density 300 30GeV.eps -flatten 30GeV.png
	echo "***6/6***"

echo "Done! (1/2)"
echo " "
echo "Converting Solid Cone..."

convert -density 300 5GeV-Solid.eps -flatten 5GeV-Solid.png
	echo "***1/6***"
convert -density 300 10GeV-Solid.eps -flatten 10GeV-Solid.png
	echo "***2/6***"
convert -density 300 15GeV-Solid.eps -flatten 15GeV-Solid.png
	echo "***3/6***"
convert -density 300 20GeV-Solid.eps -flatten 20GeV-Solid.png
	echo "***4/6***"
convert -density 300 25GeV-Solid.eps -flatten 25GeV-Solid.png
	echo "***5/6***"
convert -density 300 30GeV-Solid.eps -flatten 30GeV-Solid.png
	echo "***6/6***"

echo "Done! (2/2)"
