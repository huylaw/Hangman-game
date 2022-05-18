#include "grap.h"

using namespace std;

const int console_width = 500;
const int console_height = 400;

string word; // tu ma ng choi / bot can doan
string guessed; //cac tu ma nguoi choi / bot da doan
int lives = 7; // mang cua nguoi choi / bot
int score = 0; // diem so nguoi choi
int times = 90; //thoi gian choi
int high_score;
bool stop = 1;
int level; // luu trang thai level cua tro choi

struct Player{
    string name;
    int p_score;
};

//ve tieu de game
void drawTitle(int n, int m, int x, int y, string text){
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(i==0 || i==n-1 || j==0 || j==m-1){
                cout << "*";
            }else cout << " ";
        }
        cout << endl;
    }
    gotoXY(x,y);
    cout << text;
}

//ve gia treo co
void drawBase(int lives){
    switch(lives){
        case 7: cout << "-------" << endl;
                cout << " |" << endl;
                cout << " |" << endl;
                cout << " |" << endl;
                cout << " |" << endl;
                cout << " |" << endl;
                cout << " |" << endl;
                cout << "_|______" << endl;
                break;
        case 6: cout << "-------" << endl;
                cout << " |   |" << endl;
                cout << " |   |" << endl;
                cout << " |" << endl;
                cout << " |" << endl;
                cout << " |" << endl;
                cout << " |" << endl;
                cout << "_|______" << endl;
                break;
        case 5: cout << "-------" << endl;
                cout << " |   |" << endl;
                cout << " |   |" << endl;
                cout << " |   O" << endl;
                cout << " |" << endl;
                cout << " |" << endl;
                cout << " |" << endl;
                cout << "_|______" << endl;
                break;
        case 4: cout << "-------" << endl;
                cout << " |   |" << endl;
                cout << " |   |" << endl;
                cout << " |   O" << endl;
                cout << " |   |" << endl;
                cout << " |" << endl;
                cout << " |" << endl;
                cout << "_|______" << endl;
                break;
        case 3: cout << "-------" << endl;
                cout << " |   |" << endl;
                cout << " |   |" << endl;
                cout << " |   O" << endl;
                cout << " |  /|" << endl;
                cout << " |" << endl;
                cout << " |" << endl;
                cout << "_|______" << endl;
                break;
        case 2: cout << "-------" << endl;
                cout << " |   |" << endl;
                cout << " |   |" << endl;
                cout << " |   O" << endl;
                cout << " |  /|\\" << endl;
                cout << " |" << endl;
                cout << " |" << endl;
                cout << "_|______" << endl;
                break;
        case 1: cout << "-------" << endl;
                cout << " |   |" << endl;
                cout << " |   |" << endl;
                cout << " |   O" << endl;
                cout << " |  /|\\" << endl;
                cout << " |  /" << endl;
                cout << " |" << endl;
                cout << "_|______" << endl;
                break;
        case 0: cout << "-------" << endl;
                cout << " |   |" << endl;
                cout << " |   |" << endl;
                cout << " |   O" << endl;
                cout << " |  /|\\" << endl;
                cout << " |  / \\" << endl;
                cout << " |" << endl;
                cout << "_|______" << endl;
                break;
    }
}

// lop gio
struct Hour {
	int minute;
	int second;
};
// doi so thanh chu
char inToA(int k) {
	switch (k)
	{
	case 0:return '0';
	case 1:return '1';
	case 2:return '2';
	case 3:return '3';
	case 4:return '4';
	case 5:return '5';
	case 6:return '6';
	case 7:return '7';
	case 8:return '8';
	case 9:return '9';
	default:
		break;
	}
}
// them chu vao mang
void insertarray(char *h, Hour *j) {
	int bait = 0;
	bait = j->second;
	h[4] = inToA(bait % 10);
	h[3] = inToA(bait /= 10);

	bait = j->minute;
	h[1] = inToA(bait % 10);
	h[0] = inToA(bait /= 10);
}
// xet dk time
bool changetime(Hour *h) {
	if (h->second > 0) --h->second;
	else if (h->minute > 0) {
		h->second = 59;
		--h->minute;
	}
	else return 0;
	return 1;
}
// in dong ho
void printClock() {
    Hour h;
    if(level == 0) h = {1,1};
    else if(level == 1) h ={0, 31};
    char a[5] = {'0','0',':','0','0'};
    while (stop==1){
        if (!changetime(&h)) stop = 0;
        insertarray(a, &h);
        WriteBlockChar(a, 1, 5, 30, 3,0x004|0x008);
        Sleep(1000);
    }
    return;
}
//
void close(DWORD evt) {
	if (evt == CTRL_CLOSE_EVENT) stop = 0;
}

