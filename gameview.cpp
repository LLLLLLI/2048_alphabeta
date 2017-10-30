#include <QtGui>
#include <ctime>
#include <iostream>
#include <utility>
#include <cmath>
#include <windows.h>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

#include "gameview.h"
#include "cube.h"

GameView::GameView(QWidget *parent)
    : QGraphicsView(parent)
{
    scene = new QGraphicsScene(0, 0, 450, 450);
    scene->setBackgroundBrush(QColor("#b8af9e"));
    setScene(scene);
    setCacheMode(QGraphicsView::CacheBackground);  //ºóÌ¨»º³å
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            position[j][i] = QPointF(110*i + 10, 110*j + 10);
    startGame();
    //ai_play();
}

void GameView::startGame()
{
    score = 0;
    biggestNum = 0;
    ifstream in("high.txt");
    getline(in, high);
    in.close();
    for(int i = 0; i < rowNum; i++){
        for(int j = 0; j < colNum; j++){
            nums[j][i] = 0;
            scene->addItem(new Cube(position[i][j], QString::number(0)));
        }
    }
    newCube();
    newCube();
}

int GameView::getHigh()
{
    stringstream ss;
    ss << high;
    int l;
    ss >> l;
    return l;
}

bool GameView::newCube()
{
    QList<pair<int, int> > can_add;
    for(int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (nums[i][j] == 0)
                can_add.append(make_pair(i, j));
    if(can_add.length() != 0)
    {
        int index, num1, row, col;
        qsrand(time(0));
        index = qrand()%can_add.length();
        row = can_add.at(index).first;
        col = can_add.at(index).second;
        num1 = qrand()%10 >= 1 ? 2 : 4;
        nums[row][col] = num1;
        QList<QGraphicsItem*> new_cube = scene->items(position[row][col],Qt::IntersectsItemShape,Qt::AscendingOrder);
        Cube *n_cube = qgraphicsitem_cast<Cube*>(new_cube[0]);
        n_cube->updateNum(QString::number(num1));
        return true;
    }
    return false;
}

void GameView::restartGame()
{
    QList<QGraphicsItem*> list = scene->items(0, 0, 450, 450, Qt::IntersectsItemShape, Qt::AscendingOrder);
    foreach(QGraphicsItem *item, list)
    {
        scene->removeItem(item);
        delete item;
        item = NULL;
    }
    startGame();
}

bool GameView::left()
{
    bool able_move = false;
    bool able_new = false;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 4; j++){
            if ((nums[j][i] == 0) && nums[j][i+1] != 0){
                int row = j;
                int col = i;
                able_new = true;
                while((nums[row][col] == 0) && nums[row][col+1] != 0)
                {
                    nums[row][col] = nums[row][col+1];
                    nums[row][col+1] = 0;
                    if (--col < 0)
                        break;
                }
            }
        }
    }
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 4; j++){
            if ((nums[j][i] != 0) && (nums[j][i] == nums[j][i+1])){
                able_move = true;
                able_new = true;
                nums[j][i] *= 2;
                nums[j][i+1] = 0;
                score += nums[j][i]/2;
                if(nums[j][i] > biggestNum)
                    biggestNum = nums[j][i];
            }
        }
    }
    if(able_move == true){
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 4; j++){
                if ((nums[j][i] == 0) && nums[j][i+1] != 0){
                    nums[j][i] = nums[j][i+1];
                    nums[j][i+1] = 0;
                }
            }
        }
    }
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
    {
        QList<QGraphicsItem*> change = scene->items(position[j][i],Qt::IntersectsItemShape, Qt::AscendingOrder);
        Cube *c_cube = qgraphicsitem_cast<Cube*>(change[0]);
        c_cube->updateNum(QString::number(nums[j][i]));
    }
    if (able_new)
    {newCube();}
    viewport()->update();
    return able_move;
}

