#include <opencv2\opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main() {
	Mat img1 = imread("highlight_Sondongwoon.jpg", IMREAD_GRAYSCALE); //영상 읽어옴
	Mat img2 = imread("highlight_Sondongwoon.jpg", IMREAD_COLOR);
	Point pt;
	Point maxpos1(0, 0), p1(0, 0), p2(0, 0), p3(0,0);
	float maxval1 = 0.0;
	float width1 = 0;

	for (int w = 10; w < 15; w++) { //width는 20부터 29까지
		for (pt.y = 0; pt.y < img1.rows - 3*w; pt.y++) {
			for (pt.x = 0; pt.x < img1.cols - 15 * w; pt.x++) {
				Mat_<uchar> m1(2 * w, 5 * w), m2(2 * w, 5 * w), m3(2 * w, 5 * w), m4(w, 15 * w); //행렬 생성

				Rect roi(pt.x, pt.y, 5 * w, 2 * w); //pt를 시작점으로 가로 3*w, 세로 0.5*w 사각형 생성
				m1 = (Mat)img1(roi); //img1의 roi부분의 행렬을 m1에 저장

				Rect roi2(pt.x + 5 * w, pt.y, 5 * w, 2 * w); //(pt.x, pt.y+0.5*w)를 시작점으로 가로 3*w, 세로 0.5*w 사각형 생성
				m2 = (Mat)img1(roi2); //img1의 roi2부분의 행렬을 m2에 저장

				Rect roi3(pt.x + 10 * w, pt.y, 5 * w, 2 * w); //(pt.x+w, pt.y+w)를 시작점으로 가로 w, 세로 0.5*w 사각형 생성
				m3 = (Mat)img1(roi3);

				Rect roi4(pt.x, pt.y + 2 * w, 15 * w, w); //(pt.x+w, pt.y+w)를 시작점으로 가로 w, 세로 0.5*w 사각형 생성
				m4 = (Mat)img1(roi4);

				Scalar val = mean(m1); //m1의 평균값을 val에 저장
				Scalar val2 = mean(m2); //m2의 평균값을 val2에 저장
				Scalar val3 = mean(m3); //m3의 평균값을 val3에 저장
				Scalar val4 = mean(m4);
				
				float mavg = (10 * ((100 + int(val2[0])) % 256) + 15 * ((100 + (int)val4[0]) % 256) + 
					10 * (255 - val3[0]) + 10 * (255 - val[0])) / (255 * 45);

				if (mavg >= maxval1 && abs(pt.x - maxpos1.x) > 5) {
					maxval1 = mavg;
					width1 = w;
					maxpos1 = pt;
				}
			}
		}
	}

	cout << "maxval1: " << maxval1 << endl;
	cout << "maxpos1: " << maxpos1.x << endl << "maxpos1.y: " << maxpos1.y << endl;
	cout << "width1: " << width1 << endl;

	p1 = Point(maxpos1.x + width1 * 5, maxpos1.y + width1 * 3); //사각형의 마지막 점 계산
	p2 = Point(maxpos1.x + width1 * 15, maxpos1.y + width1 * 3);
	p3 = Point(maxpos1.x + 10 * width1, maxpos1.y); //눈썹과 함께 창을 그렸으므로 눈 시작점을 따로 계산

	rectangle(img2,maxpos1 , p1, Scalar(0, 0, 255), 2); //사각형 그림
	rectangle(img2, p3, p2, Scalar(0, 0, 255), 2);

	imshow("입력", img1);
	imshow("출력", img2);

	waitKey(0);
	return 0;
}