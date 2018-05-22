#include <ostream>
#include <string>
#include <algorithm>
#include <iostream>
using namespace std;

class largenumber
{
	string data;

	int compare(const largenumber& number)
	{
		int thislen=data.length();
		int operandlen=number.data.length();
	
		if (thislen>operandlen)
			return 1;
		else if (thislen<operandlen)
			return -1;
		else if (thislen==operandlen)
		{
			for(int i=0;i<thislen;i++)
			{
				if (data[i]==number.data[i])
					continue;
				else if (data[i]>number.data[i])
					return 1;
				else if (data[i]<number.data[i])
					return -1;
			}
			return 0;
		}
	}
	public:
		largenumber()
		{
		}
		largenumber(const string& number)
		{
			data=number;
		}
		largenumber(const largenumber& number)
		{
			data=number.data;
		}
		largenumber& operator=(const string& number)
		{
			data=number;
			return *this;
		}
		largenumber& operator=(const largenumber& number)
		{
			data=number.data;
			return *this;
		}
		largenumber operator+(const largenumber& number)
		{
			int thislen=data.length();
			int operandlen=number.data.length();
			thislen--; operandlen--;

			bool done=false;

			string result;
			int pos=0;

			int carry=0;
			while (((thislen>=0) || (operandlen>=0))) 
			{
				if ((thislen>=0) && (operandlen>=0))
				{
					int op1 = data[thislen]-'0';
					int op2 = number.data[operandlen]-'0';
					
					int res = op1+op2+carry;
					int sum = res%10;
					carry = res/10;

					result.push_back(sum+'0');

					thislen--;
					operandlen--;
				}
				else if ((thislen>=0) && (operandlen<0))
				{
					int op1 = data[thislen]-'0';

					int res = op1+carry;
					int sum = res%10;
					carry = res/10;

					result.push_back(sum+'0');
	
					thislen--;
				}
				else if ((thislen<0) && (operandlen>=0))
				{
					int op2 = number.data[operandlen]-'0';
					
					int res = op2+carry;
                                        int sum = res%10;
                                        carry = res/10;

					result.push_back(sum+'0');

					operandlen--;
				}
			}
			if (carry==1)
			{
				result.push_back(carry+'0');
			}
	
			reverse(result.begin(),result.end());
			return largenumber(result);
		}

		largenumber& operator+=(const largenumber& number)
		{
			largenumber result=this->operator+(number);
			return this->operator=(result);
		}

		largenumber& operator++()
		{
			largenumber inc("1");
			largenumber result=this->operator+(inc);
			return this->operator=(result);
				
		}
		largenumber operator++(int dummy)
		{
			largenumber temp=*this;
			largenumber inc("1");
			largenumber result=this->operator+(inc);
			this->operator=(result);
			return temp;
		}

		bool operator==(const largenumber& number)
		{
			if (data==number.data)
				return true;
			else
				return false;
		}

		bool operator>=(const largenumber& number)
		{
			int res = this->compare(number);
			if (res>=0)
				return true;
			else
				return false;
			
		}

		bool operator<=(const largenumber& number)
		{
			int res = this->compare(number);
			if (res<=0)
				return true;
			else
				return false;
		}

		bool operator>(const largenumber& number)
		{
			int res = this->compare(number);
			if (res>0)
				return true;
			else
				return false;
		}

		bool operator<(const largenumber& number)
		{
			int res = this->compare(number);
			if (res<0)
				return true;
			else
				return false;
		}

		friend ostream& operator<< (ostream &os, const largenumber& number);

};

ostream& operator<< (ostream &os, const largenumber& number)
{
	os << number.data;
	return os;
}

int main()
{
	largenumber n1(string("999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"));
	largenumber n2(string("999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"));

	for (largenumber x=n2;x<n1;x++)
	{
		cout << x <<endl;
	}
	

}