bool GameView::right()
{
    bool able_move = false;
    bool able_new = false;
    for(int i = 3; i > 0; i--){
        for(int j = 0; j < 4; j++){
            if ((nums[j][i] == 0) && nums[j][i-1] != 0){
                int row = j;
                int col = i;
                able_new = true;
                while((nums[row][col] == 0) && nums[row][col-1] != 0)
                {
                    nums[row][col] = nums[row][col-1];
                    nums[row][col-1] = 0;
                    if (++col > 3)
                        break;
                }
            }
        }
    }
    for(int i = 3; i > 0; i--){
        for(int j = 0; j < 4; j++){
            if ((nums[j][i] != 0) && (nums[j][i] == nums[j][i-1])){
                able_move = true;
                able_new = true;
                nums[j][i] *= 2;
                nums[j][i-1] = 0;
                score += nums[j][i]/2;
                if(nums[j][i] > biggestNum)
                    biggestNum = nums[j][i];
            }
        }
    }
    if(able_move == true){
        for(int i = 3; i > 0; i--){
            for(int j = 0; j < 4; j++){
                if ((nums[j][i] == 0) && nums[j][i-1] != 0){
                    nums[j][i] = nums[j][i-1];
                    nums[j][i-1] = 0;
                }
            }
        }
    }
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
    {
        QList<QGraphicsItem*> change = scene->items(position[j][i],Qt::IntersectsItemShape, Qt::AscendingOrder);
        Cube *c_cube = qgraphicsitem_cast<Cube*>(change[0]);
        c_cube->updateNum(QString::number(nums[j][i]));
    }
    if (able_new)
    {newCube();}
    viewport()->update();
    return able_move;
}

bool GameView::up()
{
    bool able_move = false;
    bool able_new = false;
    for(int j = 0; j < 3; j++){
        for(int i = 0; i < 4; i++){
            if ((nums[j][i] == 0) && nums[j+1][i] != 0){
                int row = j;
                int col = i;
                able_new = true;
                while((nums[row][col] == 0) && nums[row+1][col] != 0)
                {
                    nums[row][col] = nums[row+1][col];
                    nums[row+1][col] = 0;
                    if (--row < 0)
                        break;
                }
            }
        }
    }
    for(int j = 0; j < 3; j++){
        for(int i = 0; i < 4; i++){
            if ((nums[j][i] != 0) && (nums[j][i] == nums[j+1][i])){
                able_move = true;
                able_new = true;
                nums[j][i] *= 2;
                nums[j+1][i] = 0;
                score += nums[j][i]/2;
                if(nums[j][i] > biggestNum)
                    biggestNum = nums[j][i];
            }
        }
    }
    if(able_move == true){
        for(int j = 0; j < 3; j++){
            for(int i = 0; i < 4; i++){
                if ((nums[j][i] == 0) && nums[j+1][i] != 0){
                    nums[j][i] = nums[j+1][i];
                    nums[j+1][i] = 0;
                }
            }
        }
    }
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
    {
        QList<QGraphicsItem*> change = scene->items(position[j][i],Qt::IntersectsItemShape, Qt::AscendingOrder);
        Cube *c_cube = qgraphicsitem_cast<Cube*>(change[0]);
        c_cube->updateNum(QString::number(nums[j][i]));
    }
    if (able_new)
    {newCube();}
    viewport()->update();
    return able_move;
}

bool GameView::down()
{
    bool able_move = false;
    bool able_new = false;
    for(int j = 3; j > 0; j--){
        for(int i = 0; i < 4; i++){
            if ((nums[j][i] == 0) && nums[j-1][i] != 0){
                int row = j;
                int col = i;
                able_new = true;
                while((nums[row][col] == 0) && nums[row-1][col] != 0)
                {
                    nums[row][col] = nums[row-1][col];
                    nums[row-1][col] = 0;
                    if (++row > 3)
                        break;
                }
            }
        }
    }
    for(int j = 3; j > 0; j--){
        for(int i = 0; i < 4; i++){
            if ((nums[j][i] != 0) && (nums[j][i] == nums[j-1][i])){
                able_move = true;
                able_new = true;
                nums[j][i] *= 2;
                nums[j-1][i] = 0;
                score += nums[j][i]/2;
                if(nums[j][i] > biggestNum)
                    biggestNum = nums[j][i];
            }
        }
    }
    if(able_move == true){
        for(int j = 3; j > 0; j--){
            for(int i = 0; i < 4; i++){
                if ((nums[j][i] == 0) && nums[j-1][i] != 0){
                    nums[j][i] = nums[j-1][i];
                    nums[j-1][i] = 0;
                }
            }
        }
    }
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
    {
        QList<QGraphicsItem*> change = scene->items(position[j][i],Qt::IntersectsItemShape, Qt::AscendingOrder);
        Cube *c_cube = qgraphicsitem_cast<Cube*>(change[0]);
        c_cube->updateNum(QString::number(nums[j][i]));
    }
    if (able_new)
    {newCube();}
    viewport()->update();
    return able_move;
}

