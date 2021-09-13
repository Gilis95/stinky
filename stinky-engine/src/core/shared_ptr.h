//
// Created by christian on 7/27/21.
//

#ifndef STINKY_SHARED_PTR_H
#define STINKY_SHARED_PTR_H


template<class Type>
class ref_count_base {
public:
    void
public:
    void increment(){
        ++refCount;
    }


private:
    Type* obj;
    std::uint64_t refCount;
}

template<class Type>
    class ref_count_late_free : public ref_count_base<Type>{

    };

    template<class Type>
    class ref_count{
        Type* obj;


    };

template<class Type, class RefCount = ref_count>
class shared_ptr_base

#endif //STINKY_SHARED_PTR_H
