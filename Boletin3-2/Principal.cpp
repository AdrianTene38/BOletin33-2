#include "LBPDescriptor.hpp"
int main(int argc, char *argv[])
{
    Mat textura = imread("../plantilla.jpeg");
    Mat gato = imread("../gatito.jpg");
    Mat monito = imread("../monito.png");
    int dividir = (textura.cols / 2) - 285;
    int dividir2 = (textura.rows / 2) - 40;
    String ruta ="/home/adrian/Descargas/Dato/monkey";
    String ruta2 ="/home/adrian/Descargas/Dato/feline";

    //textura.size();
    int dividir1 = (textura.cols / 2) - 89;
    int dividir21 = (textura.rows / 50);
    Mat roi = textura(Rect(dividir, dividir2, 200, 150));
    Mat gatito = textura(Rect(dividir1, 435, 200, 150));


    cvtColor(roi, roi, CV_BGR2Lab);       //Conversion automatica RGB to lab cv::resize(IMAGEN,IMG1,Size(400,394));.
    cvtColor(gatito, gatito, CV_BGR2Lab); //Conversion automatica RGB to lab cv::resize(IMAGEN,IMG1,Size(400,394));.
    cvtColor(monito, monito, CV_BGR2Lab);
    //Mat textura1 = textura.resize(200,150);
    cvtColor(gato, gato, CV_BGR2Lab); //Conversion automatica RGB to lab cv::resize(IMAGEN,IMG1,Size(400,394));.
    cv::resize(textura, textura, Size(200, 150));
    cv::resize(gato, gato, Size(200, 150));
    cv::resize(monito, monito, Size(200, 150));

    LBPDescriptor *lbp = new LBPDescriptor();
    LBPDescriptor *lbp2 = new LBPDescriptor();
    vector<string> listadoMono = lbp2->leerDirectorios(ruta);
    vector<string> listadoGato = lbp2->leerDirectorios(ruta2);

    vector<Mat> imagenesgato,imagenesmonos;
        imagenesgato= lbp2->readImagenes(listadoGato,ruta2);
                imagenesgato= lbp2->readImagenes(listadoGato,ruta2);

    Mat B = gatito.clone();
    Mat C = roi.clone();

    namedWindow("Textura", WINDOW_AUTOSIZE);
    namedWindow("mono", WINDOW_AUTOSIZE);
    namedWindow("gato", WINDOW_AUTOSIZE);

    imshow("Textura", textura);
    imshow("mono", roi);
    imshow("gato", gatito);

    vector<int> histo = lbp->calcularHistogramaLBP(gatito);
    vector<int> mono = lbp2->calcularHistogramaLBP(roi);
    vector<int> miau = lbp2->calcularHistogramaLBP(B);
    vector<int> pruebaMono = lbp2->calcularHistogramaLBP(monito);


        
vector<int> listaResultadosGato,listaResultadosMono;
float porcentajeGato,porcentajeMono;
LBPDescriptor lbpd;
//listaResultadosGato=lbpd.clasificarImagenesGrises(histo,mono,miau);
listaResultadosMono=lbpd.clasificarImagenesGrises(histo,mono,pruebaMono);
//lbpd.getPrecision(listaResultadosGato,1);
lbpd.getPrecision(listaResultadosMono,1);
//porcentajeGato=lbpd.getPorcentajePrecision(listaResultadosGato);
porcentajeMono=lbpd.getPorcentajePrecision(listaResultadosMono);
//cout << "Porcentaje de etiqueta Gato: " << porcentajeGato << "%" << endl;
cout << "Porcentaje de etiqueta Mono: " << porcentajeMono << "%" << endl;
    waitKey(0);
    destroyAllWindows();

    delete lbp;
    delete lbp2;
    //delete lbpd;

    return 0;
}