bool GameView::canadd()
{
    bool can_add = false;
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            if(nums[i][j] == 0)
                can_add = true;
    return can_add;
}

bool GameView::canmove()
{
    bool can_move = false;
    if(!canadd()){
        for(int i = 0; i < 3; i++)
            for(int j = 0; j < 4; j++){
                if(j ==3){
                    if(nums[j][i] == nums[j][i+1])
                        can_move = true;
                }else{
                    if(nums[j][i] == nums[j][i+1] || nums[j][i] == nums[j+1][i]){
                        can_move = true;
                    }
                }
            }
    }else{can_move = true;}
    if(!can_move){
        stringstream ss;
        ss << high;
        int i;
        ss >> i;
        if (score > i)
        {
            ofstream out("high.txt");
            out << score;
            out.close();
        }
        QMessageBox::information(this, tr("Game Over!"), tr("You compounded %1 !\n"
                                                            "Your score: %2").arg(QString::number(biggestNum)).arg(QString::number(score)));
        restartGame();
    }
    return can_move;
}

void GameView::keyPressEvent(QKeyEvent * event)
 {
     switch(event->key())
     {
     case Qt::Key_Up:
        //ai_play();
        up();
        emit scoreupdata(score, biggestNum);
        print();
        canmove();
        break;
     case Qt::Key_Down:
        down();
        emit scoreupdata(score, biggestNum);
        print();
        canmove();
        break;
     case Qt::Key_Left:
        left();
        emit scoreupdata(score, biggestNum);
        print();
        canmove();
        break;
     case Qt::Key_Right:
        right();
        emit scoreupdata(score, biggestNum);
        print();
        canmove();
        break;
     default:
         QGraphicsView::keyPressEvent(event);
         break;
     }
 }

 void GameView::print()
 {
     for(int i = 0; i < 4; i++)
            for(int j = 0; j < 4; j++){
                std::cout << nums[i][j];
                if(j == 3)
                    std::cout << "\n";
    }
 }

void GameView::ai_play()
{
    double a[12] = {0.738208, 0.30245, 0.795086, 0.498721, 0.2888, 0.3991, 0.258, 0.2666, 0.9788, 0.6453, 0.5918, 0.378};
    int choice;
    while (canmove())
    {
        int tem[4][4];
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                tem[i][j] = nums[i][j];
        choice = chose_turn(tem, a);
        cout << "choice" << choice << endl;
        switch (choice)
        {
        case 0:
            right();
            print();
            break;
        case 1:
            left();
            print();
            break;
        case 2:
            down();
            print();
            break;
        case 3:
            up();
            print();
            break;
        }
        emit scoreupdata(score, biggestNum);
        //emit ai_done();
        this->show();
        qApp->processEvents();  //update every move!!!
    }
}

int GameView::chose_turn(int matrx[4][4], double parameter[12])
{
    DWORD start = GetTickCount();
    int bestchoice;
    int maxx = MININF;
    treeNode *head = NULL;
    int depth = 2;
    while (GetTickCount() - start < THINKING_TIME)
    {
        minimax_tree(head, matrx, MININF, INF, depth, parameter, true);
        for (int i = 0; i < 4; i++)
            if (head->can_choose[i] && head->child[i]->beta > maxx)
            {
                bestchoice = i;
                maxx = head->child[i]->beta;
            }
        depth += 1;
    }
    delete_tree(head);
    //cout << "depth" << depth << endl;
    return bestchoice;
}

