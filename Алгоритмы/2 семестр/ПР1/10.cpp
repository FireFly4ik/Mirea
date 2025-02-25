#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// структура точек
struct Point {
    int x, y;
};

struct Node {
    int xKey;
    vector<Point> yPoints;
    Node* left;
    Node* right;
};

//создаем range tree
Node* buildRangeTree(vector<Point> points){
    if (points.empty()) return nullptr;
    //сортируем по иксам все точки и ищем центральную, чтобы строить примерно сбаланшенное дерево
    sort(points.begin(), points.end(), [](const Point &a, const Point &b){return a.x < b.x;});
    int mid = points.size() / 2;
    Node* node = new Node;
    node->xKey = points[mid].x;
    node->left = nullptr;
    node->right = nullptr;
    //сортируем уже по игрикам
    sort(points.begin(), points.end(), [](const Point &a, const Point &b){return a.y < b.y;});
    node->yPoints = points;

    //расскидываем по левой и правой будущим частям нода
    vector<Point> leftPoints, rightPoints;
    for (int i = 0; i < (int)points.size(); i++){
        if (i == mid) continue;
        if (points[i].x <= node->xKey){
            leftPoints.push_back(points[i]);
        } else {
            rightPoints.push_back(points[i]);
        }
    }
    //строим на них дальше дерево
    node->left = buildRangeTree(leftPoints);
    node->right = buildRangeTree(rightPoints);
    return node;
}

void queryRangeTree(Node* root, int x1, int x2, int y1, int y2, vector<Point> &result){
    if (!root) return;
    // идем ток в левое поддерево
    if (root->xKey < x1){
        queryRangeTree(root->right, x1, x2, y1, y2, result);
    } 
    // идем ток в правое поддерево
    else if (root->xKey > x2){
        queryRangeTree(root->left, x1, x2, y1, y2, result);
    } 
    // остаемся в данном и сортируем нужные точки, подходящие по игрикам
    else {
        // точки в данном ноде
        const auto &vecY = root->yPoints;
        // находим границы игриков
        auto lower = lower_bound(vecY.begin(), vecY.end(), Point{0, y1}, [](const Point &a, const Point & b){return a.y < b.y;});
        auto upper = upper_bound(vecY.begin(), vecY.end(), Point{0, y2}, [](const Point &a, const Point & b){return a.y < b.y;});
        //фильтруем по игрику
        for (auto it = lower; it != upper; ++it){
            if (it->x >= x1 && it->x <= x2){
                result.push_back(*it);
            }
        }
        queryRangeTree(root->left, x1, x2, y1, y2, result);
        queryRangeTree(root->right, x1, x2, y1, y2, result);
    }
}

void deleteNodes(Node* node){
    if (node->left != nullptr){
        deleteNodes(node->left);
    }
    if (node->right != nullptr){
        deleteNodes(node->right);
    }
    delete(node);
}

int main(){
    vector<Point> points = {{1, 4}, {2, 2}, {3, 6}, {5, 3}, {6, 7}, {7, 1}, {8, 4}};
    Node* root = buildRangeTree(points);
    int x1 = 2, x2 = 6, y1 = 2, y2 = 5;
    vector<Point> answer;
    queryRangeTree(root, x1, x2, y1, y2, answer);
    //убираем дубликаты
    sort(answer.begin(), answer.end(), [](const Point &a, const Point &b){return a.x < b.x;});
    answer.erase(unique(answer.begin(), answer.end(), [](const Point &a, const Point &b){return a.x == b.x && a.y == b.y;}), answer.end());
    cout << answer.size() << endl;
    deleteNodes(root);
}