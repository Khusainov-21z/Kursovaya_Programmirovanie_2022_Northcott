#include<stdio.h>               // ������⥪� ��� ����� � �뢮��
#include<string.h>              // ������⥪� ��� �㭪樨 strcpy()
#include<stdlib.h>              // ������⥪� ��� �㭪樨 rand(), srand()
#include<time.h>                // ������⥪� ��� �㭪樨 time()
#include<unistd.h>              // ������⥪� ��� �㭪樨 sleep()

int field_row;                  // ����� ����
int field_col;                  // ��ਭ� ����
int players_count;              // ������⢮ ��ப��
int level;                      // ���������
int gamer=1;                    // ����騩 ��ப (��ࢮ��砫쭮 1-�)
char field[15][15];             // ���� ࠧ��஬ 15 �� 15
char name1[15], name2[15];      // ����� ��ப�� �� 15 ᨬ�����
int pos1[15], pos2[15];         // ������ �襪 ��ப�� �� ��ਧ��⠫�
int moves_1, moves_2;           // ������⢮ 室��, ����� ᮢ��訫 ����� ��ப
int pos1_old[15], pos2_old[15]; // ���� ����樨 �襪 ��ப�� �� ��ਧ��⠫�

/*  ������� �㭪権  */
void hello();
void rules_of_the_game();
void field_size();
void init_game();
void game_mode();
void print_state();
void print_path(int gamer, int row);
int change_pos(int gamer);
int change_pos_PC(int level);
int check_game_over();
FILE *open_save_file(int save_number, int mode);
void show_saves(int save_number);
int check_have_save(int save_number, int func);
int check_save_file(int save_number);
int save_game();
int loading_save_game();

