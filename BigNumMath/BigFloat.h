#include <iostream>
#include <string>
#include "BigInt.h"

class BigFloat {
public:
	BigFloat() { denominator.Construct("1"); minus_one.Construct("-1"); }
	~BigFloat() {}

	static const void print(BigFloat a) {
		BigInt::print(a.numerator, " / ");
		BigInt::print(a.denominator);
	}

	static const BigFloat ToFloat(BigInt a) {
		BigFloat result;
		result.numerator = a;
		return result;
	}

	friend bool operator== (const BigFloat&, const BigFloat&);
	friend bool operator> (const BigFloat&, const BigFloat&);
	friend bool operator< (const BigFloat&, const BigFloat&);
	friend bool operator>= (const BigFloat&, const BigFloat&);
	friend bool operator<= (const BigFloat&, const BigFloat&);

	friend BigFloat operator+ (BigFloat, BigFloat);
	friend BigFloat operator- (BigFloat, BigFloat);
	friend BigFloat operator* (BigFloat, BigFloat);
	friend BigFloat operator/ (BigFloat, BigFloat);

private:
	BigInt numerator;
	BigInt denominator;
	
	BigInt minus_one;
	BigInt null;

	void fix_signs() {
		if (denominator < null) {
			numerator = numerator * minus_one;
			denominator = denominator * minus_one;
		}
	}
	bool is_zero() {
		return numerator == null;
	}
};

bool operator== (const BigFloat& a, const BigFloat& b) {
	return (a.numerator == b.numerator) && (a.denominator == b.denominator);
}
bool operator> (const BigFloat& a, const BigFloat& b) {
	return (a.numerator * b.denominator) > (b.numerator * a.denominator);
}
bool operator< (const BigFloat& a, const BigFloat& b) {
	return (a.numerator * b.denominator) < (b.numerator * a.denominator);
}
bool operator>= (const BigFloat& a, const BigFloat& b) {
	return (a == b) || (a > b);
}
bool operator<= (const BigFloat& a, const BigFloat& b) {
	return (a == b) || (a < b);
}

BigFloat operator+ (BigFloat a, BigFloat b) {
	BigInt numerator;
	BigInt denominator;

	numerator = a.numerator * b.denominator + b.numerator * a.denominator;
	denominator = a.denominator * b.denominator;

	BigInt gcd = BigInt::gcd(numerator, denominator);
	numerator = numerator / gcd;
	denominator = denominator / gcd;

	BigFloat result;
	result.numerator = numerator;
	result.denominator = denominator;

	return result;
}
BigFloat operator- (BigFloat a, BigFloat b) {
	BigInt numerator;
	BigInt denominator;

	numerator = a.numerator * b.denominator - b.numerator * a.denominator;
	denominator = a.denominator * b.denominator;

	BigInt gcd = BigInt::gcd(numerator, denominator);
	numerator = numerator / gcd;
	denominator = denominator / gcd;

	BigFloat result;
	result.numerator = numerator;
	result.denominator = denominator;

	return result;
}
BigFloat operator* (BigFloat a, BigFloat b) {
	BigInt numerator = a.numerator * b.numerator;
	BigInt denominator = a.denominator * b.denominator;

	BigInt gcd = BigInt::gcd(numerator, denominator);
	numerator = numerator / gcd;
	denominator = denominator / gcd;

	BigFloat result;
	result.numerator = numerator;
	result.denominator = denominator;

	result.fix_signs();

	return result;
}
BigFloat operator/ (BigFloat a, BigFloat b) {

	if (b.is_zero()) {
		std::cout << "\nError found: Division by zero!" << std::endl;
		exit(1);
	}

	BigInt numerator = a.numerator * b.denominator;
	BigInt denominator = a.denominator * b.numerator;

	BigInt gcd = BigInt::gcd(numerator, denominator);
	numerator = numerator / gcd;
	denominator = denominator / gcd;

	BigFloat result;
	result.numerator = numerator;
	result.denominator = denominator;

	result.fix_signs();

	return result;
}

