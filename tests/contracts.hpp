#pragma once
#include <eosio/testing/tester.hpp>

namespace eosio { namespace testing {

struct contracts {
   
   static std::vector<uint8_t> contactbook_wasm() { return read_wasm("/Users/svpru/Work/contactbook/build/tests/../contactbook/contactbook.wasm"); }
   static std::string          contactbook_wast() { return read_wast("/Users/svpru/Work/contactbook/build/tests/../contactbook/contactbook.wast"); }
   static std::vector<char>    contactbook_abi() { return read_abi("/Users/svpru/Work/contactbook/build/tests/../contactbook/contactbook.abi"); }

  // struct util {
    //  static std::vector<uint8_t> test_api_wasm() { return read_wasm("/Users/svpru/Work/contactbook/tests/test_contracts/test_api.wasm"); }
      
   };
};
} //ns eosio::testing
