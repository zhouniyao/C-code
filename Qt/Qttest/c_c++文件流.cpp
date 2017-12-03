#include <QCoreApplication>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <iostream>
using namespace  std;
//C++文件流练习
int
main()
{
    ofstream outf("f3.dat", ios::binary);//二进制输出文件流
    if(!outf)
    {
        cout<<"Cannot open file\n";
        exit(1);

    }
    char ch = 'a';
    for (int i=0; i<=26;i++)
    {
        outf.put(ch);//向标准【屏幕】文件输出单个字符
        ch++;

    }
//    outf.put(13);
//    outf.put(10);
    outf.close();

    ifstream inf("f3.dat", ios::binary);//二进制输入文件流
    if(!inf)
    {
        cout<<"Cannot open input file\n";
        exit(1);

    }
    char ch2;
    while(inf.get(ch2))
    {
        cout<<ch2;
    }
    inf.close();
//    int iarray[2] = {65, 10};
//    ofstream fout("f3.dat",ios::out);
//    //fout<<iarray[0]<<endl<<iarray[1]<<endl;
//    fout.write((char*)iarray, sizeof(iarray));
//    fout.close();

//    ifstream fin("f3.dat",ios::in);
//    char str[512];
//    fin.read(str, sizeof(iarray));
////    int i = 0;
////    while(!fin.eof())

////    {
////        fin.get(str[i]);
////        i++;
////    }
//   // fin.getline(str,512);
//    //str[i]='\0';
//    cout<<str<<endl;
//    fin.close();
////    ofstream fout1("test1.dat", ios::out);
////    if(!fout1)
////    {
////        cout<<"Cannot open output file.\n";
////        exit(1);
////    }
////    fout1<<"I am a student too";
////    fout1.close();

////    ifstream fin1("test1.dat",  ios::in );
////    if(!fin1)
////    {
////        cout<<"Cannot open input file.\n";
////        exit(1);
////    }
////    char str[512];
////    char ch;
//////    fin1.getline(str, 512);
//////    cout<<str<<endl;
////    while(! fin1.eof())
////    {
////        fin1.get(ch);
////        cout.put(ch);
////    }
////    //cout.put(ch);
    return 0;
}

//c语言文件流练习
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#define SIZE 5
//typedef struct sysuser{
//	char username[20];
//	char password[10];
//}USER;
//void encrypt(char *pwd)
//{
//	char ch;
//	char *s = pwd;
//	while(*s)
//	{
//		ch = *s;
//		*s = ch ^ 15;
//		s++;
//	}
//}
//int main(void)
//{
//	FILE* fp;
//	int i;
//	void encrypt(char *pwd);//提前引用声明
//	USER u[SIZE], su[SIZE], *pu = u, *psu = su;
//	if(!(fp = fopen("f12-52.dat", "wb+")))
//	{
//		printf("File open failure! ");
//		exit(EXIT_FAILURE);
//	}
//	//for(i=0; i<SIZE; i++,pu++)
//	//{
//	//	printf("Enter%dth system-user(name password): ", i );
//	//	scanf("%s%s", pu->username, pu->password);
//	//	//fprintf(fp, "%s , %s\n", pu->username, pu->password );
//	//	encrypt(pu->password);
//	//}
//	for(i=0; i<SIZE; i++)
//	{
//		printf("Enter%dth system-user(name password): ", i );
//		scanf("%s%s", u[i].username,u[i].password);
//		//fprintf(fp, "%s , %s\n", pu->username, pu->password );
//		encrypt(u[i].password);
//	}
//	//pu = u;//回到初始位
//	fwrite(pu, sizeof(USER), SIZE, fp);//写入二进制文件
//	rewind(fp);//回头
//	fread(psu, sizeof(USER), SIZE, fp);//按大小为sizeof(USER)，数量为SIZE个记录，读取fp，保存至psu结构数组内
//	for(i=0; i<SIZE; i++,psu++)
//		printf("%s , %s\n", psu->username, psu->password);//格式化标准输出
//	fclose(fp);
//	//void encrypt(char *pwd);
//	//USER stu;
//	//if((fp = fopen("student1.txt", "w")) == NULL)
//	//{
//	//	printf("File open error!\n");
//	//	exit(EXIT_FAILURE);
//	//}
//	//for(i=0; i<3; i++)
//	//{
//	//	printf("Enter %d th systerm-user(name password):\n", i);
//	//	scanf("%s%s",stu.username,stu.password);
//	//	encrypt(stu.password);
//	//	fprintf(fp, "%s, %s\n", stu.username,stu.password);
//	//}
//	//fclose(fp);
///*	long num;
//	char stname[20];
//	int i, score;
//	int avg_score = 0;
//	if((fp = fopen("student.txt", "r")) == NULL)
//	{
//		printf("File open error!\n");
//		exit(EXIT_FAILURE);
//	}
//	for(i = 0; i < 3; i++)
//	{
//		fscanf(fp, "%ld%s%d",&num,stname,&score);
//		avg_score += score;
//		printf("%ld  %s  %d\n", num, stname, score);
//	}
//	printf("Average score: %d\n", avg_score/i);
//	if(fclose(fp))
//	{
//		printf("Can not close the file!\n");
//
//		exit(EXIT_FAILURE);
//	}*/
//	return 0;
//}