//深度优先 这里设定了一个超时时间，默认为100ms，在这个时间内，会从1开始，搜索到所能达到的深度
//返回一个头结点（不用返回，因值已经改变），然后设置一个新函数find_turn 保存头结点，一遍一遍向下更深入，返回选择
//只放入最坏的那个
//一来一回算一层
double GameView::minimax_tree(treeNode *&node, int matrx[4][4], int alpha, int beta, int layer, double parameter[12], bool ismyt)
{
    if (node)
    {
        if (ismyt == true)
        {
            for (int i = 0; node->child[i]; i++)
            {
                double value = minimax_tree(node->child[i], node->child[i]->condition, node->alpha, beta, layer-1, parameter, false);
                if (value > node->alpha)
                    node->alpha = value;
                if (node->alpha >= beta)
                    break;
            }
            return node->alpha;
        }else
        {
            for (int i = 0; node->child[i]; i++)
            {
                double value = minimax_tree(node->child[i], node->child[i]->condition, alpha, node->beta, layer-1, parameter, true);
                if (value < node->beta)
                    node->beta = value;
                if (alpha >= node->beta)
                    break;
            }
            return node->beta;
        }
    }else
    {
        if (layer == 0)
            {
                return -parameter[0]*smooth(matrx)
                   + parameter[1]*emptycell(matrx)
                   + parameter[2]*monotonicity(matrx)
                   - parameter[3]*islandemptycell(matrx);}
        else
        {
            if (ismyt == true)
            {
                node = new treeNode;
                node->ismyturn = true;
                node->alpha = alpha;
                double value;
                for (int i = 0; i < 4; i++)
                {
                    int rep[4][4];
                    for (int k = 0; k < 4; k++)
                        for (int j = 0; j < 4; j++)
                            {   rep[k][j] = matrx[k][j]; node->condition[k][j] = matrx[k][j];}
                    switch (i)
                    {
                    case 0:
                        node->can_choose[0] = right_ai(rep);
                        break;
                    case 1:
                        node->can_choose[1] = left_ai(rep);
                        break;
                    case 2:
                        node->can_choose[2] = down_ai(rep);
                        break;
                    case 3:
                        node->can_choose[3] = up_ai(rep);
                        break;
                    }
                    if (node->can_choose[i])
                    {
                        value = minimax_tree(node->child[i], rep, node->alpha, beta, layer-1, parameter, false);
                        if (value > node->alpha)
                            node->alpha = value;
                        if (node->alpha >= beta)
                            break;
                    }
                }
                return node->alpha;
            }else
            {
                node = new treeNode;
                node->ismyturn = false;
                node->beta = beta;
                vector<pair<int, int> > candidates;
                vector<pair<int, int> > socre;
                vector<pair<int, int> > zerocube;
                int maxs = MININF;
                for (int i = 0; i < 4; i++)
                    for (int j = 0; j < 4; j++)
                        if (matrx[i][j] == 0)
                            zerocube.push_back(make_pair(i, j));
                for (int i = 0; i < zerocube.size(); i++)
                {
                    matrx[zerocube[i].first][zerocube[i].second] = 2;
                    int value = islandemptycell(matrx) - smooth(matrx);
                    socre.push_back(make_pair(i, value));
                    matrx[zerocube[i].first][zerocube[i].second] = 0;
                    value = islandemptycell(matrx) - smooth(matrx);
                    socre.push_back(make_pair(i, value));
                    matrx[zerocube[i].first][zerocube[i].second] = 0;
                }
                for (int i = 0; i < socre.size(); i++)
                    if (socre[i].second > maxs)
                        maxs = socre[i].second;
                for (int i = 0; i < socre.size(); i++)
                    if (socre[i]. second == maxs)
                    {
                        if (i % 2 == 0)
                            candidates.push_back(make_pair(socre[i].first, 2));
                        else{candidates.push_back(make_pair(socre[i].first, 4));}
                    }
                for (int i = 0; i < 15 && i < candidates.size(); i++)
                {
                    int rep[4][4];
                    for (int j = 0; j < 4; j++)
                        for (int k = 0; k < 4; k++)
                            {rep[j][k] = matrx[j][k]; node->condition[j][k];}
                    rep[zerocube[candidates[i].first].first][zerocube[candidates[i].first].second] = candidates[i].second;
                    double value = minimax_tree(node->child[i], rep, alpha, node->beta, layer-1, parameter, true);
                    if (value < node->beta)
                        node->beta = value;
                    if (alpha >= node->beta)
                        break;
                }
                return node->beta;
            }
        }
    }
}

