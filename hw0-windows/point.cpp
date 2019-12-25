#include "point.h"
using namespace std;

/* Default Constructor */
CPoint2D::CPoint2D(int x, int y)
{
	this->m_xCoordinate = x;
	this->m_yCoordinate = y;
}

/* Copy Constructor */
CPoint2D::CPoint2D(const CPoint2D&p2)
{
	(*this) = p2; // calling assignment operator 
}

/* Destructor */
CPoint2D::~CPoint2D(void)
{
}

/* conversion operator */
CPoint2D::operator int()
{
	return m_xCoordinate;
}

// binary operators
/* Operator+ */
CPoint2D CPoint2D::Add(const CPoint2D &op2) const // Add a point2D in this object
{
	CPoint2D temp;
	temp.m_xCoordinate = this->m_xCoordinate + op2.m_xCoordinate;
	temp.m_yCoordinate = this->m_yCoordinate + op2.m_yCoordinate;
	return temp; // a copy is returned, see return type
}
CPoint2D CPoint2D::operator+(const CPoint2D &op2) const // Add a point2D in this object
{
	return this->Add(op2);
}


/* Operator- */
CPoint2D CPoint2D::Subtract(const CPoint2D& op2) const // Subtract a point from the this object
{
	CPoint2D temp;
	temp.m_xCoordinate = this->m_xCoordinate - op2.m_xCoordinate;
	temp.m_yCoordinate = this->m_yCoordinate - op2.m_yCoordinate;
	return temp; // a copy is returned, see return type
}

CPoint2D CPoint2D::operator-(const CPoint2D&op2) const // Subtract a point from the this object
{
	return this->Subtract(op2);
}

/* Operator* */
int CPoint2D::Multiply(const CPoint2D& op2) const // multiply (dot product) a point with this object, returns scalar
{
	int dotProduct = this->m_xCoordinate * op2.m_xCoordinate + this->m_yCoordinate * op2.m_yCoordinate;
	return dotProduct; // a copy is returned, see return type
}

int CPoint2D::operator*(const CPoint2D&op2) const // multiply (dot product) a point with this object, returns scalar
{
	return this->Multiply(op2);
}

/* Operator* scalar */
CPoint2D CPoint2D::MultiplyScalar(const int& nScalar) const // multiply a scalar with x and y coordinates of this object, return a new object
{
	CPoint2D temp;
	temp.m_xCoordinate = this->m_xCoordinate * nScalar;
	temp.m_yCoordinate = this->m_yCoordinate * nScalar;
	return temp; // a copy is returned, see return type
}

CPoint2D CPoint2D::operator*(const int& op2) const // multiply a scalar with x and y coordinates of this object, return a new object
{
	return this->MultiplyScalar(op2);
}


/* Operator+= */
CPoint2D& CPoint2D::AddAssignment(const CPoint2D& op2)
{
	this->m_xCoordinate += op2.m_xCoordinate;
	this->m_yCoordinate += op2.m_yCoordinate;
	return *this; // a copy is returned, see return type
}

const CPoint2D& CPoint2D::operator+=(const CPoint2D&op2)
{
	return this->AddAssignment(op2);
}

/* Operator-= */
CPoint2D & CPoint2D::SubAssignment(const CPoint2D& op2)
{
	this->m_xCoordinate -= op2.m_xCoordinate;
	this->m_yCoordinate -= op2.m_yCoordinate;
	return *this; // a copy is returned, see return type
}

const CPoint2D& CPoint2D::operator-=(const CPoint2D& op2)
{
	return this->SubAssignment(op2);
}

/* Operator*= */
CPoint2D &CPoint2D::MulScalarAssignment(const int& nScalar)
{
	this->m_xCoordinate *= nScalar;
	this->m_yCoordinate *= nScalar;
	return *this; // a copy is returned, see return type
}

const CPoint2D& CPoint2D::operator*=(const int& op2)
{
	return this->MulScalarAssignment(op2);
}

// I/O operators

/* Operator<< */
ostream& CPoint2D::Print(ostream& out) const
{
	out << this->m_xCoordinate << " : " << this->m_yCoordinate << endl;
	return out;
}

/* Operator>> */
istream& CPoint2D::Input(istream& in)
{
	in >> this->m_xCoordinate >> this->m_yCoordinate;
	return in;
}

