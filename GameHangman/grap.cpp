#include "grap.h"

using namespace std;

void resizeConsole(int width, int height){
    static HWND h = NULL;
    h = GetConsoleWindow();
    RECT rect;
    GetWindowRect(h, &rect);
    MoveWindow(h, rect.left, rect.top, width, height, TRUE);
}

void ClearConsole(){
    HANDLE h = NULL;
    COORD Position;
    h = GetStdHandle(STD_OUTPUT_HANDLE);
    Position.X = 0;
    Position.Y = 0;
    SetConsoleCursorPosition(h, Position);
}

void gotoXY(int x, int y){
    static HANDLE h = NULL;
    COORD Position = {x-1, y-1};
    h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(h, Position);
}

void textColor(int x){
    static HANDLE h = NULL;
    h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, x);
}

void showScrollBar(bool show){
    static HWND h = NULL;
    h = GetConsoleWindow();
    ShowScrollBar(h, SB_BOTH, show);
}

//void setScreenBufferSize(SHORT width, SHORT height){
//    static HANDLE h = NULL;
//    h = GetStdHandle(STD_OUTPUT_HANDLE);
//    COORD newSize;
//    newSize.X = width;
//    newSize.Y = height;
//    SetConsoleScreenBufferSize(h, newSize);
//}

void disableResizeConsole(){
    static HWND h = NULL;
    h = GetConsoleWindow();
    SetWindowLong(h, GWL_STYLE, GetWindowLong(h, GWL_STYLE) & ~WS_SIZEBOX);
}

//ham in ra man hinh thay the ham Cout
void WriteBlockChar(char * Arraych, int row, int col, int x, int y, int color){
	CHAR_INFO *charater = new CHAR_INFO[row*col];
	for (int i = 0; i < row*col; i++) {
		charater[i].Attributes = color;
		charater[i].Char.AsciiChar = Arraych[i];
	}
	COORD sizebuff = { col,row };
	COORD pos = { 0,0 };
	SMALL_RECT earea = { x,y,x + col - 1,y + row - 1 };
	WriteConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE), charater, sizebuff, pos, &earea);
	delete[] charater;
}

// ham tim max vowel
char find_vowelMax(string s){
    char a;
    map<char, int> vowel ={ {'a', 0}, {'e', 0}, {'i', 0}, {'o', 0}, {'u', 0} };
    for(int i=0; i<s.length(); i++){
        if(s[i] == 'a') vowel.at('a')++;
        if(s[i] == 'e') vowel.at('e')++;
        if(s[i] == 'i') vowel.at('i')++;
        if(s[i] == 'o') vowel.at('o')++;
        if(s[i] == 'u') vowel.at('u')++;
    }
            //tim ky tu xuat hien nhieu nhat
    int max_vowel = 0;
    for(auto& x: vowel){
        if(x.second >= max_vowel) max_vowel = x.second;
    }
    for(auto& x: vowel){
        if(x.second == max_vowel){
            a = x.first;
            break;
        }
    }
    return a;
}

// kiem tra xem 1 tu co chua ky tu (khong co index)
int ktra_1(string s, char a){
    for(int i=0; i<s.length(); i++){
        if(s[i] == a) return 0;
    }
    return 1;
}

int ktra_2(string s1, string s2){
    for(int i=0; i<s2.length(); i++){
        if(ktra_1(s1, s2[i])==1) return 0;
    }
    return 1; //neu s1 chua moi phan tu cua s2
}

//tim cac tu trong brain bot co chua cac tu bot_choose_right
string find_botRight(vector<string> v, string s){
    string x;
    for(int i=0; i<v.size(); i++){
        for(int j=0; j<s.length(); j++){
            if(ktra_1(v.at(i), s[j])==0) x+=v.at(i);
        }
    }
    return x;
}

//tim cac tu trong brain bot khong chua cac tu bot_chooose_wrong
string find_botWrong(vector<string> v, string s){
    string x;
    for(int i=0; i<v.size(); i++){
        for(int j=0; j<s.length(); j++){
            if(ktra_1(v.at(i), s[j])==1) x+=v.at(i);
        }
    }
    return x;
}

char find_max(map<char, int> m, string s){
    char a;
    int max=0;
    for(auto& x: m){
        if(ktra_1(s, x.first)==1){
            if(x.second>=max) max=x.second;
        }
    }
    for(auto& x: m){
        if(x.second == max){
            a = x.first;
            break;
        }
    }
    return a;
}








