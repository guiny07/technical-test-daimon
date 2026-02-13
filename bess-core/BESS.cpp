#include "BESS.h"
#include <stdexcept>
#include <cmath>



/*
    Construtor
*/
BESS::BESS()
    : startHour(0),
      endHour(0),
      dispatchIntervalSet(false),
      dispatchComputed(false) {}

/*
    Set da curva original
*/
void BESS::setOriginalCurve(const std::vector<double>&curve){
    if(curve.size() != 24)
        throw std::invalid_argument("A curva deve conter 24 pontos.");

    originalCurve = curve;
    resultCurve = curve;
    dispatchComputed = false;
}

/*
    Obter energia armazenada.
*/
double BESS::getDailyStoredEnergy() const{
    isCurveSet();

    double energy = 0.0;
    for(double e : originalCurve){
        if(e < 0)
            energy += std::abs(e);
    }

    return energy;
}

double BESS::getMonthlyStoredEnergy() const{
    return getDailyStoredEnergy() * 30.0;
}

/*
    Definir intervalo de despacho da bateria
*/
void BESS::setDispatchInterval(int start, int end){
    isCurveSet();

    if(start < 1 || start > 24 || end < 1 || end > 24)
        throw std::invalid_argument("As horas do intervalo de despacho devem estar entre 1 e 24.");
    
    // Certifica que o intervalo não possui geração de energia. 
    for(int h = 1; h <= 24; h++){
        if(isWithinDispatchInterval(h, start, end)){
            if(originalCurve[h - 1] < 0)
                throw std::invalid_argument("O intervalo de despacho não pode conter instantes de geração de energia.");
        }
    }

    startHour = start;
    endHour = end;
    dispatchIntervalSet = true;
    dispatchComputed = false;
}

/*
    Get da curva resultante para fins de análise e plotagem.
*/
std::vector<double> BESS::getResultCurve() const{
    
    if(!dispatchComputed)
        throw std::logic_error("Impossível obter curva resultante. A descarga ainda não foi computada.");
    
    return resultCurve;
}

/*
    Descarga da bateria.
*/
void BESS::batteryDischarge() {
    isCurveSet();

    if(!dispatchIntervalSet)
        throw std::logic_error("O intervalo de despacho da bateria ainda não foi definido.");
    
    // A quantidade de energia armazenada será utilizada para realizar as descargas.
    double storedEnergy = getDailyStoredEnergy();

    double consumption = 0.0;
    for(int h = 1; h <= 24; h++){
        if(isWithinDispatchInterval(h, startHour, endHour)){
            if(originalCurve[h - 1] > 0)
                consumption += originalCurve[h - 1];
        }
    }

    if(consumption <= 0)
        throw std::logic_error("Não há consumo de energia no intervalo de despacho");

        // Nova curva resultante.
    resultCurve = originalCurve;

    /*
        Distribuição proporcional da energia da bateria:
        A ideia aqui é que instantes com maior consumo recebem mais energia da bateria e vice-versa.
        Será utilizado o cálculo de consumo no instante t / consumo total.
    */
   for(int h = 1; h <= 24; h++){
        if(isWithinDispatchInterval(h, startHour, endHour)){
            if(originalCurve[h - 1] > 0){
                double percentageConsumption = originalCurve[h - 1] / consumption;
                double discharged = percentageConsumption * storedEnergy;
                resultCurve[h - 1] = originalCurve[h - 1] - discharged;
            }
        }
   }

   dispatchComputed = true;
}

/*
    Obter pontos da curva resultante em um instante t. 
*/
double BESS::getResultAt(int t) const{
    if(!dispatchComputed)
        throw std::logic_error("Descarga ainda não computada.");

    if(t < 1 || t > 24)
        throw std::out_of_range("Instante deve estar entre 1 e 24.");

    
        return resultCurve[t - 1];
}



/*
    Métodos auxiliares
*/
void BESS::isCurveSet() const{
    if(originalCurve.empty())
        throw std::logic_error("Curva não definida.");
}

bool BESS::isWithinDispatchInterval(int hour, int start, int end) const{
    if(start <= end){
        return hour >= start && hour <= end;
    }
    else {
        return hour >= start || hour <= end;
    }
}