// GLOBAL FUNCTIONS FOR STREAM INSERTION/EXTRACTION
ostream& operator<<(ostream& out, const CPoint2D& obj)
{
	return obj.Print(out);
}
istream& operator>>(istream& in, CPoint2D& obj)
{
	return obj.Input(in);
}

// Logical Operators
/* Operator< */
bool CPoint2D::LessThan(const CPoint2D& op2) const
{
	if (this->m_xCoordinate < op2.m_xCoordinate || this->m_yCoordinate < op2.m_yCoordinate)
		return true;

	return false;
}

bool CPoint2D::operator<(const CPoint2D& op2) const
{
	return this->LessThan(op2);
}

/* Operator>= */
bool CPoint2D::GreaterThanEqualTo(const CPoint2D& op2) const
{
	return !this->LessThan(op2);
}

bool CPoint2D::operator>=(const CPoint2D& op2) const
{
	return this->GreaterThanEqualTo(op2);
}

/* Operator<= */
bool CPoint2D::LessThanEqualTo(const CPoint2D& op2) const
{
	return !this->GreaterThan(op2);
}

bool CPoint2D::operator<=(const CPoint2D& op2) const
{
	return this->LessThanEqualTo(op2);
}

/* Operator> */
bool CPoint2D::GreaterThan(const CPoint2D& op2) const
{
	if (this->m_xCoordinate > op2.m_xCoordinate && this->m_yCoordinate > op2.m_yCoordinate)
		return true;

	return false;
}

bool CPoint2D::operator>(const CPoint2D& op2) const
{
	return this->GreaterThan(op2);
}

/* Operator== */
bool CPoint2D::EqualTo(const CPoint2D& op2) const
{
	if (this->m_xCoordinate == op2.m_xCoordinate && this->m_yCoordinate == op2.m_yCoordinate)
		return true;

	return false;
}

bool CPoint2D::operator==(const CPoint2D& op2) const
{
	return this->EqualTo(op2);
}

/* Operator!= */
bool CPoint2D::NotEqualTo(const CPoint2D& op2) const
{
	return !this->EqualTo(op2);
}

bool CPoint2D::operator!=(const CPoint2D& op2) const
{
	return this->NotEqualTo(op2);
}

// unary operators
/* Operator- */
CPoint2D CPoint2D::Minus() const // does not change this object but return a copy with negated values
{
	CPoint2D temp;
	temp.m_xCoordinate = -this->m_xCoordinate;
	temp.m_yCoordinate = -this->m_yCoordinate;
	return temp;
}

CPoint2D CPoint2D::operator-() const // does not change this object but return a copy with negated values
{
	return this->Minus();
}

/* Operator! */
CPoint2D CPoint2D::Not() const // return NOT of this object, i.e. x = y and y = x
{
	CPoint2D temp;
	temp.m_xCoordinate = this->m_yCoordinate;
	temp.m_yCoordinate = this->m_xCoordinate;
	return temp;
}

CPoint2D CPoint2D::operator!() const // return NOT of this object, i.e. x = y and y = x
{
	return this->Not();
}

/* Operator= */
CPoint2D& CPoint2D::Assignment(const CPoint2D& op2) // assign a point to this object, returns this object by reference for cascading calls
{
	if (this == &op2)
		return *this;
	this->m_xCoordinate = op2.m_xCoordinate;
	this->m_yCoordinate = op2.m_yCoordinate;
	return *this;
}

const CPoint2D& CPoint2D::operator=(const CPoint2D& op2) // assign a point to this object, returns this object by reference for cascading calls
{
	return this->Assignment(op2);
}

/* Operator= */
CPoint2D CPoint2D::AssignmentValue(const int nValue)
{
	this->m_xCoordinate = this->m_yCoordinate = nValue;
	return *this;
}

const CPoint2D CPoint2D::operator=(const int nValue)
{
	return this->AssignmentValue(nValue);
}

/* subscript operators */
int CPoint2D::operator[](char c) const
{
	if (c == 'x')
		return m_xCoordinate;

	if (c == 'y')
		return m_yCoordinate;
	else
		return -1;
}

int& CPoint2D::operator[](char c)
{
	if (c == 'x')
		return m_xCoordinate;

	if (c == 'y')
		return m_yCoordinate;
	else
		cout << "invalid argument";

	return m_xCoordinate; // return x coordinate anyway	
}