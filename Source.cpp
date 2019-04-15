#include <iostream>
using namespace std;

class vector {
	int *a;
public:
	vector();
	~vector();
	vector(int);
	vector(int*);
	vector(const vector&);
	vector& operator=(const vector&);
	vector& operator=(int*);
	int& operator[](int) const;
	int* get_a() const;
};

class Nr_Natural_Mare {
protected:
	int nrcif;
	vector V;
public:
	Nr_Natural_Mare();
	Nr_Natural_Mare(int, int*);
	Nr_Natural_Mare(int,vector);
	Nr_Natural_Mare(int);
	~Nr_Natural_Mare() {}
	Nr_Natural_Mare(const Nr_Natural_Mare&);
	Nr_Natural_Mare& operator=(const Nr_Natural_Mare&);
	friend istream& operator>>(istream &, Nr_Natural_Mare&);
	virtual void afisare(ostream&);
	virtual Nr_Natural_Mare& operator*(Nr_Natural_Mare&);
	virtual Nr_Natural_Mare& operator+(Nr_Natural_Mare &);
	int get_nrcif()const { return nrcif; }
	vector& get_v() { return V; }
	bool operator==(Nr_Natural_Mare&);
	bool operator<(Nr_Natural_Mare&);
	/*Nr_Natural_Mare & operator*(int s);*/
};

class Numar_Fibonacci_mare :public Nr_Natural_Mare {
public:
	Numar_Fibonacci_mare() {}
	/*Numar_Fibonacci_mare(int nr, int *a) :Nr_Natural_Mare(nr, a) {}
	Numar_Fibonacci_mare(int nr, vector a) :Nr_Natural_Mare(nr,a) {}
	Numar_Fibonacci_mare(int nr) :Nr_Natural_Mare(nr) {}*/
	Numar_Fibonacci_mare(int);
	Numar_Fibonacci_mare& operator=(Nr_Natural_Mare&);
	~Numar_Fibonacci_mare() {}
	//Numar_Fibonacci_mare& operator+(Numar_Fibonacci_mare &);
	void afisare(ostream&);
	void operator()(int index);
};

bool isFibonacci(Numar_Fibonacci_mare &a)
{
	Numar_Fibonacci_mare b(0);
	int i = 1;
	while (b < a)
	{
		b(i);
		i++;
	}
	if (b == a)
		return true;
	else return false;
}

vector::vector()
{
	a = new int[1];
}

vector::~vector()
{
	delete[] a;
}

vector::vector(int* b)
{
	if (b)
		a = b;
	else
		a = new int[1];
}

vector::vector(int dimensiune)
{
	if (dimensiune >= 1)
		a = new int[dimensiune];
	else
		a = new int[1];
}

vector::vector(const vector& b)
{
	if (b.a)
		a = b.a;
	else
		a = new int[1];
}

vector& vector::operator=(const vector& b)
{
	if (this != &b)
	{
		if (this->a)
			delete[] this->a;
		this->a = b.a;
	}
	return (*this);
}

vector& vector::operator=(int* p)
{
	if (a != p)
	{
		if (a)
			delete[] a;
		if (p)
			a = p;
		else
			a = new int[1];
	}
	return (*this);
}

int& vector::operator[](int index) const
{
	return a[index];
}

int* vector::get_a() const
{
	return a;
}

Nr_Natural_Mare::Nr_Natural_Mare()
{
	nrcif = 0;
}

Nr_Natural_Mare::Nr_Natural_Mare(int nr, int *v):V(v)
{
	if (v == NULL)
		this->nrcif = 0;
	else
		this->nrcif = nr;
}

Nr_Natural_Mare::Nr_Natural_Mare(int nr, vector a) :V(a), nrcif(nr) {}

Nr_Natural_Mare::Nr_Natural_Mare(int nr) : V(nr), nrcif(nr) {}

Nr_Natural_Mare::Nr_Natural_Mare(const Nr_Natural_Mare& b)
{	
	this->nrcif = b.nrcif;
	int *c, i;
	c = new int[b.nrcif];
	for (i = 0; i < b.nrcif; i++)
		c[i] = b.V[i];
	V = c;
}

Nr_Natural_Mare& Nr_Natural_Mare::operator=(const Nr_Natural_Mare& b)
{
	if (this != &b)
	{
		this->nrcif = b.nrcif;
		int *c, i;
		c = new int[b.nrcif];
		for (i = 0; i < b.nrcif; i++)
			c[i] = b.V[i];
		V = c;
	}
	return *this;
}

