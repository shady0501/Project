#ifndef MAP_H
#define MAP_H

#include <QObject>
#include <QPainter>

enum{
    Road,
    Wall,
    Rock,
    Flag
};

class Map : public QObject
{
    Q_OBJECT
public:
    explicit Map(QString MapFile,QObject *parent = nullptr);
    ~Map()
    {
        clear();
    }
    void clear();

    int mRow;
    int mCol;
    int **mPArr;//用于开辟二维数组
    int FlagRow,FlagCol;

    bool InitByFile(QString fileName);
    void Paint(QPainter *p);
    void setFlagPos();

signals:

};

#endif // MAP_H
