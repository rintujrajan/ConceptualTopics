#include <iostream>

using namespace std;

class Box
{
    private:
    int length, breadth, height;

    public:

    // when defined as a member function it takes only one parameter 
    // because every member function has "this" as the first parameter which takes the left hand side value of the + operator
    // so the "b" here is actually the second parameter
    Box operator+(const Box& b)
    {
        Box box;
        box.breadth = this->breadth+ b.breadth;
        box.length = this->length+ b.length;
        box.height = this->height+ b.height;
        return box;
    }

    // we can still define this as a member function because we only working essentially with the second parameter
    // the first parameter is "this" hidden which takes the left hand side value of the + operator
    Box operator+(const int& height)
    {
        Box box;
        box.breadth = this->breadth+ 20;
        box.length = this->length+ 30;
        box.height = this->height+ height;
        return box;
    }   

    // we cannot define member function since we have to pass a non class type as first parameter
    // hence we define the overload as a friend function and overload it as a nonmember function
    // since it would be a non member function "this" parameter would not be the first parameter by default
    friend Box operator+(const int& height,const Box& b);
    
    void setLength(int length)
    {
        this->length = length;
    }
    void setBreadth(int breadth)
    {
        this->breadth = breadth;
    }
    void setHeight(int height)
    {
        this->height = height;
    }
    int getLength()
    {
        return length;
    }
    int getBreadth()
    {
        return breadth;
    }
    int getHeight()
    {
        return height;
    }
};

//defined - friend function and overload it as a nonmember function 
// being a friend function, it can access private member variables like breadth, length, height of Box class
Box operator+(const int& height,const Box& b)
{
    Box box;
    box.breadth = b.breadth+ 40; 
    box.length = b.length+ 60;
    box.height = b.height+ height;
    return box;
}

int main()
{
    Box b1,b2,b3;
    b1.setBreadth(5);
    b1.setLength(10);
    b1.setHeight(15);

    b2.setBreadth(15);
    b2.setLength(10);
    b2.setHeight(5);

    
    b3 = b1+b2;     // the + operator is overloaded as a class member function 
    cout<<"Box 3 breadth:"<<b3.getBreadth()<<" length:"<<b3.getLength()<<" height:"<<b3.getHeight()<<endl;


    b3 = b1+10;     //the + operator is still overloaded as a member function since only the second parameter is different
    cout<<"Box 3 breadth:"<<b3.getBreadth()<<" length:"<<b3.getLength()<<" height:"<<b3.getHeight()<<endl;

    // here for a unary operator we have the first parameter as int and next as class object
    // either the int class should have a member function overload for it - which we do not have
    // hence we create a friend function to pass first parameter as int and second of the object type
    b3 = 80+b1;     
    cout<<"Box 3 breadth:"<<b3.getBreadth()<<" length:"<<b3.getLength()<<" height:"<<b3.getHeight()<<endl;

    cin.get();
}