Nr_Natural_Mare& Nr_Natural_Mare::operator*(Nr_Natural_Mare& b)
{
	if (this->nrcif == 0 or b.nrcif == 0)
	{
		Nr_Natural_Mare *c=new Nr_Natural_Mare;
		return *c;
	}
	if ((nrcif == 1 and V[0] == 0) or (b.nrcif == 1 and b.V[0] == 0))
	{
		int *aux = new int[1];
		aux[0] = 0;
		Nr_Natural_Mare *c=new Nr_Natural_Mare(1, aux);
		return *c;
	}
	int i1, i2, n=0 , nr_c = nrcif + b.nrcif - 1, *v3=new int[nr_c], t;
	for (int i = 0; i < nr_c; i++)
		v3[i] = 0;
	for (i1 = nrcif - 1; i1 >= 0; i1--)
	{	
		t = nr_c - (nrcif - 1 - i1) - 1;
		for (i2 = b.nrcif - 1; i2 >= 0; i2--, t--)
			v3[t] = v3[t] + V[i1] * b.V[i2];
	}
	//trec surplusul
	t = 0;
	i1 = nr_c - 1;
	while (i1)
	{
		v3[i1] += t;
		t = v3[i1] / 10;
		v3[i1] %= 10;
		i1--;
	}
	v3[0] += t;
	if (v3[0] >= 10)
	{
		int *aux = new int[nr_c];
		for (int i = 0; i < nr_c; i++)
			aux[i] = v3[i];
		delete[] v3;
		v3 = new int[nr_c + 1];
		for (int i = 0; i < nr_c; i++)
			v3[i+1] = aux[i];
		delete[] aux;
		v3[0] = v3[1] / 10;
		v3[1] %= 10;
		nr_c++;
	}
	Nr_Natural_Mare *c=new Nr_Natural_Mare(nr_c, v3);
	return *c;
}

Nr_Natural_Mare& Nr_Natural_Mare::operator+(Nr_Natural_Mare& b)
{
	int max_nrcif;
	if (nrcif > b.nrcif)
		max_nrcif = nrcif;
	else
		max_nrcif = b.nrcif;
	if (max_nrcif <= 0)
	{
		Nr_Natural_Mare *c = new Nr_Natural_Mare;
		return *c;
	}
	Nr_Natural_Mare *c = new Nr_Natural_Mare(max_nrcif);
	int i1 = nrcif-1, i2 = b.nrcif-1,t=0;
	while (i1 >= 0 and i2 >= 0)
	{
		c->V[max_nrcif-1] = V[i1] + b.V[i2];
		i1--;
		i2--;
		max_nrcif--;
	}
	while (i1 >= 0)
	{
		c->V[max_nrcif - 1] = V[i1];
		i1--;
	}
	while (i2 >= 0)
	{
		c->V[max_nrcif - 1] = b.V[i2];
		i2--;
	}
	i1 = c->nrcif - 1;
	while (i1)
	{
		c->V[i1] += t;
		t = c->V[i1] / 10;
		c->V[i1] %= 10;
		i1--;
	}
	c->V[0] += t;
	if (c->V[0] >= 10)
	{
		int *aux = new int[c->nrcif];
		for (int i = 0; i < nrcif; i++)
			aux[i] = c->V[i];
		int *v3 = new int[c->nrcif + 1];
		for (int i = 0; i < nrcif; i++)
			v3[i + 1] = aux[i];
		delete[] aux;
		v3[0] = v3[1] / 10;
		v3[1] %= 10;
		c->nrcif++;
		c->V = v3;
	}
	return *c;

}

bool Nr_Natural_Mare::operator==(Nr_Natural_Mare& b)
{
	if (nrcif<b.nrcif or nrcif>b.nrcif)
		return false;
	int i = 0;
	while (i < nrcif and V[i] == b.V[i])
		i++;
	if (i == nrcif)
		return true;
	else return false;
}

bool Nr_Natural_Mare::operator<(Nr_Natural_Mare &b)
{
	if (this->nrcif > b.nrcif)
		return false;
	if (this->nrcif < b.nrcif)
		return true;
	int i = 0;
	while (i < nrcif and V[i] == b.V[i])
		i++;
	if (i == nrcif)
		return false;
	else
	{
		if (V[i] < b.V[i])
			return true;
		else return false;
	}
}