int GameView::islandemptycell(int matrx[4][4])
{
    int sum = 0;
    int k = 0;
    int rematrx[6][6];
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 6; j++)
            if (i > 0 && i < 5 && j > 0 && j < 5)
            {   rematrx[i][j] = matrx[i-1][j-1];}
            else {rematrx[i][j] = 1;}
    for (int i = 1; i < 5; i++)
        for (int j = 1; j < 5; j++)
        {
            if (rematrx[i][j] == 0)
            {
                for (int a = -1; a < 2; a++)
                    for (int b = -1; b < 2; b++)
                        if (rematrx[i+a][j+b] != 0)
                            k++;
            }
            if (k == 9)
                sum++;
            k = 0;
        }
    return 100000*sum;
}

int GameView::emptycell(int matrx[4][4])
{
    int emptynum = 0;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (matrx[i][j] == 0)
                emptynum++;
    return 10000000*emptynum;
}

//越大的数在越大位值越大
int GameView::monotonicity(int matrx[4][4], double parameter[12])
{
    int socre = 0;
    int k;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
        {
            k = matrx[i][j]*matrx[i][j]*(j+1)*(i+1);
            socre += k;
        }
    return socre;
}

int GameView::monotonicity(int matrx[4][4])
{
    int sorce = 0;
    sorce = matrx[0][0]*4+matrx[0][1]*3+matrx[0][2]*2+matrx[0][3]*1+
            matrx[1][0]*25+matrx[1][1]*27+matrx[1][2]*29+matrx[1][3]*31+
            matrx[2][0]*62+matrx[2][1]*59+matrx[2][2]*56+matrx[2][3]*53+
            matrx[3][0]*90+matrx[3][1]*100+matrx[3][2]*120+matrx[3][3]*120;
    return sorce/10;
}

int GameView::smooth(int matrx[4][4])
{
    int sorce = 0;
    int k;
    for (int i = 3; i > 0; i--)
        for (int j = 3;j > 0; j--)
        {
            k = (4-j)*(4-j)*abs(matrx[i][j] - matrx[i][j-1]);
            sorce += k;
        }
    sorce = sorce + abs(matrx[0][0]-matrx[1][0])+abs(matrx[1][3]-matrx[2][3])+abs(matrx[2][0]-matrx[3][0]);
    return sorce;
}

bool GameView::right_ai(int matrx[4][4])
{
    bool able_move = false;
    for(int i = 3; i > 0; i--){
        for(int j = 0; j < 4; j++){
            if ((matrx[j][i] == 0) && matrx[j][i-1] != 0){
                int row = j;
                int col = i;
                able_move = true;
                while((matrx[row][col] == 0) && matrx[row][col-1] != 0)
                {
                    matrx[row][col] = matrx[row][col-1];
                    matrx[row][col-1] = 0;
                    if (++col > 3)
                        break;
                }
            }
        }
    }
    for(int i = 3; i > 0; i--){
        for(int j = 0; j < 4; j++){
            if ((matrx[j][i] != 0) && (matrx[j][i] == matrx[j][i-1])){
                able_move = true;
                matrx[j][i] *= 2;
                matrx[j][i-1] = 0;
                score += matrx[j][i]/2;
                if(matrx[j][i] > biggestNum)
                    biggestNum = matrx[j][i];
            }
        }
    }
    if(able_move == true){
        for(int i = 3; i > 0; i--){
            for(int j = 0; j < 4; j++){
                if ((matrx[j][i] == 0) && matrx[j][i-1] != 0){
                    matrx[j][i] = matrx[j][i-1];
                    matrx[j][i-1] = 0;
                }
            }
        }
    }
    return able_move;
}

bool GameView::left_ai(int matrx[4][4])
{
    bool able_move = false;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 4; j++){
            if ((matrx[j][i] == 0) && matrx[j][i+1] != 0){
                int row = j;
                int col = i;
                able_move = true;
                while((matrx[row][col] == 0) && matrx[row][col+1] != 0)
                {
                    matrx[row][col] = matrx[row][col+1];
                    matrx[row][col+1] = 0;
                    if (--col < 0)
                        break;
                }
            }
        }
    }
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 4; j++){
            if ((matrx[j][i] != 0) && (matrx[j][i] == matrx[j][i+1])){
                able_move = true;
                matrx[j][i] *= 2;
                matrx[j][i+1] = 0;
                score += matrx[j][i]/2;
                if(matrx[j][i] > biggestNum)
                    biggestNum = matrx[j][i];
            }
        }
    }
    if(able_move == true){
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 4; j++){
                if ((matrx[j][i] == 0) && matrx[j][i+1] != 0){
                    matrx[j][i] = matrx[j][i+1];
                    matrx[j][i+1] = 0;
                }
            }
        }
    }
    return able_move;
}

