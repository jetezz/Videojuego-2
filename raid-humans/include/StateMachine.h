#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <iostream>
class StateMachine
{
    public:

        StateMachine();
        virtual ~StateMachine();
        void setEstado(int i);
        int getEstado();
        bool getModo();
        void toggleModo();
        void colocando();
        void comprando();
        int getRonda();

        bool getColocando();

    protected:

    private:
        int estado;
        bool compra = true;
        int ronda = 1;
        bool colocandoTurret = false;
};

#endif // STATEMACHINE_H
