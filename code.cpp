#pragma once

#include<iostream>
#include<vector>
#include<list>
#include<algorithm>
#include<stack>
using namespace std;



struct Clan {

	int sused;
	int cena = 0;

	//za drugi deo zadatka
	bool postoji = true;

	Clan(int a) { sused = a; };
	Clan(int a, int b) { sused = a, cena = b; };



	// zbog funkcije sort
	friend bool operator<(Clan clan1, Clan clan2) {
		if (clan1.sused < clan2.sused) return true;
		else  return false;
	}


	// potrebno je za funkciju remove 
	friend bool operator==(Clan clan1, Clan clan2) {
		if (clan1.sused == clan2.sused) return true;
		else  return false;
	}
};


struct header {
	int index;
	list<Clan> Elem;

};


vector <header> stvoriGraf(int pocetnicvorovi);

void pisiGraf(vector<header>& graf);

void dodajCvor(vector<header>& graf);

void brisiCvor(vector<header>& graf, int ind);

void dodajGranu(vector<header>& graf, int cvor1, int cvor2, int tezina, bool postoji);

void ukloniGranu(vector<header>& graf, int cvor1, int cvor2);

void brisiGraf(vector<header>& graf);

void PrimovAlgoritam(vector<header>& graf, int tekuci);

void Dikstra(vector<header>& graf, int indV);

int main() {

	vector<header> graf;


	while (1) {

		cout << "Izaberite opciju" << endl;
		cout << "1. Stvori graf" << endl;
		cout << "2. Dodaj cvor" << endl;
		cout << "3. Brisi cvor" << endl;
		cout << "4. Dodaj granu" << endl;
		cout << "5. Brisi granu" << endl;
		cout << "6. Ispis grafa" << endl;
		cout << "7. Izbrisi graf" << endl;
		cout << "8. Nadji min cenu" << endl;
		cout << "9. Vatrogasna kola" << endl;
		cout << "0. Kraj programa" << endl;
		cout << endl;


		cout << "Opcija: ";
		int opcija;
		cin >> opcija;


		switch (opcija) {


		case 0:

			cout << "Program je zavrsen" << endl;
			exit(0);


		case 1:

			int pocetnicvorovi;
			cout << "Unesite broj cvorova: ";

			cin >> pocetnicvorovi;

			graf = stvoriGraf(pocetnicvorovi);
			break;

		case 2:

			if (graf.empty()) {
				cout << "Graf ne postoji" << endl;
				break;
			}


			dodajCvor(graf);
			break;

		case 3:

			int cvor;

			if (graf.empty()) {
				cout << "Graf ne postoji" << endl;
				break;
			}

			cout << "Unesite cvor: ";
			cin >> cvor;




			brisiCvor(graf, cvor);


			break;

		case 4:
			int cvor1, cvor2, tezina;

			if (graf.empty()) {
				cout << "Graf ne postoji" << endl;
				break;
			}

			cout << "Unesite cvorove i tezinu puta: ";
			cin >> cvor1 >> cvor2 >> tezina;



			if (cvor1 < 0 || cvor1 > graf.back().index || cvor2 < 0 || cvor2 > graf.back().index) {
				cout << "Greska" << endl;
				break;
			}

			dodajGranu(graf, cvor1, cvor2, tezina, true);

			break;

		case 5:

			if (graf.empty()) {
				cout << "Graf ne postoji" << endl;
				break;

			}

			cout << "Unesite cvorove: ";
			cin >> cvor1 >> cvor2;



			if (cvor1 < 0 || cvor1 > graf.back().index || cvor2 < 0 || cvor2 > graf.back().index) {
				cout << "Greska" << endl;
			}

			ukloniGranu(graf, cvor1, cvor2);
			break;

		case 6:
			pisiGraf(graf);
			break;

		case 7:

			if (graf.empty()) {
				cout << "Graf ne postoji" << endl;
				break;
			}

			brisiGraf(graf);
			cout << " Graf izbrisan" << endl;
			break;

		case 8:
			int pocetni;

			if (graf.empty()) {
				cout << "Graf ne postoji" << endl;
				break;
			}

			cout << " Unesite pocetni cvor: ";
			cin >> pocetni;


			if (pocetni < 0 || pocetni >= size(graf)) {
				cout << "Taj cvor ne postoji" << endl;
			}
			else {
				PrimovAlgoritam(graf, pocetni);
			}
			break;

		case 9:

			int index;
			if (graf.empty()) {
				cout << "Graf ne postoji" << endl;
				break;
			}
			cout << " Unesite index V: ";
			cin >> index;
			Dikstra(graf, index);
			break;

		default:
			cout << "Opcija ne postoji" << endl;

		}
		cout << endl;

	}

	return 0;
}