/*  �㭪樨: */
// �ਢ���⢨�
void hello(void){
    printf("==================================================================\n");
    printf("\t\t���� ���������� � ���� \"���⪮��\"\n");
    printf("==================================================================\n");
}
// �ࠢ��� ����
void rules_of_the_game(void){
    char c;
    printf("������ ������������ � �ࠢ����� ����? (Y/N)(y/n): ");
    while(1){
        scanf("%c", &c);
        if(c=='Y' || c=='y'){
            printf("============================================================================================================");
            printf("\n�ࠢ��� ���� \"���⪮��\":\n\n");
            printf("� ��砫� ���� � ����� �⮫�� �� ��� ��ப�� �ᯮ������ ��� �誨,\n");
            printf("� �ࠢ�� �⮫�� - ���� �誨.\n\n");
            printf("�� ���� 室 ��ப ����� ��।������ ���� ᢮� ��� � ����� ��ப� �� �� �᫮ ����� � ���� ��஭�.\n");
            printf("�� �⮬ ����� ���᪠������ �१ �誨 ��⨢����!\n\n");
            printf("��������� �� ��ப, ����� ᢮��� �誠�� \"�����\" �誨 ��⨢����.\n");
            system("Pause");
            printf("============================================================================================================\n");
            break;
        }
        else if(c=='N' || c=='n'){
            printf("==================================================================\n");
            break;
        }
    }
}
// �롮� ࠧ��� ����
void field_size(void){
    printf("���ᨬ���� ࠧ��� ����: (15*15)\n");
    while(1){
        printf("������ ࠧ��� ���� (M*N): ");
        scanf("%d*%d", &field_row, &field_col);
        if(field_row>15 || field_col>15 || field_col<3 || field_row<1)
            printf("�����४�� ࠧ��� ����, ������ ����\n");
        else{
            printf("==================================================================\n");
            break;
        }
    }
}
// ���������� ��砫�묨 ����묨
void init_game(void){
    int i;
    for(i=0;i<field_row;i++){
        field[i][0]=1;           // ���� �誨
        field[i][field_col-1]=2; // ���� �誨
        pos1[i]=0;               // ��ࢮ��砫�� ����樨 �襪 1-�� ��ப� �� ��ਧ��⠫�
        pos2[i]=field_col-1;     // ��ࢮ��砫�� ����樨 �襪 2-�� ��ப� �� ��ਧ��⠫�
        pos1_old[i]=0;           // ���� ����樨 �襪 1-�� ��ப� �� ��ਧ��⠫�
        pos2_old[i]=field_col-1; // ���� ����樨 �襪 2-�� ��ப� �� ��ਧ��⠫�
    }
    moves_1=0;                   // ������⢮ 室�� ᮢ��襭�� 1-� ��ப��
    moves_2=0;                   // ������⢮ 室�� ᮢ��襭�� 2-� ��ப��
    printf("==================================================================\n");
    printf("���� ����㧪�...");
    sleep(1);
}
// �롮� ०��� ���� (1 ��ப/2 ��ப�), ������ ����
void game_mode(void){
    printf("����쪮 ��ப�� �㤥� �����? (1 ��� 2)\n");
    while(1){
        printf("������ ������⢮ ��ப��: ");
        scanf("%d", &players_count);
        if(players_count==2){ // �᫨ ���� ����� 2 ��ப�
            printf("������ ��� ��ࢮ�� ��ப�: ");
            scanf("%s", name1);
            printf("������ ��� ��ண� ��ப�: ");
            scanf("%s", name2);
            break;
        }
        else if(players_count==1){ // �᫨ 1...
            printf("������ ��� ��ப�: ");
            scanf("%s", name1);
            strcpy(name2, "��������");
            printf("�롥�� ᫮������ (1 - ����� / 2 - �।�� / 3 - ᫮���): ");
            scanf("%d", &level);
            break;
        }
        else{
            printf("�����४⭮� �᫮ ��ப��. ������ ����.\n\n");
        }
    }
}
// ����� ��஢��� ����
void print_state(void){
    int i,j,k;
    printf("\n%s (�����)   vs   %s (��ࠢ�)\n\n", name1, name2); // ����� ����
    printf("     | ");
    for(i=0;i<field_col;i++)
        printf("%2d  | ", i+1); // ����� ���न��� �� ��ਧ��⠫�
    printf("\n");
    printf("-----|");
    for(i=0;i<field_col;i++)
        printf("-----|");
    printf("\n");
    for(i=0; i<field_row; i++){
        printf("%4d ", i+1); // ����� ���न��� �� ���⨪���
        for(j=0; j<field_col; j++)
            if(field[i][j]==0){
                printf("|  .  ");  // ����� ������ �祥�
            }
            else{
                field[i][j]==1 ? printf("|  O  ") : printf("|  X  "); // ����� �襪
            }
        printf("|");
        printf("\n");
        for(k=0;k<=field_col;k++)
            printf("-----|");
        printf("\n");
    }
}
// ����� ��� ��諮�� 室�
void print_path(int gamer, int row){
    if(gamer==1){ // �᫨ 室 ᮢ��蠥� 1-� ��ப, � �뢮����� ���ଠ�� � 2-��
        printf("\n�।��騩 室 ��ப� �2 - %s: �� �%d (%d ---> %d)\n", name2, row, (pos2_old[row-1]+1), (pos2[row-1]+1));
        printf("-------------------------------------------------------");
    }
    else{ // �᫨ 2-��...
        printf("\n�।��騩 室 ��ப� �1 - %s: �� �%d (%d ---> %d)\n", name1, row, (pos1_old[row-1]+1), (pos1[row-1]+1));
        printf("-------------------------------------------------------");
    }
}
// ����� �襪 � �஢�ઠ (��� ���짮��⥫��)
int change_pos(int gamer){
    int row, col;
    while(1){
        if(gamer==1){
            printf("\n%s, ", name1);
        }
        else{
            printf("\n%s, ", name2);
        }
        printf("������ ������, � ������ ��� ���⠢��� ��� (0 0 - ��� �� ����): ");
        scanf("%d %d", &row, &col);
        if(row==0 && col==0){ // �᫨ ���짮��⥫� ��� ���
            printf("=====================================================================================\n");
            return 0;
        }
        row=row-1;
        col=col-1;
        if(row>=0 && row<field_row && col>=0 && col<field_col) // �஢�ઠ ���������
            if(field[row][col]==0 && gamer==1 && col<pos2[row]){ // �᫨ �祩�� �� �����, ��ப �1, � �� ���室�� �� ����� ���
                field[row][pos1[row]]=0; // ���ࠥ� ��� � ��ன ����樨
                field[row][col]=1; // �⠢�� ��� � ����� ������
                pos1_old[row]=pos1[row];
                pos1[row]=col; // �����㥬 ����� ��������� �� ��ਧ��⠫�
                system("cls");
                break;
            }
            else if(field[row][col]==0 && gamer==2 && pos1[row]<col){ // �᫨ �祩�� �� �����, ��ப �2, � �� ���室�� �� ����� ���
                field[row][pos2[row]]=0; // ���ࠥ� ��� � ��ன �祩��
                field[row][col]=2; // �⠢�� ��� � ����� �祩��
                pos2_old[row]=pos2[row]; // �����뢠�� ��஥ ���������
                pos2[row]=col; // �����뢠�� ����� ���������
                system("cls");
                break;
            }
            else
                printf("�����४⭠� ������.");
    }
    if(gamer==1){ // �᫨ 室 ᮢ��訫 1-� ��ப, � 㢥��稢��� ���-�� 室�� 1-�� ��ப�
        moves_1++;
    }
    else{ // �᫨ 2-��...
        moves_2++;
    }
    return (row+1);
}
// ����� �襪 � �஢�ઠ (��� ��������)
int change_pos_PC(int level){
    int row, col, i, count=0, try=0;
    for(i=0;i<field_row;i++){
        if(pos2[i]==pos1[i]+1){
            count++; // ������⢮ �襪, ����� �� ����� 室��� ���।
        }
    }
    srand(time(NULL));
    while(1){
        row=0+rand()%((field_row-1)-0+1);
        if(level==1){ // �����
            col=1+rand()%((field_col-1)-1+1);
        }
        else if(level==2){ // �।��
            col=(pos1[row]+1)+rand()%((pos1[row]+3)-(pos1[row]+1)+1);
            if(count==field_row){
                col=(pos2[row]+1)+rand()%((pos2[row]+3)-(pos2[row]+1)+1);
            }
        }
        else if(level==3){ // ������
            col=pos1[row]+1;
            if(count==(field_row-3)){
                col=pos1[row]+1;
            }
            if(count==(field_row-2)){
                col=(pos1[row]+2)+rand()%((pos1[row]+4)-(pos1[row]+2)+1);
                if(try==(field_row+25)){
                    col=pos2[row]-1;
                    try=0;
                }
                if(col>=field_col){
                    try++;
                }
                if(col==pos2[row]){
                    col=pos2[row]+1;
                }
            }
            else if(count==(field_row-1)){
                col=pos1[row]+1;
            }
            else if(count==field_row){
                col=(pos2[row]+1)+rand()%((pos2[row]+3)-(pos2[row]+1)+1);
            }
        }
        if(row>=0 && row<field_row && col>=0 && col<field_col){ // �஢�ઠ ���������
            if(field[row][col]==0 && pos1[row]<col){ // �᫨ �祩�� ᢮����� � �� "���室��" �� ����� ���
                field[row][pos2[row]]=0; // ���ࠥ� ��� � ��ன �祩��
                field[row][col]=2; // �⠢�� ��� � ����� �祩��
                pos2_old[row]=pos2[row]; // �����뢠�� ��஥ ���������
                pos2[row]=col; // �����뢠�� ����� ���������
                moves_2++; // �����稢��� 室� ��������
                sleep(1);
                system("cls");
                break;
            }
        }
    }
    return (row+1);
}
/* 
    �஢�ઠ �����襭�� ����
    0 - ������ ���� �� ���ঠ�
    1 - ������ ���ঠ� ���� �� ��ப��
*/
int check_game_over(void){
    int i, count_1=0, count_2=0;
    for(i=0;i<field_row;i++){
        if(field[i][field_col-2]==1){ // �᫨ �誠 ��ࢮ�� ��ப� "��४�뫠" ��� ��ண� ��ப�
            count_1++;
        }
        else if(field[i][1]==2){ // �᫨ �誠 ��ண� ��ப� "��४�뫠" ��� ��ࢮ�� ��ப�
            count_2++;
        }
    }
    if(count_1==field_row || count_2==field_row){
        printf("\n��� ����祭�!\n");
        printf("==================================================================\n");
        if(count_1==field_row){
            printf("�� %d 室�� ������ ���ঠ� %s.\n",moves_1, name1);
        }
        else{
            printf("�� %d 室�� ������ ���ঠ� %s.\n",moves_2, name2);
        }
        return 1;
    }
    return 0;
}
/*  
    ���뢠�� 䠩� ��࠭���� ��� ��।������� �����:
    0 - ���� �� ������
    f - ���� ������
    mode (1 - �⥭��, 2 - ������)
*/
FILE *open_save_file(int save_number, int mode){
    FILE *f;
    char namefile[10]={"save0.txt"};
    namefile[4]+=save_number;
    if(mode==1){
        f=fopen(namefile, "r");
    }
    else{
        f=fopen(namefile, "w");
    }
    if(!f){ // �᫨ �� ������, � �����頥� 0
        return NULL;
    }
    else{ // �᫨ ������, � �����頥� 㪠��⥫� �� 䠩�
        return f;
    }
}
// �⮡ࠦ���� ᫮⮢
void show_saves(int save_number){
    FILE* f;
    f=open_save_file(save_number, 1);
    if(f){ // �᫨ 䠩� ������, � �� �������
        printf("���� �%d - �����\n", save_number);
        fclose(f);
    }
    else{ // ���� �� �������
        printf("���� �%d - ��������\n", save_number);
    }
}
/*  
    �஢�ઠ ������ ��࠭����:
    0 - ���� 㦥 ����� ��࠭���� � ��� �� ��१����뢠��
    1 - ���� 㦥 ����� ��࠭���� � ��� ��१����뢠��
    2 - ���࠭���� �� �������
    3 - ���� ��� ��࠭���� ᢮�����
    func (1 - ��࠭����, 2 - ����㧪�)
*/
int check_have_save(int save_number, int func){
    char symbol;
    FILE* f;
    f=open_save_file(save_number, 1);
    if(f && func==1){ // �᫨ 䠩� ������ � ��� ���� ��࠭���
        printf("� ������ ᫮� 㦥 ������� ��࠭����.\n�� ��� ��१������ ��࠭����? (Y/N)(y/n): ");
        while(1){
            scanf("%c", &symbol);
            if(symbol=='Y' || symbol=='y'){
                return 1;
            }
            else if(symbol=='N' || symbol=='n'){
                return 0;
            }
        }
    }
    else if(!f && func==1){ // �᫨ 䠩� �� ������ � ��� ���� ��࠭���, � ᫮� ᢮�����
        return 3;
    }
    else if(!f && func==2){ // �᫨ 䠩� �� ������ � ��� ���� ����㧨��, � ��� �� �����.
        printf("���࠭���� �%d �� �������! �롥�� ��㣮� ᫮�.\n", save_number);
        return 2;
    }
}
/*
    �஢�ઠ 䠩�� �� 楫��⭮���:
    0 - ���� ���०���
    1 - ���� 楫��⥭
*/
int check_save_file(int save_number){
    char str[15];
    int line=0;
    FILE* f;
    f=open_save_file(save_number, 1);
    fscanf(f,"%d ", &field_row);
    while(fgets(str,15,f)){ // ���� �� ���⨣��� ����� 䠩�� ���뢠�� ��ப�
        line++;
    }
    if(line-1!=(2+(4*field_row))){ // �᫨ ������⢮ ��ப, ���஥ ������ ����, �� ᮢ������ � ⥪�騬
        printf("���� ��࠭���� �%d ���०���. ������ � �롥�� ��㣮�.\n", save_number);
        field_row=0;
        return 0;
    }
    else{
        return 1;
    }
}
/*
    ���࠭���� ⥪�饩 ����:
    0 - ��室 �� ���� ��� ��࠭����
    1 - ��室 �� ���� � ��࠭�����
*/
int save_game(void){
    char symbol;
    int save_number, i, j, step;
    printf("������ ��࠭��� ����? (Y/N)(y/n): ");
    while(1){
        scanf("%c", &symbol);
        if(symbol=='N' || symbol=='n'){
            printf("=====================================================================================\n");
            return 0;
        }
        else if(symbol=='Y' || symbol=='y'){
            break;
        }
    }
    while(1){
        printf("�롥�� ᫮� (1 - 3) (9 - ��� / 0 - ��ᬮ���� ��࠭����): ");
        scanf("%d", &save_number);
        if(save_number==9){
            printf("=====================================================================================\n");
            return 0;
        }
        if(save_number==0){
            for(i=1;i<=3;i++){
                show_saves(i); // ��ᬮ�� �������� ��࠭����
            }
            continue;
        }
        FILE* f;
        step=check_have_save(save_number, 1); // �஢�ઠ 䠩�� �� ����稥 � ��� 㦥 ��࠭����
        if(!step){ // �᫨ ��࠭���� �� �⠫� ��१����뢠�� - �롨ࠥ� ��㣮� ᫮�
            continue;
        }
        f=open_save_file(save_number, 2);
        fprintf(f,"%d %d %d %d %d %d %d\n", field_row, field_col, players_count, gamer, level, moves_1, moves_2);
        for(i=0;i<field_row;i++){
            fprintf(f,"%d\n%d\n%d\n%d\n", pos1[i], pos1_old[i], pos2[i], pos2_old[i]);
        }
        fprintf(f,"%s %s", name1, name2);
        fclose(f);
        break;
    }
    printf("\n���� ��࠭����...");
    sleep(1);
    printf("\n��� ��࠭���.\n\n");
    printf("==================================================================\n");
    return 1;
}
/*
    ����㧪� ࠭�� ��࠭������ ����:
    0 - ��砫� ����� ����
    1 - �த������ ��࠭����� ����
*/
int loading_save_game(void){
    char symbol;
    int save_number, i, step;
    printf("������ ����㧨�� ࠭�� ��࠭������ ����? (Y/N)(y/n): ");
    while(1){
        scanf("%c", &symbol);
        if(symbol=='N' || symbol=='n'){
            printf("==================================================================\n");
            return 0;
        }
        else if(symbol=='Y' || symbol=='y'){
            break;
        }
    }
    while(1){
        printf("�롥�� ᫮� (1 - 3) (9 - ����� ����� / 0 - ��ᬮ���� ����騥��): ");
        scanf("%d", &save_number);
        if(save_number==9){
            printf("==================================================================\n");
            return 0;
        }
        if(save_number==0){
            for(i=1;i<=3;i++){
                show_saves(i); // ��ᬮ�� �������� ��࠭����
            }
            continue;
        }
        FILE* f;
        step=check_have_save(save_number, 2); // �஢�ઠ �� ����稥 ��࠭����
        if(step==2){ // �᫨ ��࠭���� �� ������� - �롨ࠥ� ��㣮�
            continue;
        }
        step=check_save_file(save_number); // �஢�ઠ 䠩�� �� 楫��⭮���
        if(!step){ // �᫨ ���०��� - �롨ࠥ� ��㣮�
            continue;
        }
        f=open_save_file(save_number, 1);
        fscanf(f,"%d %d %d %d %d %d %d\n", &field_row, &field_col, &players_count, &gamer, &level, &moves_1, &moves_2);
        for(i=0;i<field_row;i++){
            fscanf(f,"%d\n%d\n%d\n%d\n", &pos1[i], &pos1_old[i], &pos2[i], &pos2_old[i]);
            field[i][pos1[i]]=1;
            field[i][pos2[i]]=2;
        }
        fscanf(f,"%s %s", &name1, &name2);
        fclose(f);
        break;
    }
    printf("==================================================================\n");
    printf("���� ����㧪�...");
    sleep(1);
    return 1;
}
void main(){
    int step, row;
    hello();
    rules_of_the_game();
    step=loading_save_game();
    if(step==0){ // �᫨ ��稭��� ����� ����
        field_size();
        game_mode();
        init_game();
    }
    system("cls");
    print_state();
    if(players_count==2){ // ���� ��� ���� ��ப��
        while(1){
            step=check_game_over();
            if(step){ // ��室 �� ���� �᫨ ��-� �������
                break;
            }
            row=change_pos(gamer);
            if(!row){ // ��室 �� ���� �� ���樠⨢� ���짮��⥫�
                save_game();
                break;
            }
            print_state();
            gamer=3-gamer; // ����� ��ப�
            print_path(gamer, row);
        }
    }
    else { // ���� ��� ���� � �������஬
        while(1){
            row=change_pos(gamer);
            if(!row){ // ��室 �� ���� �� ���樠⨢� ���짮��⥫�
                save_game();
                break;
            }
            print_state();
            step=check_game_over();
            if(step){ // ��室 �� ���� �᫨ ��-� �������
                break;
            }
            printf("\n�������� �㬠��...");
            sleep(1);
            row=change_pos_PC(level);
            print_state();
            print_path(gamer, row);
            step=check_game_over();
            if(step){ // ��室 �� ���� �᫨ ��-� �������
                break;
            }
        }
    }
    system("pause");
}