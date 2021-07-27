#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <random>
#include <time.h>

using namespace std;

enum {
	emp = 0,
	sfu = 1,
	sgi = 2,
	ski = 3,
	ska = 4,
	shi = 5,
	sto = 6,
	sng = 7,
	sum = 8,
	sry = 9,
	sgy = 10,
	efu = -1,
	egi = -2,
	eki = -3,
	eka = -4,
	ehi = -5,
	eto = -6,
	eng = -7,
	eum = -8,
	ery = -9,
	egy = -10,
};

string FU = "FU";
string GI = "GI";
string KI = "KI";
string KA = "KA";
string HI = "HI";
string TO = "TO";
string NG = "NG";
string UM = "UM";
string RY = "RY";
string GY = "GY";

int board[5][5] = {
	{ehi, eka, egi, eki, egy},
	{emp, emp, emp, emp, efu},
	{emp, emp, emp, emp, emp},
	{sfu, emp, emp, emp, emp},
	{sgy, ski, sgi, ska, shi}
};

string te[100];

int a;
int b;
int c;
int d;
int e;
int f;
int flag;
int x;
int r;
int nx;
string sKoma[10];

string eKoma[10];
string koma;
string tt;
string buffer;
string buff;

int fusion();

void draw() {
	cout<<endl<<" 5  4  3  2  1 "<<endl;

	for(int i = 0; i < 5; i++) {
		for(int j = 0; j < 5; j++) {
			switch(board[i][j]) {
				case emp: cout<<" * "; break;
				case sfu: cout<<"+歩"; break;
				case sgi: cout<<"+銀"; break;
				case ski: cout<<"+金"; break;
				case ska: cout<<"+角"; break;
				case shi: cout<<"+飛"; break;
				case sto: cout<<"+と"; break;
				case sng: cout<<"+全"; break;
				case sum: cout<<"+馬"; break;
				case sry: cout<<"+竜"; break;
				case sgy: cout<<"+玉"; break;
				case efu: cout<<"-歩"; break;
				case egi: cout<<"-銀"; break;
				case eki: cout<<"-金"; break;
				case eka: cout<<"-角"; break;
				case ehi: cout<<"-飛"; break;
				case eto: cout<<"-と"; break;
				case eng: cout<<"-全"; break;
				case eum: cout<<"-馬"; break;
				case ery: cout<<"-竜"; break;
				case egy: cout<<"-玉"; break;
				default: break;
			}
		}
		cout<<" "<<i+1<<endl<<endl;
	}
}

int komaBoard(string koma) {
	if(koma == "FU") {
		//cout<<"eureka"<<endl;
		return sfu;
	}else if(koma == "GI") {
		return sgi;
	}else if(koma == "KI") {
		return ski;
	}else if(koma == "KA") {
		return ska;
	}else if(koma == "HI") {
		return shi;
	}else if(koma == "TO") {
		return sfu;
	}else if(koma == "NG") {
		return sgi;
	}else if(koma == "UM") {
		return ska;
	}else if(koma == "RY") {
		return shi;
	}else if(koma == "GY") {
		return sgy;
	}
}

int komaOp(string koma) {
	if(koma == "FU") {
		//cout<<"eureka"<<endl;
		return efu;
	}else if(koma == "GI") {
		return egi;
	}else if(koma == "KI") {
		return eki;
	}else if(koma == "KA") {
		return eka;
	}else if(koma == "HI") {
		return ehi;
	}else if(koma == "TO") {
		return eto;
	}else if(koma == "NG") {
		return eng;
	}else if(koma == "UM") {
		return eum;
	}else if(koma == "RY") {
		return ery;
	}else if(koma == "GY") {
		return egy;
	}
}

string komaKind(int i, int j) {
	switch(board[i][j]) {
		case sfu:
		case efu:
			return FU; break;
		case sgi:
		case egi:
			return GI; break;
		case ski:
		case eki:
			return KI; break;
		case ska:
		case eka:
			return KA; break;
		case shi:
		case ehi:
			return HI; break;
		case sto:
		case eto:
			return TO; break;
		case sng:
		case eng:
			return NG; break;
		case sum:
		case eum:
			return UM; break;
		case sry:
		case ery:
			return RY; break;
		case sgy:
		case egy:
			return GY; break;
		default: break;
	}
}

