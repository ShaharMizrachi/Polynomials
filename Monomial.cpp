#include "Monomial.h"
#include <math.h>

int Monomial::count = 0;

Monomial::Monomial(double c, int d) : c(c) {
	setDeg(d);
	count++;
	next = prev = NULL;
}


int Monomial::getNumberOfMonomials() {
	return count;
}

void Monomial::setC(double c) {
	this->c = c;
}

int Monomial::getD() {
	return this->d;
}

double Monomial::getC()const {
	return this->c;
}

Monomial * Monomial::getNext() const {
	return this->next;
}


bool Monomial::add(const Monomial &m) {
	if (d == m.d) {
		c += m.c;
		return true;
	}
	return false;
}

Monomial::Monomial(const Monomial &m) {
	*this = m;
	count++;
}

void Monomial::setDeg(int d) {
	this->d = d > 0 ? d : 0;
}

const Monomial  Monomial:: operator+(const Monomial &m) const {
	if (d != m.d) return *this;
	return Monomial(c + m.c, d);
}

const Monomial & Monomial::operator=(const Monomial &m) {
	if (&m != this) {
		d = m.d;
		c = m.c;
	}
	return *this;
}

const Monomial Monomial:: operator-(const Monomial &m) const {
	const Monomial &temp = *this + Monomial(m.c*-1, m.d);
	return temp;
}

const Monomial  Monomial::operator*(const Monomial &m) const {
	Monomial temp(c*m.c, d + m.d);
	return temp;
}

const Monomial & Monomial::operator+=(const Monomial &m) {
	this->add(m);
	return *this;
}

const Monomial & Monomial:: operator-=(const Monomial &m) {
	return *this += Monomial(m.c*-1, m.d);
}

const Monomial & Monomial:: operator*=(const Monomial &m) {
	c *= m.c;
	d += m.d;
	return *this;
}

const Monomial Monomial :: operator-() const {
	return Monomial(c*-1, d);
}

bool Monomial::operator==(const Monomial &m) const {
	return (c == 0 && m.c == 0) || (d == m.d && c == m.c);
}

bool Monomial::operator!=(const Monomial &m) const {
	return !(*this == m);
}

double Monomial :: operator()(double r) const {
	return pow(r, d)*c;
}

ostream & operator<<(ostream &buff, const Monomial &m) {
	if (m.d == 0 || m.c == 0) buff << m.c;
	else {
		if (m.c == -1) buff << '-';
		else if (m.c != 1) buff << m.c << '*';
		buff << "x";
		if (m.d > 1) buff << "^" << m.d;
	}
	return buff;
}


istream & operator >> (istream &buff, Monomial &m) {
	string str;
	getline(buff, str);
	m.stringToMonomial(str);
	return buff;
}

void Monomial::stringToMonomial(const string &str) {
	string temp = "";
	int size = str.length(), i;
	d = 0; // clear the deg
	for (i = 0; i < size && str[i] != 'x'; i++) temp += str[i];
	c = stod(temp);
	for (temp = ""; i < size; i++) {
		if (str[i] == 'x') d = 1;
		else if (str[i] == '-' || (str[i] >= '0' && str[i]<='9')) temp += str[i];
	}
	if (temp != "")setDeg(stoi(temp));
}