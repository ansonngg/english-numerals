#include <iostream>
#include <string>
using namespace std;

string largeNumName(size_t illion, bool containLast, bool isThousand) {
	if (isThousand) {
		return "thousand";
	}

	if (illion < 1000) {
		string name;
		if (illion < 10) {
			switch (illion) {
			case 0:
				name = "n";
				break;
			case 1:
				name = "m";
				break;
			case 2:
				name = "b";
				break;
			case 3:
				name = "tr";
				break;
			case 4:
				name = "quadr";
				break;
			case 5:
				name = "quint";
				break;
			case 6:
				name = "sext";
				break;
			case 7:
				name = "sept";
				break;
			case 8:
				name = "oct";
				break;
			case 9:
				name = "non";
				break;
			}
		}
		else {
			string table[3][10] = {
			{ "", "un", "duo", "tre", "quattuor", "quinqua", "se", "septe", "octo", "nove" },
			{ "", "dec", "vigint", "trigint", "quadragint", "quinquagint", "sexagint", "septuagint", "octogint", "nonagint" },
			{ "", "cent", "ducent", "trecent", "quadringent", "quingent", "sescent", "septingent", "octingent", "nongent" }
			};
			int units = illion % 10;
			int tens = (illion / 10) % 10;
			int hundreds = (illion / 100) % 10;

			if (units > 0) {
				name = table[0][units];
				if (tens > 0) {
					if (((units == 3 || units == 6) && (tens == 2 || tens == 3 || tens == 4 || tens == 5)) ||
						(units == 3 && tens == 8)) {
						name += "s";
					}
					else if (units == 6 && tens == 8) {
						name += "x";
					}
					else if (units == 7 || units == 9) {
						if (tens == 2 || tens == 8) {
							name += "m";
						}
						else if (tens != 9) {
							name += "n";
						}
					}
					name += table[1][tens];
					if (hundreds > 0) {
						if (tens > 2) {
							name += "a";
						}
						else {
							name += "i";
						}
						name += table[2][hundreds];
					}
				}
				else if (hundreds > 0) {
					if (((units == 3 || units == 6) && (hundreds == 3 || hundreds == 4 || hundreds == 5)) ||
						(units == 3 && (hundreds == 1 || hundreds == 8))) {
						name += "s";
					}
					else if (units == 6 && (hundreds == 1 || hundreds == 8)) {
						name += "x";
					}
					else if (units == 7 || units == 9) {
						if (hundreds == 8) {
							name += "m";
						}
						else if (hundreds != 9) {
							name += "n";
						}
					}
					name += table[2][hundreds];
				}
			}
			else if (tens > 0) {
				name = table[1][tens];
				if (hundreds > 0) {
					if (tens > 2) {
						name += "a";
					}
					else {
						name += "i";
					}
					name += table[2][hundreds];
				}
			}
			else if (hundreds > 0) {
				name = table[2][hundreds];
			}
		}

		name += "illi";
		if (containLast) {
			return name + "on";
		}
		else {
			return name;
		}
	}

	if (containLast) {
		return largeNumName(illion / 1000, false, false) + largeNumName(illion % 1000, true, false);
	}
	else {
		return largeNumName(illion / 1000, false, false) + largeNumName(illion % 1000, false, false);
	}
}

string numName(string digits) {
	size_t digitNum = digits.length();
	int units = digits[digitNum - 1] - 48;
	int tens = digitNum > 1 ? digits[digitNum - 2] - 48 : 0;
	int hundreds = digitNum > 2 ? digits[digitNum - 3] - 48 : 0;
	int numTillTens = units + tens * 10;
	string numTillTensStr;
	string table[2][10] = {
		{ "", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" },
		{ "", "", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety" }
	};

	switch (numTillTens) {
	case 10:
		numTillTensStr = "ten";
		break;
	case 11:
		numTillTensStr = "eleven";
		break;
	case 12:
		numTillTensStr = "twelve";
		break;
	case 13:
		numTillTensStr = "thirteen";
		break;
	case 14:
		numTillTensStr = "fourteen";
		break;
	case 15:
		numTillTensStr = "fifteen";
		break;
	case 16:
		numTillTensStr = "sixteen";
		break;
	case 17:
		numTillTensStr = "seventeen";
		break;
	case 18:
		numTillTensStr = "eighteen";
		break;
	case 19:
		numTillTensStr = "nineteen";
		break;
	default:
		if (tens > 0) {
			numTillTensStr = table[1][tens];
			if (units > 0) {
				numTillTensStr += "-" + table[0][units];
			}
		}
		else if (units > 0) {
			numTillTensStr = table[0][units];
		}
	}

	string name;
	if (hundreds > 0) {
		name = table[0][hundreds] + " hundred";
		if (numTillTens > 0) {
			name += " " + numTillTensStr;
		}
	}
	else {
		name = numTillTensStr;
	}
	return name;
}

int main() {
	string num;
	cin >> num;
	size_t digitNum = num.length();
	string name;

	if (digitNum == 1 && num[0] == '0') {
		name = "zero";
	}
	else if (digitNum < 4) {
		name = numName(num);
	}
	else {
		int remainDigitNum = (digitNum - 1) % 3 + 1;
		for (size_t i = 0; i < digitNum; i += (i == 0 ? remainDigitNum : 3)) {
			bool isThousand = (digitNum < 7 || i > digitNum - 7) && i < digitNum - 3;
			if (i == 0) {
				name = numName(num.substr(0, remainDigitNum)) + " " + largeNumName((digitNum - 1 - i) / 3 - 1, true, isThousand);
			}
			else if (num[i] == '0' && num[i + 1] == '0' && num[i + 2] == '0') {
				continue;
			}
			else if (i == digitNum - 3) {
				name += " " + numName(num.substr(i));
			}
			else {
				name += " " + numName(num.substr(i, 3)) + " " + largeNumName((digitNum - 1 - i) / 3 - 1, true, isThousand);
			}
		}
	}

	name[0] -= 32;
	cout << name << endl;
	return 0;
}