//Nr_Natural_Mare& Nr_Natural_Mare::operator*(int s)
//{
//	if (nrcif == 0 or s<0)
//	{
//		Nr_Natural_Mare *c = new Nr_Natural_Mare;
//		return *c;
//	}
//	if ((nrcif==0 and V[0] == 0) or s==0)
//	{
//		int *aux = new int[1];
//		aux[0] = 0;
//		Nr_Natural_Mare *c = new Nr_Natural_Mare(1, aux);
//		return *c;
//	}
//	int t = 0, *aux2 = new int[nrcif],nr_n=nrcif;
//	for (int i = 0; i < nrcif; i++)
//		aux2[i] = V[i];
//	for (int i = nrcif - 1; i >= 0; i--)
//		aux2[i] *= s;
//	for (int i = nrcif - 1; i > 0; i--)
//	{
//		aux2[i] += t;
//		t = aux2[i] / 10;
//		aux2[i] %= 10;
//	}
//	V[0] += t;
//	if (V[0] >= 10)
//	{
//		int *aux = new int[nrcif+1];
//		for (int i = 0; i < nrcif; i++)
//			aux[i] = aux2[i];
//		delete[] aux2;
//		aux2 = new int[nrcif + 1];
//		for (int i = 0; i < nrcif; i++)
//			aux2[i + 1] = aux[i];
//		delete[] aux;
//		aux2[0] = aux2[1] / 10;
//		aux2[1] %= 10;
//		nr_n++;
//		V = aux2;
//	}
//	Nr_Natural_Mare *c = new Nr_Natural_Mare(nr_n, aux2);
//	return *c;
//}

istream& operator>>(istream &in, Nr_Natural_Mare& b)
{	
	cout << "\nIntroduceti numarul: ";
	char *buffer = new char[200];
	try {
		in.getline(buffer, 200);
		int i=0;
		while (buffer[i] and isdigit(buffer[i]))
			i++;
		if (buffer[i] == NULL)
		{	
			b.nrcif = i;
			int i,*aux=new int[b.nrcif];
			for (i = 0; i < b.nrcif; i++)
				aux[i] = buffer[i] - '0';
			b.V=aux;
			delete[] buffer;
		}
		else
			throw "Nu ati introdus doar cifre.\n";
	}
	catch (const char* v)
	{	
		delete[] buffer;
		cout << v;
	}
	return in;
}

void Nr_Natural_Mare::afisare(ostream& out)
{	
	if (this->nrcif)
	{	
		int i, *aux;
		aux = this->V.get_a();
		for (i = 0; i < this->nrcif; i++)
			out << aux[i];
	}
	else
		out << "Numarul natural mare nu exista.\n";
}

void Numar_Fibonacci_mare::afisare(ostream& out)
{
	if (this->nrcif)
	{
		int i;
		try{
			if (isFibonacci(*this) == false)
				throw "\n Numarul pe care incercati sa il afisati nu e un umar fibonacci.\n";
		}
		catch (const char* s)
		{
			cout << s;
			return;
		}
		for (i = 0; i < this->nrcif; i++)
			out << V[i];
		out << " = ";
		bool exit = false;
		i = 0;
		while (exit == false)
		{
			Numar_Fibonacci_mare a(i);
			if (a == *this)
				exit = true;
			i++;
		}
		i--;
		if (i == 0)
			out << 0 << " + " << 0;
		else
		{
			if (i == 1 or i==2)
				out << 1<<" + "<<0;
			else
			{
				Numar_Fibonacci_mare a(i - 1), b(i - 2);
				for (i = 0; i < a.nrcif; i++)
					out << a.V[i];
				out << " + ";
				for (i = 0; i < b.nrcif; i++)
					out << b.V[i];
			}
		}
	}
	else
		out << "Numarul Fibonnaci mare nu exista.\n";
}

Numar_Fibonacci_mare::Numar_Fibonacci_mare(int index)
{
	try {
		if (index < 0)
			throw "Primul numar fibonacci are indexul 0.\n";
	}
	catch (const char *a)
	{
		cout << a;
	}
	this->nrcif = 1;
	int *a = new int[1],*a2 = new int[1],i=0;
	a[0] = 0;
	this->V = a;
	Numar_Fibonacci_mare b,c;
	a2[0] = 1;
	b.nrcif = 1;
	b.V = a2;
	while (i < index)
	{	
		c = *this + b;
		*this = b;
		b = c;
		i++;
	}
}

Numar_Fibonacci_mare& Numar_Fibonacci_mare::operator=(Nr_Natural_Mare& b)
{
	nrcif = b.get_nrcif();
	V = b.get_v();
	return (*this);
}

void Numar_Fibonacci_mare::operator()(int index)
{
	Numar_Fibonacci_mare *aux = new Numar_Fibonacci_mare(index);
	this->nrcif = aux->nrcif;
	this->V = aux->V;
}

ostream& operator<<(ostream &out, Nr_Natural_Mare& b)
{
	b.afisare(out);
	return out;
}

int main()
{	
	int n,x	;
	cin >> n;
	Numar_Fibonacci_mare *v = new Numar_Fibonacci_mare[n], aux;
	for (int i = 0; i < n; i++)
	{
		cout << "Al catalea element al sirului fibonacci sa fie? ";
		cin >> x;
		v[i](x);
	}
	Numar_Fibonacci_mare b;
	b = v[n-1];
	b = b + b;
	for (int i = 0; i < n ; i++)
		cout << v[i] << '\n';
	cout << "\n####################\n";
	cout << v[n - 1] << " " << b;
	return 0;
}