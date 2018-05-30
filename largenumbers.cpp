#include <ostream>
#include <string>
#include <algorithm>
#include <iostream>
using namespace std;

class largenumber
{
	string data;

	void removeleadingzeros()
	{
		int startpos=0;
		if (data[0]=='-')
		{
			startpos=1;
		}
		int len=data.length();

		for (int i=startpos;i<len;i++)
		{
			if ((data[i]=='0')||(data[i]=='+'))	
			{
				data.erase(i,1);
				len=len-1;
				i=startpos-1;
			}
			else
			{
				break;
			}
		}
		if (len==0)
		{
			data.append("0");	
		}
		
	}

	int compare(const largenumber& number)
	{

		string operand1=data;
                string operand2=number.data;

		bool isoperand1positive=true;
		bool isoperand2positive=true;

		if ((operand1[0]=='-'))
		{
			isoperand1positive=false;
		}
		if ((operand2[0]=='-'))
		{
			isoperand2positive=false;
		}

		if ((isoperand1positive==true) && (isoperand2positive==false))
		{
			return 1;
		}
		if ((isoperand1positive==false) && (isoperand2positive==true))
		{
			return -1;
		}

		largenumber op1=*this;
		op1.removeleadingzeros();
		largenumber op2=number;
		op2.removeleadingzeros();

                int operand1len=op1.data.length();
                int operand2len=op2.data.length();		

		operand1=op1.data;
                operand2=op2.data;

		int operand1start=0;
		int operand2start=0;	

		if ((operand1[0]=='+') || (operand1[0]=='-'))
		{
			operand1start=1;
		}
		if ((operand2[0]=='+') || (operand2[0]=='-'))
		{		
			operand2start=1;
		}	


		if ((operand1len-operand1start)>(operand2len-operand2start))
			return 1;
		else if ((operand1len-operand1start)<(operand2len-operand2start))
			return -1;
		else if ((operand1len-operand1start)==(operand2len-operand2start))
		{
			for(int i=operand1start,j=operand2start;i<operand1len&&j<operand2len;i++,j++)
			{
				if (operand1[i]==operand2[j])
					continue;
				else if (operand1[i]>operand2[j])
					return 1;
				else if (operand1[i]<operand2[j])
					return -1;
			}
			return 0;
		}
	}

	int borrow(string &number, int pos)
	{
		int prev = number[pos-1]-'0';
		if (prev > 0)
		{
			prev--;
			number[pos-1]=prev+'0';
			return 1;	
		}
		else if (prev==0)
		{
			int carry=borrow(number,pos-1);
			number[pos-1]='9';
			return 1;	
		}
	}

	bool isaddition(const string& operand1, const string& operand2)
	{
		/*
 		*	+ + addition
 		*	- - addition
 		*	+ 9 addition
 		*	9 + addition
 		*	9 9 addition
 		*/
		if( 
		((operand1[0]=='+') && (operand2[0]=='+')) ||
		((operand1[0]=='-') && (operand2[0]=='-')) ||
		((operand1[0]=='+') && (operand2[0]!='-')) ||
		((operand1[0]!='-') && (operand2[0]=='+')) ||
		((operand1[0]!='-') && (operand2[0]!='-'))
		)
			return true;
		else
			return false;
				

	}

