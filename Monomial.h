#pragma once
#include <iostream>
#include <iomanip>
#include <string>



using namespace std;

class Monomial {
private:
	double c;
	int d;
	Monomial *next;
	Monomial *prev;
	static int count;
public:
	Monomial(double c = 1.0, int d = 0);
	static int getNumberOfMonomials();
	bool add(const Monomial &m);
	~Monomial() { count--; }
	friend class Polynomial;
	Monomial(const Monomial &m);
	Monomial *getNext() const;
	double getC() const;
	void setDeg(int d);
	int getD();
	void setC(double c);
	const Monomial  operator+(const Monomial &m) const;
	const Monomial & operator=(const Monomial &m);
	const Monomial  operator-(const Monomial &m) const;
	const Monomial  operator*(const Monomial &m) const;
	const Monomial & operator+=(const Monomial &m);
	const Monomial & operator-=(const Monomial &m);
	const Monomial & operator*=(const Monomial &m);
	const Monomial  operator-()const;
	bool operator==(const Monomial &m) const;
	bool operator!=(const Monomial &m) const;
	friend ostream & operator<<(ostream &buff, const Monomial &m);
	friend istream & operator >> (istream &buff, Monomial &m);
	void stringToMonomial(const string &str);
	double operator()(double r) const;
};