//管绍春——绘彩色图
//#include <stdio.h>
//#include<cmath>
//#include<cstdlib>
//#define DIM 70
//#define DM1 (DIM-1)
//#define _sq(x) ((x)*(x))
//#define _cb(x) abs((x)*(x)*(x))

//#define _cr(x) (unsigned char)(pow((x),1.0/3.0))
// unsigned char GR(int i,int j);
// unsigned char BL(int i,int j);

//unsigned char RD(int i,int j)
//{
//    static double k;
//   // srand(i+j);
//    k+=1024*rand()/RAND_MAX;
//    int I=k; I%=512;return I>255?511-I:I;

//}
//unsigned char GR(int i, int j){

//     static double k;
//     //srand(i+j);
//    k+=1024*rand()/RAND_MAX;
//     int I=k;I%=512;return I>255?511-I:I;
// }
//unsigned char BL(int i,int j){

//     static double k;
//    // srand(i+j);
//     k+=1024*rand()/RAND_MAX;
//     int I=k;I%=512;return I>255?511-I:I;
// }
// void pixel_write(int i,int j);
// FILE*fp;
// int main  ()
// {
//     char ch = '\n';
//     fp=fopen("MathPic.ppm","wb");
//     fprintf(fp,"P6\n%d%d\n255\n",1,DIM);//此处设置图像长宽
//     for (int j=0;j<=DIM;j++)
//     {
//         for(int i=0;i<=DIM;i++)
//             pixel_write(i,j);
//         // fwrite(&ch,1,1,fp);
//     }
//    fclose(fp);
//    return 0;
// }

//void pixel_write(int i,int j)
//{
//    static unsigned char color [3];
//    color[0]=RD(i,j);//图像RGB
//    color[1]=GR(i,j);
//    color[2]=BL(i,j);

//    //for(int k = 0; k <= 3; k++)
//    //	fwrite ((const void *)&color[k],1,1,fp);
//    if( fwrite(color, 1, 3, fp) != 3)printf("error!!!!");
//}

////使用用户自定义的操纵符进行输入输出格式控制
//ostream &z1(ostream &ss)
//{
//    ss<<setfill('*')<<hex<<setw(20);
//    return ss;
//}
//istream &z2(istream &ii)
//{
//    ii>>dec;
//    cout<<"Enter number using hex format: ";
//    return ii;
//}

////操纵符进行输入输出格式控制
//int main()
//{
//   int x = 1234;
//   // cout<<setiosflags(ios::scientific | ios::left | ios::showpos)<<x<<endl;//科学计数法|左对齐|显示+-号

