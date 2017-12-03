bool isspace(char ch)
{
	if(ch == 32)return true;
	return false;
}
/*

这个函数是把浮点数字符串转换为浮点数的函数。

函数将会跳过字符串中的空格字符和不是'+'、'-'、'.'、

数字的字符。如果字符串是空的或者都是由空格组成，将不会

做任何转换，仅仅是把字符串的结束地址赋给endptr。如果字

符串合法，将会进行转换，并把字符串最后的NULL的地址给

endptr。如果你想使用endptr参数，那么赋一个NULL值就

可以了。

*/

double my_strtod(const char* s, char** endptr) 

{

	register const char*  p     = s;

	register long double  value = 0.L;

	int                   sign  = 0;
	//char sign;
	long double           factor;

	unsigned int          expo;

	

	while ( isspace(*p) )//跳过前面的空格
		p++;

	if(*p == '-' || *p == '+')
		sign = *p++;//把符号赋给字符sign，指针后移。

	//处理数字字符
	while ( (unsigned int)(*p - '0') < 10u )//转换整数部分
		value = value*10 + (*p++ - '0');

	//如果是正常的表示方式（如：1234.5678）

	if ( *p == '.' ) 
	{
		factor = 1.;
		p++;

		while ( (unsigned int)(*p - '0') < 10u ) //收集小数
		{
			factor *= 0.1;
			value  += (*p++ - '0') * factor;
		}
	}

	//如果是IEEE754标准的格式（如：1.23456E+3）
	//if ( (*p | 32) == 'e' ) 
	if ( tolower(*p) == 'e' ) 
	{ 
		expo   = 0;
		factor = 10.L;

		switch (*++p)
		{ 
			case '-': 
				factor = 0.1;
			case '+': 
				p++;
				break;
			case '0': 
			case '1': 
			case '2':
			case '3':
			case '4': 
			case '5': 
			case '6': 
			case '7': 
			case '8': 
			case '9':
				break;
			default : 
				value = 0.L;
				p = s;
				goto done;

		}

		while ( (unsigned int)(*p - '0') < 10u )//收集指数
			expo = 10 * expo + (*p++ - '0');

		while (1)
		{
			if ( expo & 1 )
				value *= factor;
			if ( (expo >>= 1) == 0 )
				break;
			factor *= factor;
		}
	}

done:

	if ( endptr != 0 )

		*endptr = (char*)p;



	return (sign == '-' ? -value : value);

}

double my_atof(char *str)

{

	return my_strtod(str,0);

}

