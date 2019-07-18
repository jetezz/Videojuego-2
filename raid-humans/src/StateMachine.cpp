#include "StateMachine.h"

StateMachine::StateMachine()
{
    estado=1;

}

StateMachine::~StateMachine()
{
    //dtor
}

int StateMachine::getEstado(){

return estado;
}

bool StateMachine::getModo(){


return compra;
}

bool StateMachine::getColocando(){


return colocandoTurret;
}

void StateMachine::toggleModo(){

if(compra) compra = false;
else {compra = true; ronda+=1;}


}

void StateMachine::colocando(){

colocandoTurret =true;
}


void StateMachine::comprando(){
colocandoTurret = false;
}



void StateMachine::setEstado(int i){

    if(i>0&&i<=5)
    estado= i;

}

int StateMachine::getRonda(){
    return ronda;
}



