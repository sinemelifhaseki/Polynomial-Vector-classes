//Sinem Elif Haseki
//150160026
#include <iostream>

class Vector {
	int size;
	int *value;
public:
	Vector(int, int*);//constructor with parameter
	Vector(const Vector &); //copy
	Vector operator+(Vector&);
	Vector operator*(int);
	int operator*(Vector &);
	friend std::ostream& operator<<(std::ostream&, const Vector&);
	const int get_size() const;
	const int* get_value() const;
    ~Vector();
	Vector(){};
	void deletefunc();
};

//constructor with parameter
Vector::Vector(int size, int *val) {
	this->size = size;
	value = new int[size];
	for (int k = 0; k < this->size; k++){
		value[k] = val[k];
	}
}

// copy constructor
Vector::Vector(const Vector &obj) {
	this->size = obj.size;
	this->value = new int[size];
	for(int i = 0; i < size; i++)
		this->value[i] = obj.value[i];
}

//destructor in order to prevent memory leak
Vector::~Vector(){
    //delete[] value;
}

// overloading + operator 
Vector Vector::operator+(Vector& toadd) {
	int *sum_array;
	if(this->size == toadd.size){
		sum_array = new int[this->size];
		for(int i = 0; i<this->size; i++)
			sum_array[i] = 0;
		for(int i = 0; i<this->size; i++)
			sum_array[i] = this->value[i] + toadd.value[i];
	}
	return Vector(this->size,sum_array);
}

// getter method
const int Vector::get_size() const{
	return this->size;
}
const int* Vector::get_value() const{
	return value;
}

// overloading * operator as scalar multiplication
Vector Vector::operator*(int scalar) {
    int *newarr = new int[this->size];
	for(int i = 0; i<size; i++){
		newarr[i] = this->value[i] * scalar;
	}
	return Vector(size,newarr);
    
}

// overloading * operator as dot product
int Vector::operator*(Vector& dotpro) {
	int sum = 0;
	if(this->size == dotpro.size){
		for(int i = 0; i < this->size; i++){
			sum += this->value[i]*dotpro.value[i];
		}
	}
	return sum;
}

// overloading << operator like a print function
std::ostream& operator<< (std::ostream& output, const Vector& vec) {
	output << "(";
	for (int i = 0; i < vec.get_size(); i++) {
		output << (vec.get_value())[i];
		if (i+1 != vec.get_size()) //if not last element
			output << ", ";
	}
	output << ")";
	return output;
}

void Vector::deletefunc(){
		delete[] value;
}
