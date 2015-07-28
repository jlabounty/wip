echo " "
echo " "
echo " "
echo "**************Beginning Conversion**************"
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

echo "Done! (1/3)"
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

echo "Done! (2/3)"
echo
echo "Converting Comparison Plots..."

convert -density 300 5GeV-Comparison.eps -flatten 5GeV-Comparison.png
	echo "***1/6***"
convert -density 300 10GeV-Comparison.eps -flatten 10GeV-Comparison.png
	echo "***2/6***"
convert -density 300 15GeV-Comparison.eps -flatten 15GeV-Comparison.png
	echo "***3/6***"
convert -density 300 20GeV-Comparison.eps -flatten 20GeV-Comparison.png
	echo "***4/6***"
convert -density 300 25GeV-Comparison.eps -flatten 25GeV-Comparison.png
	echo "***5/6***"
convert -density 300 30GeV-Comparison.eps -flatten 30GeV-Comparison.png
	echo "***6/6***"

echo "Done! (3/3)"
echo "**************All done!**************"
echo " "
echo " "
echo " "
