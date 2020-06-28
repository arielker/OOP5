#ifndef OOP5_STREAM_H
#define OOP5_STREAM_H

#include <functional>
#include <algorithm>
#include <map>
#include <vector>
#include <numeric>

using namespace std;

template <typename T>
class Stream {
    function<vector<T*>()> func;

public:
    explicit Stream(function<vector<T*>()> f) : func(f) {};

private:
    template <typename K>
    explicit Stream(map<K,T>& container){
        func = [container](){
            vector<T*> ret_vec(container.size());
            for (auto i = container.begin(); i != container.end() ; i++) {
                ret_vec.push_back(i->second);
            }
            return ret_vec;
        };
    }

    template <typename Tcontainer>
    explicit Stream(Tcontainer& container){
        func = [container]() -> vector<T*> {
            vector<T*> ret_vec(container.size());
            copy(container.begin(), container.end(), ret_vec.begin());
            return ret_vec;
        };
    }

public:
    //specialization for map container:
    template <typename K>
    static Stream<T> of(map<K, T*>& container){
        return Stream(container);
    }

    template <typename Tcontainer>
    static Stream<T> of(Tcontainer& tcontainer){
        return Stream(tcontainer);
    }

    ~Stream() = default;

    Stream<T> filter(function<bool(const T*)> pred){
        auto f1 = this->func;
        this->func = [f1, pred]() -> vector<T*> {
            vector<T*> tmp_vec1 = f1(), tmp_vec2(tmp_vec1.size());
            auto it = copy_if(tmp_vec1.begin(), tmp_vec1.end(), tmp_vec2.begin(), pred);
            tmp_vec2.resize(it - tmp_vec2.begin());
            return tmp_vec2;
        };
        return *this;
    }

    template <typename K>
    Stream<K> map(function<K*(const T*)> map_func){
        auto f1 = this->func;
        function<vector<K*>()> f2 = [f1, map_func]() -> vector<K*> {
            vector<T*> tmp_vec1 = f1();
            vector<K*> tmp_vec2(tmp_vec1.size());
            transform(tmp_vec1.begin(), tmp_vec1.end(), tmp_vec2.begin(), map_func);
            return tmp_vec2;
        };
        return Stream<K>(f2);
    }

    Stream<T> distinct(function<bool(const T*, const T*)> comp_func){
        auto f1 = this->func;
        this->func = [f1, comp_func]() -> vector<T*> {
            vector<T*> tmp_vec1 = f1();
            auto it = unique(tmp_vec1.begin(), tmp_vec1.end(), comp_func);
            tmp_vec1.resize(it - tmp_vec1.begin());
            return tmp_vec1;
        };
        return *this;
    }

    Stream<T> distinct(){
        auto f1 = this->func;
        this->func = [f1]() -> vector<T*> {
            vector<T*> tmp_vec1 = f1();
            auto it = unique(tmp_vec1.begin(), tmp_vec1.end(), [](const T* a, const T* b) -> bool {return *a == * b;});
            tmp_vec1.resize(it - tmp_vec1.begin());
            return tmp_vec1;
        };
        return *this;
    }

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
            sort(tmp_vec1.begin(), tmp_vec1.end(), [](const T* a, const T* b) -> bool {return *a < *b;});
            return tmp_vec1;
        };
        return *this;
    }

    template <typename Tcontainer>
    Tcontainer collect(){
        auto vec = this->func();
        Tcontainer tcontainer(vec.size());
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
    }

    T* min(){
        auto vec = this->func();
        return *(min_element(vec.begin(), vec.end()));
    }

    T* max(){
        auto vec = this->func();
        return *(max_element(vec.begin(), vec.end()));
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
        return *(find_if(vec.begin(), vec.end(), function));
    }
};

#endif //OOP5_STREAM_H
