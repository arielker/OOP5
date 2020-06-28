#ifndef OOP5_STREAM_H
#define OOP5_STREAM_H

#include <functional>
#include <algorithm>
//#include <set>
#include <map>
#include <vector>
//#include <list>
#include <numeric>

using namespace std;

template <typename T>
class Stream {
    function<vector<T*>()> func;

public:
    explicit Stream(function<vector<T*>()> f) : func(f) {};

private:
    template </*template<typename U> class*/ typename Tcontainer>
    explicit Stream(Tcontainer/*<T*>*/& container){
        func = [container]() -> vector<T*> {
            vector<T*> ret_vec;
            copy<Tcontainer/*<T*>*/, vector<T*>>(container.begin(), container.end(), ret_vec.begin());
            return ret_vec;
        };
    }

public:

    //TODO: implement of specialization that receives map function!
    template </*template<typename U> class*/ typename Tcontainer>
    static Stream<T> of(Tcontainer/*<T*>*/& tcontainer){
        return Stream(tcontainer);
    }

    ~Stream() = default;

    Stream<T> filter(function<bool(const T*)> pred){
        auto f1 = this->func;
        this->func = [f1, pred]() -> vector<T*> {
            vector<T*> tmp_vec1 = f1(), tmp_vec2;
            copy_if(tmp_vec1.begin(), tmp_vec1.end(), tmp_vec2.begin(), pred);
            return tmp_vec2;
        };
        return *this;
    }

    template <typename K>
    Stream<K> map(function<K*(const T*)> map_func){
        auto f1 = this->func;
        auto f2 = [f1, map_func]() -> vector<K*> {
            vector<T*> tmp_vec1 = f1();
            vector<K*> tmp_vec2;
            transform(tmp_vec1.begin(), tmp_vec1.end(), tmp_vec2.begin(), map_func);
            return tmp_vec2;
        };
        return Stream<K>(f2);
        //TODO: check if works! cuz Stream<K> is a different class and its c'tor is private
    }

    /*TODO: make sure cpp power is real, solid, strong, stunning and brave! So stunningly brave...
     * jk... make sure T::operator== works*/
    Stream<T> distinct(function<bool(const T*, const T*)> comp_func){
        auto f1 = this->func;
        this->func = [f1, comp_func]() -> vector<T*> {
            vector<T*> tmp_vec1 = f1();
            unique(tmp_vec1.begin(), tmp_vec1.end(), comp_func);
            return tmp_vec1;
        };
        return *this;
    }

    Stream<T> distinct(){
        auto f1 = this->func;
        this->func = [f1]() -> vector<T*> {
            vector<T*> tmp_vec1 = f1();
            unique(tmp_vec1.begin(), tmp_vec1.end());
            return tmp_vec1;
        };
        return *this;
    }

    /*TODO: make sure cpp power is real, solid, strong, stunning and brave! So stunningly brave...
     * jk... make sure T::operator< works*/
    Stream<T> sorted(function<bool(const T*, const T*)> comp_func){
        auto f1 = this->func;
        this->func = [f1, comp_func]() -> vector<T*>{
            vector<T*> tmp_vec1 = f1();
            sort(tmp_vec1.begin(), tmp_vec1.end(), comp_func);
            return tmp_vec1;
        };
        return *this;
    }

    Stream<T> sorted(){
        auto f1 = this->func;
        this->func = [f1]() -> vector<T*>{
            vector<T*> tmp_vec1 = f1();
            sort(tmp_vec1.begin(), tmp_vec1.end());
            return tmp_vec1;
        };
        return *this;
    }

    template </*template<typename U> class*/ typename Tcontainer>
    Tcontainer/*<T*>*/ collect(){
        Tcontainer/*<T*>*/ tcontainer;
        auto vec = this->func();
        copy(vec.begin(), vec.end(), tcontainer.begin());
        return tcontainer;
    }

    void forEach(function<void(T*)> function){
        auto vec = this->func();
        for_each(vec.begin(), vec.end(), function);
    }

    T* reduce(T* starter, function<T*(const T*, const T*)> f){
        auto vec = this->func();
        return accumulate(vec.begin(), vec.end(), starter, f);
        //TODO: check if it works cuz last param of accumulate is a binary op. (wtf is that?!)
        /*T* ender; *ender = *starter;
        for(auto &t : vec){
            ender = f(ender, t);
        }
        return ender;*/
    }

    T* min(){
        auto vec = this->func();
        return &(*(min_element(vec.begin(), vec.end())));
    }

    T* max(){
        auto vec = this->func();
        return &(*(max_element(vec.begin(), vec.end())));
    }

    int count(){
        return this->func().size();
    }

    bool anyMatch(function<bool(const T*)> function){
        auto vec = this->func();
        return any_of(vec.begin(), vec.end(), function);
    }

    bool allMatch(function<bool(const T*)> function){
        auto vec = this->func();
        return all_of(vec.begin(), vec.end(), function);
    }

    T* findFirst(function<bool(const T*)> function){
        auto vec = this->func();
        return find_if(vec.begin(), vec.end(), function);
    }
};

#endif //OOP5_STREAM_H
