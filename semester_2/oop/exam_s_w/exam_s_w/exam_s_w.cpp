// exam_s_w.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//#include <iostream>
//#include <vector>
//#include <string>
//#include <assert.h>
//
//using namespace std;
//
//class Object
//{
//
//public:
//    virtual void print() = 0;
//};
//
//class Integer: public Object
//{
//private:
//    int value;
//
//public:
//    Integer(int value)
//    {
//        this->value = value;
//    }
//
//    virtual void print() override
//    {
//        cout << to_string(value) + " ";
//    }
//};
//
//class String: public Object
//{
//private:
//    string value;
//
//public:
//    String(string value)
//    {
//        this->value = value;
//    }
//
//    virtual void print() override
//    {
//        cout << value + " ";
//    }
//
//    bool operator== (const char* characters) 
//    {
//        return this->value == characters;
//    }
//};
//
//class MyObjectList
//{
//    friend class ListIterator;
//
//private:
//    vector<Object*> objects;
//    
//public:
//    MyObjectList& add(Object* obj)
//    {
//        this->objects.push_back(obj);
//
//        return *this;
//    }
//
//    int length() const
//    {
//        return this->objects.size();
//    }
//};
//
//class ListIterator
//{
//    friend MyObjectList;
//
//private:
//    const MyObjectList& list;
//    int currentElement;
//
//public:
//    ListIterator(const MyObjectList& list) : list(list) 
//    {
//        this->currentElement = 0;
//    };
//
//    bool isValid() const 
//    {
//        return this->currentElement < this->list.length();
//    }
//
//    void next() 
//    {
//        if (!this->isValid()) 
//        {
//            return;
//        }
//
//        this->currentElement++;
//    }
//
//    Object* element() const
//    {
//        if (!this->isValid())
//        {
//            return nullptr;
//        }
//
//        return this->list.objects[this->currentElement];
//    }
//};
//
//void function()
//{
//    MyObjectList list{};
//    list.add(new Integer{ 2 }).add(new String{ "Hi" });
//    String* s = new String{ "Bye" };
//    assert(*s == "Bye");
//    list.add(s).add(new Integer{ 5 });
//    assert(list.length() == 4);
//
//    ListIterator i{ list };
//    while (i.isValid()) {
//        Object* o = i.element();
//        o->print();
//        i.next();
//    } // prints: 2 Hi Bye 5
//}

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Encoder
{
public:
    virtual string encode(string msg) = 0;
};

class AlienEncoder : public Encoder
{
private:
    string header;

public:
    AlienEncoder(string header)
    {
        this->header = header;
    }

    virtual string encode(string msg) override
    {
        return msg + header;
    }
};

class MorseEncoder : public Encoder
{
private:

public:
    virtual string encode(string msg) override
    {
        string encoded = "";

        for (size_t i = 0; i < msg.length(); i++)
        {
            encoded += ".";
        }

        return encoded;
    }
};

class Mixer : public Encoder
{
private:
    Encoder* encoder1;
    Encoder* encoder2;

public:
    Mixer(Encoder* encoder1, Encoder* encoder2)
    {
        this->encoder1 = encoder1;
        this->encoder2 = encoder2;
    }

    ~Mixer()
    {
        delete this->encoder1;
        delete this->encoder2;
    }

    virtual string encode(string msg) override
    {
        string encoded1 = this->encoder1->encode(msg);
        string encoded2 = this->encoder2->encode(msg);

        string encoded = "";

        size_t maxLength = encoded1.length() > encoded2.length() ? encoded1.length() : encoded2.length();

        for (size_t i = 0; i < maxLength; i++)
        {
            if (i % 2 == 0)
            {
                if (i < encoded2.length())
                {
                    encoded += encoded2[i];
                }
            }
            else
            {
                if (i < encoded1.length())
                {
                    encoded += encoded1[i];
                }
            }
        }

        return encoded;
    }
};

class Communication
{
private:
    vector<string> messages;
    Encoder* encoder;

public:
    Communication(Encoder* encoder)
    {
        this->encoder = encoder;
    }
    
    ~Communication()
    {
        delete this->encoder;
    }

    void addMessage(string msg)
    {
        this->messages.push_back(msg);
    }

    string communicate()
    {
        sort(this->messages.begin(), this->messages.end(), [](string first, string second) { return first < second; });

        string encodedMessages = "";

        for (string message : this->messages)
        {
            encodedMessages += this->encoder->encode(message) + "\n";
        }

        return encodedMessages;
    }
};

int main()
{
    Communication comm1 = Communication(new MorseEncoder());
    Communication comm2 = Communication(new Mixer(new AlienEncoder("ET"), new MorseEncoder()));

    comm1.addMessage("TestMessage1");
    comm1.addMessage("TestMessage2");

    comm2.addMessage("TestMessage1");
    comm2.addMessage("TestMessage2");

    cout << comm1.communicate();
    cout << comm2.communicate();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
