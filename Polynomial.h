//Sinem Elif Haseki
//150160026
#include <iostream>

class Polynomial {
	int degree;
	int *value; //if degree is n, there are n+1 elements
public:
	Polynomial(int, int*);
	Polynomial(const Polynomial &);
	const int get_degree() const;
	const int* get_value() const;
	Polynomial operator+(Polynomial&);
	Polynomial operator*(Polynomial&);
	friend std::ostream& operator<<(std::ostream&, const Polynomial& );
	~Polynomial();
	Polynomial(){}; //default constructor
	void deletefunc();
};

//constructor with parameters of array and its size
Polynomial::Polynomial(int indegree, int *val) {   
	this->degree = indegree - 1;
	this->value = new int[indegree];
	for(int i=0; i < indegree; i++){
		value[i] = val[i]; //poly's first element is the largest
	}
}
//copy constructor
Polynomial::Polynomial(const Polynomial &pol) {
	this->degree = pol.degree;
	this->value = new int[this->degree+1];
	for(int i = 0; i < this->degree+ 1; i++)
		this->value[i] = pol.value[i];
}

//destructor for preventing memory leak
Polynomial::~Polynomial(){
	//delete[] value;
}

//getter method for degree
const int Polynomial::get_degree() const{
	return this->degree;
}
const int* Polynomial::get_value() const {
	return this->value;
}
// overloading << operator like a print function, prints from largest to least
std::ostream& operator<< (std::ostream& output, const Polynomial& pol) {
	int size = pol.get_degree();
	for (int i = 0; i < pol.get_degree()+1; i++) {
		if(i != pol.get_degree()){//if not last element
			if((pol.get_value())[i] != 0){
				if((pol.get_value())[i] != 1 && size != 1){ //both its exp and its value not 1
					output << (pol.get_value())[i] << "x^" << size;
				}
				else if ((pol.get_value())[i] == 1 && size!= 1){ //don't write its coeff. but write its exp
					output << "x^"<<size;
				}
				else if((pol.get_value())[i] != 1 && size == 1){ //write its coeff. but don't write its exp
					output << (pol.get_value())[i] << "x";
				}
				else if((pol.get_value())[i] == 1 && size == 1){ //write neither its coeff nor its exp
					output << "x";
				}
				output << " + ";
			}				
		}else { // last element
			output << (pol.get_value())[i];
		}
		size--;	
	}
	return output;	
}

//overloading operator + for polynomial addition
Polynomial Polynomial::operator+(Polynomial& toadd) {
	int newsize = this->degree > toadd.degree ? this->degree : toadd.degree;
	int *addarr = new int[newsize+1]; // will be sorted from larger degree to least
	if(this->degree == toadd.degree){
		for(int i = 0; i<=degree; i++){
			addarr[i] = this->value[i] + toadd.value[i];
		}
	}else if(this->degree > toadd.degree){
		int counter = 0; //counts how many elements added to the add array
		for(int i = 0; i < this->degree - toadd.degree; i++ ){
			addarr[i] = this->value[i];
			counter++;
		}
		for(int i = 0; i <= toadd.degree; i++){
			addarr[i+counter] = this->value[i+counter] + toadd.value[i];
		}
	}else if(this->degree < toadd.degree){
		int counter = 0; //counts how many elements added to the add array
		for(int i = 0; i < toadd.degree-this->degree; i++ ){
			addarr[i] = toadd.value[i];
			counter++;
		}
		for(int i = 0; i <= this->degree; i++){
			addarr[i+counter] = this->value[i] + toadd.value[i+counter];
		}
	}
	return Polynomial(newsize+1, addarr);
}

//overload operator* for polynomial multiplication
Polynomial Polynomial::operator*(Polynomial& tomult) {
	int size1 = this->degree+1, size2 = tomult.degree+1;
	int *finalarray = new int[size1+size2-1];
	//initialize
	for(int i = 0; i < size1 + size2 -1; i++){
		finalarray[i] = 0;
	}
	
	for(int i = 0; i < size1; i++){ //all terms of *this
		for(int j = 0; j<size2;j++ ){ //all terms of tomult
			finalarray[i+j] += this->value[i] * tomult.value[j];
		}
	}
	return Polynomial(size1+size2-1, finalarray);
}

void Polynomial::deletefunc(){
		delete[] value;
}