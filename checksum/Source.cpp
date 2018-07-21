#include<iostream>
#include<vector>
#include<string>

using namespace std;

int getValue(char a) {
	int value = 0;
	switch (a) {
	case '0': return 0;
	case '1': return 1;
	case '2': return 2;
	case '3': return 3;
	case '4': return 4;
	case '5': return 5;
	case '6': return 6;
	case '7': return 7;
	case '8': return 8;
	case '9': return 9;
	case 'A': return 10;
	case 'B': return 11;
	case 'C': return 12;
	case 'D': return 13;
	case 'E': return 14;
	case 'F': return 15;
	default:
		return -1;
	}
}

vector<int> reverse(vector<int> a) {
	vector<int> result;
	for (int i = 0; i < a.size(); i++)
		result.push_back(a[a.size() - i - 1]);

	return result;
}

vector<int> toBinary(string a) {
	vector<int> result;

	for (int i = 0; i < a.length(); i++) {
		vector<int> tempResult;
		int val = getValue(a[i]);
		while (val > 0) {
			tempResult.push_back(val % 2);
			val = val / 2;
		}
		while (tempResult.size() < 4)
			tempResult.push_back(0);
		tempResult = reverse(tempResult);
		result.insert(result.end(), tempResult.begin(), tempResult.end());
	}


	return result;
}

vector<int> add(vector<int> a, vector<int> b, int c) {
	vector<int> sum(16, 0);

	for (int i = sum.size() - 1; i >= 0; i--) {
		sum[i] = ((a[i] ^ b[i]) ^ c); // c is carry
		c = ((a[i] & b[i]) | (a[i] & c)) | (b[i] & c);
	}
	if (c != 0) {
		vector<int> carry = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,c };
		sum = add(sum, carry, 0);
	}

	return sum;
}

vector<int> onesCompliment(vector<int>a) {
	for (int i = 0; i < a.size(); i++)
		a[i] = a[i] ^ 1;
	return a;
}

int main() {
	vector<string> data(4, "");
	vector< vector<int> > binary(4, vector<int>(4, 0));

	cout << "===========\nSender Side\n===========\n";
	cout << "Enter the 4 data with a space:";

	for (int i = 0; i < 4; i++)
		cin >> data[i];


	// Binary data
	for (int i = 0; i < data.size(); i++)
		binary[i] = toBinary(data[i]);

	// Addition

	vector<int> res(binary[0].size(), 0);
	for (int i = 0; i < binary.size(); i++) 
		res = add(res, binary[i], 0);

	// Checksum by taking complement
	vector<int> checksum = onesCompliment(res);
	cout << "Checksum: ";
	for (auto i : checksum)
		cout << i;
	cout << endl;
	


	cout << "\n\n==============\nReciever Side\n==============\n";
	
	cout << "Data is: ";
	for (auto i : data)
		cout <<i<<" ";
	

	cout << "\n\nAdding all the tranmitted data along with checksum...";
	res=vector<int>(binary[0].size(), 0);

	// Addition
	for (int i = 0; i < binary.size(); i++)
		res = add(res, binary[i], 0);

	cout << "\nChecksum is: ";
	for (auto i : checksum)
		cout << i;
	cout << "\nSum without checksum: ";
	for (auto i : res)
		cout << i;

	vector<int> verify = add(res, checksum, 0);
	verify = onesCompliment(verify);
	bool valid = true;
	cout << "\nWith checksum: ";
	for (auto i : verify) {
		cout << i;
		if (i != 0)
			valid = false;
	}
	cout << endl;

	if (valid)
		cout << "Data is transmitted correctly!";
	else
		cout << "Data is faulty!";

	cout << endl;
	system("PAUSE");
	return 0;
}