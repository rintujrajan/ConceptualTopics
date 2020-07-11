#include <iostream>
#include <string>
#include <iomanip> // used for setting custom white space

using namespace std;

int copyCounter = 1;
int moveCounter = 1;

/*
    C++ compiler provide default copy constructor (and assignment operator) with class. 
    When we don’t provide implementation of copy constructor (and assignment operator) 
    and tries to initialize object with already initialized object of same class then copy constructor gets called
    and copies members of class one by one in target object.

    The problem with default copy constructor (and assignment operator) is –
    When we have members which dynamically gets initialized at run time,
    default copy constructor copies this members with address of dynamically allocated memory and not real copy of this memory.
    Now both the objects points to the same memory and changes in one reflects in another object.
    Further the main disastrous effect is, when we delete one of this object other object still points to same memory,
    which will be dangling pointer, and memory leak is also possible problem with this approach.

    Hence, in such cases, we should always write our own copy constructor (and assignment operator).

    As per the rule of Big Five If we create any one of the copy constr, copy assignment, move constr, move assignment, destructor
    then all the five special member functions have to be created
*/
class MoveSemantics
{
    int strSize;
    char* strPtr;
    int* intPtr; 
    string objectName;

    public:
    MoveSemantics():strSize(0), strPtr(nullptr),intPtr(nullptr),objectName("")
    {
        cout<<"Default constructor\n"<<endl;
    }

    MoveSemantics(const char* str,int intVal)
    {
        cout<<"Parameterized constructor\t"<<str <<"\t" <<intVal<<  "\n"<<endl;

        strSize = strlen(str);

        strPtr = new char[strSize+1];
        memcpy(strPtr, str, strSize+1);

        intPtr = new int();
        *intPtr = intVal;

        objectName = str;
    }

    /*
        Copy Constructor
        Called when an object is created and copied in the same line of code e.g. MoveSemantics appleCopy1 = apple;
        The parameter takes const refernce so that it can take both lValue as an rValue(temporary values)
    */
    MoveSemantics(const MoveSemantics &moveSemantics)
    {
        cout<<"Copy constructor"<<endl;

        strSize = moveSemantics.strSize;
        
        strPtr = new char[strSize+1];
        memcpy(strPtr, moveSemantics.strPtr, strSize+1);

        intPtr = new int();
        *intPtr = *(moveSemantics.intPtr);

        objectName = moveSemantics.objectName+ "Copy"+ to_string(copyCounter++);

        cout<<"Copied data of strPtr from addr "<< &moveSemantics.strPtr << " of ("<< moveSemantics.objectName << ") to "<< &strPtr << " of ("<< objectName << ")" <<endl;
    }

    /*
        Copy Assigment
        Called when an already created object is being used to copy from another existing object e.g. appleCopy2 = apple; 
        The parameter takes const refernce so that it can take both lValue as an rValue(temporary values)
    */
    MoveSemantics& operator=(const MoveSemantics &moveSemantics)
    {
        cout<<"Copy assignment"<<endl;
        if(this != &moveSemantics)
        {
            strSize = moveSemantics.strSize;
            
            delete strPtr;  // since there is a chance that the current object being copied into would have already been assigned we delete to avoid memory leak
            strPtr = new char[strSize+1];
            memcpy(strPtr, moveSemantics.strPtr, strSize+1);

            delete intPtr;  // since there is a chance that the current object being copied into would have already been assigned we delete to avoid memory leak
            intPtr = new int();
            *intPtr = *(moveSemantics.intPtr);

            objectName = moveSemantics.objectName+ "Copy"+ to_string(copyCounter++);

            cout<<"Copied data of strPtr from addr "<< &moveSemantics.strPtr << " of ("<< moveSemantics.objectName << ") to "<< &strPtr << " of ("<< objectName << ")" <<endl;
        }
        else
        {
            cout<<"Copy called on same object. Same object returned!\n"<<endl;
        }
        return *this;
    }

    /*
        Move Constructor
        Called when an object is created and moved(stealing resources) in the same line of code e.g. MoveSemantics mangoCopy1 = move(mango);
        The parameter takes rValue refernce. No constness is needed since it is a temporary refrence in the first place
    */
    MoveSemantics(MoveSemantics &&moveSemantics)
    {
        cout<<"Move constructor"<<endl;
        strSize = moveSemantics.strSize;
        
        strPtr  = moveSemantics.strPtr;

        intPtr = moveSemantics.intPtr;

        objectName = moveSemantics.objectName+ "Moved"+ to_string(moveCounter++);

        moveSemantics.strSize = 0;
        moveSemantics.strPtr = nullptr;
        moveSemantics.intPtr = nullptr;
        //we will not reset the object name since we would like to keep it to identify the object name
    }

