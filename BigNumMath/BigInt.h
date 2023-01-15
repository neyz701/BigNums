#include <iostream>
#include <string>

class BigInt {
public:
	BigInt() {}
	~BigInt() {}

	void Construct(std::string str) {

		long long i = 0;

		if (str[0] == '-') {
			negative = true;
			++i;
		}

		//Избавляемся от передних незначащих нулей
		while (str[i] == '0' && str != "0") {
			++i;
		}

		length = str.length() - i;
		BigNum = str.substr(i, length);
	}

	static const void print(BigInt a) {
		print(a, "\n");
	}
	static const void print(BigInt a, std::string end) {
		if (a.negative) {
			std::cout << '-';
		}

		std::cout << a.BigNum;
		std::cout << end;
	}

	friend bool operator> (const std::string&, const std::string&);
	friend bool operator< (const std::string&, const std::string&);
	friend bool operator>= (const std::string&, const std::string&);
	friend bool operator<= (const std::string&, const std::string&);

	friend bool operator== (const BigInt&, const BigInt&);
	friend bool operator> (const BigInt&, const BigInt&);
	friend bool operator< (const BigInt&, const BigInt&);
	friend bool operator>= (const BigInt&, const BigInt&);
	friend bool operator<= (const BigInt&, const BigInt&);

	friend BigInt operator+ (BigInt, BigInt);
	friend BigInt operator- (BigInt, BigInt);
	friend BigInt operator* (BigInt, BigInt);
	friend BigInt operator/ (BigInt, BigInt);
	friend BigInt operator% (BigInt, BigInt);

	static BigInt gcd(BigInt, BigInt);

private:
	std::string BigNum = "0";
	long long length = 1;
	bool negative = false;
};

// std::string operators
bool operator> (const std::string& a, const std::string& b) {
	if (a.length() > b.length()) {
		return true;

	}
	else if (a.length() == b.length()) {

		for (long long i = 0; i < a.length(); ++i) {

			if (a[i] > b[i]) {
				return true;
			}
			if (a[i] < b[i]) {
				return false;
			}
		}
	}
	return false;
}

bool operator< (const std::string& a, const std::string& b) {
	return not(a == b || a > b);
}

bool operator>= (const std::string& a, const std::string& b) {
	return a == b || a > b;
}

bool operator<= (const std::string& a, const std::string& b) {
	return a == b || a < b;
}

// BigInt logic operators
bool operator==(const BigInt& a, const BigInt& b) {
	return (a.negative == b.negative) && (a.BigNum == b.BigNum);
}

bool operator> (const BigInt& a, const BigInt& b) {

	if (a == b) {
		return false;
	}

	if (a.negative + b.negative == 1) {
		return b.negative;
	}

	bool result = a.BigNum > b.BigNum;
	return not(result) == a.negative;
}

bool operator< (const BigInt& a, const BigInt& b) {
	return not(a == b || a > b);
}

bool operator>= (const BigInt& a, const BigInt& b) {
	return a == b || a > b;
}

bool operator<= (const BigInt& a, const BigInt& b) {
	return a == b || a < b;
}

// BigInt math operators
BigInt operator+ (BigInt a, BigInt b) {

	/*
	 * Если одно из чисел отрицательное
	 * То заменяем сложение на вычитание
	 */
	if (a.negative + b.negative == 1) {
		if (a.negative) {
			a.negative = false;
			return b - a;
		}
		else {
			b.negative = false;
			return a - b;
		}
	}

	if (a.length < b.length) {
		return b + a;
	}

	short buf = 0;
	long long i = 0;

	for (; i < b.length; ++i) {
		short a_char = a.BigNum[a.length - i - 1] - '0';
		short b_char = b.BigNum[b.length - i - 1] - '0';
		buf = buf + a_char + b_char;
		a.BigNum[a.length - i - 1] = buf % 10 + '0';
		buf /= 10;
	}

	for (; i < a.length && buf != 0; ++i) {
		short a_char = a.BigNum[a.length - i - 1] - '0';
		buf = buf + a_char;
		a.BigNum[a.length - i - 1] = buf % 10 + '0';
		buf /= 10;
	}

	if (buf != 0) {
		a.BigNum = (char)(buf + '0') + a.BigNum;
		++a.length;
	}
	a.length = a.BigNum.length();
	return a;
}

