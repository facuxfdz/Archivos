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


int main(){
    ifstream forigenPrueba;
    ofstream fprueba;
    reg registro[71004];

    Abrir(forigenPrueba,fprueba);
    procOrigPr(forigenPrueba,registro);
    Escribir(fprueba,registro);
    
    return 0;
}

void Abrir(ifstream &forigenPrueba, ofstream &fprueba){
    forigenPrueba.open("PartesDiarios.txt", ios::in);
    fprueba.open("PartesDiariosV2.txt", ios::out);
}


bool Leer(ifstream &forigenPrueba, linea &line){
    getline(forigenPrueba,line.pais,',');
    forigenPrueba >> line.mes;
    forigenPrueba.ignore();
    forigenPrueba >> line.dia;
    forigenPrueba.ignore();
    forigenPrueba >> line.cant[HISOPADOS];
    forigenPrueba.ignore();
    forigenPrueba >> line.cant[INFECTADOS];
    forigenPrueba.ignore();
    forigenPrueba >> line.cant[RECUPERADOS];
    forigenPrueba.ignore();
    forigenPrueba >> line.cant[FALLECIDOS];
    forigenPrueba.ignore();

    return forigenPrueba.good();
}

void procOrigPr(ifstream &forigenPrueba, reg registro[]){
    linea renglon;
    int i=0;

    while(Leer(forigenPrueba,renglon)&&i<71004){
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

void Escribir(ofstream &fprueba, reg registro[]){
    for(int i=0;i<71004;i++){
        if(registro[i].nombrePais.length() >= 20 ){
            continue;
        }
        else{
            fprueba << left << setw(21) <<registro[i].nombrePais
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