void above(int i, int j, int s) {
	if(board[i][j] > 0) {
		if(i-s >= 0) {
			if(board[i-s][j] != 0) {
						flag++;
			}
			if(board[i-s][j] > 0) {
						flag++;
			}
			if(board[i-s][j] <= 0) {
				for(int n = 0; n < sizeof(te[100]); n++) {
					if(te[n].empty() != 0 && flag < 2) {
						te[n] = to_string(1000 * j + 100 * i + 10 * (j) + i-s) + komaKind(i, j);
						break;
					}
				}
			}
		}
	}

	if(board[i][j] < 0) {
		if(i+s < 5) {
			if(board[i+s][j] >= 0) {
				if(board[i+s][j] != 0) {
						flag++;
				}
				for(int n = 0; n < sizeof(te[100]); n++) {
					if(te[n].empty() != 0 && flag < 2) {
						te[n] = to_string(1000 * j + 100 * i + 10 * (j) + i+s) + komaKind(i, j);
						break;
					}
				}
			}
		}
	}
}

void below(int i, int j, int s) {
	if(board[i][j] > 0) {
		if(i+s < 5) {
			if(board[i+s][j] != 0) {
						flag++;
			}
			if(board[i+s][j] > 0) {
						flag++;
			}
			if(board[i+s][j] <= 0) {
				for(int n = 0; n < sizeof(te[100]); n++) {
					if(te[n].empty() != 0 && flag < 2) {
						te[n] = to_string(1000 * j + 100 * i + 10 * (j) + i+s) + komaKind(i, j);
						break;
					}
				}
			}
		}
	}

	if(board[i][j] < 0) {
		if(i-s >= 0) {
			if(board[i-s][j] >= 0) {
				if(board[i-s][j] != 0) {
						flag++;
				}
				for(int n = 0; n < sizeof(te[100]); n++) {
					if(te[n].empty() != 0 && flag < 2) {
						te[n] = to_string(1000 * j + 100 * i + 10 * (j) + i-s) + komaKind(i, j);
						break;
					}
				}
			}
		}
	}
}

void right(int i, int j, int s) {
	if(board[i][j] > 0) {
		if(j+s < 5) {
			if(board[i][j+s] != 0) {
						flag++;
			}
			if(board[i][j+s] > 0) {
						flag++;
			}
			if(board[i][j+s] <= 0) {
				for(int n = 0; n < sizeof(te[100]); n++) {
					if(te[n].empty() != 0 && flag < 2) {
						te[n] = to_string(1000 * j + 100 * i + 10 * (j+s) + i) + komaKind(i, j);
						break;
					}
				}
			}
		}
	}

	if(board[i][j] < 0) {
		if(j+s < 5) {
			if(board[i][j+s] != 0) {
						flag++;
			}
			if(board[i][j+s] >= 0) {
				for(int n = 0; n < sizeof(te[100]); n++) {
					if(te[n].empty() != 0 && flag < 2) {
						te[n] = to_string(1000 * j + 100 * i + 10 * (j+s) + i) + komaKind(i, j);
						break;
					}
				}
			}
		}
	}
}

void left(int i, int j, int s) {
	if(board[i][j] > 0) {
		if(j-s >= 0) {
			if(board[i][j-s] != 0) {
		    	flag++;
			}
			if(board[i][j-s] > 0) {
		    	flag++;
			}
			if(board[i][j-s] <= 0) {
				for(int n = 0; n < sizeof(te[100]); n++) {
					if(te[n].empty() != 0 && flag < 2) {
						te[n] = to_string(1000 * j + 100 * i + 10 * (j-s) + i) + komaKind(i, j);
						break;
					}
				}
			}
		}
	}

	if(board[i][j] < 0) {
		if(j-s >= 0) {
			if(board[i][j-s] >= 0) {
				if(board[i][j-s] != 0) {
						flag++;
				}
				for(int n = 0; n < sizeof(te[100]); n++) {
					if(te[n].empty() != 0 && flag < 2) {
						te[n] = to_string(1000 * j + 100 * i + 10 * (j-s) + i) + komaKind(i, j);
						break;
					}
				}
			}
		}
	}
}

void UeNaMi(int i, int j, int s) {
	if(board[i][j] > 0) {
		if(i-s >= 0 && j+s < 5) {
			if(board[i-s][j+s] != 0) {
						flag++;
			}
			if(board[i-s][j+s] > 0) {
						flag++;
			}
			if(board[i-s][j+s] <= 0) {
				for(int n = 0; n < sizeof(te[100]); n++) {
					if(te[n].empty() != 0 && flag < 2) {
						te[n] = to_string(1000 * j + 100 * i + 10 * (j+s) + i-s) + komaKind(i, j);
						break;
					}
				}
			}
		}
	}

	if(board[i][j] < 0) {
		if(i+s < 5 && j+s < 5) {
			if(board[i+s][j+s] != 0) {
						flag++;
			}
			if(board[i+s][j+s] >= 0) {
				for(int n = 0; n < sizeof(te[100]); n++) {
					if(te[n].empty() != 0 && flag < 2) {
						te[n] = to_string(1000 * j + 100 * i + 10 * (j+s) + i+s) + komaKind(i, j);
						break;
					}
				}
			}
		}
	}
}

