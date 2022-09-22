#include <iostream>
#include "NewBear.h"
using namespace std;

// Bear //
Bear::Bear(){
    weight=0;
}
Bear::Bear(float aWeight){
        weight = aWeight;
}
void Bear::SetWeight (float aWeight){
        weight = aWeight;
}
float Bear::GetWeight(void){
        return(weight);
}
void Bear::PrintSelf(void){
        weight=weight;
}
float Bear::Aggressiveness(void){
        return(weight);
}
Bear::~Bear(){}


// Polar Bear //
Polar::Polar(): Bear(){ }
Polar::Polar(float aWeight): Bear(aWeight)
{weight = aWeight;}

float Polar::Aggressiveness(void){
        return (GetWeight());
}
void Polar::PrintSelf(){
    cout<<"I am Polar bear, Weight="<<weight<<", Aggressive="<<Aggressiveness()<<endl;
}
Polar::~Polar(){}


// Grizzly Bear //
Grizzly::Grizzly():Bear(){ }
Grizzly::Grizzly(float aWeight): Bear(aWeight)
{weight = aWeight;}

float Grizzly::Aggressiveness(void){
        return (GetWeight()*0.9);
}
void Grizzly::PrintSelf(){
        cout<<"I am Grizzly bear, Weight="<< weight<<", Aggressive="<<Aggressiveness()<<endl;
}
Grizzly::~Grizzly(){}


// Black //
Black::Black():Bear(){ }
Black::Black(float aWeight): Bear(aWeight)
{weight = aWeight;}

float Black::Aggressiveness(void){
        return (GetWeight()*0.7);
}
void Black::PrintSelf(){
        cout<<"I am Black bear, Weight="<<weight<<", Aggressive="<<Aggressiveness()<<endl; 
}
Black::~Black(){}


// Black_momma //
Black_Momma::Black_Momma():Black(){ 
    cubaggressiveness=0;
    cub=0;
}
Black_Momma::Black_Momma(float aWeight):Black(aWeight){
    cubaggressiveness=0;
    cub=0;
} 
void Black_Momma::AddCub(Black *aCub) {
	if (cub==2) return;
	else {
		cub+=1;
		cubaggressiveness += aCub->GetWeight()*0.7; }
}
float Black_Momma::Aggressiveness(void){
        float agg = Black::Aggressiveness();
	if (cub==0){return agg;}
	else {return agg*2;}
	}

float Black_Momma::TotalAggressiveness(void){
        float agg = Black::Aggressiveness();
        if (cub==0){return agg;}
        else {return agg*2 + cubaggressiveness;}
}

void Black_Momma::PrintSelf(){
    cout<<"I am Black Mommabear with "<<cub <<" cub(s), Weight="<<GetWeight()<<", Aggressive="<<Aggressiveness()<<", Total Aggressiveness="<<TotalAggressiveness()<<endl;
}
Black_Momma::~Black_Momma(){}


