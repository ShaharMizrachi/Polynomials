#pragma once

#include "Monomial.h"
class Polynomial {
	Monomial *head;
	Monomial *tail;
	int d;

public:
	Polynomial(const Polynomial &p);
	Polynomial();
	bool IsEmpty() const;
	void InsertFirst(const Monomial &m);
	void DeleteFirst();
	void InsertLast(const Monomial &m);
	void DeleteLast();
	void InsertBefore(Monomial &x, const Monomial &y);
	void DeleteMonomial(Monomial *x);
	void InsertCheck(Monomial &x, const Monomial &y);
	void add(const Monomial &m);
	void clearPoly();
	const Polynomial & operator=(const Polynomial &p);
	const Polynomial operator+(const Polynomial &p) const;
	const Polynomial operator-() const;
	const Polynomial operator-(const Polynomial &p) const;
	const Polynomial operator+(const Monomial &m) const;
	const Polynomial operator-(const Monomial &m) const;
	const Polynomial & operator+=(const Polynomial &p);
	const Polynomial & operator-=(const Polynomial &p);
	const Polynomial & operator+=(const Monomial &m);
	const Polynomial & operator-=(const Monomial &m);
	bool operator==(const Polynomial &p);
	bool operator!=(const Polynomial &p);
	bool operator!=(const Monomial &m);
	friend ostream & operator<<(ostream &buff, const Polynomial &p);
	friend istream & operator >> (istream &buff, Polynomial &p);
	double operator()(double c) const;
	const double& operator[](int d)const;
	double& operator[](int d);
	~Polynomial();
};