void SiNaMi(int i, int j, int s) {
	if(board[i][j] > 0) {
		if(i+s < 5 && j+s < 5) {
			if(board[i+s][j+s] != 0) {
						flag++;
			}
			if(board[i+s][j+s] > 0) {
						flag++;
			}
			if(board[i+s][j+s] <= 0) {
				for(int n = 0; n < sizeof(te[100]); n++) {
					if(te[n].empty() != 0 && flag < 2) {
						te[n] = to_string(1000 * j + 100 * i + 10 * (j+s) + i+s) + komaKind(i, j);
						break;
					}
				}
			}
		}
	}

	if(board[i][j] < 0) {
		if(i-s >= 0 && j+s < 5) {
			if(board[i-s][j+s] >= 0) {
				if(board[i-s][j+s] != 0) {
						flag++;
				}
				for(int n = 0; n < sizeof(te[100]); n++) {
					if(te[n].empty() != 0 && flag < 2) {
						te[n] = to_string(1000 * j + 100 * i + 10 * (j+s) + i-s) + komaKind(i, j);
						break;
					}
				}
			}
		}
	}
}

void UeNaHi(int i, int j, int s) {
	if(board[i][j] > 0) {
		if(i-s >= 0 && j-s >=  0) {
			if(board[i-s][j-s] != 0) {
						flag++;
			}
			if(board[i-s][j-s] > 0) {
						flag++;
			}
			if(board[i-s][j-s] <= 0) {
				for(int n = 0; n < sizeof(te[100]); n++) {
					if(te[n].empty() != 0 && flag < 2) {
						te[n] = to_string(1000 * j + 100 * i + 10 * (j-s) + i-s) + komaKind(i, j);
						break;
					}
				}
			}
		}
	}

	if(board[i][j] < 0) {
		if(i+s < 5 && j-s >=  0) {
			if(board[i+s][j-s] >= 0) {
				if(board[i+s][j-s] != 0) {
						flag++;
				}
				for(int n = 0; n < sizeof(te[100]); n++) {
					if(te[n].empty() != 0 && flag < 2) {
						te[n] = to_string(1000 * j + 100 * i + 10 * (j-s) + i+s) + komaKind(i, j);
						break;
					}
				}
			}
		}
	}
}

void SiNaHi(int i, int j, int s) {
	if(board[i][j] > 0) {
		if(i+s < 5 && j-s >= 0) {
			if(board[i+s][j-s] != 0) {
						flag++;
			}
			if(board[i+s][j-s] > 0) {
						flag++;
			}
			if(board[i+s][j-s] <= 0) {
				for(int n = 0; n < sizeof(te[100]); n++) {
					if(te[n].empty() != 0 && flag < 2) {
						te[n] = to_string(1000 * j + 100 * i + 10 * (j-s) + i+s) + komaKind(i, j);
						break;
					}
				}
			}
		}
	}

	if(board[i][j] < 0) {
		if(i-s >= 0 && j-s >= 0) {
			if(board[i-s][j-s] >= 0) {
				if(board[i-s][j-s] != 0) {
						flag++;
				}//atodeyaru
				for(int n = 0; n < sizeof(te[100]); n++) {
					if(te[n].empty() != 0 && flag < 2) {
						te[n] = to_string(1000 * j + 100 * i + 10 * (j-s) + i-s) + komaKind(i, j);
						break;
					}
				}
			}
		}
	}
}

//!
void seiri() {
	for(int i = 0; i < sizeof(te[100]); i++) {
		if(te[i].empty() == 0) {
			while(te[i].size() != 6) {
				te[i] = "0" + te[i];
			}
		}
	}
}

void ekoma(int i, int j) {
	int kf = 0;
	int ki = 0;

	if(board[i][j] != 0) {
		while(kf == 0) {
			if(eKoma[ki].empty() != 0) {
				eKoma[ki] = komaKind(i, j);
				kf++;
			}
			ki++;
			if(ki > 10) {
				kf++;
			}
		}
	}else {
		return;
	}
}

