Copyright (C) 2011

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

========================================================================
    APPLICATION : PSS Project Overview
========================================================================

RegulatorManager - nie zdefiniowany regulator i blad
ConfigParser.cpp - uwspolnic configgneratorparameter z regulatorem
backgroundWorker_porcess - zrobic konwersje deque na vector !!
Problemy:
1. Przy czyszczeniu regulatora w trackie symulacji po nacisnieciu stop zostaje poprzednia wartosc wyjscie i sie nie zmienia nic juz na wykresie (chyba powinno siê to ju¿ zerowaæ)
2. Usun wszystkie pointery w Dekstrukorze GUI
3. W wpisywaniu GUI dodaj zeby pobieral parametry i je wpisal do textboxu czy numericow
4. RegulatorGPC jak config nie uwzglednial liczb double to te liczby psuly totalnie symulacje
5. Kombinacja OBIEKT + GENERATOR + START + WYJSCIE Z APLIKACJI BLAD
6. REGULATOR PID - po wyjscia wyjebuje blad

========================================================================
    CONFIGURATION FILES
========================================================================

========================================================================
File: regulator.txt
========================================================================


// KEY&VAL
param=name&1; // GPC
param=H&6;
param=L&3;
param=alpha&0.3;
param=ro&0.3;
param=rankA&1;
param=rankB&0;
param=lambda&0.9;

END-CONFIG;

// ------------------------------------------------------------------//

// KEY&VAL
param=name&2; // PID
param=k&1;
param=Td&1;
param=Tp&1;
param=Ti&1;
param=b&1;
param=N&1;

END-CONFIG;

// ------------------------------------------------------------------//

// KEY&VAL
param=name&3; // P
param=k&1;

END-CONFIG;

========================================================================
File:  plant.txt
========================================================================

// -------------------------------------- A Parameters ----------------------------//
// KEY&VAL

a=0&-0.6;

// -------------------------------------- B Parameters ----------------------------//
// KEY&VAL

b=0&0.4;

// -------------------------------------- Others ----------------------------------//

stationary=1; 
da=1;
db=0;
k=1;

END-CONFIG;

// -------------------------------------- A Parameters ----------------------------//
// KEY&VAL

a=0&0.2;
// -------------------------------------- B Parameters ----------------------------//
// KEY&VAL

b=0&0.2;
b=1&0.3;

// -------------------------------------- Others ----------------------------------//

stationary=1; 
da=1;
db=1;
k=1;
noise=1.5;

END-CONFIG;

========================================================================
File:  generator.txt
========================================================================

// -------------------------------------- A Parameters ----------------------------//
// KEY&VAL
param=name&2;
param=period&40.0;
param=fill&0.4;
param=amplitude&6.0;

END-CONFIG;

// -------------------------------------- A Parameters ----------------------------//
// KEY&VAL

param=name&10;
param=val&3.0;

END-CONFIG;
