#include "dependencies.h"

using namespace std;

/*
 * @Constructor
 */
    TravelPack::TravelPack(){

    }

    TravelPack::TravelPack(int packId, string poi, Date startDate, Date endDate, float price, int maxSpots, int soldSpots){
        id = packId;
        locais = poi;
        data_inicio = startDate;
        data_fim = endDate;
        preco = price;
        lugares_max = maxSpots;
        lugares_vendidos = soldSpots;
    }

/*
 * @Get Methods
 */
    int TravelPack::getId() const{
        return id;
    }

    string TravelPack::getLocais() const{
        return locais;
    }

    Date TravelPack::getDataInicio() const{
        return data_inicio;
    }

    Date TravelPack::getDataFim() const{
        return data_fim;
    }

    float TravelPack::getPreco() const{
        return preco;
    }

    int TravelPack::getLugaresMax() const{
        return lugares_max;
    }

    int TravelPack::getLugaresVendidos() const{
        return lugares_vendidos;
    }

/*
 * @Set Methods
 */
    void TravelPack::setId(int packId){
        id = packId;
    }

    void TravelPack::setLocais(string poi){
        locais = poi;
    }

    void TravelPack::setDataInicio(Date startDate){
        data_inicio = startDate;
    }

    void TravelPack::setDataFim(Date endDate){
        data_fim = endDate;
    }

    void TravelPack::setPreco(float price){
        preco = price;
    }

    void TravelPack::setLugaresMax(int maxSpots){
        lugares_max = maxSpots;
    }

    void TravelPack::setLugaresVendidos(int soldSpots){
        lugares_vendidos = soldSpots;
    }