#include "LBPDescriptor.hpp"
#include <iostream>
LBPDescriptor::LBPDescriptor()
{
}

vector<int> LBPDescriptor::calcularHistogramaLBP(Mat imagen)
{
    vector<int> histograma;

    int *data = (int *)malloc(imagen.rows * imagen.cols * sizeof(int));
    for (int i = 0, k = 0; i < imagen.rows; i++)
    {
        for (int j = 0; j < imagen.cols; j++, k++)
        {
            //data[k] = imagen.at<uchar>(i,j);
            *(data + k) = imagen.at<uchar>(i, j);
        }
    }

    int *histo = this->LBP8(data, imagen.rows, imagen.cols);

    for (int i = 0; i < 256; i++)
        histograma.push_back(histo[i]);

    free(data);

/*


    for (int i = 0; i < vectorImagenes.size(); i++)
    {
        float rango[] = {0, 256};

        const float *rangoHistograma = {rango};

        Mat imagenTemporal;

        imagenTemporal = vectorImagenes[i];

        Mat histoGris;

        int tam = 256;
        calcHist(&imagenTemporal, 1, 0, Mat(), histoGris, 1, &tam, &rangoHistograma, true, false);
        listadoHistogramas.push_back(histoGris);
    }
*/


    return histograma;



}

int *LBPDescriptor::LBP8(const int *data, int rows, int columns)
{
    const int
        *p0 = data,
        *p1 = p0 + 1,
        *p2 = p1 + 1,
        *p3 = p2 + columns,
        *p4 = p3 + columns,
        *p5 = p4 - 1,
        *p6 = p5 - 1,
        *p7 = p6 - columns,
        *center = p7 + 1;

    int r, c, cntr;
    unsigned int value;
    int *result = (int *)malloc(256 * sizeof(int));
    memset(result, 0, 256 * sizeof(int));

    for (r = 0; r < rows - 2; r++)
    {
        for (c = 0; c < columns - 2; c++)
        {
            value = 0;
            cntr = *center - 1;
            compab_mask_inc(p0, 0);
            compab_mask_inc(p1, 1);
            compab_mask_inc(p2, 2);
            compab_mask_inc(p3, 3);
            compab_mask_inc(p4, 4);
            compab_mask_inc(p5, 5);
            compab_mask_inc(p6, 6);
            compab_mask_inc(p7, 7);
            center++;
            result[value]++;
        }
        p0 += 2;
        p1 += 2;
        p2 += 2;
        p3 += 2;
        p4 += 2;
        p5 += 2;
        p6 += 2;
        p7 += 2;
        center += 2;
    }
    return result;
};


vector<string> LBPDescriptor::leerDirectorios(string dir)
{
    vector<string> lista;
    DIR *pDir = opendir(dir.c_str());
    struct dirent *entrada;
    while ((entrada = readdir(pDir)) != NULL)
    {
        //cout << entrada->d_name << endl;
        // entrada->d_type;
        lista.push_back(string(entrada->d_name)); //String a = new String("abc");
        // String a = "abc";
    }
    closedir(pDir);
    return lista;
}

vector<Mat> LBPDescriptor::readImagenes(vector<string> vectorImagenes, string rutaImagenes)
{
    vector<Mat> imagenesLeidas;
    ///home/adrian/Descargas/Dato

    for (int i = 0; i < vectorImagenes.size(); i++)
    {

        Mat imagen = imread(rutaImagenes + "/" + vectorImagenes[i]);

        if (imagen.cols != 0)
        {
            imagenesLeidas.push_back(imagen);
        }
    };

    return imagenesLeidas;
}

float LBPDescriptor::calcularDistanciaGrises(vector<int> histo, vector<int> histogramaTest)
{
    float auxiliarTemporal = 0.0;

    for (int i = 0; i < histo.size(); i++)
    {

        float resultado1;

        resultado1 = 0.0;

        for (int j = 0; j < 10000; j++)
        {
            float var = histo[i] - histogramaTest[i];
            resultado1 = resultado1 + pow(var, 2);
        }

        float raiz = sqrt(resultado1);

        float sumaTotal = 0.0;

        sumaTotal = raiz;

        if (auxiliarTemporal == 0.0)
        {
            auxiliarTemporal = sumaTotal;
        }
        else if (auxiliarTemporal > sumaTotal)
        {
            auxiliarTemporal = sumaTotal;
        }
    }
    return auxiliarTemporal;
};

vector<int> LBPDescriptor::clasificarImagenesGrises(vector<int> histogato, vector<int> histomono, vector<int> entrada)
{
        vector<int> listaResultados;
    for (size_t i = 0; i < entrada.size(); i++)
{
    float resOne = 0.0;
    float resDos = 0.0;
    float resTres = 0.0;

    vector<int> matTemp;
    matTemp.push_back(entrada[i]);
    resOne = calcularDistanciaGrises(histogato, matTemp);
    resDos = calcularDistanciaGrises(histomono, matTemp);

    if ((resOne < resDos))
    {
        listaResultados.push_back(0);
        
    }
    else if ((resDos < resOne))
    {
        listaResultados.push_back(1);
    }  
}
return listaResultados;
};

vector<int> LBPDescriptor::getPrecision(vector<int> resultados, int etiqueta)
{
    vector<int> listaPrecision;

    //Si el resultados es igual a la etiqueta pasada como parametro entonces va a ser 1, caso contrario, 0

    for (size_t i = 0; i < resultados.size(); i++)
    {
        if (resultados[i] == etiqueta)
        {
            listaPrecision.push_back(1);
        }
        else
        {
            listaPrecision.push_back(0);
        }
    }
    return listaPrecision;
};


float LBPDescriptor::getPorcentajePrecision(vector<int> listaAciertos)
{
    float porcentaje;
    int numAciertos;
    numAciertos = 0;
    for (size_t i = 0; i < listaAciertos.size(); i++)
    {
        if (listaAciertos[i] == 1)
        {
            numAciertos += 1;
        }
    }

    cout << numAciertos << endl;
    cout << listaAciertos.size();
    porcentaje = (numAciertos * 100) / listaAciertos.size();
    return porcentaje;
}
vector<Mat> LBPDescriptor::convertirCielab(vector<Mat> listaImagenes)
{
    vector<Mat> lista;
    for (size_t i = 0; i < listaImagenes.size(); i++)
    {
        Mat gris;
        cvtColor(listaImagenes[i], gris, CV_BGR2Lab);
        lista.push_back(gris);
    }
    return lista;
}