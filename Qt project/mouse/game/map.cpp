#include <QFile>
#include "map.h"

Map::Map(QString MapFile,QObject *parent) : QObject(parent)
{
    mRow=0;
    mCol=0;
    mPArr=nullptr;
    InitByFile(MapFile);
    setFlagPos();
}

bool Map::InitByFile(QString fileName)//用文件给地图初始化
{
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly))
    {
        return false;
    }
    QByteArray arrAll=file.readAll();
    arrAll.replace("\r\n","\n");
    QList<QByteArray> lineList=arrAll.split('\n');
    mRow=lineList.size();
    mPArr=new int*[mRow];

    for(int i=0;i<mRow;i++)
    {
        QList<QByteArray> colList=lineList[i].split(',');
        mCol=colList.size();
        mPArr[i]=new int[mCol];

        for(int j=0;j<mCol;j++)
        {
            mPArr[i][j]=colList[j].toInt();
        }
    }

    return false;
}

void Map::clear()//清空
{
    if(mPArr!=nullptr)
    {
        for(int i=0;i<mRow;i++)
        {
            delete[] mPArr[i];
        }

        delete[] mPArr;
    }
}

void Map::Paint(QPainter *p)
{
    for(int i=0;i<mRow;i++)
    {
        for(int j=0;j<mCol;j++)
        {
            QImage img(":/icon/PATH.png");
            p->drawImage(QRect(j*img.width(),i*img.height(),img.width(),img.height()),img);
        }
    }

    for(int i=0;i<mRow;i++)
    {
        for(int j=0;j<mCol;j++)
        {
            QString imgUrl;
            switch(mPArr[i][j])
            {
                case Road:imgUrl="";break;
                case Wall:imgUrl=":/icon/WALL.png";break;
                case Rock:imgUrl=":/icon/ROCK.png";break;
                case Flag:imgUrl=":/icon/FLAG.png";break;
            }
            QImage img(imgUrl);
            p->drawImage(QRect(j*img.width(),i*img.height(),img.width(),img.height()),img);
        }
    }
}

void Map::setFlagPos()
{
    for(int i=0;i<mRow;i++)
    {
        for(int j=0;j<mCol;j++)
        {
            if(mPArr[i][j]==Flag)
            {
                FlagRow=i;
                FlagCol=j;
            }
        }
    }
}