bool GameView::down_ai(int matrx[4][4])
{
    bool able_move = false;
    for(int j = 3; j > 0; j--){
        for(int i = 0; i < 4; i++){
            if ((matrx[j][i] == 0) && matrx[j-1][i] != 0){
                int row = j;
                int col = i;
                able_move = true;
                while((matrx[row][col] == 0) && matrx[row-1][col] != 0)
                {
                    matrx[row][col] = matrx[row-1][col];
                    matrx[row-1][col] = 0;
                    if (++row > 3)
                        break;
                }
            }
        }
    }
    for(int j = 3; j > 0; j--){
        for(int i = 0; i < 4; i++){
            if ((matrx[j][i] != 0) && (matrx[j][i] == matrx[j-1][i])){
                able_move = true;
                matrx[j][i] *= 2;
                matrx[j-1][i] = 0;
                score += matrx[j][i]/2;
                if(matrx[j][i] > biggestNum)
                    biggestNum = matrx[j][i];
            }
        }
    }
    if(able_move == true){
        for(int j = 3; j > 0; j--){
            for(int i = 0; i < 4; i++){
                if ((matrx[j][i] == 0) && matrx[j-1][i] != 0){
                    matrx[j][i] = matrx[j-1][i];
                    matrx[j-1][i] = 0;
                }
            }
        }
    }
    return able_move;
}

bool GameView::up_ai(int matrx[4][4])
{
    bool able_move = false;
    for(int j = 0; j < 3; j++){
        for(int i = 0; i < 4; i++){
            if ((matrx[j][i] == 0) && matrx[j+1][i] != 0){
                int row = j;
                int col = i;
                able_move = true;
                while((matrx[row][col] == 0) && matrx[row+1][col] != 0)
                {
                    matrx[row][col] = matrx[row+1][col];
                    matrx[row+1][col] = 0;
                    if (--row < 0)
                        break;
                }
            }
        }
    }
    for(int j = 0; j < 3; j++){
        for(int i = 0; i < 4; i++){
            if ((matrx[j][i] != 0) && (matrx[j][i] == matrx[j+1][i])){
                able_move = true;
                matrx[j][i] *= 2;
                matrx[j+1][i] = 0;
                score += matrx[j][i]/2;
                if(matrx[j][i] > biggestNum)
                    biggestNum = matrx[j][i];
            }
        }
    }
    if(able_move == true){
        for(int j = 0; j < 3; j++){
            for(int i = 0; i < 4; i++){
                if ((matrx[j][i] == 0) && matrx[j+1][i] != 0){
                    matrx[j][i] = matrx[j+1][i];
                    matrx[j+1][i] = 0;
                }
            }
        }
    }
    return able_move;
}

