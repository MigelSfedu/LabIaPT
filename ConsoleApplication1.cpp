#include <iostream>
using namespace std;

struct Point 
{
    int x, y;
    Point(int x, int y)
        :x(x), y(y) {};
};



class Figure
{
protected:
    Point* point = nullptr;
    int tops;
public:
    Figure(int tops,Point* point)
    {
        this->tops = tops;
        this->point = point;
    }
    virtual void print()
    {
        for (int i = 0; i < tops; i++)
        {
            std::cout << "X=" << point[i].x << " Y=" << point[i].y << std::endl;
        }
    }
    virtual float Perimeter()
    {
        float perimeter = 0;
        for (int i = 0; i < tops - 1; i++)
        {
            perimeter += sqrt(pow(point[i + 1].x - point[i].x, 2) + pow(point[i + 1].y - point[i].y, 2));
        }
        perimeter += sqrt(pow(point[tops - 1].x - point[0].x, 2) + pow(point[tops - 1].y - point[0].y, 2));

        return perimeter;

    }
    virtual float Area()
    {
        float area=0;
        for (int i = 0; i < tops - 1; i++)
        {
            area += 0.5 * abs(point[i].x * point[i + 1].y - point[i + 1].x * point[i].y);
        }
        area += 0.5 * abs(point[tops].x * point[0].y - point[0].x * point[tops].y);

        return area;
    }
    virtual void getName()
    {
        std::cout << "..." << std::endl;
    }
};

class Rectangle : public Figure
{
protected:
    int width = NULL;
    int height = NULL;
public:
    Rectangle(int height, int width)
        :Figure(4, new Point[4]{ Point{ 0,0 }, Point{ 0,height }, Point{width ,height },Point{width ,0 } })
    {
        this->height = height;
        this->width = width;
    }
    void getName()
    {
        std::cout << "Rectangle" << std::endl;
    }
};

class Square :public Rectangle
{
private:
    int side = NULL;
public:
    Square(int side)
      : Rectangle(side, side)
    {
        this->side = side;
    }
    void getName()
    {
        std::cout << "Square" << std::endl;
    }
};

class Ellipse:public Figure
{
private:
    int radius = NULL;
    int Radius = NULL;
public:
    Ellipse(int Radius, int radius)
        :Figure(4, new Point[4]{ Point{ 0,radius }, Point{ -Radius,0 }, Point{0 ,-radius },Point{Radius,0 } })
    {
        this->Radius = Radius;
        this->radius = radius;
    }
    float Area()
    {
        return 3.14 * radius * Radius;
    }
    virtual float Perimeter()
    {
        return 2 * 3.14 * sqrt(pow(radius, 2) * pow(Radius, 2) / 2);
    }
    void getName()
    {
        std::cout << "Ellipse" << std::endl;
    }
};

class Circle: public Ellipse
{
private:
    int radius=NULL;
public:
    Circle(int radius)
        :Ellipse(radius, radius)
    {
        this->radius = radius;
    }
    float Perimeter()
    {
        return 2 * 3.14 * pow(radius, 2);
    }
    void getName()
    {
        std::cout << "Circle" << std::endl;
    }
};



int main()
{
    const int count = 10;
    Figure* figure[count];
    for (int i = 0; i < count; i++)
    {
        if (i % 2 == 0)
            figure[i] = new Rectangle(i, i * 2);
        else if (i % 3 == 0)
            figure[i] = new Square(i);
        else if (i % 5 == 0)
            figure[i] = new Circle(i / 5);
        else
            figure[i] = new Ellipse(i / 2, i);
    }

    for (int i = 0; i < count; i++)
    {
        figure[i]->getName();
        std::cout << "S = " << figure[i]->Area() << std::endl;
        std::cout << "P = " << figure[i]->Perimeter() << std::endl;
        std::cout << "" << std::endl;
    }

    delete[] figure;

    return 0;
}