vector<header> stvoriGraf(int pocetnicvorovi) {



	vector<header> graf;

	header temp;

	for (int i = 0; i < pocetnicvorovi; i++) {

		temp.index = i;

		graf.push_back(temp);

	}

	return graf;
}


void pisiGraf(vector<header>& graf) {

	if (graf.empty()) {
		cout << "Graf ne postoji" << endl;

	}

	for (int i = 0; i < size(graf); i++) {

		if (graf[i].index == -1) continue;

		cout << graf[i].index << " | ";


		if (graf[i].Elem.empty()) { cout << "Nema suseda"; }

		list<Clan>::iterator pok = graf[i].Elem.begin();

		while (pok != graf[i].Elem.end()) {
			cout << pok->sused << " ";
			pok++;

		}
		cout << endl;

	}
	cout << endl;

}


void dodajCvor(vector<header>& graf) {

	int i = graf.back().index + 1;

	header temp;
	temp.index = i;

	graf.push_back(temp);


}

void brisiCvor(vector<header>& graf, int ind) {

	Clan hit{ ind };

	bool provera = false;

	for (int i = 0; i < size(graf); i++) {
		if (ind == graf[i].index) {
			provera = true;
			break;
		}
	}

	if (provera == false) {
		cout << "Taj cvor ne postoji" << endl;
		return;
	}


	for (int i = 0; i < size(graf); i++) {

		graf[i].Elem.remove(hit);
	}


	for (int i = 0; i < size(graf); i++) {

		if (graf[i].index == ind) {
			graf[i].index = -1;
			graf[i].Elem.clear();

		}
	}
	cout << "Cvor obrisan" << endl;
}


void dodajGranu(vector<header>& graf, int cvor1, int cvor2, int tezina, bool postoji) {

	if (tezina < 0) {
		cout << "Greska" << endl;
		return;
	}

	Clan clan1{ cvor1,tezina };
	Clan clan2{ cvor2,tezina };



	bool provera1 = false;
	bool provera2 = false;


	for (int i = 0; i < size(graf); i++) {

		if (clan1.sused == graf[i].index) provera1 = true;
		if (clan2.sused == graf[i].index) provera2 = true;

	}
	if (provera1 == false || provera2 == false) {
		cout << "Greska" << endl;
		return;
	}


	for (int i = 0; i < size(graf); i++) {

		if (graf[i].index == clan1.sused) {

			bool duplikat = find(graf[i].Elem.begin(), graf[i].Elem.end(), clan2) != graf[i].Elem.end();

			if (duplikat == true) {
				cout << "Grana vec postoji" << endl;
				break;
			}

			else {
				clan2.postoji = postoji;
				graf[i].Elem.push_back(clan2);
				graf[i].Elem.sort();
			}
		}

		if (graf[i].index == clan2.sused) {


			bool duplikat = find(graf[i].Elem.begin(), graf[i].Elem.end(), clan1) != graf[i].Elem.end();

			if (duplikat == true) {
				cout << "Grana vec postoji" << endl;
				break;
			}

			else {
				clan1.postoji = postoji;
				graf[i].Elem.push_back(clan1);
				graf[i].Elem.sort();
			}
		}

	}
}

void ukloniGranu(vector<header>& graf, int cvor1, int cvor2) {

	Clan clan1{ cvor1 };
	Clan clan2{ cvor2 };


	for (int i = 0; i < size(graf); i++) {

		if (graf[i].index == clan1.sused) {

			bool postoji = (find(graf[i].Elem.begin(), graf[i].Elem.end(), clan2) != graf[i].Elem.end());

			if (!postoji) {
				cout << "Grana ne postoji" << endl;
				break;
			}
			else graf[i].Elem.remove(clan2);

		}

		if (graf[i].index == clan2.sused) {


			bool postoji = (find(graf[i].Elem.begin(), graf[i].Elem.end(), clan1) != graf[i].Elem.end());

			if (!postoji) {
				cout << "Grana ne postoji" << endl;
				break;
			}
			else graf[i].Elem.remove(clan1);

		}

	}

}

void brisiGraf(vector<header>& graf) {

	for (int i = 0; i < size(graf); i++) {
		graf[i].Elem.clear();
	}

	graf.clear();

}