	bool issubtraction(const string& operand1, const string& operand2)
	{
		/*
 		*	+ + subtraction
 		*	- - subtraction
 		*	+ - addition
 		*	- + addition
 		*/

		if(
		((operand1[0]=='+') && (operand2[0]=='+')) ||
		((operand1[0]=='-') && (operand2[0]=='-')) ||
		((operand1[0]!='-') && (operand2[0]=='+')) ||
		((operand1[0]=='+') && (operand2[0]!='-')) ||
		((operand1[0]!='-') && (operand2[0]!='-'))
		)
			return true;
		else
			return false;
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

		largenumber abs() const
		{
			string operand=data;
			if ((operand[0]=='+')||(operand[0]=='-'))
			{
				operand.erase(0,1);
			}
			return largenumber(operand);
		}

		largenumber operator-() const
		{
			string result;
			if (data[0]=='-')
			{
				result.append(data,1,string::npos);
				
			}
			else if (data[0]=='+')
			{
				result.append(string("-"));
				result.append(data,1,string::npos);	
			}
			else	
			{
				result.append(string("-"));
				result.append(data);
			}
			return largenumber(result);	
		}

		largenumber operator+(const largenumber& number)
		{

			string operand1=data;
                        string operand2=number.data;

			bool toadd=isaddition(operand1, operand2);
			
			if (!toadd)
			{
				return this->operator-(-number);
			}

			int operand1len=data.length();
			int operand2len=number.data.length();
			operand1len--; operand2len--;

			bool done=false;

			string result;
			int pos=0;

			int carry=0;

			int operand1start=0;
			int operand2start=0;

			if ((operand1[0]=='+') || (operand1[0]=='-'))
			{
				operand1start=1;
			}

			if ((operand2[0]=='+') || (operand2[0]=='-'))
                        {
                                operand2start=1;
                        }

			while (((operand1len>=operand1start) || (operand2len>=operand2start))) 
			{
				if ((operand1len>=operand1start) && (operand2len>=operand2start))
				{
					int op1 = operand1[operand1len]-'0';
					int op2 = operand2[operand2len]-'0';
					
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

					operand1len--;
					operand2len--;
				}
				else if ((operand1len>=operand1start) && (operand2len<operand2start))
				{
					int op1 = operand1[operand1len]-'0';

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
	
					operand1len--;
				}
				else if ((operand1len<operand1start) && (operand2len>=operand2start))
				{
					int op2 = operand2[operand2len]-'0';
					
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

					operand2len--;
				}
			}
			if (carry==1)
			{
				result.push_back(carry+'0');
			}

			/*
 			* we add only when both the numbers are negative
 			* so first char of both numbers will be negative
 			* we need to check the first one only as the second
 			* will be the same sign as the first one to be added
 			*/
			if ((operand1[0]=='-')) 
			{
				result.push_back('-');
			}
	
			reverse(result.begin(),result.end());
			
			largenumber res(result);
			res.removeleadingzeros();
			return res;
			
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
			int res =  this->compare(number);
			if (res==0)
				return true;
			else
				return false;

		}

		bool operator!=(const largenumber& number)
		{
			int res =  this->compare(number);
			if (res!=0)
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
			int operand1len=data.length();
                        int operand2len=number.data.length();

			string operand1=data;
			string operand2=number.data;

			int operand1start=0;
			int operand2start=0;

			if ((operand1[0]=='+') || (operand1[0]=='-'))
                        {
                                operand1start=1;
                        }

                        if ((operand2[0]=='+') || (operand2[0]=='-'))
                        {
                                operand2start=1;
                        }

			bool isnegative=false;
			if (((operand1[0]=='-') && (operand2[0]!='-'))||((operand1[0]!='-')&& (operand2[0]=='-')))
			{
				isnegative=true;	
			}
		

			largenumber answer("0");
			for(int i=operand2len-1;i>=operand2start;i--)
			{
				int op1=operand2[i]-'0'; 	
				
				int operand1len=operand1.length()-1;
				int carry=0;
				string intermediate;
				while(operand1len>=operand1start)
				{
					int op2=operand1[operand1len--]-'0';
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
			if (isnegative)
			{
				answer=-answer;
			}
			return answer;
		}

		largenumber operator/(const largenumber& number)
		{
			/*
 			* dividend
 			* --------
 			*  divisor
 			*/
                        int dividendlen=data.length();
                        int divisorlen=number.data.length();

			
                        int dividendstart=0;
                        int divisorstart=0;

                        bool isnegative=false;
                        if (((data[0]=='-') && (number.data[0]!='-'))||((data[0]!='-')&& (number.data[0]=='-')))
                        {
                                isnegative=true;
                        }

			largenumber dividend=this->abs();
			largenumber divisor=number.abs();

			string result="0";
			bool done=false;
			int increasedividentlen=0;
			largenumber temp(string(dividend.data,0,divisorlen-divisorstart+increasedividentlen));
			int toerase=divisorlen-divisorstart+increasedividentlen;
			while ((!done))
			{
				bool found=false;	
				largenumber multiplier;
				largenumber prev("0");
				int j;
				for(j=1;j<=10&&!found;j++)	
				{
					string x;
					x.push_back(j+'0');
					largenumber mul(x);
					multiplier=divisor*mul;
					if (multiplier>temp)
					{
						multiplier=prev;
						//if divisor*1 > temp then the divisor is bigger break and consider the next digit also
						if (j==1) break;
						found=true;
					}
					else
					{
						prev=multiplier;
					}

				}

				largenumber diff;
				int difflen;
				if (found)
				{
					result.push_back((j-2)+'0');
					diff=temp-multiplier;
					string value=dividend.data;
					value.erase(0,toerase);
					if (!value.empty()) 
					{
						if (diff!=largenumber("0"))
						{
							string diffval=diff.data;
							value.insert(dividendstart,diffval);
						}
						dividend.data=value;
						largenumber zero("0");
						if (dividend==zero)
						{
							result.append(dividend.data);
							done=true;
						}
						difflen=diff.data.length();
					}
					else
					{
						done=true;
					}
				}
				else
				{
					result.push_back(0+'0');
					difflen=temp.data.length();
				}
				increasedividentlen=1;
				temp=largenumber(string(dividend.data,0,difflen+increasedividentlen));	
				while ((temp<divisor) && (!done))
                                {
                                	increasedividentlen++;
                                	if (difflen+increasedividentlen>dividend.data.length())
                                	{
                                		done=true;
                                	}
                                	else
                                	{
                                		temp=largenumber(string(dividend.data,0,difflen+increasedividentlen));
                                		result.push_back(0+'0');
                                	}
                                }
				toerase=difflen+increasedividentlen;
			}
			if (isnegative)
			{
				result.insert(0,"-");
			}
			largenumber res(result);			

			res.removeleadingzeros();
			
			return res;
		}

		largenumber& operator/=(const largenumber& number)
		{
			largenumber result=this->operator/(number);
                        return this->operator=(result);
		}

                largenumber& operator*=(const largenumber& number)
                {
                        largenumber result=this->operator*(number);
                        return this->operator=(result);
                }

		largenumber operator-(const largenumber& number)
		{
			string operand1=data;
                        string operand2=number.data;

                        bool tosub=issubtraction(operand1, operand2);

                        if (!tosub)
                        {
                                return this->operator+(-number);
                        }


			int operand1len=data.length();
                        int operand2len=number.data.length();

			string result;
			bool isnegative=false;

			/*
 			* operand1 will be the bigger number
 			* operand2 will be the smaller number
 			*/
		
			largenumber absop1=this->abs();
			largenumber absop2=number.abs();		
			
			int comparison=absop1.compare(absop2);
			if (comparison<0)
			{
				//if (operand2[0]=='-')
				{
					isnegative=true;
				}
				operand1=number.data;
				operand2=data;
				int temp;
				temp=operand1len;
				operand1len=operand2len;
				operand2len=temp;
			}
			else if (comparison >0)
			{
				if (operand1[0]=='-')
				{
					isnegative=true;
				}
			}


			operand1len--;operand2len--;

			int operand1start=0;
			int operand2start=0;

		 	if ((operand1[0]=='+') || (operand1[0]=='-'))
                        {
                                operand1start=1;
                        }

                        if ((operand2[0]=='+') || (operand2[0]=='-'))
                        {
                                operand2start=1;
                        }

			
			for (int i=operand2len,j=operand1len;i>=operand2start;i--,j--)
			{
				int op1=operand1[j]-'0';
				int op2=operand2[i]-'0';

				int diff;
				
				if (op1>=op2)
				{
					diff=op1-op2;
				}
				else
				{
					int br = borrow(operand1, j);
					diff = ((br*10)+op1)-op2;
				}
				
				result.push_back(diff+'0');	
			}
			for(int i=(operand1len-(operand2len-operand2start))-1;i>=operand1start;i--)
			{
				result.push_back(operand1[i]);
			}
			if (isnegative)
				result.push_back('-');

			reverse(result.begin(),result.end());

                        largenumber res(result);
                        res.removeleadingzeros();
                        return res;

	
		}

		largenumber& operator-=(const largenumber& number)
                {
                        largenumber result=this->operator-(number);
                        return this->operator=(result);
                }

                largenumber& operator--()
                {
                        largenumber dec("1");
                        largenumber result=this->operator-(dec);
                        return this->operator=(result);

                }
                largenumber operator--(int dummy)
                {
                        largenumber temp=*this;
                        largenumber dec("1");
                        largenumber result=this->operator-(dec);
                        this->operator=(result);
                        return temp;
                }



};

ostream& operator<< (ostream &os, const largenumber& number)
{
	os << number.data;
	return os;
}

int main()
{
	largenumber n1(string("78236783467856782357438134878634786238456782634587627834657862345786782356782634675126582899835489734895728973458972358972893457892743589724839578294735897234588293745892734895702983475089723458967823456672567456256523465672354623402934950292378231234567891011121314151617181920"));
	largenumber n2(string("-5623679287382239212767864782687678246345234564256345642323652467524589298924635924735678623457863457783456783567023909820393"));


	cout << n2*n1/n2 << endl;



}