//    //cout<<setw(10)<<setiosflags(ios::showpos)<<setfill('&')<<internal<<x<<endl;//在符号与数字之间插入指定的填充符，并指定宽度，超过宽度截断且四舍五入。
////    cout<<"=============================================================="<<endl;
////    cout<<setfill('#');//设置填充符为#一直有效。
////    cout<<setw(10)<<123<<4567<<endl;
////    cout<<123<<setiosflags(ios::scientific)<<setw(20)<<123.456789<<endl;
////    cout<<123<<setw(10)<<hex<<123<<x<<endl;//16进制
////    cout<<123<<setw(10)<<oct<<123<<x<<endl;//8进制
////    cout<<123<<setw(10)<<dec<<123<<x<<endl;//恢复默认的十进制
////    cout<<resetiosflags(ios::scientific )<<fixed<<setprecision(4)<<123.456789<<endl;//取消科学计数法，设置有效位4，最后一位有效位四舍五入
////    cout<<setiosflags(ios::left)<<setfill('@')<<setw(8)<<123<<endl;//
////    cout<<resetiosflags(ios::left)<<setfill('$')<<setw(8)<<456<<endl;
//double i;
//cin>>z2>>i;
//cout<<"hex: "<<hex<<i<<"-------dec: "<<dec<<i<<" -----oct: "<<oct<<i<<endl;

//    return 0;
//}




////十进制TO十六进制
//void
//binaryToASCII(unsigned int value)
//{
//    if(!value)exit(0);
//    unsigned int quotient;
//    quotient = value / 16;
//    if(quotient != 0)
//        binaryToASCII(quotient);

//   int remain = value%16;
//    if(remain < 10)
//        putchar (remain + '0');
//    else
//        putchar (remain + 'A');
//}



//int //文件流
//main()
//{
//    ostringstream strbuf;
//    int lucky = 8;
//    float pi = 3.1415;
//    double e = 2.17;
//    cout<<"An in-memory stream"<<endl;
//    strbuf<<"luckynumber: "<<lucky<<endl
//            <<"pi: "<<pi<<endl
//              <<"e: "<<e<<endl;
//    string strval = strbuf.str();
//    cout<<strval;
//    ofstream outf;
//    outf.open("mydata");
//    outf<<strval;
//    outf.close();

//    cout<<"Read data from the file - watch for errors."<<endl;
//    string newstr;
//    ifstream inf;
//    inf.open("mydata");
//    if(inf)
//    {
//        int lucky2;
//        inf>>newstr>>lucky2;
//        cout<<newstr<<lucky2<<endl;

//        float pi2;
//        inf>>newstr>>pi2;
//        cout<<newstr<<pi2<<endl;

//        double e2;
//        inf>>newstr>>e2;
//        cout<<newstr<<e2<<endl;
//        inf.close();

//    }

//    return 0;
//}


//int main(int argc, char *argv[])
//{
//    QCoreApplication a(argc, argv);
////    char *strings[] = {{"me"},{"have"},{"an"},{"wonderful"},{"family"}};
////    char value = 'z';
////    if(findChar(strings, value))
////        cout<<"OK"<<endl;
////    else
////        cout<<"FAILE"<<endl;
////    while(*argv != NULL)
////    //while(*argv)
////    {
////        cout<<*argv++<<endl;
////        //(argv)++;
////    }
////mystery(-4);
//int ch = 12345;
//binaryToASCII(ch);
//    return a.exec();
//}


//#include<QApplication>
//#include<QVBoxLayout>
//#include<QLabel>
//#include<QPushButton>

//int main(int argc,char *argv[])
//{
//QApplication app(argc,argv);

//QWidget *window = new QWidget;
//window->setWindowTitle("QtTest");

////QLabel *label= new QLabel("Hello Qt");
//QLabel *label = new QLabel("<h2><i>Hello</i>"" <font color = red>Qt</font><h2>");

//QPushButton *button=new QPushButton("Quit");
//QObject::connect(button,SIGNAL(clicked()),&app,SLOT(quit()));

//QVBoxLayout *layout=new QVBoxLayout;
//layout->addWidget(label);
//layout->addWidget(button);
//window->setLayout(layout);

//window->show();

//return app.exec();
//}
//int
//findChar(char **strings, char value)
//{
//    char *string;
//    while((string = *strings++) != NULL)
//    {
//        //while(*string++ != NULL)
//        while(*string++)
//            if(*string == value)return 1;
//    }
//    return 0;

//}

int
findChar(char **strings, char value)
{
    if(strings == NULL)return 0;
    while(*strings )
    {
        while(**strings )
        {
            if(**strings == value)
                return 1;
           (*strings)++;
        }

         strings++;
    }
    return 0;
}
