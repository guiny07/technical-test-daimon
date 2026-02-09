import java.util.Math

public class BESS {

    private double[] originalCurve; // Curva original
    private double[] resultCurve; // Curva após uso do BESS

    private int startHour; // Início do intervalo.
    private int endHour; // Fim do intervalo.

    private boolean dispatchInterval; // Flag para verificar se o intervalo foi definido.
    private boolean dispatchComputed; // Flag para verificar se a descarga da bateria foi computada.

    //=====================
    // Construtor
    //=====================

    public BESS{
        this.originalCurve = null;
        this.resultCurve = null;
        this.dispatchIntervalSet = false;
        this.dispatchComputed = false;
    }

    //=======================
    // Obter energia armazenada.
    //=======================

    public double getDailyStoredEnergy() {
        isCurveSet();

        double energy = 0.0;
        for(double e : originalCurve){
            if(e < 0)
                energy += Math.abs(e); // Deve ser a soma das cargas negativas, em módulo.
        }

        return energy;
    }

    public double getMonthlyStoredEnergy(){
        isCurveSet();

        return getDailyStoredEnergy() * 30.0;
    }


    //==========================================
    // Definir intervalo de despacho da bateria
    //==========================================

    public void setDispatchInterval(int startHour, int endHour){
        isCurveSet();

        if(startHour < 1 || startHour > 24 || endHour < 1 || endHour > 24)
            throw new IllegalArgumentException("As horas do intervalo de despacho devem estar entre 1 e 24");

        // Certifica que o intervalo não possui geração de energia.
        for(int h = 1; h <= 24; h++){
            if(isWithinDispatchInterval(h, startHour, endHour)){
                if(originalCurve[h - 1] < 0){
                    throw new IllegalArgumentException("O intervalo de despacho não pode conter instantes de geração de energia.");
                }
            }
        }

        this.startHour = startHour;
        this.endHour = endHour;
        this.dispatchInterval = true;
        this.dispatchComputed = false;
    }


    //================================================
    // Get da curva resultante para fins de análise e plotagem.
    //================================================
    public double[] getResultCurve(){
        if(!dispatchComputed){
            throw new IllegalStateException("Impossível obter curva resultante, a descarga ainda não foi computada.");
        }

        return resultCurve.clone();
    }

    //====================================
    // Descarga da bateria
    //====================================
    public void batteryDischarge(){
        isCurveSet();

        if(!dispatchInterval)
            throw new IllegalStateException("O intervalo de despacho da bateria ainda não foi definido.");

        // A quantidade de energia armazenada será utilizada para realizar a descarga da bateria.
        double storedEnergy = getDailyStoredEnergy();

        double consumption = 0.0;
        for(int i = 0; i < 24; i++){
            if(isWithinDispatchInterval(i, startHour, endHour)){
                if(originalCurve[i] > 0)
                    consumption += originalCurve[i];
            }
        }

        if(consumption <= 0)
            throw new IllegalStateException("Não há consumo de energia no intervalo de despacho.");

        // Nova curva  resultante.
        resultCurve = originalCurve.clone();

        /* Distribuição proporcional da energia da bateria:
        *  A ideia aqui é que instantes com maior consumo recebem mais energia da bateria e vice-versa.
        *  Será utilizado o cálculo de consumo no instante t / consumo total.
         */
        for(int i = 0; i < 24; i++){
            if(isWithinDispatchInterval(i, startHour, endHour)){
                if(originalCurve[i] > 0){
                    double percentageConsumption = originalCurve[i] * consumption;
                    double discharged = percentageConsumption * storedEnergy;
                    resultCurve[i] = originalCurve[i] - discharged; // Subtrai do consumo. Essa abordagem permite zerar ou ainda manter um consumo residual.
                }
            }
        }

        this.dispatchComputed = true;
    }

    //======================================================
    // Obter pontos da curva resultante em um instante t.
    //======================================================
    public double getResultAt(int t){
        if(!dispatchComputed){
            throw new IllegalStateException("Descarga ainda não computada.")
        }

        return resultCurve[t - 1];
    }

    //===================================
    // Métodos auxiliares
    //===================================
    private void isCurveSet(){
        if(originalCurve == null)
            throw new IllegalStateException("Curva não foi definida.");
    }

    private boolean isWithinDispatchInterval(int hour, int start, int end){
        if(start >= end){
            return hour >= start && hour <= end;
        }
        else {
            return hour >= start || hour <= end;
        }
    }
}