#ifndef GAMEVIEW_H_INCLUDED
#define GAMEVIEW_H_INCLUDED

#include <QGraphicsView>
#include <string>
#include <QWidget>

#define PC 0.9
#define PM 0.3
#define STEP 0.03
using namespace std;

struct treeNode
{
    bool ismyturn;
    int layer;
    int alpha;
    int beta;
    treeNode *child[15];
    int value;
    int condition[4][4];
    bool can_choose[4];

    treeNode()
    {
        for (int i = 0; i < 15; i++)
            this->child[i] = NULL;
    }
};

struct unit
{
    double parameter[12];
    double score;
    double possiblity;
};

class GameView : public QGraphicsView
{
    Q_OBJECT

public:
    GameView(QWidget *parent = 0);
    int getScore(){ return score;}
    int getBiggest(){return biggestNum;}
    int getHigh();

private:
    void startGame();
    bool up_ai(int matrx[4][4]);
    bool down_ai(int matrx[4][4]);
    bool left_ai(int matrx[4][4]);
    bool right_ai(int matrx[4][4]);
    bool newCube();
    bool canadd();
    bool canmove();
    void print();
    int smooth(int matrx[4][4]);
    int monotonicity(int matrx[4][4], double parameter[12]);
    int monotonicity(int matrx[4][4]);
    int emptycell(int matrx[4][4]);
    int islandemptycell(int matrx[4][4]);
    double minimax_tree(treeNode *&node, int matrx[4][4], int alpha, int beta, int layer, double parameter[12], bool ismyt);
    int chose_turn(int matrx[4][4], double paremeter[12]);
    void keyPressEvent(QKeyEvent *event);

    QGraphicsScene *scene;
    int score;
    int biggestNum;
    string high;
    int ai_chose;
    int max_alpha;
    int max_beta;
    enum {rowNum = 4,
          colNum = 4,
          INF = 1000000000,
          MININF = -1000000000,
          THINKING_TIME = 1,
          ITERATION = 100,
          INITIAL_NUM = 101,    //odd
          };
    int nums[rowNum][colNum];
    QPointF position[rowNum][colNum];
    void ai_train_play(unit &a);
    bool canmove_ai(unit &a);
    void assignment(unit &a, unit b);
    void delete_tree(treeNode *& t);

signals:
    void scoreupdata(int, int);
    void ai_done();

public slots:
    void restartGame();
    void ai_play();
    void train();
    bool up();
    bool down();
    bool left();
    bool right();
};

#endif // GAMEVIEW_H_INCLUDED
