#include <iostream>
#include <omp.h>
#include <vector>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

vector<int>histograma(256,0);
vector<float>tempPA(256,0);
int linha, coluna, x;
int h = 0;



int main(int, char**) {
    //Mat img = imread("../../../foto.jpg");
    Mat img = imread("../../../bender.png");
    imshow("teste", img);
    //imshow("teste2", img2);

    Mat cinza(img.rows, img.cols, CV_8U);
    int tamImag = (img.rows) * (img.cols);
     
    
#pragma omp parallel for private(linha,coluna)
    for (linha = 0; linha < img.rows; linha++)
    {
        for (coluna = 0; coluna < img.cols; coluna++)
        {   //BGR0
            cinza.at<uchar>(linha, coluna) =
                (img.at<Vec3b>(linha, coluna)[0] +           //AZUL[0] 
                    img.at<Vec3b>(linha, coluna)[1] +           //VERDE[1] 
                    img.at<Vec3b>(linha, coluna)[2]) / 3;       //VERMELHO[2]
        }
    }
    imshow("teste cinza", cinza);
    int linha2, coluna2;

#pragma omp parallel for private(linha2,coluna2)
        for (linha2 = 0; linha2 < img.rows; linha2++)//contagem de valores de pixels(vetor dp histograma)
        {
            for (coluna2 = 0; coluna2 < img.cols; coluna2++)
            {   //BGR0
                histograma[cinza.at<uchar>(linha2, coluna2)] += 1;
            }                           
        }
//#pragma omp parallel for 
        for (int i = 0; i < 256; i++)//probabilidade acumuladas dos valores
        {
            float anterior;
            float temp2 =float(histograma[i]);
            temp2 = temp2 * 256 / float(tamImag);
            if (i > 0)
            {
                anterior = tempPA[i-1];
            }
            if (i == 0)
            {
                if (temp2 > 255)
                {
                    tempPA[i] = 255;
                }
                tempPA[i] = temp2;    
            }
            else
            {
                cout << i<< " " << temp2 << " " << anterior << endl;
                temp2 += anterior;
                if (temp2 > 255)
                {
                    tempPA[i] = 255;
                }
                tempPA[i] = temp2;
            }
        }

    int linha3, coluna3;
#pragma omp parallel for private(linha3,coluna3)
        for (linha3 = 0; linha3 < img.rows; linha3++)//verifica posição no histograma para novo valor da imagem
        {
            for (coluna3 = 0; coluna3 < img.cols; coluna3++)
            {   //BGR0
                int temp = cinza.at<uchar>(linha3, coluna3);
                cinza.at<uchar>(linha3, coluna3) = tempPA[temp];
            }
        }
 
       
    imshow("teste equalizado", cinza);
    
    waitKey(0);
}
