//̰���ߵ�����,�������ϰ�ģʽ
#include <stdio.h>
#include <windows.h>
#include <time.h>

#define PRINTF    printf("��");
#define PRINTFOOD printf("��");
#define EMPTY     printf("  ");
#define LINEheng  printf("_");
#define LINEshu   printf("|");
#define MapHeight 20
#define MapWide   80

typedef struct body
{
    int x,y;
    struct body* next;
} Body;

void setColor(unsigned short ForeColor,unsigned short BackGroundColor);
void introduction();
void information();
void SetPos(int x,int y);
int Menu();
void setLevel();
void countdown();
void PrintMap();
void inisnake();
void newFood();
void movesnake();
void movesnake_v2();
int JudgeWall();
int JudgeFood();
int JudgeBody();
void GameOver();
void freebody();
void HideCursor()
{
CONSOLE_CURSOR_INFO cursor_info = {1, 0};
SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
int level = 1;//��Ϸ�ȼ�
int direction;
int score;
int xx,yy;//ʳ������
Body *head;

int main(){
    srand(time(0));
    HideCursor();
    introduction();
    while(1){
        score = 0;
        int choice = 0;
        choice = Menu();
        switch(choice){
            case 1:
                setLevel();
                break;
            case 2:
            countdown();
            PrintMap();
            inisnake();
            movesnake();
            if(JudgeBody() == 0||JudgeWall() == 0){
                GameOver();
                SetPos(0,21);
                system("pause");
            }
            freebody();
            break;
            case 3:
            countdown();
            PrintMap();
            inisnake();
            movesnake_v2();
            if(JudgeBody() == 0){
                GameOver();
                SetPos(0,21);
                system("pause");
            }
            freebody();
            break;
            case 4:
                information();
                break;
            default:
                break;
        }
        if(choice == 0)
            break;
    }
    SetPos(0,21);
    return 0;
}
//������ɫ
void setColor(unsigned short ForeColor,unsigned short BackGroundColor){
    HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE);//��ȡ��ǰ���ھ��
    SetConsoleTextAttribute(handle,ForeColor+BackGroundColor*0x10);//������ɫ
}
//���ù��λ��
void SetPos(int x,int y){
    COORD pos;
    HANDLE handle;
    pos.X=x;
    pos.Y=y;
    handle=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(handle,pos);
}
//��Ϸ��ʼ����
void introduction(){
    for(int i = 0; i <= 15; i++){
        setColor(i,0);
        SetPos(0,0);
        printf("\n\n\n----------------------��  ӭ-----------------------");
        printf("\n\n\n\n\n\n");
        printf("-------------------̰   ��   ��---------------------\n\n\n\n\n");
        printf("           by: SGNYYYY\n\n\n");

        Sleep(300);
    }
    system("pause");
    system("cls");
}
//��Ϸ˵��
void information(){
    system("cls");
    printf("\n\n ���! ����! , ���ǵ�����̰����,SG-̰����-version3.0\n");
    printf("\n�˰汾������wsad���ƺ����ϰ�ģʽ, �����޸���һЩ����\n\n");
    printf("���������ʹ��wsad���߷���������ߵ��ƶ�����\n\n");
    printf("    ENJOY  YOURSELF!\n");
    printf("    HAPPY   EVERY    DAY\n\n");
    system("pause");
}
//�û�ѡ��˵�
int Menu(){
reset:
    system("cls");
    int z = 0;
    char c;
    SetPos(0,0);
    printf("--------------ѡ��˵�-------------\n\n\n");
    printf("1,ѡ��ȼ�\n\n");
    printf("2,����ģʽ\n\n");
    printf("3,���ϰ�ģʽ\n\n");
    printf("4,��Ϸ˵��\n\n");
    printf("0,�˳���Ϸ\n\n");
    printf("���������ѡ��(�Իس�����): ");
    while ((c = getchar()) != EOF && c != '\n'){
        z += z*10 + c - '0';
    }
    if(z != 0 && z != 1&&z != 2&&z != 3&&z != 4)
        goto reset;
    return z;
}
//���õȼ�
void setLevel(){
    set:
    system("cls");
    int l = 0;
    char c;
    SetPos(0,0);
    printf("1>>>>>>10");
    printf("\n\n��>>>>>����\n\n");
    printf("������ȼ�(�Իس�����): ");
    while ((c = getchar()) != EOF && c != '\n'){
        l += l*10 + c - '0';
    }
    level = l;
    if(level < 1||level > 10){
        level = 1;
        goto set;
    }
}
//��ʼǰ�ĵ���ʱ
void countdown(){
    system("cls");
    int i = 0;
    SetPos(15,10);
    printf("ARE   YOU    READY?");
    Sleep(1000);
    system("cls");
    for(i = 3;i >= 1;i--){
        SetPos(20,10);
        printf("%d",i);
        Sleep(1000);
    }
}
//��ӡ��ͼ
void PrintMap(){
    system("cls");
    int i = 0;
    for(i = 1; i <= MapWide; i++)
    {
        SetPos(i,0);
        LINEheng
        SetPos(i,MapHeight);
        LINEheng
    }
    for(i = 1; i <= MapHeight; i++)
    {
        SetPos(1,i);
        LINEshu
        SetPos(MapWide,i);
        LINEshu
    }
    SetPos(MapWide+1,10);
    printf("your score: 0");
}

