#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

enum{
    HISOPADOS = 0,
    INFECTADOS,
    RECUPERADOS,
    FALLECIDOS
};

struct
{
    string nombrePais;
    int mes;
    int dia;
    int cantidades[4];
}typedef reg;

struct
{
    string pais;
    int mes;
    int dia;
    int cant[4];
}typedef linea;

void Abrir(ifstream&, ofstream&);
bool Leer(ifstream&, linea&);
void procOrigPr(ifstream&,reg[]);
void Escribir(ofstream&,reg[]);
void Cerrar(ifstream&, ofstream&);


int main(){
    ifstream arPartesDiarios;
    ofstream arPartesDiariosV2;
    reg registro[71004];

    Abrir(arPartesDiarios,arPartesDiariosV2);
    procOrigPr(arPartesDiarios,registro);
    Escribir(arPartesDiariosV2,registro);
    Cerrar(arPartesDiarios,arPartesDiariosV2);
    
    return 0;
}

void Abrir(ifstream &fpartesDiarios, ofstream &fpartesDiariosOut){
    fpartesDiarios.open("PartesDiarios.txt", ios::in);
    fpartesDiariosOut.open("PartesDiariosV2.txt", ios::out);
}


bool Leer(ifstream &fpartesDiarios, linea &line){
    getline(fpartesDiarios,line.pais,',');
    fpartesDiarios >> line.mes;
    fpartesDiarios.ignore();
    fpartesDiarios >> line.dia;
    fpartesDiarios.ignore();
    fpartesDiarios >> line.cant[HISOPADOS];
    fpartesDiarios.ignore();
    fpartesDiarios >> line.cant[INFECTADOS];
    fpartesDiarios.ignore();
    fpartesDiarios >> line.cant[RECUPERADOS];
    fpartesDiarios.ignore();
    fpartesDiarios >> line.cant[FALLECIDOS];
    fpartesDiarios.ignore();

    return fpartesDiarios.good();
}

void procOrigPr(ifstream &fpartesDiarios, reg registro[]){
    linea renglon;
    int i=0;

    while(Leer(fpartesDiarios,renglon)&&i<71004){
        registro[i].nombrePais = renglon.pais;
        registro[i].mes = renglon.mes;
        registro[i].dia = renglon.dia;
        registro[i].cantidades[HISOPADOS] = renglon.cant[HISOPADOS];
        registro[i].cantidades[INFECTADOS] = renglon.cant[INFECTADOS];
        registro[i].cantidades[RECUPERADOS] = renglon.cant[RECUPERADOS];
        registro[i].cantidades[FALLECIDOS] = renglon.cant[FALLECIDOS];
        i++;
    }
}

void Escribir(ofstream &fpartesDiariosOut, reg registro[]){
    for(int i=0;i<71004;i++){
        if(registro[i].nombrePais.length() >= 20 ){
            continue;
        }
        else{
            fpartesDiariosOut << left << setw(21) <<registro[i].nombrePais
                << right << setw(21) <<registro[i].mes
                << right << setw(21) <<registro[i].dia
                << right << setw(21) <<registro[i].cantidades[HISOPADOS]
                << right << setw(21) << registro[i].cantidades[INFECTADOS]
                << right << setw(21) <<registro[i].cantidades[RECUPERADOS]
                << right << setw(21) <<registro[i].cantidades[FALLECIDOS]
                ;
        }
    }
    cout<<"Todo leido y escrito correctamente"<<endl;
}

void Cerrar(ifstream &fpartesDiarios, ofstream &fpartesDiariosOut){
    fpartesDiarios.close();
    fpartesDiariosOut.close();
}