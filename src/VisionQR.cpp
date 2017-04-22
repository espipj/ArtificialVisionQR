/**
 * Simple shape detector program.
 * It loads an image and tries to find simple shapes (rectangle, triangle, circle, etc) in it.
 * This program is a modified version of `squares.cpp` found in the OpenCV sample dir.
 *
 * https://opencv-code.com/tutorials/detecting-simple-shapes-in-an-image/
 */
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <cmath>
#include <iostream>

/**
 * Helper function to find a cosine of angle between vectors
 * from pt0->pt1 and pt0->pt2
 */

void setLabel(cv::Mat& im, const std::string label, std::vector<cv::Point>& contour)
{
	int fontface = cv::FONT_HERSHEY_SIMPLEX;
	double scale = 0.4;
	int thickness = 1;
	int baseline = 0;

	cv::Size text = cv::getTextSize(label, fontface, scale, thickness, &baseline);
	cv::Rect r = cv::boundingRect(contour);
	
	

	cv::Point pt(r.x + ((r.width - text.width) / 2), r.y + ((r.height + text.height) / 2));
	cv::rectangle(im, pt + cv::Point(0, baseline), pt + cv::Point(text.width, -text.height), CV_RGB(255,255,255), CV_FILLED);
	cv::putText(im, label, pt, fontface, scale, CV_RGB(0,0,0), thickness, 8);
}
cv::Point calcularVerticeAbajoIzq(cv::Rect r){

	return cv::Point(r.x+r.width,r.y+r.height);

}
int calcularDesplazamientoHorizontal(cv::Point ai, cv::Point ad,cv::Mat src){
	int distder,distizq;
	distder=src.cols-ad.x;
	distizq=ai.x;
	//Da negativo, el robot deberia girar hacia izquierda
	return distder-distizq;
}

int calcularDesplazamientoVertical(cv::Point ai, cv::Point ad,cv::Mat src){
	int distarriba,distabajo;
	distabajo=src.rows-ad.y;
	distarriba=ai.y;
	//Da negativo, el robot deberia girar/mirar hacia arriba
	return distarriba-distabajo;
}
bool calcularTamano(cv::Rect r, cv::Mat src){
	/* Tam=180 el tamaño que creemos que sería optimo para leer el cuadrado del BIDI
	Rango=+-20 es el rango admisible de diferencia respecto al tamaño que queremos*/ 
	float tam=src.cols/3;
	int rango=20;
	std::cout << "Diferencia:" << tam-r.width;
	if((tam-r.width)<rango && (tam-r.width)>(-rango)){
		return true;
	}else{
		return false;
	}

}
void imprimirResultados(std::vector<cv::Point>& contour, cv::Mat src){
	cv::Rect r = cv::boundingRect(contour);
	
	std::cout << "Ancho: " << r.width << "\n";
	std::cout << "Alto: " << r.height << "\n";
	std::cout << "Largo Imagen: " << src.cols << "\n";
	std::cout << "Ancho Imagen: " << src.rows << "\n";
	std::cout << "Vertice Arriba-Izquierda X: " << r.x << " Vertice Arriba-Izquierda Y: " << r.y << "\n";
	std::cout << "Vertice Abajo-Derecha X: " << calcularVerticeAbajoIzq(r).x << " Vertice Abajo-Derecha Y: " << calcularVerticeAbajoIzq(r).y << "\n";
	
	std::cout << "Desplazamiento vertical: " << calcularDesplazamientoVertical(cv::Point(r.x,r.y),calcularVerticeAbajoIzq(r),src) << "\n";
	std::cout << "Desplazamiento horizontal: " << calcularDesplazamientoHorizontal(cv::Point(r.x,r.y),calcularVerticeAbajoIzq(r),src) << "\n";
	
	std::cout << "Tamaño adecuado: " << std::boolalpha << calcularTamano(r,src) << "\n";
}


int main()
{
	//cv::Mat src = cv::imread("../images/polygon.png");
	//cv::Mat src = cv::imread("../images/img1.png");
	//cv::Mat src = cv::imread("../images/centro.png");
	//cv::Mat src = cv::imread("../images/centro_peque.png");
	cv::Mat src = cv::imread("../images/derecha.png");
	//cv::Mat src = cv::imread("../images/derecha_peque.png");
	//cv::Mat src = cv::imread("../images/izquierda.png");
	//cv::Mat src = cv::imread("../images/izquierda_peque.png");
	
	if (src.empty())
		return -1;

	// Convert to grayscale
	cv::Mat gray;
	cv::cvtColor(src, gray, CV_BGR2GRAY);
	
	// Use Canny instead of threshold to catch squares with gradient shading
	cv::Mat bw;
	cv::Canny(gray, bw, 0, 50, 5);

	imshow("after canny", bw);

	// Find contours
	std::vector<std::vector<cv::Point> > contours;
	cv::findContours(bw.clone(), contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

	std::vector<cv::Point> approx;
	cv::Mat dst = src.clone();


	/*
	cv::Rect r = cv::boundingRect(contours[0]);
	std::cout << r.x << "\n";
	std::cout << r.y << "\n";
	std::cout << r.width << "\n";
	std::cout << r.height << "\n";
	*/
	imprimirResultados(contours[0],src);
	//cv::imshow("src", src);
	//cv::imshow("dst", dst);
	//cv::waitKey(0);
	return 0;
}
