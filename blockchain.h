//
// Created by Alan de Freitas on 23/02/18.
//

#ifndef BLOCKCHAIN_BLOCKCHAIN_H
#define BLOCKCHAIN_BLOCKCHAIN_H

#include <functional>
#include <vector>

namespace bc {

    template <class _Tp, class _Hash = std::hash<_Tp>, class _Pred = std::equal_to<_Tp>, class _Alloc = std::allocator<_Tp> >
    class block {
        public:
            size_t previous_hash;
            _Tp    transaction;
            size_t block_hash;

            block(){}

            block(size_t _previous_hash, _Tp _transaction) : previous_hash(_previous_hash), transaction(_transaction) {
                this->block_hash = calculate_hash();
            }

            size_t calculate_hash(){
                return this->pair_hash(std::pair<size_t,size_t>({_Hash{}(transaction), previous_hash}));
            }

            size_t get_previous_hash(){
                return this->previous_hash;
            }

            _Tp get_transaction(){
                return this->transaction;
            }

            void set_previous_hash(size_t _previous_hash){
                this->previous_hash = _previous_hash;
            }

            void set_transaction(_Tp _transaction){
                this->transaction = _transaction;
            }

            size_t get_block_hash(){
                return this->block_hash;
            }

        private:
            template <typename _Tp1, typename _Tp2>
            size_t pair_hash(const std::pair<_Tp1,_Tp2>& x){
                return std::hash<_Tp1>()(x.first) ^ std::hash<_Tp2>()(x.second);
            }

    };


    template <class _Tp, class _Hash = std::hash<_Tp>, class _Pred = std::equal_to<_Tp>, class _Alloc = std::allocator<_Tp> >
    class blockchain : public std::vector<block<_Tp,_Hash,_Pred,_Alloc>> {
        public:
            // types
            typedef _Tp                                                           value_type;
            typedef block<_Tp,_Hash,_Pred,_Alloc>                                 block_type;
            typedef _Hash                                                         hasher;
            typedef _Pred                                                         key_equal;
            typedef _Alloc                                                        allocator_type;
            typedef value_type&                                                   reference;
            typedef const value_type&                                             const_reference;
            typedef typename std::vector<block<_Tp,_Hash,_Pred,_Alloc>>::iterator          iterator;
            typedef typename std::vector<block<_Tp,_Hash,_Pred,_Alloc>>::const_iterator    const_iterator;

            static_assert((std::is_same<value_type, typename allocator_type::value_type>::value), "Invalid allocator::value_type");

        public:
            blockchain(){
                this->emplace_back(block_type(0,_Alloc()));
            }

            blockchain(_Tp genesis_transaction){
                this->emplace_back(block_type(0,genesis_transaction));
            }

            void push_back(const value_type& x){
                this->emplace_back(block_type(this->back().block_hash,x));
            }

            void push_back(value_type&& x){
                this->emplace_back(block_type(this->back().block_hash,x));
            }

            bool check(iterator begin, iterator end){
                iterator second = begin;
                ++second;
                while (second != end){
                    size_t calculated_hash = begin->calculate_hash();
                    if (second->previous_hash != begin->block_hash
                        || second->previous_hash != calculated_hash
                        || calculated_hash != begin->block_hash){
                        return false;
                    }
                    ++begin;
                    ++second;
                }
                return true;
            }

            bool check(){
                return this->check(this->begin(),this->end());
            }

            bool check_hash(iterator begin, iterator end){
                iterator second = begin;
                ++second;
                while (second != end){
                    if (second->previous_hash != begin->block_hash){
                        return false;
                    }
                    ++begin;
                    ++second;
                }
                return true;
            }

            bool check_hash(){
                return this->check(this->begin(),this->end());
            }

    };
}

#endif //BLOCKCHAIN_BLOCKCHAIN_H