void PrimovAlgoritam(vector<header>& graf, int tekuci) {



	bool provera = false;

	for (int i = 0; i < size(graf); i++) {
		if (tekuci == graf[i].index) {
			provera = true;
			break;
		}
	}

	if (provera == false) {
		cout << "Taj cvor ne postoji" << endl;
		return;
	}



	int cena = 0;
	int min = 1000000;
	int novi;

	list<int> stablo;
	list<int> ostali;




	stablo.push_back(tekuci);


	for (int i = 0; i < size(graf); i++) {

		if (graf[i].index == -1) continue;
		ostali.push_back(graf[i].index);
	}

	ostali.remove(tekuci);

	list<int> ::iterator stb;
	list<Clan>::iterator pok;
	bool ustablu = true;

	while (!empty(ostali)) {

		for (stb = begin(stablo); stb != end(stablo); stb++) {




			for (pok = graf[*stb].Elem.begin(); pok != graf[*stb].Elem.end(); pok++) {


				//proveri jel pok sused u ostalima



				ustablu = (find(begin(stablo), end(stablo), pok->sused)) != end(stablo);

				if (ustablu == false) {
					if (min > pok->cena) {
						min = pok->cena;
						novi = pok->sused;
					}
				}



			}


		}

		if (!empty(ostali) && min == 1000000) {
			cout << "Graf nije povezan" << endl;
			return;
		}

		cena += min;
		min = 1000000;
		stablo.push_back(novi);
		ostali.remove(novi);



	}



	cout << "Minimalna cena je " << cena << endl;
};



void Dikstra(vector<header>& graf, int indV) {

	//provera jel postoji index V
	bool uslov = false;

	for (int i = 0; i < size(graf); i++) {
		if (graf[i].index == indV) {
			uslov = true;
		}
	}

	if (uslov == false) {
		cout << "Taj index cvora ne postoji";
		return;
	}



	int cvor1, cvor2, tezina;

	cout << "Unesite puteve koji POSTOJE";
	while (1) {

		cin >> cvor1;
		if (cvor1 < 0) break;

		cin >> cvor2;
		if (cvor2 < 0) break;


		cin >> tezina;
		if (tezina < 0) break;
		dodajGranu(graf, cvor1, cvor2, tezina, true);

	}

	cout << "Unesite puteve koji MOGU DA SE NAPRAVE";

	while (1) {


		cin >> cvor1;
		if (cvor1 < 0) break;

		cin >> cvor2;
		if (cvor2 < 0) break;

		cin >> tezina;
		if (tezina < 0) break;
		dodajGranu(graf, cvor1, cvor2, tezina, false);
	}


	// poseceni

	struct Elem {
		int index = -1;
		int putdosad = 0;
		stack<int> stek;
		Elem() {};

	};

	Elem prvi;
	prvi.index = indV;
	prvi.putdosad = 0;


	list<Elem> poseceni;

	poseceni.push_back(prvi);


	//ostali

	list<int> ostali;

	for (int i = 0; i < size(graf); i++) {
		ostali.push_back(graf[i].index);
	}

	ostali.remove(indV);


	int min = 1000000;
	bool posecen = false;


	list<Elem>::iterator pose;
	list<Clan>::iterator pok;



	while (!ostali.empty()) {
		Elem novi;


		for (pose = poseceni.begin(); pose != poseceni.end(); pose++) {


			for (pok = graf[pose->index].Elem.begin(); pok != graf[pose->index].Elem.end(); pok++) {

				//	posecen = (find(begin(poseceni), end(poseceni), pok->sused) != end(poseceni);  ne moze jer trebe index iz posecenih

				for (list<Elem>::iterator pose1 = poseceni.begin(); pose1 != poseceni.end(); pose1++) {
					if (pose1->index == pok->sused) {
						posecen = true;
						break;
					}
					posecen = false;
				}


				if (posecen == false) {

					if (min > (pok->cena + pose->putdosad)) {
						min = pok->cena + pose->putdosad;
						novi.index = pok->sused;
						novi.putdosad = pok->cena + pose->putdosad;

						if (!novi.stek.empty()) {
							if (novi.stek.top() != pose->index) novi.stek.pop();
						}

						if (novi.stek.empty()) {
							novi.stek.push(pose->index);
						}
						if (novi.stek.top() != pose->index) {

							novi.stek.push(pose->index);
						}
					}

				}


			}
		}


		if (!empty(ostali) && (min == 1000000)) {
			cout << "Graf nije povezan" << endl;
			return;
		}

		min = 1000000;


		poseceni.push_back(novi);
		ostali.remove(novi.index);


	}

	cout << endl;
	cout << "Za cvor " << "V=" << indV << endl;
	for (pose = poseceni.begin(); pose != poseceni.end(); pose++) {

		if (pose->index != indV) {

			cout << "Do cvora " << pose->index << " Najkraci put je:";
			cout << " V - ";

			while (!pose->stek.empty()) {

				if (pose->stek.top() != indV) {
					cout << pose->stek.top() << " - ";
				}
				pose->stek.pop();

			}

			cout << pose->index;
			cout << "  duzine: " << pose->putdosad << endl;
		}
	}

	brisiGraf(graf);
}