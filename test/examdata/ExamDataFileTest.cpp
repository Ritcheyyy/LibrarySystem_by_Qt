#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

class Question  
{ public:
    int id;
    char ques[80]; 
    char ans[4][50];
    int ansok;
  public:        
    Question(int uid=0, char *uq="", char *ua0="", char *ua1="", char *ua2="", char *ua3="", int uaok=0)  
    {   id = uid;  
        strcpy(ques, uq);
        strcpy(ans[0], ua0);
        strcpy(ans[1], ua1);
        strcpy(ans[2], ua2);
        strcpy(ans[3], ua3);
		ansok = uaok;
    }
};
const int PLen = sizeof(Question);

int main()  
{   Question as[20] = { Question(0,  "忽如一夜春风来，千树万树梨花开。吟咏的对象是：", "梨花", "杏花", "雪", "桃花", 2),
                        Question(1,  "下列作家中，不属于“唐宋八大家”的是", "欧阳修", "柳宗元", "司马光", "王安石", 2),
                        Question(2,  "“何当共剪西窗烛，却话巴山夜雨时”是李商隐的诗句，诗题是", "《夜雨寄北》", "《观书有感》", "《过故人庄 》", "《滁州西涧》", 0),
                        Question(3,  "“问渠那得清如许”的下一句是", "百般红紫斗芳菲", "一江春水向东流", "孤帆一片日边来", "为有源头活水来", 3),
                        Question(4,  "《孙权劝学》选自哪部书", "《史记 》", "《世说新语》", "《资治通鉴》", "《山海经》", 2),
                        Question(5,  "“学而时习之”的下一句是", "不亦乐乎", "不亦说乎", "不亦君子乎", "不亦远乎", 1),
                        Question(6,  "《山市》的作者蒲松龄，字留仙，别号“柳泉居士”，他是", "唐朝", "宋朝", "元朝", "清朝", 3),
                        Question(7,  "《乐府诗集》是宋代", "王安石", "郭茂倩", "李清照", "朱熹", 1),
                        Question(8,  "下列古代的文化典籍中，以书房命名的一项是", "《聊斋志异》", "《杜工部集》", "《稼轩长短句》", "《临川先生文集》", 0),
                        Question(9,  "四大古典名著中，孙权、吕蒙出现在哪一部作品中", "《红楼梦》", "《西游记》", "《三国演义》", "《水浒传》", 2),
                        Question(10, "以下表示条件反射的一个成语是", "朝三暮四", "耳濡目染", "望梅止渴", "乐不思蜀", 2),
                        Question(11, "《七步诗》的作者是", "曹操", "曹丕", "曹睿", "曹植", 3),
                        Question(12, "“海内存知己，天涯若比邻”是", "王勃", "李白", "白居易", "欧阳修", 0),
                        Question(13, "“北方有佳人，绝世而独立”中的佳人和李延年是什么关系？", "情人关系", "兄妹关系", "父女关系", "朋友关系", 1),
                        Question(14, "“小荷才露尖尖角，早有蜻蜓立上头。”出自谁的《小池》？", "杨万里", "苏轼", "贺知章", "陆游", 0),
                        Question(15, "“飞流直下三千尺，疑是银河落九天”指的是哪个风景区？", "华山", "黄山", "泰山", "庐山", 3),
                        Question(16, "下列哪位诗人凭借哪首诗，赢得了“以孤篇压倒全唐”的美誉？", "陈子昂《登幽州台歌》", "张若虚 《春江花月夜 》", "《杨炯 从军行》", "《李清照 如梦令》", 1),
                        Question(17, "李清照的《如梦令》里的“绿肥红瘦”是描写什么季节的景象？", "晚春", "盛夏", "初秋", "寒冬", 0),
                        Question(18, "“采菊东篱下，悠然见南山”的生活方式被现代人所向往。请问被称为“菊月”的月份是？", "八月", "九月", "十月", "十一月", 2),
                        Question(19, "在宋初词坛影响最大，成为词从晚唐五代过度到宋代的关键人物是？", "范仲淹", "欧阳修", "王安石", "晏殊", 3)
                    };
                    
    ofstream dfile("examdata.dat", ios::out|ios::binary);
    if(!dfile)  
    {   cout << "文件 examdata.dat 创建失败!" << endl; 
        exit(1);	
    }
    for(int i = 0; i < 20; i ++)
        dfile.write((char *)&as[i], PLen);
    dfile.close();
	cout << "对象成功写入！" << endl << endl;
            
    cout << "对象数据显示读出成功！" << endl << endl;
    ifstream ifile("examdata.dat", ios::in|ios::binary);
    if(!ifile)  
    {   cout << "文件 examdata.dat 打开失败!" << endl; 
        exit(1);	
    }

    Question q;
    char ansstr[4] = {'A', 'B', 'C', 'D'};
    while(! ifile.eof())
    {   ifile.read((char *)&q, PLen);
        cout << (q.id+1) << "  " << q.ques << endl;  
        cout << "   A: " << q.ans[0] << "    B: " << q.ans[1] << "    C: " << q.ans[2] << "    D: " << q.ans[3] << endl;
        cout << "   标准答案：" << ansstr[q.ansok] << endl;
        cout << endl; 
    }
    ifile.close(); 
}

