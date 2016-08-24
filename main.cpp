#include <iostream>


// Ana Karen Beltrán A01192508
// Andrés Sosa A01176075
// Sergio Diaz A01192313


//Caso de prueba
/**
 
 INPUT: 
 
 4 4
 1 -1 2 -1 -8
 2 -2 3 -3 -20
 1 1 1 0 -2
 1 -1 4 3 4
 
 OUTPUT:
 
 X1 = -7
 X2 = 3
 X3 = 2
 X4 = 2
 
 */



using namespace std;



void swapArray(double iA[500][501],int iCambia1,int iCambia2,int iNumero){
    for(int iC=0; iC<iNumero;iC++){
        swap(iA[iCambia1][iC],iA[iCambia2][iC]);
    }
}

void print(double iMatriz[500][501],int iEcu, int iX){
    
    cout << endl;
    
    for(int iA=0; iA<iEcu ; iA++){
        
        for(int iB=0; iB<iX;iB++){
            
            cout << iMatriz[iA][iB] << " ";
        }
        
        cout << endl;
    }
    cout << endl;
}

void printSolu(double iMatriz[500][501],int iEcu, int iX){
    
    for(int iA=0; iA<iEcu; iA++){
        cout << "X" << iA+1 << " = " << iMatriz[iA][iX-1]/iMatriz[iA][iA]<<endl;
    
    }
}


void PonerInput(int &iEcua, int &iX, double iMatriz[500][501],bool &valido){
    
    double aux;
    
    while(!valido){
        
        /**
         * Pide numero de ecuaciones y de incognitas
         */
       
        cout << "Poner numero de Ecuaciones y numero de Incognitas" << endl;
        cin >> iEcua >> iX;
        if(iEcua == iX){
            valido = true;
        }
        
        /**
         * Valida
         */
        
        else{
            cout << "Datos no validos" << endl<< endl;
        }
    }
    
    
    /**
     * El usuario pone coeficientes para cada ecuacion
     *
     */
   
    iX++;
    cout << "Poner el coficiente de cada ecuacion" << endl;
    for(int iA=0; iA<iEcua ; iA++){
        for(int iB=0; iB<iX;iB++){
            cin >> aux;
            iMatriz[iA][iB] = aux;
        }
    }
}

int EncuentraNumeroNoCero(double iMatriz[500][501],int iMover,int iEcu,bool &valido){
   
    for(int iA=iMover;iA<iEcu;++iA){
    
        if(iMatriz[iA][iMover]!=0){
        
            swapArray(iMatriz,iMover,iA,iEcu+1);
            
            return iA;
        }
    }
    
    valido = false;
    return -1;
}

void CuadCuarto(double iMatriz[500][501],int iPivote,int iEcua, int iX, double iAnt ){
    
    for(int iA=iPivote+1 ; iA<iEcua;iA++){
    
        for(int iB=iPivote+1; iB<iX; iB++){
        
            iMatriz[iA][iB] = (iMatriz[iPivote][iPivote]*iMatriz[iA][iB]-iMatriz[iPivote][iB]*iMatriz[iA][iPivote])/iAnt;
        }
    }
    
}

void CuadUno(double iMatriz[500][501],int iPivote,int iEcua, int iX, double iAnt ){
    
    for(int iA= iPivote-1; iA>=0;iA--){
    
        for(int iB= iPivote+1; iB<iX; iB++){
        
            iMatriz[iA][iB] = ((iMatriz[iPivote][iB]*iMatriz[iA][iPivote]-iMatriz[iPivote][iPivote]*iMatriz[iA][iB])/iAnt)*-1;
        }
    }
    
}

void ModificarMatriz(double iMatriz[500][501],int iPivote,int iEcuaciones,int iX,double &iAnt,double &iAct){
    
    iAct = iMatriz[iPivote][iPivote];
    iAnt = iAct;
    
    for(int iA=iPivote-1; iA>=0; iA--){
        
        iMatriz[iPivote][iA] = 0;
        iMatriz[iA][iPivote] = 0;
        iMatriz[iA][iA] = iAct;
    }
    
    for(int iB=iPivote+1; iB<iEcuaciones;++iB){
    
        iMatriz[iB][iPivote] = 0;
    }
}

void Montante(double iMatriz[500][501],int iEcuaciones, int iX,bool valido){
   
    int iPivote=0,swapWith;
    
    double iAnt=1, iAct;
    
    print(iMatriz,iEcuaciones,iX);
    
    while(iPivote!=iEcuaciones && valido){
    
        if(iMatriz[iPivote][iPivote]==0){
            swapWith = EncuentraNumeroNoCero(iMatriz,iPivote,iEcuaciones,valido);
        
            if(swapWith==-1){
            
                break;
            }
        }
        
        if(iPivote == 0){
            
            CuadCuarto(iMatriz,iPivote,iEcuaciones,iX,iAnt);
        }else{
           
            CuadUno(iMatriz,iPivote,iEcuaciones,iX,iAnt);
            CuadCuarto(iMatriz,iPivote,iEcuaciones,iX,iAnt);
        }
        
        ModificarMatriz(iMatriz,iPivote,iEcuaciones,iX,iAnt,iAct);
        iPivote++;
        print(iMatriz,iEcuaciones,iX);
    }
    
    
    
    if(swapWith == -1){
        
        cout << "La ecuaciones no tiene respuesta o tiene multiple respuesta" << endl;
    }
}



int main()
{
    bool valido = false;
    int iEcuaciones, iX;
    double iMatriz[500][501];
    PonerInput(iEcuaciones,iX,iMatriz,valido);
    Montante(iMatriz,iEcuaciones,iX,valido);
    printSolu(iMatriz,iEcuaciones,iX);
    return 0;
}
