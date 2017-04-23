//
//  chainable_setter.hpp
//
//  Created by ISHII 2bit on 2017/04/14.
//
//

#pragma once

#define bbb_chainable_setter_is_loaded

#include <utility>
#include <iostream>

namespace bbb {
    template <typename parent_type>
    struct base_setter {
        void set_parent(parent_type *parent) { this->parent = parent; }
    protected:
        parent_type *parent;
    };
    
    template <typename type, typename parent_type>
    struct chainable_setter : base_setter<parent_type> {
        chainable_setter() {}
        
        chainable_setter(const chainable_setter &mom)
        : body(mom.body) {}
        chainable_setter(chainable_setter &&mom)
        : body(std::move(mom.body)) {};
        
        chainable_setter(const type &default_value)
        : body(default_value) {};
        chainable_setter(type &&default_value)
        : body(std::move(default_value)) {};
        
#pragma mark getter

        inline type &operator()() { return body; }
        inline type operator()() const { return body; }

#pragma mark cast
        
        inline operator type&() { return body; };
        inline operator type() const { return body; };
        
#pragma mark setter
        
        inline parent_type &operator()(const chainable_setter &rhs) {
            body = rhs.body;
            return *parent;
        }
        inline parent_type &operator()(const type &value) {
            body = value;
            return *parent;
        }
        inline parent_type &operator()(chainable_setter &&rhs) {
            body = std::move(rhs.body);
            return *parent;
        }
        inline parent_type &operator()(type &&value) {
            body = std::move(value);
            return *parent;
        }
        
#pragma mark assignment
        
        inline chainable_setter &operator=(const chainable_setter &b) {
            body = b.body;
            return *this;
        }
        template <typename other_parent>
        inline chainable_setter &operator=(const chainable_setter<type, other_parent> &b) {
            body = b.body;
            return *this;
        }
        
        inline chainable_setter &operator=(chainable_setter &&b) {
            body = std::move(b.body);
            return *this;
        }
        template <typename other_parent>
        inline chainable_setter &operator=(chainable_setter<type, other_parent> &&b) {
            body = std::move(b.body);
            return *this;
        }
        
        inline type &operator=(const type &b) { return body = b; }
        inline type &operator=(type &&b) { return body = std::move(b); }
        
#pragma mark compare equality
        
        
        template <typename other_parent>
        inline bool operator==(const chainable_setter<type, other_parent> &rhs) const { return body == rhs.body; }
        inline bool operator==(const type &body) const { return this->body == body; }
        
        template <typename other_parent>
        inline bool operator!=(const chainable_setter<type, other_parent> &rhs) const { return body != rhs.body; }
        inline bool operator!=(const type &body) const { return this->body != body; }
        
#pragma mark compare order
        
        template <typename other_parent>
        inline auto operator<(const chainable_setter<type, other_parent> &rhs) const
        -> decltype(type() < type()) { return body < rhs.body; }
        inline auto operator<(const type &value) const
        -> decltype(type() < type()) { return body < value; }
        
        template <typename other_parent>
        inline auto operator<=(const chainable_setter<type, other_parent> &rhs) const
        -> decltype(type() <= type()) { return body <= rhs.body; }
        inline auto operator<=(const type &value) const
        -> decltype(type() <= type()) { return body <= value; }
        
        template <typename other_parent>
        inline auto operator>(const chainable_setter<type, other_parent> &rhs) const
        -> decltype(type() > type()) { return body > rhs.body; }
        inline auto operator>(const type &value) const
        -> decltype(type() > type()) { return body > value; }
        
        template <typename other_parent>
        inline auto operator>=(const chainable_setter<type, other_parent> &rhs) const
        -> decltype(type() >= type()) { return body >= rhs.body; }
        inline auto operator>=(const type &value) const
        -> decltype(type() >= type()) { return body >= value; }
        
#pragma swap

        inline void swap(chainable_setter &b) noexcept  { std::swap(body, b.body); }
        inline void swap(chainable_setter &&b) noexcept { std::swap(body, b.body); }
        inline void swap(type &b) noexcept  { std::swap(body, b); }
        inline void swap(type &&b) noexcept { std::swap(body, b); }
        
        friend void swap(chainable_setter &lhs, chainable_setter &rhs) noexcept {
            lhs.swap(rhs);
        }
        friend void swap(chainable_setter &lhs, type &rhs) noexcept {
            lhs.swap(rhs);
        }
        friend void swap(type &lhs, chainable_setter &rhs) noexcept {
            rhs.swap(lhs);
        }
        
    private:
        using base_setter<parent_type>::parent;
        type body;
    };
};
