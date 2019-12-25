#include<iostream>
using namespace std;
class CPoint2D
{
public:
	/* Point class overloads following operators
	+
	+=
	-
	-=
	*
	* scalar
	*=
	*= scalar
	=
	==
	<
	<=
	>
	>=
	!=
	!
	++
	--
	<<
	>>
	[]
	*/

	// binary operators functions

	CPoint2D operator+(const CPoint2D &) const; // Add a point2D in this object
	CPoint2D operator-(const CPoint2D&) const; // Subtract a point from the this object
	int operator*(const CPoint2D&) const; // multiply (dot product) a point with this object, returns scalar
	CPoint2D operator*(const int&) const; // multiply a scalar with x and y coordinates of this object, return a new object
	const CPoint2D& operator+=(const CPoint2D&);
	const CPoint2D& operator-=(const CPoint2D&);
	const CPoint2D& operator*=(const int&);
	const CPoint2D& operator=(const CPoint2D&); // assign a point to this object, returns this object by reference for cascading calls
	const CPoint2D operator=(const int nValue); // assign same value to both coordinates


	// public functions for I/O operators

	ostream& Print(ostream&) const;
	istream& Input(istream&);

	// Logical Operators

	bool operator<(const CPoint2D&) const;
	bool operator>=(const CPoint2D&) const;
	bool operator<=(const CPoint2D&) const;
	bool operator>(const CPoint2D&) const;
	bool operator==(const CPoint2D&) const;
	bool operator!=(const CPoint2D&) const;

	// unary operators

	CPoint2D operator-() const; // does not change this object but return a copy with negated values
	CPoint2D operator!() const; // return NOT of this object, i.e. x = y and y = x
	operator int(); // conversion operator to int data type
	int operator[](char c) const; // subscript operator for non-modifiable R-value
	int& operator[](char c); // subscript operator for modifiable L-value

	CPoint2D(const CPoint2D&);
	CPoint2D(int = 0, int = 0);
	~CPoint2D(void);


private:
	int m_xCoordinate, m_yCoordinate;

	CPoint2D Add(const CPoint2D &) const; // Add a point2D in this object
	CPoint2D Subtract(const CPoint2D&) const; // Subtract a point from the this object
	int Multiply(const CPoint2D&) const; // multiply (dot product) a point with this object, returns scalar
	CPoint2D MultiplyScalar(const int&) const; // multiply a scalar with x and y coordinates of this object, return a new object
	CPoint2D &AddAssignment(const CPoint2D&); // operator += ( a+=b)
	CPoint2D &SubAssignment(const CPoint2D&); // operator -= (a-=b)
	CPoint2D &MulScalarAssignment(const int&); // operator *= (a*=b)
	CPoint2D& Assignment(const CPoint2D&); // assign a point to this object, returns this object by reference for cascading calls
	CPoint2D AssignmentValue(const int nValue);

	// logical operators functions
	bool LessThan(const CPoint2D&) const;
	bool GreaterThanEqualTo(const CPoint2D&) const;
	bool LessThanEqualTo(const CPoint2D&) const;
	bool GreaterThan(const CPoint2D&) const;
	bool EqualTo(const CPoint2D&) const;
	bool NotEqualTo(const CPoint2D&) const;

	// unary operators functions
	CPoint2D Minus() const; // does not change this object but return a copy with negated values
	CPoint2D Not() const; // return NOT of this object, i.e. x = y and y = x
};