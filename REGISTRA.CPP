#include <stdio.h>
#include <fstream.h>
#include <stdlib.h>
#include <conio.h>
#include <graphics.h>
#include <string.h>
#include <dos.h>
#include <ctype.h>
static int count=0;
struct det
{
char p[80];
char u[80];
};
union REGS in,out;
class reg
{
  int xmax,ymax;
  int gmode,errorcode,gdriver;
  public:
  reg()
  {
    gdriver=DETECT;
    gmode=0,errorcode=0;
    initgraph(&gdriver,&gmode,"C:\\TURBOC3\\BGI");
    errorcode=graphresult();
    if(errorcode!=grOk)
    {
      printf("Graphics error : %s\n",grapherrormsg(errorcode));
      printf("Press any key to exit\n");
      delay(4000);
      exit(0);
    }
    in.x.ax=0;
    int86(0x33,&in,&out);
    if(out.x.ax==0)
    {
      printf("Mouse support not available\n");
      printf("Press any key to exit\n");
      delay(4000);
      exit(0);
    }
    in.x.ax=1;
    int86(0x33,&in,&out);
    in.x.ax=3;
    xmax=getmaxx();
    ymax=getmaxy();
    setfillstyle(1,0);
    setcolor(WHITE);
  }
  void login();
  void signup();
  void menu();
  int authen(char *,char *);
};
void reg::signup()
{
  clrscr();
  bar(0,0,xmax,ymax);
  printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t");
  line(xmax/2-165,ymax/2-70,xmax/2-165,ymax/2+130);
  line(xmax/2-165,ymax/2-70,xmax/2+155,ymax/2-70);
  line(xmax/2-165,ymax/2+130,xmax/2+155,ymax/2+130);
  line(xmax/2+155,ymax/2-70,xmax/2+155,ymax/2+130);
  line(xmax/2-165,ymax/2-30,xmax/2+155,ymax/2-30);
  line(xmax/2-165,ymax/2+50,xmax/2+155,ymax/2+50);
  outtextxy(xmax/2-155,ymax/2-50,"Sign-up !!!, Input with your details :");
  outtextxy(xmax/2-155,ymax/2-10,"              Username");
  outtextxy(xmax/2-155,ymax/2+70,"              Password");
  struct det ob;
  scanf("%[^\n]",ob.u);
  fflush(stdin);
  printf("\n\n\n\n\t\t\t");
  line(xmax/2-165,ymax/2-70,xmax/2-165,ymax/2+130);
  scanf("%[^\n]",ob.p);
  fflush(stdin);
  if(authen(ob.p,ob.u)==1)
  {
  outtextxy(xmax/2-100,ymax/2+150,"No special character allowed(Except _ )");
  delay(4000);
  signup();
  }
  fstream f1;
  f1.open("d",ios::in|ios::binary);
  struct det ob1;
  while(f1.eof()==0)
  {
  f1.read((char *)&ob1,sizeof(ob1));
  if(strcmp(ob.u,ob1.u)==0)
  {
  outtextxy(xmax/2-100,ymax/2+150,"Username already taken !!!");
  delay(4000);
  signup();
  }
  }
  f1.close();
  fstream f;
  f.open("d",ios::out|ios::ate|ios::binary);
  f.write((char *)&ob,sizeof(ob));
  f.close();
  bar(0,0,xmax,ymax);
  outtextxy(xmax/2-70,ymax/2,"SIGNUP SUCCESSFUL");
  delay(4000);
  exit(0);
}
int reg::authen(char p[],char u[])
{
int j=0,k=0,pl=0,ul=0;
pl=strlen(p);
  ul=strlen(u);
  k=(pl>ul)?pl:ul;
  for(int i=0;i<k;i++)
  {
  if(i<pl&&isalnum(p[i])==0&&p[i]!='_')
  {
  j=1;
  break;
  }
  if(i<ul&&isalnum(u[i])==0&&u[i]!='_')
  {
  j=1;
  break;
  }
  }
  if(strcmp(u,"")==0||strcmp(p,"")==0||j==1)
  {
  return 1;
  }
  return 0;
}
void reg::login()
{
  char m[80]={'\0'};
  if(count==5)
  {
  bar(0,0,xmax,ymax);
  outtextxy(xmax/2-70,ymax/2,"CAN'T LOG-IN. PLEASE TRY AGAIN LATER.");
  delay(4000);
  menu();
  }
  char pa[80]={'\0'},us[80]={'\0'};
  clrscr();
  bar(0,0,xmax,ymax);
  printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t");
  line(xmax/2-165,ymax/2-70,xmax/2-165,ymax/2+130);
  line(xmax/2-165,ymax/2-70,xmax/2+155,ymax/2-70);
  line(xmax/2-165,ymax/2+130,xmax/2+155,ymax/2+130);
  line(xmax/2+155,ymax/2-70,xmax/2+155,ymax/2+130);
  line(xmax/2-165,ymax/2-30,xmax/2+155,ymax/2-30);
  line(xmax/2-165,ymax/2+50,xmax/2+155,ymax/2+50);
  outtextxy(xmax/2-155,ymax/2-50,"Log-in !!!, Input with your details :");
  outtextxy(xmax/2-155,ymax/2-10,"              Username");
  outtextxy(xmax/2-155,ymax/2+70,"              Password");
  scanf("%[^\n]",us);
  fflush(stdin);
  printf("\n\n\n\n\t\t\t");
  line(xmax/2-165,ymax/2-70,xmax/2-165,ymax/2+130);
  scanf("%[^\n]",pa);
  fflush(stdin);
  if(authen(pa,us)==1)
  {
  count++;
  outtextxy(xmax/2-100,ymax/2+150,"No special character allowed(Except _ )");
  sprintf(m,"%d tries left",(5-count));
  outtextxy(xmax/2-100,ymax/2+170,m);
  delay(4000);
  login();
  }
  fstream f3;
  struct det ob;
  f3.open("d",ios::in||ios::binary);
  while(f3.eof()==0)
  {
  f3.read((char *)&ob,sizeof(ob));
  if(strcmp(ob.u,us)==0&&strcmp(ob.p,pa)==0)
  {
  bar(0,0,xmax,ymax);
  outtextxy(xmax/2-70,ymax/2,"LOG-IN SUCCESSFUL");
  f3.close();
  delay(4000);
  exit(0);
  }
  }
  count++;
  outtextxy(xmax/2-100,ymax/2+150,"Username or Password incorrect !!!");
  sprintf(m,"%d tries left",(5-count));
  outtextxy(xmax/2-100,ymax/2+170,m);
  delay(4000);
  f3.close();
  login();
}
void reg::menu()
{
bar(0,0,xmax,ymax);
line(xmax/2-100,ymax/2-10,xmax/2-100,ymax/2+20);
line(xmax/2-100,ymax/2-10,xmax/2-25,ymax/2-10);
line(xmax/2-100,ymax/2+20,xmax/2-25,ymax/2+20);
line(xmax/2-25,ymax/2-10,xmax/2-25,ymax/2+20);
outtextxy(xmax/2-90,ymax/2+3,"Sign-up");
line(xmax/2-10,ymax/2-10,xmax/2-10,ymax/2+20);
line(xmax/2-10,ymax/2-10,xmax/2+65,ymax/2-10);
line(xmax/2-10,ymax/2+20,xmax/2+65,ymax/2+20);
line(xmax/2+65,ymax/2-10,xmax/2+65,ymax/2+20);
outtextxy(xmax/2,ymax/2+3,"Log-in");
line(xmax-20,10,xmax-10,10);
line(xmax-20,10,xmax-20,20);
line(xmax-20,20,xmax-10,20);
line(xmax-10,10,xmax-10,20);
line(xmax-18,12,xmax-12,18);
line(xmax-18,18,xmax-12,12);
while(1)
{
int86(0x33,&in,&out);
if(out.x.bx==1&&out.x.cx>=(xmax/2-100)&&out.x.cx<=(xmax/2-25)&&out.x.dx>=(ymax/2-10)&&out.x.dx<=(xmax/2+25))
signup();
else if(out.x.bx==1&&out.x.cx>=(xmax/2-10)&&out.x.cx<=(xmax/2+65)&&out.x.dx>=(ymax/2-10)&&out.x.dx<=(xmax/2+25))
login();
else if(out.x.bx==1&&out.x.cx>=(xmax-20)&&out.x.cx<=(xmax-10)&&out.x.dx>=(10)&&out.x.dx<=(20))
exit(0);
}
}
int main()
{
clrscr();
reg z;
z.menu();
return 0;
}