void op() {
	int kf = 0;
	int ki = 0;
	int i = 0;
	int j = 0;
	cout<<"Black >";
	cin>>tt;

	x = stoi(tt.substr(0, 4));
	koma = tt.substr(4, 5);

	a = x / 1000;
	b = (x % 1000) /100;
	c = (x % 100) / 10;
	d = x % 10;

	e = 0;
	f = 0;
	b -= 1;
	d -= 1;

	if(a != 9 && c != 9) {
		while(f == 0) {
			if((a + e) == 5) {
				a = e;
				f++;
			}
			e++;
		}
		e = 0;
		f = 0;
		while(f == 0) {
			if((c + e) == 5) {
				c = e;
				f++;
			}
			e++;
		}
	}

	i = d;
	j = c;

	ekoma(i, j);

	if(a == 9 && c == 9) {
		board[d][c] = komaOp(koma);
	}else {

		board[d][c] = komaOp(koma);
		board[b][a] = 0;
	}
}

void eval() {

}

void skoma(int i, int j) {
	int kf = 0;
	int ki = 0;

	if(board[i][j] != 0) {
		while(kf == 0) {
			if(sKoma[ki].empty() != 0) {
				sKoma[ki] = komaKind(i, j);
				kf++;
			}
			ki++;
			if(ki > 10) {
				kf++;
			}
		}
	}else {
		return;
	}
}

void sop() {
	int fl = 0;
	int kf = 0;
	int ki = 0;
	int i = 0;
	int j = 0;
	int kff = 0;

	eval();

	srand(time(NULL));
	//int ir = rand() % 100 + 0;
	while(fl == 0) {

		r = rand() % 100 + 0;

		//cout<<r<<endl;

		if(te[r].empty() == 0) {
			x = stoi(te[r].substr(0, 4));
			koma = te[r].substr(4, 5);

			a = x / 1000;
			b = (x % 1000) /100;
			c = (x % 100) / 10;
			d = x % 10;

			i = d;
			j = c;

			skoma(i, j);

			if(a == 9 && b == 9) {
				for(int u = 0; u < 5; u++) {
					if(board[u][j] == sfu) {
						kff++;
					}
				}
				if(j == 0) {
					kff++;
				}
				if(kff == 0) {
					board[i][j] = komaBoard(koma);
					cout<<endl<<"White >"<<te[r]<<endl;
				}
				break;
			}

			cout<<endl<<"White >"<<te[r]<<endl;
			board[d][c] = board[b][a];
			board[b][a] = 0;

			//wc++;
			fl++;
		}

	}

}

void gameRule() {
	int i = 0;
	int j = 0;
	int s = 0;
	int c = 0;

	for(i = 0; i < 5; i++) {
		for(j = 0; j < 5; j++) {
			s = 0;
			flag = 0;
			c = 0;
			switch(board[i][j]) {
				// i+s < 5; i-s >= 0;
				case sfu:
				//case efu:
					s = 1;
					flag = 0;
					above(i, j, s); break;
				case sgi:
				//case egi:
					s = 1;
					flag = 0;
					above(i, j, s);
					UeNaMi(i, j, s);
					UeNaHi(i, j, s);
					SiNaMi(i, j, s);
					SiNaHi(i, j, s); break;
				case sto:
				case sng:
				case ski:
				//case eto:
				//case eng:
				//case eki:
					s = 1;
					flag = 0;
					above(i, j, s);
					below(i, j, s);
					UeNaMi(i, j, s);
					UeNaHi(i, j, s);
					right(i, j, s);
					left(i, j, s); break;
				case ska:
				//case eka:
					flag = 0;
					s = 1;
					do {
						UeNaMi(i, j, s);
						UeNaHi(i, j, s);
						SiNaMi(i, j, s);
						SiNaHi(i, j, s);
						++s;
					}while(s <= 4);
					break;
				case shi:
				//case ehi:
					flag = 0;
					s = 1;
					do {
						above(i, j, s);
						below(i, j, s);
						right(i, j, s);
						left(i, j, s);
						++s;
					}while(s <= 4);
					break;
				case sum:
				//case eum:
					flag = 0;
					s = 1;
					above(i, j, s);
					below(i, j, s);
					right(i, j, s);
					left(i, j, s);
					s = 1;
					do {
						UeNaMi(i, j, s);
						UeNaHi(i, j, s);
						SiNaMi(i, j, s);
						SiNaHi(i, j, s);
						++s;
					}while(s <= 4);
					break;
				case sry:
				//case ery:
					flag = 0;
					s = 1;
					UeNaMi(i, j, s);
					UeNaHi(i, j, s);
					SiNaMi(i, j, s);
					SiNaHi(i, j, s);
					s = 1;
					do {
						above(i, j, s);
						below(i, j, s);
						right(i, j, s);
						left(i, j, s);
						++s;
					}while(s <= 4);
					break;
				case sgy:
				//case egy:
					flag = 0;
					s = 1;
					above(i, j, s);
					below(i, j, s);
					right(i, j, s);
					left(i, j, s);
					UeNaMi(i, j, s);
					UeNaHi(i, j, s);
					SiNaMi(i, j, s);
					SiNaHi(i, j, s); break;
				default: break;
			}
			/*
			for(int n = 0; i < 10; n++) {
				if(eKoma[n].empty() == 0) {
					if(board[i][j] == 0) {
						for(int p = 0; n < 100; p++) {
							if(te[p].empty() != 0) {
								te[p] = to_string(9000 + 900 + 10 * j + i) + eKoma[n];

							}
						}
					}
				}
			}*/

		}
	}

	seiri();
}

