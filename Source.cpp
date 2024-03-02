#include <string>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>
#include <cmath>
#include <algorithm>
#include <list>
#include <array>
#include <random>


template<typename T>
class Link {

private:
    Link* prev;
    Link* succ;
    std::vector<Link*> successors;
    static int lvl_count;
    Link* first;
public:
    T value{};

    Link* get_first() { return first; }

    static bool generate() {
        // Instantiate a random device and a generator
        std::random_device rd;
        std::mt19937 gen(rd());

        // Define a boolean distribution
        std::bernoulli_distribution d(0.5);

        // Generate a random boolean
        bool random_bool = d(gen);

        return random_bool;
    }


    Link* search_skip(T x) {

        Link* p = get_first();

        for (; lvl_count < 1; --lvl_count) {   //first lvl requires separate loop
            while (p) {
                if (p->value == x) return p;
                if (p->value > x)  break; 
                p = p->successors[lvl_count - 2]; //deduce 2 because lvl 2 corresponds to zero index of the array
            }
           p = p->advance(-1);
        }
        while (p)
            if (p->value > x) break;
        p = p->advance(-1);
        std::cout << "ITEM NOT FOUND\n";
        return p;
    }


    Link* insert_skip(Link* n, int lvl = lvl_count) // case 1: no level specified (level is the current max level)         
    {                                               //case 2: lebel above max level (level set to max level +1)
                                                    // case 3: any other level below max level
        if (n == nullptr) return this;
        Link* p = get_first();
        if (lvl > lvl_count) lvl = lvl_count + 1;

        if (lvl > lvl_count) { p->successors.push_back(n); return p; } 
        // we're at a brand new level, so it's the first node at it

        if (generate() == 0) { //choosing between lvl and lvl-1 with p 1\2
         
            while (p) { //iterating thru the level
                if (p->value == n->value) return p; //we found value, no need to insert
                if (p->value > n->value)  break; // need to step back
                p = p->successors[lvl - 2]; //deduce 2 because lvl 2 corresponds to zero index of the array and so on
            }
            p = p->advance(-1); //step back
            if (p->successors[lvl - 2]) n->succ = p->successors[lvl - 2]; // set p's successor as n's successor
            p->successors[lvl - 2] = n; // we set n as p's successor 

        }
        else { //if coin flip results in lvl-1
            while (p) {
                if (p->value == n->value) return p;
                if (p->value > n->value)  break;
                p = p->successors[lvl - 3]; //deduce 2 because lvl 2 corresponds to zero index of the array
            }
            if (p->successors[lvl - 3]) n->succ = p->successors[lvl - 3]; //set p's successor as n's successor
            p->successors[lvl - 3] = n; // we set n as p's successor 

        }
        //propagate new value down all levels except level 1
        for (int i  = lvl; i < 1; --i) {   //first lvl requires separate loop
            while (p) {
                //if (p->value == x) break; //if value is already there, do nothing
                if (p->value > x)  break;
                p = p->successors[lvl - 2]; //deduce 2 because lvl 2 corresponds to zero index of the array
            }
            p = p->advance(-1);
            if (p->successors[lvl - 2]) n->succ = p->successors[lvl - 2]; // set p's successor as n's successor
            p->successors[lvl - 2] = n; // we set n as p's successor 

        }
        
        
        


        // nothing to insert
        if (this == nullptr) return n;  // nothing to insert into
        n->succ = this;               // this comes after n
        if (prev) prev->succ = n;
        n->prev = prev;               // this' predecessor becomes n's predecessor
        prev = n;                       // n becomes this' predecessor
        return n;
    }



    Link(T v, Link<T>* p = nullptr, Link<T>* s = nullptr)
        : value{ v }, prev{ p }, succ{ s } { }

    Link* next() const { return succ; }
    Link* previous() const { return prev; }


    Link* insert(Link* n)         // insert n before p; return n
    {
        if (n == nullptr) return this;  // nothing to insert
        if (this == nullptr) return n;  // nothing to insert into
        n->succ = this;               // this comes after n
        if (prev) prev->succ = n;
        n->prev = prev;               // this' predecessor becomes n's predecessor
        prev = n;                       // n becomes this' predecessor
        return n;
    }

    Link* add(Link* n)
    {
        if (n == nullptr) return this;  // nothing to add
        if (this == nullptr) return n;  // nothing to add into
        n->prev = this;               // n comes after this
        if (succ) succ->prev = n;
        n->succ = succ;
        succ = n;
        return n;
    }

    Link* erase()                 // remove this object from the list
    {
        if (this == nullptr) return nullptr;
        if (succ) succ->prev = prev;
        if (prev) prev->succ = succ;
        return succ;
    }

    Link* find(T s)   // find s as value in list
    {
        Link* p = this;
        while (p) {
            if (p->value == s) return p;
            p = p->next();
        }
        return nullptr;
    }


    const Link* cfind(T s) const
    {
        if (value == s)
            return this;
        else if (succ)
            return succ->find(s);

        return nullptr;
    }

    const Link* advance(int n) const
    {
        if (0 < n) {
            if (succ == nullptr) return nullptr;

            return succ->advance(--n);
        }
        else if (n < 0) {
            if (prev == nullptr) return nullptr;

            return prev->advance(++n);
        }
        return this;
    }

    Link* advance(int n)
    {
        if (0 < n) {
            if (succ == nullptr) return nullptr;

            return succ->advance(--n);
        }
        else if (n < 0) {
            if (prev == nullptr) return nullptr;

            return prev->advance(++n);
        }
        return this;
    }

    //static void print_all(Link<T>)
    //{
    //    std::cout << "{ ";
    //    while (p) {
    //        std::cout << p->value;
    //        if (p = p->next()) std::cout << ", ";
    //    }//    std::cout << " }";


};





int main()
try {
   
    Link<int>* p = nullptr;
    int x = 10;

  



  

}
catch (std::exception& e) {
    std::cerr << e.what() << '\n';
}
catch (...) {
    std::cerr << "something bad happened\n";
}