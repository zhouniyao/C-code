#include <iomanip> 

/*
*��֤����cin�������������ո������
*���Ҷ����ո�����������в������ݣ�
*�������ֱ�Ӵӻ�������ȡ���ݡ�
**��������Enter��Space��Tab��
*/
void cinDisplay()
{
	char str[10],str2[10];
	//cin.getline(str,5);
	cin>>str;
	cin>>str2;
	cout<<str<<endl;
	
	cout<<str2<<endl;
}
/*
*cin.get(�����������ȣ�������)
*���÷���������Ϊ��ѡ������������ַ��������Ϊ�����鳤��-1�������������涨�����ַ�����ȡ���ַ���Ĭ��ΪENTER
*��Ҫ��ȡ�ַ���ֱ��cin.get(char ch)��ch=cin.get()����
*��Enter�����������⣬������������Ȼ�ڻ������С�
*/
void cingetDisplay()
{
	/*
	char c1,c2;
	cin.get(c1);
	cin.get(c2);
	cout<<c1<<"    "<<c2<<endl;
	cout<<(int)c1<<"    "<<(int)c2<<endl;
	*/
	char ch[50];
	int i=0;
	cin.get(ch,49,'\n');
	//cout<<ch;
	for(;ch[i]!='\0';i++)//�ַ���������'\0'������
		cout<<ch[i];
	cout<<"##"<<(int)ch[i];//��ʾ'\0'��ASCIIֵ0��

}
/*
	cin.clear();   //cin.fail()����0������ѭ��¼�룬��������ѭ����

	cin.sync();   //�����

*/
//============================================
//cout��ʽ�����
//============================================
void coutDisplay()
{
//=================================================================
///*���ڸ������ĸ�ʽ*/ 
	/*
	�������� ���˫��������
    double a=123.456789012345;  // ��a����ֵ
		1) cout<<a;  ����� 123.456
		2) cout<<setprecision(9)<<a;  ����� 123.456789
		3) cout<<setprecision(6);  �ָ�Ĭ�ϸ�ʽ(����Ϊ6)
		4) cout<< setiosflags(ios��fixed);  ����� 123.456789
		5) cout<<setiosflags(ios��fixed)<<setprecision(8)<<a;  ����� 123.45678901
		6) cout<<setiosflags(ios��scientific)<<a;  ����� 1.234568e+02
		7) cout<<setiosflags(ios��scientific)<<setprecision(4)<<a;  ����� 1.2346e02
	*/
	//================================

	float f=2.0/3.0,f1=0.000000001,f2=-9.9;

	cout<<f<<' '<<f1<<' '<<f2<<endl; //�������

	cout.setf(ios::showpos); //ǿ��������ǰ��+�� 

	cout<<f<<' '<<f1<<' '<<f2<<endl; 

	cout.unsetf(ios::showpos); //ȡ������ǰ��+�� 

	cout.setf(ios::showpoint); //ǿ����ʾС��������Ч0

	cout<<f<<' '<<f1<<' '<<f2<<endl; 

	cout.unsetf(ios::showpoint); //ȡ����ʾС��������Ч0

	cout.setf(ios::scientific); //��ѧ������ 

	cout<<f<<' '<<f1<<' '<<f2<<endl; 

	cout.unsetf(ios::scientific); //ȡ����ѧ������

	cout.setf(ios::fixed); //���������ʾ 

	cout<<f<<' '<<f1<<' '<<f2<<endl; 

	cout.unsetf(ios::fixed); //ȡ�����������ʾ 

	cout.precision(18); //����Ϊ18������Ϊ6 

	cout<<f<<' '<<f1<<' '<<f2<<endl; 

	cout.precision(6); //���Ȼָ�Ϊ6 
	//===========================================================
	//�����ʽ�����������
	//===========================================================
	float f=2.0/3.0,f1=0.000000001,f2=-9.9;

	cout<<f<<' '<<f1<<' '<<f2<<endl; //�������

	cout<<setiosflags(ios::showpos); //ǿ��������ǰ��+��

	cout<<f<<' '<<f1<<' '<<f2<<endl; 

	cout<<resetiosflags(ios::showpos); //ȡ������ǰ��+��

	cout<<setiosflags(ios::showpoint); //ǿ����ʾС��������Ч0

	cout<<f<<' '<<f1<<' '<<f2<<endl; 

	cout<<resetiosflags(ios::showpoint); //ȡ����ʾС��������Ч0

	cout<<setiosflags(ios::scientific); //��ѧ������

	cout<<f<<' '<<f1<<' '<<f2<<endl; 

	cout<<resetiosflags(ios::scientific); //ȡ����ѧ������

	cout<<setiosflags(ios::fixed); //���������ʾ

	cout<<f<<' '<<f1<<' '<<f2<<endl; 

	cout<<resetiosflags(ios::fixed); //ȡ�����������ʾ

	cout<<setprecision(18); //����Ϊ18������Ϊ6 

	cout<<f<<' '<<f1<<' '<<f2<<endl; 

	cout<<setprecision(6); //���Ȼָ�Ϊ6 



//=================================================================
//�������
//=================================================================
	int x=30, y=300, z=1024; 

	cout<<x<<' '<<y<<' '<<z<<endl; //��ʮ�������

	cout.unsetf(ios::dec ); //ȡ��ʮ�����������

	cout.setf(ios::showbase | ios::uppercase); //���û�ָʾ���������ֵ�е���ĸ��д���

	cout<<x<<' '<<y<<' '<<z<<endl; 

	cout.unsetf(ios::showbase | ios::uppercase); //ȡ����ָʾ���������ֵ�е���ĸ��д���

	cout.setf(ios::oct); //����Ϊ�˽������,�����ò�ȡ��һֱ��Ч

	cout<<x<<' '<<y<<' '<<z<<endl; //���˽������

	cout.setf(ios::showbase | ios::uppercase); //���û�ָʾ���������ֵ�е���ĸ��д���

	cout<<x<<' '<<y<<' '<<z<<endl; 

	cout.unsetf(ios::showbase | ios::uppercase); //ȡ����ָʾ���������ֵ�е���ĸ��д���

	cout.unsetf(ios::oct); //ȡ���˽���������ã��ָ���ʮ�������

	cout.setf(ios::hex); //����Ϊʮ��������� 

	cout<<x<<' '<<y<<' '<<z<<endl; 

	cout.setf(ios::showbase | ios::uppercase); //���û�ָʾ���������ֵ�е���ĸ��д���

	cout<<x<<' '<<y<<' '<<z<<endl; 

	cout.unsetf(ios::showbase | ios::uppercase); //ȡ����ָʾ���������ֵ�е���ĸ��д���

	cout.unsetf(ios::hex); //ȡ��ʮ������������ã��ָ���ʮ�������

	cout<<x<<' '<<y<<' '<<z<<endl; 

	//==========================================================
	//���������������
	//==========================================================
	cout<<x<<' '<<y<<' '<<z<<endl; //��ʮ�������

	cout<<oct<<x<<' '<<y<<' '<<z<<endl; //���˽������

	cout<<setiosflags(ios::showbase); //���û�ָʾ��

	cout<<x<<' '<<y<<' '<<z<<endl; //�԰��˽������

	cout<<resetiosflags(ios::showbase); //ȡ����ָʾ��

	cout<<hex<<x<<' '<<y<<' '<<z<<endl; //��ʮ���������

	cout<<setiosflags(ios::showbase | ios::uppercase);

	//���û�ָʾ������ֵ�е���ĸ��д����� 

	cout<<x<<' '<<y<<' '<<z<<endl; //�԰�ʮ���������

	cout<<resetiosflags(ios::showbase | ios::uppercase);

	//ȡ����ָʾ������ֵ�е���ĸ��д��� 

	cout<<x<<' '<<y<<' '<<z<<endl; //�԰�ʮ���������

	cout<<dec<<x<<' '<<y<<' '<<z<<endl; //��ʮ�������

}
/*
��c/c++ϵͳ�г��˱�׼����������⣬���ṩ�˸�������뺯������д������Ҫ��getch(),getche(),

getchar 

(),cin.get(),putch(),putchar(),cout.put(),gets(),cin.getline(),puts()������

����ЩΪ���û�������Ӱ��������ȷ�����Ļ���ȥ�Ĳ������磺cin.putback(),fflush(stdin),cout.flush().����

��һ�¼򵥵�˵���� 

1��getch()��getche(),�ǻ���ʽ���룬�Ӽ��̶���һ���ַ���getch()�����ַ�����ʾ����conio.h֧�֡�

2��cin.get(),getchar()������ʽ���룬�Ӽ��̶���һ���ַ�������ʾ��getchar()��stdio.h֧�֣�cin.get()��iostream.h֧�֡�

3��putch()��putchar()���ǻ���ʽ��������һ���ַ�����ʾ����putch()��conio.h֧�֣�putchar()��stdio.h֧�֡�

4��cout.put()������ʽ��������һ���ַ�����ʾ������iostream.h֧�֡�

5��gets()��cin.geline()������ʽ���룬����һ�ַ����������ո񣬲��������Ļس�����gets()��stdio.h֧�֣�cin.getline()��iostream.h֧�֡�

6��puts()���ǻ�����������һ���ַ�������stdio.h֧�֡� 

7��cin.putback()����һ���ַ��ͻ����뻺������ 

8��fflush(stdin)��������뻺�����������޷����cin.get()�ȴ����Ĳ�����

9��cout.flush()���������������� 


*/