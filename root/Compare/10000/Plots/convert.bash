echo "Converting..."

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

echo "Done!"
