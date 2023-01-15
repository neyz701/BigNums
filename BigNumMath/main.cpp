#include <iostream>
#include <string>
#include "BigFloat.h"

// BigInt at work
int main1() {
	std::cout << "-------------------------BigInt----------------------------" << std::endl;
	while (true) {
		std::string a;
		std::string b;
		std::string c;
		std::string d;

		std::cin >> a >> b;

		BigInt aa;
		aa.Construct(a);

		BigInt bb;
		bb.Construct(b);

		BigInt cc;
		cc.Construct(c);

		BigInt dd;
		dd.Construct(d);

		std::cout << "a + b = ";
		BigInt::print(aa + bb);

		std::cout << "a - b = ";
		BigInt::print(aa - bb);

		std::cout << "a * b = ";
		BigInt::print(aa * bb);

		std::cout << "a / b = ";
		BigInt::print(aa / bb);

		std::cout << "a % b = ";
		BigInt::print(aa % bb);
		std::cout << "-----------------------------------------------------" << std::endl;
	}
	return 0;
}

// BigFloat at work
int main() {
	std::cout << "---------------------------BigFloat--------------------------" << std::endl;
	while (true) {
		std::string a;
		std::string b;
		std::string c;
		std::string d;

		std::cin >> a >> b >> c >> d;

		BigInt aa;
		aa.Construct(a);

		BigInt bb;
		bb.Construct(b);

		BigInt cc;
		cc.Construct(c);

		BigInt dd;
		dd.Construct(d);

		BigFloat first = BigFloat::ToFloat(aa) / BigFloat::ToFloat(bb);
		BigFloat second = BigFloat::ToFloat(cc) / BigFloat::ToFloat(dd);

		std::cout << "a/b + c/d = ";
		BigFloat::print(first + second);

		std::cout << "a/b - c/d = ";
		BigFloat::print(first - second);

		std::cout << "a/b * c/d = ";
		BigFloat::print(first * second);

		std::cout << "a/b / c/d = ";
		BigFloat::print(first / second);

		std::cout << "-----------------------------------------------------" << std::endl;
	}
	return 0;
}