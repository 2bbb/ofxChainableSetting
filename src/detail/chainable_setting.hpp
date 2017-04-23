//
//  chainable_setting.hpp
//  Derby
//
//  Created by ISHII 2bit on 2017/04/22.
//
//

#pragma once

#define bbb_chainable_setting_is_loaded

#include <cstdint>
#include <vector>
#include <memory>

#include "chainable_setter.hpp"

namespace bbb {
    template <typename this_type>
    struct chainable_setting {
        using register_types = chainable_setting<this_type>;
        
        template <typename ... setters>
        chainable_setting(setters & ... children)
        : children_addrs({calc_address(reinterpret_cast<this_type *>(cast()), children) ...})
        { set_this(); }
        
        chainable_setting(const chainable_setting &mom)
        : children_addrs(mom.children_addrs)
        { set_this(); };
        
        chainable_setting(chainable_setting &&mom)
        : children_addrs(std::move(mom.children_addrs))
        { set_this(); };
        
        chainable_setting &operator=(const chainable_setting &mom) {
            children_addrs = mom.children_addrs;
            set_this();
            return *this;
        };
        
        chainable_setting &operator=(chainable_setting &&mom) {
            std::swap(children_addrs, mom.children_addrs);
            set_this();
            return *this;
        };
        
    protected:
        inline this_type *cast() { return reinterpret_cast<this_type *>(this); }
        void set_this() {
            for(auto & child : children_addrs) calc_setter(cast(), child)->set_parent(cast());
        }
        template <typename type>
        using setter = chainable_setter<type, this_type>;
        
    private:
        std::vector<std::ptrdiff_t> children_addrs;
        template <typename T>
        static std::intptr_t addr(T &t) { return reinterpret_cast<std::intptr_t>(&t); }
        static std::ptrdiff_t calc_address(this_type *that, base_setter<this_type> &setter) {
            return addr(setter) - addr(*that);
        }
        static base_setter<this_type> *calc_setter(this_type *that, std::ptrdiff_t setter_address) {
            return reinterpret_cast<base_setter<this_type> *>(addr(*that) + setter_address);
        }
    };
};