    /*
        Move Assigment
        Called when an already created object is being used to move data(stealing resources) from another existing object e.g. mangoCopy2 = move(mangoCopy1); 
        The parameter takes const refernce so that it can take both lValue as an rValue(temporary values)
    */
    MoveSemantics& operator=(MoveSemantics&& moveSemantics)
    {
        cout<<"Move assignemnt"<<endl;
        if(this != &moveSemantics)
        {
            strSize = moveSemantics.strSize;
        
            delete strPtr;  // since there is a chance that the current object being copied into would have already been assigned we delete to avoid memory leak
            strPtr  = moveSemantics.strPtr;

            delete intPtr;  // since there is a chance that the current object being copied into would have already been assigned we delete to avoid memory leak
            intPtr = moveSemantics.intPtr;

            objectName = moveSemantics.objectName+ "Moved"+ to_string(moveCounter++);

            moveSemantics.strSize = 0;
            moveSemantics.strPtr = nullptr;
            moveSemantics.intPtr = nullptr;
            //we will not reset the object name since we would like to keep it to identify the object name
        }
        else
        {
            cout<<"Move called on same object. Same object returned!\n"<<endl;
        }
        
        return *this;
    }

    // Destructor
    ~MoveSemantics()
    {
        cout<<"Destructor called for : "<< objectName <<endl;

        // Delete all pointer objects which have been assigned memory using new keyword
        delete strPtr;
        delete intPtr;
    }
    string getStringValue()
    {     
        string str = "";   
        for (int i = 0; i < strSize; ++i)
        {
            str+=strPtr[i];
        }
        return str;
    }
    string getObjectName()
    {
        return objectName;
    }
    int getintPtrValue()
    {
        if(intPtr != nullptr)
        {
            return *intPtr;
        }
        return 0;
    }

};
void myFunc()
{
    cout << left;

    MoveSemantics apple("apple", 1);       // Parameterized constructor will be called 
    MoveSemantics appleCopy1 = apple;      // Copy constructor will be called since a new object is being copied
    cout<<"Checking the copy done.."<<endl;
    cout<<setw(10) <<apple.getObjectName()<<".strPtrVal :"<< apple.getStringValue()<<"\t"
        << apple.getObjectName() <<".intPtrVal :"<< apple.getintPtrValue()<<endl;
    cout<< appleCopy1.getObjectName()<<".strPtrVal :"<< appleCopy1.getStringValue()<<"\t"
        << appleCopy1.getObjectName() <<".intPtrVal :"<< appleCopy1.getintPtrValue()<<endl<<endl;
    
    MoveSemantics appleCopy2;              // Default constructor called to create object
    appleCopy2 = apple;                    // Copy assignment will be called since the object appleCopy2 is already created and will be only copied                                                           
    cout<<"Checking the copy done.."<<endl;
    cout<< appleCopy2.getObjectName()<<".strPtrVal :"<< appleCopy2.getStringValue()<<"\t"
        << appleCopy2.getObjectName() <<".intPtrVal :"<< appleCopy2.getintPtrValue()<<endl<<endl;

    appleCopy2 = appleCopy2;               // Copy assigment is called but the same object shall be returned

    MoveSemantics mango("mango", 2);       // Parameterized constructor will be called 
    MoveSemantics mangoCopy1 = move(mango);// Move constructor will be called since a new object is being created(mangocopy1) by moving existing object(mango)
    cout<<"Checking the move done.."<<endl;
    cout<<setw(11) << mango.getObjectName()<<".strPtrVal :"<<setw(5)<< mango.getStringValue()<<"\t"
        << mango.getObjectName() <<".intPtrVal :"<< mango.getintPtrValue()<<endl;
    cout<< mangoCopy1.getObjectName()<<".strPtrVal :"<< mangoCopy1.getStringValue()<<"\t"
        << mangoCopy1.getObjectName() <<".intPtrVal :"<< mangoCopy1.getintPtrValue()<<endl<<endl;

    mangoCopy1 = mangoCopy1;                

    MoveSemantics mangoCopy2;               // Default constructor called to create object
    mangoCopy2 = move(mangoCopy1);          // Move assigment will be called since the object(mangocopy2) is already created and data will be moved from existing object(mangoCopy1)
    cout<<"Checking the move done.."<<endl;
    cout<<setw(17)<< mangoCopy1.getObjectName()<<".strPtrVal :"<<setw(5)<< mangoCopy1.getStringValue()<<"\t"
        << mangoCopy1.getObjectName() <<".intPtrVal :"<< mangoCopy1.getintPtrValue()<<endl;
    cout<< mangoCopy2.getObjectName()<<".strPtrVal :"<< mangoCopy2.getStringValue()<<"\t"
        << mangoCopy2.getObjectName() <<".intPtrVal :"<< mangoCopy2.getintPtrValue()<<endl<<endl;

    mangoCopy2 = move(mangoCopy2);          // Move assigment is called but the same object shall be returned

    cout<<"\n\nDestructors: "<<endl;        // Destructors are called since the objects would be doing out of scope outside function scope
}

int main()
{
    myFunc();
    cin.get();
}