void Koma() {
	int kc = 0;
	for(int n = 0; n < 10; n++) {
		if(sKoma[n].empty() == 0) {
			flag = 0;
			kc = 0;
			for(int i = 0; i < 5; i++) {
				for(int j = 0; j < 5; j++) {
					if(board[i][j] == 0) {
						flag = 0;
						while(flag == 0) {
							if(te[kc].empty() != 0) {
								te[kc] = to_string(9900 + 10 * j + i) + sKoma[n];
								flag++;
							}
							if(kc > 100) {
								flag++;
							}
							kc++;
						}
					}
				}
			}
		}
	}
}

int fusion() {
	x = (1000 * a) + (100 * b) + (10 * c) + d;

	return x;
}

/*string getHCR() {
	f = 0;
	x = stoi(te[r].substr(0, 4));
	koma = te[r].substr(4, 5);

	a = x / 1000;
	b = (x % 1000) /100;
	c = (x % 100) / 10;
	d = x % 10;

	e = 0;
	f = 0;
	b -= 1;
	d -= 1;
	while(f == 0) {
		if((a + e) == 5) {
			a = e;
			f++;
		}
		e++;
	}
	e = 0;
	f = 0;
	while(f == 0) {
		if((c + e) == 5) {
			c = e;
			f++;
		}
		e++;
	}

	x = (1000 * a) + (100 * b) + (10 * c) + d;

	te[r] = to_string(x) + koma;

	if(te[r].empty() == 0) {
		while(te[r].size() != 6) {
			te[r] = "0" + te[r];
		}
	}

	buff = te[r];
	return buff;
}*/

int main() {
	cout<<"\x1b[H\x1b[2J";
	int count = 1;
	cout<<"<POSITION "<<count<<">";
	while(1) {
		draw();
		op();//junban
		//cout<<"0"<<eKoma[0]<<endl<<"1"<<eKoma[1]<<endl<<"2"<<eKoma[2]<<endl<<"3"<<eKoma[3]<<endl;
		count++;
		cout<<"<POSITION "<<count<<">";
		draw();

		gameRule();
		Koma();

		cout<<"<LEGAL MOVE>"<<endl;
		for(int nr = 1; nr < 100; nr++) {
			if(te[nr-1].empty() == 0) {
				//r = nr-1;
				cout<<setw(2)<<nr<<"."<<te[nr-1]<<" ";
				if(nr % 9 == 0) {
					cout<<endl;
				}
			}
		}
		cout<<endl;

		//cout<<"0"<<eKoma[0]<<endl<<"11"<<eKoma[11]<<endl<<"12"<<eKoma[12]<<endl;//<<"3"<<eKoma[3]<<endl;
		cout<<"<ENEMYS PIECE>"<<endl;
		for(int i = 0; i < 10; i++) {
			if(eKoma[i].empty() == 0) {
				cout<<i+1<<"."<<eKoma[i]<<" ";
			}
		}
		cout<<endl;

		//while(f)

		sop();

		count++;
		cout<<"<POSITION "<<count<<">";

		draw();

		cout<<"<SELFS PIECE>"<<endl;
		for(int i = 0; i < 10; i++) {
			if(sKoma[i].empty() == 0) {
				cout<<i+1<<"."<<sKoma[i]<<" ";
			}
		}

		for(int i = 0; i < 100; i++) {
			te[i] = "";
		}

	}

	cout<<endl;

	return 0;
}