//��ʼ������
void inisnake(){
    srand(time(0));
    head = (Body*)malloc(sizeof(Body));
    Body *temp = (Body*)malloc(sizeof(Body));
    head->next = temp;
    temp->x = rand()%21+4;
    temp->y = rand()%11+4;
    direction = rand()%4+1;                     //�ĸ�����
    for(int i = 1; i <= 2; i++)
    {
        Body *p = (Body*)malloc(sizeof(Body));
        temp->next = p;
        switch(direction)
        {
        case 1://�����ӳ�����
            p->x = temp->x;
            p->y = temp->y-1;
            break;
        case 2://�����ӳ�����
            p->y = temp->y;
            p->x = temp->x+1;
            break;
        case 3://�����ӳ�����
            p->x = temp->x;
            p->y = temp->y+1;
            break;
        case 4://�����ӳ�����
            p->y = temp->y;
            p->x = temp->x-1;
            break;
        }
        temp = p;
    }
    temp->next = NULL;
    Body *ptr = head;
    for(ptr = head->next; ptr!=NULL; ptr = ptr->next)
    {
        SetPos(ptr->x*2,ptr->y);
        PRINTF
    }
}
//����ʳ��
void newFood(){
retry:
    xx = rand()%30+2;
    yy = rand()%18+2;
    int judge = 0;
    for(Body *p = head->next; p != NULL; p = p->next){
        if(xx == p->x&&yy == p->y)
            judge = 1;
    }
    if(judge)
        goto retry;
    SetPos(xx*2,yy);
    PRINTFOOD
}

