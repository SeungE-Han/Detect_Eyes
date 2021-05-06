#include <opencv2\opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main() {
	Mat img1 = imread("highlight_Sondongwoon.jpg", IMREAD_GRAYSCALE); //���� �о��
	Mat img2 = imread("highlight_Sondongwoon.jpg", IMREAD_COLOR);
	Point pt;
	Point maxpos1(0, 0), p1(0, 0), p2(0, 0), p3(0,0);
	float maxval1 = 0.0;
	float width1 = 0;

	for (int w = 10; w < 15; w++) { //width�� 20���� 29����
		for (pt.y = 0; pt.y < img1.rows - 3*w; pt.y++) {
			for (pt.x = 0; pt.x < img1.cols - 15 * w; pt.x++) {
				Mat_<uchar> m1(2 * w, 5 * w), m2(2 * w, 5 * w), m3(2 * w, 5 * w), m4(w, 15 * w); //��� ����

				Rect roi(pt.x, pt.y, 5 * w, 2 * w); //pt�� ���������� ���� 3*w, ���� 0.5*w �簢�� ����
				m1 = (Mat)img1(roi); //img1�� roi�κ��� ����� m1�� ����

				Rect roi2(pt.x + 5 * w, pt.y, 5 * w, 2 * w); //(pt.x, pt.y+0.5*w)�� ���������� ���� 3*w, ���� 0.5*w �簢�� ����
				m2 = (Mat)img1(roi2); //img1�� roi2�κ��� ����� m2�� ����

				Rect roi3(pt.x + 10 * w, pt.y, 5 * w, 2 * w); //(pt.x+w, pt.y+w)�� ���������� ���� w, ���� 0.5*w �簢�� ����
				m3 = (Mat)img1(roi3);

				Rect roi4(pt.x, pt.y + 2 * w, 15 * w, w); //(pt.x+w, pt.y+w)�� ���������� ���� w, ���� 0.5*w �簢�� ����
				m4 = (Mat)img1(roi4);

				Scalar val = mean(m1); //m1�� ��հ��� val�� ����
				Scalar val2 = mean(m2); //m2�� ��հ��� val2�� ����
				Scalar val3 = mean(m3); //m3�� ��հ��� val3�� ����
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

	p1 = Point(maxpos1.x + width1 * 5, maxpos1.y + width1 * 3); //�簢���� ������ �� ���
	p2 = Point(maxpos1.x + width1 * 15, maxpos1.y + width1 * 3);
	p3 = Point(maxpos1.x + 10 * width1, maxpos1.y); //����� �Բ� â�� �׷����Ƿ� �� �������� ���� ���

	rectangle(img2,maxpos1 , p1, Scalar(0, 0, 255), 2); //�簢�� �׸�
	rectangle(img2, p3, p2, Scalar(0, 0, 255), 2);

	imshow("�Է�", img1);
	imshow("���", img2);

	waitKey(0);
	return 0;
}