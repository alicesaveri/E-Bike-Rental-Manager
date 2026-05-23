/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm> 
#include <cstdlib>   
#include <ctime>     

using namespace std;

// carratteristiche e-bike
struct EBike {
    int ID;
    double x;
    double y;
    double distanza;    
    double km_residui;   
    bool disponibile;
};

// Funzione distanza tra bici e utente
double calcolaDistanza(EBike bike, double utenteX, double utenteY) {
    return sqrt(pow(bike.x - utenteX, 2) + pow(bike.y - utenteY, 2));
}

// Criterio di ordinamento
bool confrontaDistanza(const EBike &a, const EBike &b) {
    return a.distanza < b.distanza;
}

int main() {
    // numeri causali
    srand(time(0));

    double utenteX;
    double utenteY;

    cout << "Benvenuto su EBike Rental Manager" << endl;
    cout << "Inserisci la tua posizione attuale tramite coordinate X e Y" << endl;
    cout << "Coordinata X: ";
    cin >> utenteX;
    cout << "Coordinata Y: ";
    cin >> utenteY;

    // bici
    const int NUM_BICI = 3;
    EBike numero_bici[NUM_BICI];
    
    numero_bici[0] = {1, 67.89, 54.50, 0.0, 70.0, true};
    numero_bici[1] = {2, 45.65, 33.10, 0.0, 20.0, true};
    numero_bici[2] = {3, 98.00, 24.30, 0.0,  5.0, true};

    // FASE 1
    for (int i = 0; i < NUM_BICI; i++) {
        numero_bici[i].distanza = calcolaDistanza(numero_bici[i], utenteX, utenteY);
    }

    // FASE 2
    sort(numero_bici, numero_bici + NUM_BICI, confrontaDistanza);

    // FASE 3
    cout << "Ecco l' EBike disponibili (ordinate per distanza): " << endl;
    bool ciSonoBiciDisponibili = false;
    for (int i = 0; i < NUM_BICI; i++) {
        if (numero_bici[i].disponibile) {
            cout << "ID Bici: " << numero_bici[i].ID << endl;
            cout << "Coordinate: " << numero_bici[i].x << ", " << numero_bici[i].y << "." << endl;
            cout << "Autonomia residua: " << numero_bici[i].km_residui << " km" << endl;
            cout << "Distanza da te: " << numero_bici[i].distanza << " metri" << endl;
            ciSonoBiciDisponibili = true;
        }
    }

    if (!ciSonoBiciDisponibili) {
        cout << "Non ci sono bici disponibili al momento, riprova pù tardi" << endl;
        return 0; 
    }

    // FASE 4
    cout << endl << "Inserisci l'ID della bici che vorresti sbloccare: ";
    int id_scelto;
    cin >> id_scelto;

    // indice bici dentro array
    int indice_bici = -1;
    for (int i = 0; i < NUM_BICI; i++) {
        if (numero_bici[i].ID == id_scelto && numero_bici[i].disponibile) {
            indice_bici = i;
            break;
        }
    }

    // Controllo validità ID
    if (indice_bici == -1) {
        cout << "Errore: ID non valido o bici non disponibile." << endl;
        return 0;
    }

    // FASE 5
    cout << "Quanti chilometri intendi percorrere? ";
    double km_percorrere;
    cin >> km_percorrere;

    // verifica autonomia
    if (km_percorrere > numero_bici[indice_bici].km_residui) {
        cout << "Noleggio negato: i km che deve percorrere superano l'autonomia residua della bici" << endl;
        return 0;
    }

    // FASE 6
    const double VELOCITA_MEDIA = 20.0; 
    int ritardo_casuale = rand() % 15 + 1; 
    
    double tempo_stimato = ((km_percorrere / VELOCITA_MEDIA) * 60.0) + ritardo_casuale;

    // FASE 7
    // agg autonomia bici
    numero_bici[indice_bici].km_residui -= km_percorrere;

    // importo dovuto (0.20€ al minuto)
    double costo_finale = tempo_stimato * 0.20;

    cout << endl << "RIEPILOGO NOLEGGIO" << endl;
    cout << "Minuti totali stimati (incluso ritardo di " << ritardo_casuale << " min): " << tempo_stimato << " minuti" << endl;
    cout << "Km percorsi: " << km_percorrere << " km" << endl;
    cout << "Costo finale: " << costo_finale << " EUR" << endl;
    cout << "Nuova autonomia residua della bici: " << numero_bici[indice_bici].km_residui << " km" << endl;

    // bici torna disponibile 
    numero_bici[indice_bici].disponibile = true; 
    cout << "La bici ID " << numero_bici[indice_bici].ID << " è tornata disponibile." << endl;

    return 0;
}