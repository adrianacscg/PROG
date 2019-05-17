#pragma once
#include "dependencies.h"

using namespace std;


class TravelPack {
    private:
        int id;
        string locais;
        Date data_inicio;
        Date data_fim;
        float preco;
        int lugares_max;
        int lugares_vendidos;

    public:
        // @Constructors
        TravelPack();
        TravelPack(int packId, string poi, Date startDate, Date endDate, float price, int maxSpots, int soldSpots);

        // @Get Methods
        int getId() const;
        string getLocais() const;
        Date getDataInicio() const;
        Date getDataFim() const;
        float getPreco() const;
        int getLugaresMax() const;
        int getLugaresVendidos() const;

        // @Set Methods
        void setId(int packId);
        void setLocais(string poi);
        void setDataInicio(Date startDate);
        void setDataFim(Date endDate);
        void setPreco(float price);
        void setLugaresMax(int maxSpots);
        void setLugaresVendidos(int soldSpots);
};
