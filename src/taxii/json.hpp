#ifndef JSON_HPP_
#define JSON_HPP_


#include <cstddef>
#include <cstdio>
#include <string>
#include <type_traits>

/*
 * A simplified JSON serialization helper; this does nothing fancy or clever
 * but does achieve one thing - zero allocation.
 */

template<typename _CharT, std::size_t _Size>
class basic_json_buffer
{
public:
    typedef _CharT value_type;
    typedef std::size_t size_type;
    typedef value_type *pointer;
    typedef value_type &reference;
    typedef value_type const *const_pointer;
    typedef value_type const &const_reference;
    typedef value_type *iterator;
    typedef value_type const *const_iterator;
    
    inline reference operator[](size_type pos) noexcept { return data_[pos]; }
    inline const_reference operator[](size_type pos) const noexcept { return data_[pos]; }
    inline bool empty(void) { return size() == 0; }

    inline const_iterator begin() const noexcept { return const_iterator(data()); }
    inline iterator begin() noexcept { return iterator(data()); }
    inline const_iterator end() const noexcept { return const_iterator(data() + size_); }
    inline iterator end() noexcept { return iterator(data() + size_); }

    template<typename ...Args>
    void emplace_back(Args &&... args)
    {
        new (&data_[size_]) _CharT(std::forward<Args>(args)...);
        ++size_;
    }

    void push_back(const_reference v)
    {
        new (&data_[size_]) _CharT(v);
        ++size_;
    }

    inline void push_key(char const *key)
    {

    }

    inline void push_object(void)
    {
        emplace_back('{');
    }

    inline void push_object(char const *name)
    {
        push_key(name);
        push_object();
    }

    inline void pop_object(void)
    {
        emplace_back('}');
    }

    inline void push_array(void)
    {
        emplace_back('[');
    }

    inline void push_array(char const *name)
    {
        push_key(name);
        push_array();
    }

    inline void pop_array(void)
    {
        emplace_back(']');
    }

    template<typename _OtherT, typename _Traits, typename _Alloc>
    inline void push_ascii(std::basic_string<_OtherT, _Traits, _Alloc> const &s)
    {
        std::copy(std::begin(s), std::end(s), std::back_inserter(*this));
    }

    template<typename _OtherT, typename _Traits, typename _Alloc>
    inline void push_ascii(char const *key, std::basic_string<_OtherT, _Traits, _Alloc> const &s)
    {
        push_key(key);
        push_ascii(s);
    }

    inline void push(uint64_t i)
    {
        
    }

    inline void push(char const *name, double d)
    {
        push_key(name);
        push(d);
    }

    inline void push(double d)
    {

    }

    char const *c_str() const 
    {
        return reinterpret_cast<char const *>(data());
    }

    size_type length() const { return size(); }

protected:
    const_pointer data() const { return data_; }
    size_type size() const { return size_; }

private:
    _CharT data_[_Size];
    size_type size_;
};

#endif