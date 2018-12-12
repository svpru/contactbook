#include <boost/test/unit_test.hpp>
#include <eosio/testing/tester.hpp>
#include <eosio/chain/abi_serializer.hpp>
#include <eosio/chain/wast_to_wasm.hpp>

#include <fc/variant_object.hpp>
#include <Runtime/Runtime.h>


#include "contracts.hpp"

using namespace eosio::testing;
using namespace eosio;
using namespace eosio::chain;
using namespace eosio::testing;
using namespace fc;

using mvo = fc::mutable_variant_object;

struct person_t {
    name key;
    string first_name;
    string last_name;
    string ph_num;
    string email;
    bool status;
    uint64_t primary_key() const { return key; }
};
FC_REFLECT( person_t, (key)(first_name)(last_name)(ph_num)(email));