void GameView::train()
{
    ofstream out("train3.txt");
    srand(time(0));
    unit population[INITIAL_NUM];
    unit newpop[INITIAL_NUM];
    double tttry[12] = {0.7283, 0.3255, 0.8226, 0.5283, 0, 0, 0, 0, 0, 0, 0, 0};
    for (int i = 0; i < INITIAL_NUM; i++)
        for (int j = 0; j < 12; j++)
            {
                population[i].parameter[j] = tttry[j] + (rand()%10000)/1000000.0;
                //cout << population[i].parameter[j] << " ";
            }
    double generation = 0;
    while(generation++ < ITERATION)
    {
        double sum = 0.0;
        double average = 0.0;
        double square = 0.0;
        out << "generation : #" << generation << endl;
        cout << "generation : #" << generation << endl;
        for (int i = 0; i < INITIAL_NUM; i++)
            {
                ai_train_play(population[i]);
                sum += population[i].score;
                for (int j = 0; j < 12; j++)
                    out << population[i].parameter[j] << " ";
                out << population[i].score << endl;
            }
        average = sum / INITIAL_NUM;
        cout << "average:" << average << endl;
        out << "average:" << average << endl;
        for (int i = 0; i < INITIAL_NUM; i++)
            square = square + abs(population[i].score - average);
        square = square/double(INITIAL_NUM);
        cout <<"square:" << square << endl;
        out <<"square:" << square << endl;
        for (int i = 0; i < INITIAL_NUM; i++)
            population[i].possiblity = population[i].score/sum;
        int num = 0;
        for (int i = 0; i < INITIAL_NUM; i++)
            if (population[num].score < population[i].score)
                num = i;
        assignment(newpop[0], population[num]);
        num = 1;
        while (num < INITIAL_NUM)
        {
            double m = 0.0;
            int index[2];
            int k = 0;
            while (k < 2)
            {
                double rand_num = double(rand()%10000)/10000.0;
                for (int i = 0; i < INITIAL_NUM; i++)
                {
                    m = m + population[i].possiblity;
                    if (rand_num < m)
                    {
                        if (k == 1 && i != index[0])
                        {
                            index[k] = i;k++;
                        }
                        else if(k == 0)
                        {index[k] = i; k++;break;}
                    }
                }
            }
            unit be_choose[2];
            assignment(be_choose[0], population[index[0]]);
            assignment(be_choose[1], population[index[1]]);
            double pc = double(rand()%10000)/10000.0;
            double pm = double(rand()%10000)/10000.0;
            if (pc < PC)
            {
                for(int i = 0; i < 12; i++)
                {
                    double p = (rand()%10000)/10000.0;
                    if (p < 0.5)
                    {
                        double a = be_choose[0].parameter[i];
                        be_choose[0].parameter[i] = be_choose[1].parameter[i];
                        be_choose[1].parameter[i] = a;
                    }
                }
            }
            if (pm < PM)
            {
                for(int i = 0; i < 12; i++)
                {
                    double p = double(rand()%10000)/10000.0;
                    if (p < 0.5)
                    {
                        be_choose[0].parameter[i] += STEP;
                        be_choose[1].parameter[i] -= STEP;
                    }
                }
            }
            assignment(newpop[num++], be_choose[0]);
            assignment(newpop[num++], be_choose[1]);
            delete [] be_choose;
        }
        for (int i = 0; i < INITIAL_NUM; i++)
            assignment(population[i], newpop[i]);
    }
    out.close();
}

void GameView::ai_train_play(unit &a)
{
    int choice;
    while (canmove_ai(a))
    {
        int tem[4][4];
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                tem[i][j] = nums[i][j];
        choice = chose_turn(tem, a.parameter);
        //cout << "choice" << choice << endl;
        switch (choice)
        {
        case 0:
            right();
            //print();
            break;
        case 1:
            left();
            //print();
            break;
        case 2:
            down();
            //print();
            break;
        case 3:
            up();
            //print();
            break;
        }
        emit scoreupdata(score, biggestNum);
        //emit ai_done();
        this->show();
        qApp->processEvents();  //update every move!!!
    }
}

bool GameView::canmove_ai(unit & a)
{
    bool can_move = false;
    if(!canadd()){
        for(int i = 0; i < 3; i++)
            for(int j = 0; j < 4; j++){
                if(j ==3){
                    if(nums[j][i] == nums[j][i+1])
                        can_move = true;
                }else{
                    if(nums[j][i] == nums[j][i+1] || nums[j][i] == nums[j+1][i]){
                        can_move = true;
                    }
                }
            }
    }else{can_move = true;}
    if(!can_move){
        a.score = score;
        stringstream ss;
        ss << high;
        int i;
        ss >> i;
        if (score > i)
        {
            ofstream out("high.txt");
            out << score;
            out.close();
        }
        restartGame();
    }
    return can_move;
}

void GameView::assignment(unit &a, unit b)
{
    for (int i = 0; i < 12; i++)
        a.parameter[i] = b.parameter[i];
    a.score = b.score;
    a.possiblity = b.possiblity;
}

void GameView::delete_tree(treeNode *& t)
{
    for (int i = 0; t->child[i]; i++)
        delete_tree(t->child[i]);
    delete t;
}