int main(){
    bool game = true; //vong lap game
    bool run_menu = true; // man menu
    bool run_level = false; // level cho game
    bool run_topic = false; // chon topic
    bool player_run = false; //vong lap mode ng choi
    bool bot_run = false; // mode bot choi
    bool run_highScore = false; // xem diem cao
    bool end_game = false; // hien thi man end game

    int wordLength;
    char menu;
    fstream f;
    char choose_topic; // chon topic
    char choose_level; // chon level
    char choose_highScore; // man xem diem cao
    char exit_loop; // thoat game
    string topic; // luu ten topic

    vector<string> a; //luu data doc tu file
    string data; // luu tung data trong txt
    Player pl; //
    int X = 1;

    vector<string> v; //luu data brain bot
    f.open("brainBot.txt", ios::in);
    while(!f.eof()){
        getline(f, data);
        v.push_back(data);
    }
    f.close();

	SetConsoleTitle("19021305");
    resizeConsole(console_width, console_height);
    disableResizeConsole();
    SetConsoleOutputCP(65001); // viet tieng viet tren console

    while(game==true){
        //tao menu
        while(run_menu==true){
            //lay high_score trong file
            f.open("high_scores.txt", ios::out | ios::in);
            while(f && !f.eof()){
                f >> pl.name >> pl.p_score;
            }
            high_score = pl.p_score;
            f.close();

            system("cls");
            textColor(14);
            drawTitle(3, 64, 27, 2, "HANGMAN GAME");
            gotoXY(28,7);
            textColor(4);
            cout << "MENU GAME";
            gotoXY(27,10);
            textColor(11);
            cout << "Người chơi(a)";
            gotoXY(27,12);
            cout << "Bot chơi(b)";
            gotoXY(27,14);
            cout << "Điểm cao(c)";
            gotoXY(27,16);
            cout << "Exit(d)";
            do{
                gotoXY(25,18);
                cout << "Lựa chọn của bạn: ";
                menu = getche();
                if(menu=='a' || menu=='b' || menu=='c' || menu=='d') break;
            }while(menu!='a' || menu!='b' || menu!='c' || menu!='d');
            if(menu=='a'){
                run_level = true;
            }else if(menu=='b'){
                bot_run = true;
                topic = "brainBot.txt";
            }else if(menu=='c'){
                run_highScore = true;
            }else X = 0;
            run_menu = false;
        }
        // chon muc do
        while(run_level == true){
            system("cls");
            textColor(14);
            drawTitle(3, 64, 27, 2, "HANGMAN GAME");
            gotoXY(28,7);
            textColor(4);
            cout << "CHOOSE LEVEL";
            gotoXY(27,10);
            textColor(11);
            cout << "Dễ(a)";
            gotoXY(27,12);
            cout << "Khó(b)";
            gotoXY(27,14);
            cout << "Menu Game(c)";
            do{
                gotoXY(25,18);
                cout << "Lựa chọn của bạn: ";
                choose_level = getche();
                if(choose_level=='a' || choose_level=='b' || choose_level=='c') break;
            }while(choose_level!='a' || choose_level!='b' || choose_level!='c');
            if(choose_level=='a'){
                level=0;
                run_topic=true;
            }else if(choose_level=='b'){
                level=1;
                run_topic=true;
            }else{
                run_menu = true;
            }
            run_level=false;
        }
        // chon chu de cho game
        while(run_topic){
            system("cls");
            textColor(14);
            drawTitle(3, 64, 27, 2, "HANGMAN GAME");
            gotoXY(28,7);
            textColor(4);
            cout << "CHOOSE TOPIC";
            gotoXY(27,10);
            textColor(11);
            cout << "Trái cây(a)";
            gotoXY(27,12);
            cout << "Phương tiện(b)";
            gotoXY(27,14);
            cout << "Choose Level(c)";
            do{
                gotoXY(25,18);
                cout << "Lựa chọn của bạn: ";
                choose_topic = getche();
                if(choose_topic=='a' || choose_topic=='b' || choose_topic=='c') break;
            }while(choose_topic!='a' || choose_topic!='b' || choose_topic!='c');
            if(choose_topic=='a'){
                topic="fruits.txt";
                player_run=true;
            }
            else if(choose_topic=='b'){
                topic="transports.txt";
                player_run=true;
            }else{
                run_level=true;
            }
            f.open(topic, ios::in);
            a.clear();
            while(!f.eof()){
                getline(f, data);
                a.push_back(data);
            }
            f.close();
            run_topic=false;
        }
        // Mode nguoi choi
        while(player_run==true){
            system("cls");

            SetConsoleCtrlHandler((PHANDLER_ROUTINE)close, TRUE);
            stop = 1;
            thread t;
            t = thread(printClock);
            t.detach();

            srand(time(NULL));
            word = a[rand()%a.size()];
            wordLength = word.length();
            string hidden_word(wordLength, '_');
            char guess=' '; //bien luu gia tri ng dung nhap
            int found = 0;
            textColor(14);
            drawTitle(3, 64, 27, 2, "HANGMAN GAME");
            while(lives>=0){
                //consoleClear();
                gotoXY(5, 4);
                textColor(6);
                cout << "Scores: " << score << " " << char(15);
                gotoXY(5, 5);
                cout << "High Score: " << high_score;
                gotoXY(50, 4);
                textColor(4);
                cout << "Lives: " << lives << " " << char(3);

                textColor(11);
                gotoXY(15, 10);
                cout << "Hidden Word: (There are " << wordLength << " character)";

                gotoXY(15, 11);
                for(int i=0; i<wordLength; i++){
                    cout << " " << hidden_word[i] << " ";
                }

                gotoXY(15, 13);
                cout << "Guessed Letters: " << guessed;

                gotoXY(1, 10);
                drawBase(lives);
                if(found == wordLength)stop = 0;
                if(found == wordLength){
                    guessed = "";
                    gotoXY(25,17);
                    cout << "Exactly!   " << "(This word is: " << word << ")";
                    char s;
                    do{
                        gotoXY(15,19);
                        cout << "The next word(y/n): ";
                        s = getche();
                        if(s=='y'||s=='n') break;
                    }while(s!='y' || s!='n');
                    if(s=='y'){
                        break;
                    }else if(s=='n'){
                        lives = 0;
                        break;
                    }
                }
                if(lives==0) stop = 0;
                if(stop==0){
                    lives = 0;
                    gotoXY(50, 4);
                    textColor(4);
                    cout << "Lives: " << lives << " " << char(3);
                }
                if(lives==0 || stop==0){
                    guessed = "";
                    gotoXY(25,17);
                    textColor(11);
                    cout << "You Died!   " << "(This word is: " << word << ")";
                    char s;
                    do{
                        gotoXY(15,19);
                        cout << "Do you want play again??(y/n): ";
                        s = getche();
                        if(s=='y'||s=='n') break;
                    }while(s!='y' || s!='n');
                    if(s=='y'){
                        lives=7;
                        score=0;
                        break;
                    }else if(s=='n'){
                        break;
                    }
                }
                gotoXY(15, 15);
                cout << "Pick a letter: ";
                guess = getche();
                guessed = guessed + " " + guess;
                if( hidden_word.find(guess)!=string::npos ) lives++;

                int flagFound = 0;
                for(int i=0; i<wordLength; i++){
                    if(word[i]==guess && hidden_word[i]=='_'){
                        hidden_word[i]=guess;
                        found++;
                        score+=5;
                        flagFound = 1;
                    }
                }
                if(flagFound!=1) lives--;
                if(found == wordLength){score+=10;}
            }
            if(lives==0){
                if(score > high_score){
                    system("cls");
                    string name;
                    textColor(11);
                    gotoXY(25,12);
                    cout << "High score: " << score;
                    gotoXY(25,13);
                    cout << "Enter your name: ";
                    cin >> name;
                    f.open("high_scores.txt", ios::trunc | ios::out | ios::in);
                    pl.name = name;
                    pl.p_score = score;
                    f << pl.name << " " << pl.p_score;
                    f.close();
                }
                end_game = true;
                player_run = false;
            }
        }
        // Mode bot choi
        while(bot_run==true){
            system("cls");
            textColor(14);
            drawTitle(3, 64, 27, 2, "HANGMAN GAME");
            gotoXY(21,10);
            cout << "Enter your chosen Word: " << endl;
            gotoXY(27,12);
            cin >> word;
            wordLength = word.length();
            string hidden_word(wordLength, '_');
            char bot = ' '; //luu cac lan bot doan
            string arr_bot; // luu all ca ky tu ma bot da doan
            string bot_choose_wrong; // luu cac tu ma bot doan sai
            string bot_choose_right; // luu cac tu ma bot doan dung
            int found = 0;

            system("cls");
            textColor(14);
            drawTitle(3, 64, 27, 2, "HANGMAN GAME");
            textColor(11);
            gotoXY(15,8);
            cout << "Your chosen Word: " << word;

//BUOC 1:   // tim cac tu trong data co cung wordLength
            vector<string> brain_bot; //vecto luu cac tu co cung kich thuoc
            string brain; // luu data dang chuoi
            for(int i=0; i<v.size(); i++){
                int len = v.at(i).length();
                if(len == wordLength) {
                    brain+=v.at(i);
                    brain_bot.push_back(v.at(i));
                }
            }
            // tim nguyen am xuat hien nhieu nhat
            bot = find_vowelMax(brain);
            while(lives>=0){
                system("cls");
                cout << "Bot choose: " << bot << endl;
                arr_bot+=bot;
                cout << "Bot da doan: " << arr_bot << endl;
                char you;
                cout << "Yes/no: ";
                you = getche();
                cout << endl;
                if(you=='y'){
                    bot_choose_right+=bot;
                    found++;
                    brain = "";
                    // ktra , lay nhung tu co chua bot choose right
                    for(int i=0; i<brain_bot.size(); i++){
                        if(ktra_2(brain_bot.at(i), bot_choose_right)==0){
                            brain_bot.erase(brain_bot.begin()+i);
                        }
                    }
                }else if(you=='n'){
                    bot_choose_wrong+=bot;
                    lives--;
                    //ktra, xoa nhung tu co chua bot choose wrong
                    for(int i=0; i<brain_bot.size(); i++){
                        if(ktra_2(brain_bot.at(i), bot_choose_wrong)==1){
                            brain_bot.erase(brain_bot.begin()+i);
                        }
                    }
                    for(auto& x: brain_bot){ cout << x <<" ";}
                    //for(auto& x: brain_bot){ brain+=x;}
                }
                //dem tan suat

                getch();
            }
            if(lives!=0) cout << "You lose";
            else cout << "You win";
            getch();
        }
        // Xem diem cao
        while(run_highScore==true){
            system("cls");
            textColor(14);
            drawTitle(3, 64, 27, 2, "HANGMAN GAME");
            gotoXY(28,7);
            textColor(4);
            cout << "HIGH SCORE";
            gotoXY(27,10);
            textColor(11);
            cout << pl.name << " - " << high_score << " điểm";
            gotoXY(27,14);
            cout << "Menu Game(c)";
            do{
                gotoXY(25,18);
                cout << "Lựa chọn của bạn: ";
                choose_highScore = getche();
                if(choose_highScore=='c') break;
            }while(choose_highScore!='c');
            if(choose_highScore=='c'){
                run_menu = true;
            }
            run_highScore=false;
        }
        // man hinh endgame
        while(end_game==true){
            system("cls");
            textColor(4);
            gotoXY(1,5);
            drawTitle(5, 64, 28, 7, "YOU DIED");
            textColor(6);
            gotoXY(28,12);
            cout << "SCORES: " << score;
            textColor(11);
            gotoXY(1,10);
            drawBase(lives);

            gotoXY(20,15);
            cout << "Menu Game(a)";
            gotoXY(40,15);
            cout << "Exit(b)";
            do{
                gotoXY(25,18);
                cout << "Lựa chọn của bạn: ";
                exit_loop = getche();
                if(exit_loop=='a' || exit_loop=='b') break;
            }while(exit_loop!='a' || exit_loop!='b');
            if(exit_loop == 'a'){
                run_menu = true;
                lives = 7;
                score = 0;
            }else{
                X = 0;
            }
            end_game = false;
        }
        if(X==0) game = false;
    }
    system("cls");
    textColor(14);
    gotoXY(20,10);
    cout << "THANK YOU FOR PLAYING THE GAME!!!";
    gotoXY(1,18);
    getch();
    return 0;
}
