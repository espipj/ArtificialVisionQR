all: VisionQR.o
	g++  -o "VisionQR"  VisionQR.o -lopencv_core -lopencv_highgui -lopencv_imgproc

VisionQR.o: VisionQR.cpp
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"VisionQR.d" -MT"VisionQR.d" -o "VisionQR.o" "VisionQR.cpp"


clean:
	rm *.o
	rm *.d
	rm VisionQR
