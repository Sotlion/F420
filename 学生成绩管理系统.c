#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<dos.h>
#include<string.h>
#define LEN sizeof(struct student)
#define FORMAT "%-8d%-15s%-12.1lf%-12.1lf%-12.1lf%-12.1lf\n"
#define DATA stu[i].num,stu[i].name,stu[i].elec,stu[i].expe,stu[i].requ,stu[i].sum
#define data data.txt
float Felec,Fexpe,Frequ;
struct student //定义学生成绩结构体
{
    int num;//学号
    char name[15];//姓名
    double elec;//选修课
    double expe;//实验课
    double requ;//必修课
    double sum;//总分
};
struct student stu[50];//定义结构体数组，容纳50个学生
void in();//录入学生成绩函数
void show();//显示学生成绩信息函数
void order();//按总分数排序的函数
void del();//删除学生信息函数
void modify();//修改学生成绩函数
void menu();//主菜单函数
void insert();//插入学生信息函数
void total();//计算总人数函数
void search();//查找学生成绩函数

/////////////////////////////////////主函数开始//////////////////////////////////////
int main()
{
    int n;
    menu();//显示菜单
    scanf("%d",&n);//输入数字选择功能
    while(n)
    {
        switch(n)
        {
        case 1:
            in();
            break;
        case 2:
            search();
            break;
        case 3:
            del();
            break;
        case 4:
            modify();
            break;
        case 5:
            insert();
            break;
        case 6:
            order();
            break;
        case 7:
            total();
            break;
        default:
            break;
        }
        getch();
        menu();//执行完功能以后再次显示菜单
        scanf("%d",&n);
    }
}





/////////////////////////////////////主函数结束//////////////////////////////////////////////////////










/////////////////////////////////////////////////////////////////////////////////////////////////////
void in()//录入学生信息的函数
{
    int i,m=0;//m是当前记录的条数
    char ch[2];
    FILE *fp;//定义文件指针
    if((fp=fopen("data","ab+"))==NULL)//打开指定的文件
    {
        printf("无法打开\n");
        return;
    }
    while(!feof(fp))
    {
        if(fread(&stu[m],LEN,1,fp)==1)
            m++;//统计当前的记录条数
    }
    fclose(fp);
    if(m==0)
        printf("没有记录\n");
    else
    {
        system("cls");
        show();//显示原有的信息
    }
    if((fp=fopen("data","wb"))==NULL)
    {
        printf("无法打开\n");
        return;
    }
    for(i=0;i<m;i++)
        fwrite(&stu[i],LEN,1,fp);//向文件里写入信息
    printf("请选择(y/n):");
    scanf("%s",ch);
    if(strcmp(ch,"Y")==0||strcmp(ch,"y")==0)
    {
        printf("请输入以下成绩所占比重:\n");
        printf("选修课:");
        scanf("%f",&Felec);
        printf("\n实验课:");
        scanf("%f",&Fexpe);
        printf("\n必修课成绩:");
        scanf("%f",&Frequ);
    }
    while(strcmp(ch,"Y")==0||strcmp(ch,"y")==0)//判断是否要录入新信息
    {
        printf("学号:");
        scanf("%d",&stu[m].num);//输入学生学号
        printf("姓名:");
        scanf("%s",stu[m].name);
        printf("选修课成绩:");
        scanf("%lf",&stu[m].elec);
        printf("实验课成绩:");
        scanf("%lf",&stu[m].expe);
        printf("必修课成绩:");
        scanf("%lf",&stu[m].requ);
        stu[m].sum=stu[m].elec*Felec+stu[m].expe*Fexpe+stu[m].requ*Frequ;//计算总成绩
        if(fwrite(&stu[m],LEN,1,fp)!=1)//将新信息录入文件
        {
            printf("保存失败");
            getch();
        }
        else
        {
            printf("%s 存储成功",stu[m].name);
            m++;
        }
        printf("是否继续？(y/n):");//询问是否继续
        scanf("%s",ch);
    }
    fclose(fp);
    printf("OK!\n");
}





////////////////////////////////////////////////////////////////////////////////////////////////////////







////////////////////////////////////////////////////////////////////////////////////////////////////////
void show()
{
    FILE *fp;
    int i,m=0;
    fp=fopen("data","ab+");
    while(!feof(fp))
    {
        if(fread(&stu[m],LEN,1,fp)==1)
            m++;
    }
    fclose(fp);
    printf("学号            姓名   选修课成绩  实验课成绩  必修课成绩  总成绩\t\n");
    for(i=0;i<m;i++)
    {
        printf(FORMAT,DATA);//打印信息
    }

}
///////////////////////////////////////////////////////////////////////////////////////////////////////




/////////////////////////////////////////////////////////////////////////////////////////////////////////
void menu()//菜单界面
{
    system("cls");
    printf("\n\n\n\n\n");
    printf("\t\t|---------------------STUDENT-------------------|\n");
    printf("\t\t|\t 0. 退出                                |\n");
    printf("\t\t|\t 1. 输入成绩                        |\n");
    printf("\t\t|\t 2. 查找成绩                       |\n");
    printf("\t\t|\t 3. 删除成绩                       |\n");
    printf("\t\t|\t 4. 修改成绩                       |\n");
    printf("\t\t|\t 5. 插入成绩                       |\n");
    printf("\t\t|\t 6. 查看排名                               |\n");
    printf("\t\t|\t 7. 年级人数                              |\n");
    printf("\t\t|-----------------------------------------------|\n\n");
    printf("\t\t\tchoose(0-7):");
}





////////////////////////////////////////////////////////////////////////////////////////////////////









