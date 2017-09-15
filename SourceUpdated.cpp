#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>


using namespace std;

//http://www.wykop.pl/ramka/3840275/czym-jest-sztuczna-siec-neuronowa-wprowadzenie-dla-kazdego/
//the source
//connecting neurons in brain
/*

layer 1               | layer 2     |       layer 3     | out

in1 to all 4 neurons    neuron2in x4     neuron4in x1   output


in2 to all 4 neurons


*/

//2 input neuron
class Neuron2in{
public:
	int in[2];  //mine, opponent

	float val[2]; //mine, coefficient //opponent, coefficient, values for learning

	float values[2];   //checked values

	float out;

	float calculation(int input[], float value[]){ //m,o,val[0],val[1]
		float res=0;
		res = (input[0] * value[0]) + (input[1] * value[1]); //addition
		return (1 / (1 + pow(M_E,(-res)))); //normalizacja, sigmoida
	}

};

//4 input neuron
class Neuron4in{
public:
	float in[4];

	float val[4]; //values for learning

	float values[4];  //checked values

	float out;

	float calculation(float input[], float value[]){ //m,o,val[0],val[1]
		float res=0; //result
		for (int i = 0; i < 4; i++){
			res +=(input[i]*value[i]); //addition
		}
		return (1 / (1 + pow(M_E, (-res)))); //normalizacja, sigmoida
	}

};

class Brain{

public:

	Neuron2in N2[4];
	Neuron4in N4;

	float simplyThink(int mine, int opp){ //the data just go through the neural network with fixed values for each neuron
		int result;
		//loading data from 1st layer to 2nd one
		for (int i = 0; i < 4; i++){
			N2[i].in[0] = mine; //loading data, mine
			N2[i].in[1] = mine; //loading data, opponent
			N2[i].out = N2[i].calculation(N2[i].in, N2[i].val); //loading to output the result of calculation, for each of 4 neurons
		}
		//loading results from 2nd layer to 3rd layer
		for (int i = 0; i < 4; i++){
			N4.in[i] = N2[i].out;//loading data
		}
		N4.out=N4.calculation(N4.in, N4.val); //loading to output the result of calculation for neuron in 3rd layer
		result = N4.out;
		return result;
	}

	//function that returns values that must be acquired by neural network
	bool result(int mine, int opp){
		try
		{
			if (mine == 1 && opp == 1) return 0;
			if (mine == 1 && opp == 2) return 1;
			if (mine == 1 && opp == 3) return 0;
			if (mine == 2 && opp == 1) return 0;
			if (mine == 2 && opp == 2) return 0;
			if (mine == 2 && opp == 3) return 1;
			if (mine == 3 && opp == 1) return 1;
			if (mine == 3 && opp == 2) return 0;
			if (mine == 3 && opp == 3) return 0;
			throw 1; //if there was no return, then there must have been wrong input data
		}
		catch (int a)
		{
			cout << "Bad input data!!!" << endl;
		}
		//returning: 1-I won,0-opponent won
	}

	void showValues(){
		for (int i = 0; i < 4; i++){
			for (int j = 0; j < 2; j++){
				cout << "Neuron nr: " << i+1 << " wejscie " << j+1 << "ma wartosc " << N2[i].values[j] << endl;
			}
		}
		for (int i = 0; i < 4; i++){
			cout << "Neuron nr: " << 5 << " wejscie " << i+1 << "ma wartosc " << N4.values[i] << endl;
		}
	}

	//trying out all possibilities of input entries and values for neural networks
	void learn(){
		int mine=1; //val 1-3
		int opp =1;  //val 1-3
		int min=-2;
		int max =3;//for max value of being checked for coefficients
		unsigned long long counter =0;
		for (int i = 1; i < 4; i++){ //all possibilities for mine
			for (int j = 1; j < 4; j++){//all possibilities for opponent
				for (int a = min; a < max; a++){			//1
					for (int b = min; b < max; b++){			//2
						for (int c = min; c < max; c++){			//3
							for (int d = min; d < max; d++){			//4
								for (int e = min; e < max; e++){			//5
									for (int f = min; f < max; f++){			//6
										for (int g = min; g < max; g++){			//7
											for (int h = min; h < max; h++){			//8
												for (int k = min; k < max; k++){			//9
													for (int l = min; l < max; l++){			//10
														for (int m = min; m < max; m++){			//11
															for (int n = min; n < max; n++){			//12
																//setting values to test network
																//counter++;
																N2[0].val[0] = a;
																N2[0].val[1] = b;
																N2[1].val[0] = c;
																N2[1].val[1] = d;
																N2[2].val[0] = e;
																N2[2].val[1] = f;
																N2[3].val[0] = g;
																N2[3].val[1] = h;
																N4.val[0] = k;
																N4.val[1] = l;
																N4.val[2] = m;
																N4.val[3] = n;
																//checking whether a neural network was right
																float difference;
																difference = fabs(simplyThink(i, j) - (float)result(i, j)); //difference between calculated result and expected one
																if (difference < 0.2) {
																	//saving the correct coefficients
																	N2[0].values[0] = a;
																	N2[0].values[1] = b;
																	N2[1].values[0] = c;
																	N2[1].values[1] = d;
																	N2[2].values[0] = e;
																	N2[2].values[1] = f;
																	N2[3].values[0] = g;
																	N2[3].values[1] = h;
																	N4.values[0] = k;
																	N4.values[1] = l;
																	N4.values[2] = m;
																	N4.values[3] = n;

																}
															}
														}
													}
												}
											}
										}
									}
								}counter++;cout << "progress: "<< counter <<"/"<<9*pow((max+abs(min)),4)<< endl;
							}//9*max^3
						}//9*max^2
					}//9*maxcout<<"Z"<< endl;
				}//9cout<<"Y"<< endl;
			}//3cout<<"X"<< endl;
		}//1cout << "progress: "<< pow((double)(counter/9),(1/12))<< endl;
	}

	void play(){
		//setting checked values
		N2[0].val[0] = 5;
		N2[0].val[1] = 5;
		N2[1].val[0] = 5;
		N2[1].val[1] = 5;
		N2[2].val[0] = 5;
		N2[2].val[1] = 5;
		N2[3].val[0] = 5;
		N2[3].val[1] = 5;
		N4.val[0] = 5;
		N4.val[1] = 5;
		N4.val[2] = 5;
		N4.val[3] = 2;
		int a, b,result;
		cout << "1 dla kamienia 2 dla nozyczek 3 dla papieru - ty" << endl;
		cin >> a;
		cout << "1 dla kamienia 2 dla nozyczek 3 dla papieru - przeciwnik" << endl;
		cin >> b;
		result=simplyThink(a, b); //calculating results
		switch (result){
			case 0:{
				cout << "przegrales"<< endl;
				break;
			}
			case 1:{
				cout << "wygrales" << endl;
				break;
			}
			default:{
				cout << "BLAD!!!"<<endl;
			}
		}




	}






};


int main()
{
	cout << "START" << endl;
	Brain brain;
	brain.learn();  //for learing
	brain.showValues(); //coefficients that were set by learning
	for (;;){
		brain.play();  //testing whether network was taught properly
	}

	cout << "END"  << endl;
	//system("pause");
	return 0;
}