//������
void movesnake(){
    newFood();
    while(1){
        if((GetAsyncKeyState(VK_DOWN)&0x8000)||(GetAsyncKeyState('S')&0x8000)){
            if(direction != 3){
                direction = 1;
            }
        }
        else if((GetAsyncKeyState(VK_LEFT)&0x8000)||(GetAsyncKeyState('A')&0x8000)){
            if(direction != 4){
                direction = 2;
            }
        }
        else if((GetAsyncKeyState(VK_UP)&0x8000)||(GetAsyncKeyState('W')&0x8000)){
            if(direction != 1){
                direction = 3;
            }
        }
        else if((GetAsyncKeyState(VK_RIGHT)&0x8000)||(GetAsyncKeyState('D')&0x8000)){
            if(direction != 2){
                direction = 4;
            }
        }
        int forx,fory,tempx,tempy;
        Body *p = head->next;
        forx = p->x;               //�����洢��ͷԭ����λ��
        fory = p->y;
        switch(direction){         //�ƶ�ͷ
        case 1:                    //�����ƶ�
            p->y+=1;
            break;
        case 2:                    //�����ƶ�
            p->x-=1;
            break;
        case 3:                    //�����ƶ�
            p->y-=1;
            break;
        case 4:                    //�����ƶ�
            p->x+=1;
            break;
        }
        p = p->next;
        while(p!=NULL){             //ÿһ������ֻҪ��ǰһ������ԭ����λ���ƶ�
            tempx = p->x;
            tempy = p->y;
            p->x  = forx;
            p->y  = fory;
            forx  = tempx;
            fory  = tempy;
            p = p->next;
        }
        Body *Fptr = head;
        for(p = head->next; p != NULL; p = p->next){    //��ӡ�ƶ��������
            SetPos(p->x*2,p->y);
            PRINTF
            Fptr = Fptr->next;
        }
        if(JudgeWall() == 0){                          //�ж��Ƿ���ǽ
            break;
        }
        if(JudgeFood() == 1){                           //�ж��Ƿ�Ե�ʳ��
            Body *newp = (Body*)malloc(sizeof(Body));
            Fptr->next = newp;
            newp->y = fory;
            newp->x = forx;
            newp->next = NULL;
            newFood();
            SetPos(MapWide+1,10);
            printf("your score: %d",score*level);
        }else{
            SetPos(forx*2,fory);
            EMPTY
        }
        if(JudgeBody() == 0){
            break;
        }

        for(int i = 0; i < 10000000*(12-level); i++) {}
    }
}
void movesnake_v2(){                //���ϰ�ģʽ�ƶ�
    newFood();
    while(1){
        if((GetAsyncKeyState(VK_DOWN)&0x8000)||(GetAsyncKeyState('S')&0x8000)){
            if(direction != 3){
                direction = 1;
            }
        }
        else if((GetAsyncKeyState(VK_LEFT)&0x8000)||(GetAsyncKeyState('A')&0x8000)){
            if(direction != 4){
                direction = 2;
            }
        }
        else if((GetAsyncKeyState(VK_UP)&0x8000)||(GetAsyncKeyState('W')&0x8000)){
            if(direction != 1){
                direction = 3;
            }
        }
        else if((GetAsyncKeyState(VK_RIGHT)&0x8000)||(GetAsyncKeyState('D')&0x8000)){
            if(direction != 2){
                direction = 4;
            }
        }
        int forx,fory,tempx,tempy;
        Body *p = head->next;
        forx = p->x;               //�����洢��ͷԭ����λ��
        fory = p->y;
        switch(direction){         //�ƶ�ͷ
        case 1:                    //�����ƶ�
            p->y+=1;
            if(p->y == MapHeight)
                p->y = 1;
            break;
        case 2:                    //�����ƶ�
            p->x-=1;
            if(p->x == 0)
                p->x = MapWide/2-1;
            break;
        case 3:                    //�����ƶ�
            p->y-=1;
            if(p->y == 0)
                p->y = MapHeight-1;
            break;
        case 4:                    //�����ƶ�
            p->x+=1;
            if(p->x == MapWide/2)
                p->x = 1;
            break;
        }
        p = p->next;
        while(p!=NULL){             //ÿһ������ֻҪ��ǰһ������ԭ����λ���ƶ�
            tempx = p->x;
            tempy = p->y;
            p->x  = forx;
            p->y  = fory;
            forx  = tempx;
            fory  = tempy;
            p = p->next;
        }
        Body *Fptr = head;
        for(p = head->next; p != NULL; p = p->next){    //��ӡ�ƶ��������
            SetPos(p->x*2,p->y);
            PRINTF
            Fptr = Fptr->next;
        }
        if(JudgeFood() == 1){                           //�ж��Ƿ�Ե�ʳ��
            Body *newp = (Body*)malloc(sizeof(Body));
            Fptr->next = newp;
            newp->y = fory;
            newp->x = forx;
            newp->next = NULL;
            newFood();
            SetPos(MapWide+1,10);
            printf("your score: %d",score*level);
        }else{
            SetPos(forx*2,fory);
            EMPTY
        }
        if(JudgeBody() == 0){
            break;
        }

        for(int i = 0; i < 10000000*(12-level); i++) {}
    }
}
int JudgeWall(){
    if((head->next->x <= 0||head->next->x >= MapWide/2)||(head->next->y == 0 ||head->next->y == MapHeight))
        return 0;
    return 1;
}
int JudgeFood(){
    if(head->next->x == xx&&head->next->y == yy)
    {
        score++;
        return 1;
    }
    return 0;
}
int JudgeBody(){
    int toux,touy;
    toux = head->next->x;
    touy = head->next->y;
    for(Body *p = head->next->next; p != NULL; p = p->next){
        if(p->x == toux&&p->y == touy){
            return 0;
        }
    }
    return 1;
}
void GameOver(){
    system("cls");
    for(int i = 0; i <= 15; i++)
    {
        setColor(i,0);
        SetPos(0,8);
        printf("------------------GAME   OVER-------------------\n\n\n\n\n");
        printf("YOUR  SCORE:   %d",score*level);
        Sleep(200);
    }
}
void freebody(){
    Body *pr = head->next;
    while(pr!=NULL)
    {
        Body *temp = pr;
        pr = pr->next;
        free(temp);
    }
    free(head);
}
