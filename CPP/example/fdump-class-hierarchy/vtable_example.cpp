class BaseClass
{

public:



    virtual int call_me1()
    {
        return 5;
    }



    virtual int call_me2()
    {
        return 10;
    }



    int call_me3()
    {
        return 15;
    }

};



class ChildClass : public BaseClass
{

public:

    int call_me1()

    {
        return 20;
    }



    int call_me2()

    {
        return 25;
    }

};


int main(int argc, char* argv[]) {
    return 0;
}
