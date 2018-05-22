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
					int sum;

					if (res>=10)
					{
						sum = res-10;
						carry = 1;
					}
					else
					{
						sum=res;
						carry=0;	
					}

					result.push_back(sum+'0');

					thislen--;
					operandlen--;
				}
				else if ((thislen>=0) && (operandlen<0))
				{
					int op1 = data[thislen]-'0';

					int res = op1+carry;
					int sum;

                                        if (res>=10)
                                        {
                                                sum = res-10;
                                                carry = 1;
                                        }
                                        else
                                        {
                                                sum=res;
                                                carry=0;
                                        }



					result.push_back(sum+'0');
	
					thislen--;
				}
				else if ((thislen<0) && (operandlen>=0))
				{
					int op2 = number.data[operandlen]-'0';
					
					int res = op2+carry;
					int sum;

                                        if (res>=10)
                                        {
                                                sum = res-10;
                                                carry = 1;
                                        }
                                        else
                                        {
                                                sum=res;
                                                carry=0;
                                        }



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

		largenumber operator*(const largenumber& number)
		{
			int thislen=data.length();
                        int operandlen=number.data.length();

			string operand1=data;
			string operand2=number.data;

			largenumber answer("0");
			for(int i=operandlen-1;i>=0;i--)
			{
				int op1=operand2[i]-'0'; 	
				
				int thislen=operand1.length()-1;
				int carry=0;
				string intermediate;
				while(thislen>=0)
				{
					int op2=operand1[thislen--]-'0';
					int result = (op1*op2)+carry;
					int sum=result%10;
					carry=result/10;
					
					intermediate.push_back(sum+'0');
				}
				if (carry!=0)
					intermediate.push_back(carry+'0');

				reverse(intermediate.begin(),intermediate.end());

				answer+=intermediate;
				operand1.push_back(0+'0');
			}

			return answer;
		}

                largenumber& operator*=(const largenumber& number)
                {
                        largenumber result=this->operator*(number);
                        return this->operator=(result);
                }


};

ostream& operator<< (ostream &os, const largenumber& number)
{
	os << number.data;
	return os;
}

int main()
{
	largenumber n1(string("99999999999999999999999999999999999999999999999999999999999999999999999999"));
	largenumber n2(string("1017230988098097623161348123767234781823461782316523651902367861278346"));

	n1*=n2;

	cout << n1;	

}
