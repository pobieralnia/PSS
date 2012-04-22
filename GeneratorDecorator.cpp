#include "StdAfx.h"
#include "GeneratorDecorator.h"


DekoratorPure::DekoratorPure (Signal * s) : GeneratorDecorator(s)
{
}
 
double DekoratorPure::simulate (int t) {
    return s_dekorowany->simulate(t);
}

DekoratorStartu::DekoratorStartu (Signal * s, int start) 
    : GeneratorDecorator(s), s_start(start)
{

}
 
double DekoratorStartu::simulate (int t) {
    return (t >= s_start) ? s_dekorowany->simulate(t) : 0;
}
 
DekoratorKonca::DekoratorKonca (Signal * s, int koniec)
    : GeneratorDecorator(s), s_koniec(koniec)
{
}
 
double DekoratorKonca::simulate (int t) {
    return (t <= s_koniec) ? s_dekorowany->simulate(t) : 0;
}