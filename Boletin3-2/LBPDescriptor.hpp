#include <iostream>
#include <cstdlib>

#include <cmath> // Esta librería contiene las funciones para realizar operaciones matemáticas (sin, cos, tan, log, exp, etc.)
#include <ctime>
#include <vector>
#include <cstring>
#include <iostream>
#include <cstdlib>
#include <opencv2/core/core.hpp>
#include <cmath>
#include <vector>
#include <fstream>
#include <sstream>
#include <dirent.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/video/video.hpp>
#include <opencv2/videoio/videoio.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <math.h>
#include <cmath>
#include <stdlib.h>
#include <ctime>


// Cuando se carga la cabecer opencv.hpp automáticamente se cargan las demás cabeceras
//#include <opencv2/opencv.hpp>

#include <opencv2/core/core.hpp> // Contiene los elementos básicos como el objeto Mat (matriz que representa la imagen)
#include <opencv2/highgui/highgui.hpp> // Contiene los elementos para crear una interfaz gráfica básica
// OpenCV no está pensado para crear interfaces gráficas potentes. Se centra en la visión artificial y PDI. Si se desea crear una interfaz gráfica completa, se debe usar QT

#include <opencv2/imgcodecs/imgcodecs.hpp> // Contiene las funcionalidad para acceder a los códecs que permiten leer diferentes formatos de imagen (JPEG, JPEG-2000, PNG, TIFF, GIF, etc.)

// Librerías para acceder al video y para poder escribir vídeos en disco
#include <opencv2/video/video.hpp> 
#include <opencv2/videoio/videoio.hpp>

#include <opencv2/imgproc/imgproc.hpp> // Librería para realizar operaciones de PDI 

#include <opencv2/objdetect/objdetect.hpp> // Librería contiene funciones para detección de objetos

#include <opencv2/features2d/features2d.hpp> // Librería que contiene funciones para detección de descriptores como SIFT

#include <opencv2/xfeatures2d/nonfree.hpp> // Librería que contiene funciones para detección de descriptores (que no son libres) como SURF

using namespace std;
using namespace cv;
using namespace cv::xfeatures2d;

#define compab_mask_inc(ptr,shift) \
{ value |= ((unsigned int)(cntr - *ptr) & 0x80000000) \
>> (31-shift); ptr++; }


class LBPDescriptor{
    private:
        int *LBP8(const int*, int, int );
       
    public:
        vector<int> calcularHistogramaLBP(Mat);
        vector<Mat> readImagenes(vector<string>, string);

        //vector<int> clasificarImagenes(vector<Mat>, vector<Mat>, vector<Mat>, vector<Mat>);
        float calcularDistanciaGrises(vector<int>, vector<int>);
        vector<int> clasificarImagenesGrises( vector<int>, vector<int>, vector<int>);
        vector<int> getPrecision(vector<int>, int);
        vector<string> leerDirectorios(string);
            vector<Mat> convertirCielab(vector<Mat>);

        float getPorcentajePrecision(vector<int>);
        LBPDescriptor();

};