//////////////////////////////////////////////////////////////////////////////////////////////////
void order()//按总分数排序的函数
{
    FILE *fp;
    struct student t;
    int i=0,j=0,m=0;
    if((fp=fopen("data","ab+"))==NULL)
    {
        printf("无法打开\n");
        return;
    }
    while(!feof(fp))
        if(fread(&stu[m] ,LEN,1,fp)==1)
            m++;
        fclose(fp);
        if(m==0)
        {
            printf("没有成绩\n");
            return;
        }
        for(i=0;i<m-1;i++)
            for(j=i+1;j<m;j++)//冒泡法降幂排序
                if(stu[i].sum<stu[j].sum)
                {
                    t=stu[i];
                    stu[i]=stu[j];
                    stu[j]=t;
                }
         if((fp=fopen("data","wb"))==NULL)
          {
            printf("can not open\n");
            return;
          }
                for(i=0;i<m;i++)//重新写入文件里
                    fwrite(&stu[i] ,LEN,1,fp);
                   
                    fclose(fp);
                    printf("保存成功\n");
}
/////////////////////////////////////////////////////////////////////////////////////////////////





/////////////////////////////////////////////////////////////////////////////////////////////////////
void del()//删除学生信息函数
{
    FILE *fp;
    int snum,i,j,m=0;
    char ch[2];
    if((fp=fopen("data","ab+"))==NULL)
    {
        printf("无法打开\n");
        return;
    }
    while(!feof(fp))
        if(fread(&stu[m],LEN,1,fp)==1)
            m++;
        fclose(fp);
        if(m==0)
        {
            printf("没有成绩\n");
            return;
        }
        printf("请输入学号:");
        scanf("%d",&snum);
        for(i=0;i<m;i++)
            if(snum==stu[i].num)
                break;
        if(i==m)
        {
            printf("没有找到");
            getchar();
            return;
        }
        printf("已找到该学生，是否删除？(y/n)");
        scanf("%s",ch);
        if(strcmp(ch,"Y")==0||strcmp(ch,"y")==0)
        {
            for(j=i;j<m;j++)
                stu[j]=stu[j+1];//将后一个成绩移动到前一个记录的位置
            m--;//总记录个数要减少一个
            printf("删除成功\n");
        }
        fp=fopen("data","wb");
        for(j=0;j<m;j++)//将修改的成绩重新写入文件里
            if(fwrite(&stu[j],LEN,1,fp)!=1)
            {
                printf("无法存储\n");
                getch();
            }
            fclose(fp);

}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////












//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void modify()//修改学生成绩函数
{
    FILE *fp;
    int i,j,m=0,snum;
    if((fp=fopen("data","ab+"))==NULL)
    {
        printf("无法打开\n");
        return;
    }
    while(!feof(fp))
        if(fread(&stu[m],LEN,1,fp)==1)
            m++;
        if(m==0)
        {
            printf("没有成绩\n");
            fclose(fp);
            return;
        }
        printf("请输入学号:");
        scanf("%d",&snum);
        for(i=0;i<m;i++)
            if(snum==stu[i].num)//检查记录中是否有要修改的成绩
                break;
        if(i<m)
        {
            printf("已找到该学生,请修改:\n");

            printf("\n选修课成绩比重:");
            scanf("%f",&Felec);
            printf("\n实验课成绩比重:");
            scanf("%f",&Fexpe);
            printf("\n必修课成绩比重:");
            scanf("%f",&Frequ);
            printf("\n姓名:");
            scanf("%s",stu[i].name);
            printf("\n选修课成绩:");
            scanf("%lf",&stu[i].elec);
            printf("\n实验课成绩:");
            scanf("%lf",&stu[i].expe);
            printf("\n必修课成绩:");
            scanf("%lf",&stu[i].requ);
            stu[i].sum=stu[i].elec*Felec+stu[i].expe*Fexpe+stu[i].requ*Frequ;
            }
            else
            {
                printf("无法找到");
                getchar();
                return;
            }
            fp=fopen("data","wb");
            for(j=0;j<m;j++)//将修改的成绩重新写入文件里
                if(fwrite(&stu[j],LEN,1,fp)!=1)
                {
                    printf("无法存储\n");
                    getch();
                }
            fclose(fp);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////
void insert()//插入学生信息函数
{
    ;
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////
void total()//计算总人数函数
{
    FILE *fp;
    int m=0;
    if((fp=fopen("data","ab+"))==NULL)
    {         
        printf("无法打开\n");
        return;
    }
    while(!feof(fp))  
        if(fread(&stu[m],LEN,1,fp)==1)
            m++;//统计记录个数即学生个数
        if(m==0)
        {
            printf("no record!\n");
            fclose(fp);
            return;
        }
        printf("总共有%d名学生\n",m);//将统计的个数输出
        fclose(fp);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////









//////////////////////////////////////////////////////////////////////////////////////////////////////
void search()//查找学生成绩函数
{
    FILE *fp;
    int snum,i,m=0;
    char ch[2];
    if((fp=fopen("data","ab+"))==NULL)
    {
        printf("无法打开\n");
        return;

    }
    while(!feof(fp))
        if(fread(&stu[m],LEN,1,fp)==1)
        m++;
    fclose(fp);
    if(m==0)
    {
        printf("成绩为空\n");
        return;
    }
    printf("请输入学号:");
    scanf("%d",&snum);
    for(i=0;i<m;i++)
        {if(snum==stu[i].num)//看是否在记录中
    {


        printf("学号            姓名   选修课成绩  实验课成绩  必修课成绩  总成绩\t\n");
        printf(FORMAT,DATA);//指定格式输出
        break;


    }
    else
        printf("未查到该学生信息");
        return;}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
