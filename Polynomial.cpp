#include "Polynomial.h"



Polynomial::Polynomial() {
	head = tail = NULL;
	d = 0;
}

Polynomial::Polynomial(const Polynomial &p) :head(NULL), tail(NULL) {
	*this = p;
}

bool Polynomial::IsEmpty()const {
	return head == NULL;
}

void Polynomial::InsertFirst(const Monomial &m) {
	Monomial *temp = new Monomial(m);
	if (IsEmpty()) head = tail = temp;
	else {
		temp->next = head;
		head->prev = temp;
		head = temp;
	}
}

void Polynomial::DeleteFirst() {
	Monomial *temp = head;
	if (head == tail) head = tail = NULL;
	else {
		head = head->next;
		head->prev = NULL;
	}
	delete temp;
}

void Polynomial::InsertLast(const Monomial &m) {
	Monomial *temp = new Monomial(m);
	if (IsEmpty()) head = tail = temp;
	else {
		temp->prev = tail;
		tail->next = temp;
		tail = temp;
	}
}

void Polynomial::DeleteLast() {
	Monomial *temp = tail;
	tail = tail->prev;
	tail->next = NULL;
	delete temp;
}

void Polynomial::InsertBefore(Monomial &x, const Monomial &y) { //insert y before x
	if (&x == head) InsertFirst(y);
	else {
		Monomial *temp = new Monomial(y);
		temp->next = &x;
		temp->prev = x.prev;
		temp->prev->next = temp;
		temp->next->prev = temp;
	}
}

void Polynomial::DeleteMonomial(Monomial *x) {
	if (x == head) DeleteFirst();
	else if (x == tail) DeleteLast();
	else {
		x->next->prev = x->prev;
		x->prev->next = x->next;
		delete x;
	}
}

void Polynomial::InsertCheck(Monomial &x, const Monomial &y) { // checking if insert y before x or add y to x
	if (y.d == x.d) {
		x.add(y);
		if (x.c == 0) DeleteMonomial(&x); // case after add , c=0 , we delete x(x is element in the list that allocated in the past)
	}
	else InsertBefore(x, y);
}

void Polynomial::add(const Monomial &m) {
	if (m.c != 0) {
		Monomial *temp = head;
		while (temp != NULL && m.d < temp->d) temp = temp->next;
		if (temp != NULL) InsertCheck(*temp, m);
		else InsertLast(m);
		if (!IsEmpty()) d = head->d;
		else d = 0;
	}
}


Polynomial::~Polynomial() {
	clearPoly();
}

void Polynomial::clearPoly() {
	while (!IsEmpty())
		DeleteFirst();
}

const Polynomial & Polynomial :: operator=(const Polynomial &p) {
	if (this != &p) {
		clearPoly();
		Monomial *temp = p.head;
		while (temp != NULL) {
			InsertLast(*temp);
			temp = temp->next;
		}
		d = p.d;
	}
	return *this;
}

const Polynomial Polynomial:: operator+(const Polynomial &p)const {
	Polynomial temp;
	Monomial *iter1 = this->head, *iter2 = p.head;
	while (iter1 != NULL && iter2 != NULL) {
		if (iter1->d > iter2->d) {
			temp.InsertLast(*iter1);
			iter1 = iter1->next;
		}
		else if (iter1->d < iter2->d) {
			temp.InsertLast(*iter2);
			iter2 = iter2->next;
		}
		else {
			if (iter1->c + iter2->c != 0) temp.InsertLast(*iter1 + *iter2);
			iter1 = iter1->next;
			iter2 = iter2->next;
		}
	}
	while (iter1 != NULL) {
		temp.InsertLast(*iter1);
		iter1 = iter1->next;
	}
	while (iter2 != NULL) {
		temp.InsertLast(*iter2);
		iter2 = iter2->next;
	}
	return temp;
}

const Polynomial Polynomial::operator-() const {
	Polynomial temp;
	Monomial *iter = head;
	while (iter != NULL) {
		temp.InsertLast(Monomial(iter->c*-1, iter->d));
		iter = iter->next;
	}
	return temp;
}

const Polynomial Polynomial::operator-(const Polynomial &p) const {
	const Polynomial &temp = *this + (-p);
	return temp;
}

const Polynomial Polynomial :: operator+(const Monomial &m) const {
	Polynomial temp(*this);
	temp.add(m);
	return temp;
}

const Polynomial Polynomial :: operator-(const Monomial &m) const {
	const Polynomial &temp = *this + Monomial(m.c*-1, m.d);
	return temp;
}

const Polynomial & Polynomial::operator+=(const Polynomial &p) {
	*this = *this + p;
	return *this;
}

const Polynomial & Polynomial:: operator-=(const Polynomial &p) {
	*this = *this + (-p);
	return *this;
}

const Polynomial & Polynomial::operator+=(const Monomial &m) {
	this->add(m);
	return *this;
}

const Polynomial & Polynomial :: operator-=(const Monomial &m) {
	this->add(-m);
	return *this;
}

bool Polynomial :: operator==(const Polynomial &p) {
	if (this == &p) return true; // for the case that the user check if x==x
	Monomial *iter1 = head, *iter2 = p.head;
	while (iter1 != NULL && iter2 != NULL) {
		if (*iter1 != *iter2) return false;
		iter1 = iter1->next;
		iter2 = iter2->next;
	}
	return iter1 == NULL && iter2 == NULL;
}

bool Polynomial :: operator!=(const Polynomial &p) {
	return !(*this == p);
}

ostream & operator<<(ostream &buff, const Polynomial &p) {
	if (p.IsEmpty()) buff << 0;
	else {
		Monomial *temp = p.head->getNext();
		buff << *(p.head);
		while (temp != NULL) {
			if (temp->getC() > 0) buff << '+';
			buff << *temp;
			temp = temp->getNext();
		}
	}
	return buff;
}

istream & operator >> (istream &buff, Polynomial &p) {
	string str, temp;
	Monomial m;
	int size;
	p.clearPoly();
	getline(buff, str);
	temp = str[0]; // case the first char is '-'
	size = str.length();
	for (int i = 1; i < size; i++) {
		if (str[i] != ' ') {
			if (str[i] != '+' && str[i] != '-' && str[i] != ',') temp += str[i];
			else {
				m.stringToMonomial(temp);
				p.add(m);
				temp = str[i];
			}
		}
	}
	return buff;
}

double Polynomial :: operator()(double c) const {
	double sum = 0;
	Monomial *temp = head;
	while (temp != NULL) {
		sum += (*temp)(c);
		temp = temp->next;
	}
	return sum;
}

const double& Polynomial :: operator[](int d) const {
	static double zero = 0;
	Monomial *temp = head;
	while (temp != NULL && temp->d > d) temp = temp->next;
	if (temp == NULL || temp->d != d) return zero;
	return temp->c;
}


double& Polynomial :: operator[](int d) {
	static double zero = 0;
	Monomial *temp = head;
	while (temp != NULL && temp->d > d) temp = temp->next;
	if (temp == NULL || temp->d != d) return  zero;
	return temp->c;
}

bool Polynomial :: operator!=(const Monomial &m)  {
	return !((IsEmpty() && m.c == 0) || ( !IsEmpty() && head == tail && *head == m ));
}