BigInt operator- (BigInt a, BigInt b) {

	if (a.negative + b.negative == 1) {
		b.negative = not(b.negative);
		return a + b;
	}

	if (a == b) {
		a.BigNum = "0";
		a.length = 1;
		a.negative = false;
		return a;
	}

	/*
	 * Первая часть операции:
	 *	Если второе число по модулю больше первого
	 *	То мы меняем их местами для более удобного вычисления
	 *	И запоминаем, что мы поменяли их местами
	 */

	BigInt result;
	bool swap;

	if ((a > b && a.negative == 0) || (a < b && a.negative)) {
		result = a;
		swap = false;
	}
	else {
		result = b;
		b = a;
		swap = true;
	}

	/*
	 * Вторая часть операции:
	 *	Подсчеты
	 */

	short buf = 0;

	long long i = 0;

	for (; i < b.length; ++i) {
		short a_char = result.BigNum[result.length - i - 1] - '0';
		short b_char = b.BigNum[b.length - i - 1] - '0';
		buf = a_char - b_char - buf;

		if (buf < 0) {
			result.BigNum[result.length - i - 1] = 10 + buf + '0';
			buf = 1;
		}
		else {
			result.BigNum[result.length - i - 1] = buf + '0';
			buf = 0;
		}
	}

	// Если занимали единичку у старшего разряда, то продолжаем вычитать
	for (; buf == 1; ++i) {
		short a_char = result.BigNum[result.length - i - 1] - '0';
		buf = a_char - buf;

		if (buf < 0) {
			result.BigNum[result.length - i - 1] = 10 + buf + '0';
			buf = 1;
		}
		else {
			result.BigNum[result.length - i - 1] = buf + '0';
			buf = 0;
		}
	}

	// Избавляемся от передних незначащих нулей
	while (result.BigNum[0] == '0') {
		result.BigNum.erase(0, 1);
		--result.length;
	}

	// Меняем знак, если числа были поменяны местами
	if (swap) {
		result.negative = not(result.negative);
	}
	result.length = result.BigNum.length();

	return result;
}

BigInt operator* (BigInt a, BigInt b) {

	BigInt c;

	if (a.BigNum == "0" || b.BigNum == "0") {
		return c;
	}

	long long b_index = 0;
	std::string zeros = ""; // Сюда мы будем добавлять нули для сложения

	// Во внешнем цикле мы идем по цифрам числа b
	// Во внутреннем умножаем и прибавляем результат к числу c

	for (; b_index < b.length; ++b_index, zeros += '0') {
		std::string a_num = a.BigNum;
		short b_char = b.BigNum[b.length - b_index - 1] - '0';
		long long a_index = 0;
		short buf = 0;

		for (; a_index < a.length; ++a_index) {
			short a_char = a_num[a.length - a_index - 1] - '0';
			buf = buf + a_char * b_char;
			a_num[a.length - a_index - 1] = buf % 10 + '0';
			buf /= 10;
		}

		if (buf != 0) {
			a_num = (char)(buf + '0') + a_num;
		}
		a_num += zeros;

		BigInt to_add;
		to_add.Construct(a_num);

		c = c + to_add;
	}

	if (a.negative + b.negative == 1) {
		c.negative = true;
	}

	return c;
}

BigInt operator/ (BigInt a, BigInt b) {

	bool negative_result = false;

	if (b.BigNum == "0") {
		std::cout << "\nError found: Division by zero!" << std::endl;
		exit(1);
	}

	if (a.negative + b.negative == 1) {
		negative_result = true;
	}

	a.negative = false;
	b.negative = false;

	if (a < b) {
		BigInt zero;
		return zero;
	}

	std::string result = "";

	BigInt a_num = a;
	a_num.BigNum = a_num.BigNum.substr(0, b.length);
	a_num.length = b.length;

	for (long long i = 0; i < (a.length - b.length + 1); ++i) {

		short buf = 0;

		while (b <= a_num) {
			++buf;
			a_num = a_num - b;
		}

		result += (char)(buf + '0');
		++a_num.length;
		a_num.BigNum += a.BigNum[b.length + i];
	}

	if (negative_result) {
		result = '-' + result;
	}

	BigInt res;
	res.Construct(result);

	return res;
}

BigInt operator% (BigInt a, BigInt b) {
	a.negative = false;
	b.negative = false;
	return a - (a / b * b);
}

BigInt BigInt::gcd(BigInt a, BigInt b) {
	if (b.BigNum == "0") {
		return a;
	}
	return gcd(b, a % b);
}

