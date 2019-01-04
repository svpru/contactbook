#include <boost/test/unit_test.hpp>
#include <eosio/testing/tester.hpp>
#include <boost/test/tools/old/interface.hpp>
#include <eosio/chain/abi_serializer.hpp>
#include "Runtime/Runtime.h"
#include <fc/variant_object.hpp>
#define BOOST_TEST_MODULE boost_test_strings

#include "contracts.hpp"
#include "test.hpp"

using namespace eosio::testing;
using namespace eosio;
using namespace eosio::chain;
using namespace eosio::testing;
using namespace fc;
using namespace std;

class contactbook_tester : public tester {
public:
    contactbook_tester() {
        produce_block();

        create_accounts( {  N(contactbook),N(testacc), N(sriaccount11) } );
        produce_block();

        set_code( N(contactbook), contracts::contactbook_wasm() );
        set_abi( N(contactbook), contracts::contactbook_abi().data() );
    }

   void init_abi_ser(abi_serializer& abi_ser, account_name name) {
        const auto& accnt = control->db().get<account_object,by_name>( name );
        abi_def abi;
        // BOOST_REQUIRE_EQUAL(abi_serializer::to_abi(accnt.abi, abi), true);
        abi_serializer::to_abi(accnt.abi, abi);
        abi_ser.set_abi(abi, abi_serializer_max_time);
    }

    bool get_person( person_t& person, uint64_t user ) {
        return get_table_entry(person, N(contactbook), N(contactbook), N(people), user, false);   
    }
};

BOOST_AUTO_TEST_SUITE(contactbook_tests)

    BOOST_FIXTURE_TEST_CASE( insert_of_upsert_tests, contactbook_tester ) try {
        
        //============// INSERT

        auto person_i_1 = mvo()
            ("user", "testacc") 
            ("first_name", "AAA") 
            ("last_name", "aaa")
            ("ph_num", "01000001111")
            ("email","AAAaaa@gmail.com");

        push_action( N(contactbook), N(upsert), N(testacc), person_i_1);
        produce_block();

        person_t person_o_1;
        get_person( person_o_1, N(testacc));
        //BOOST_TEST_MESSAGE( fc::json::to_pretty_string(person_i_1));
        //BOOST_TEST_MESSAGE( fc::json::to_pretty_string(person_o_1));
        
        // ========= to check and compare the input person and output person
        
        auto po = variant(person_o_1).get_object();
        for (auto v : person_i_1) {
            auto key = v.key();
            auto iv = person_i_1.find(key);
            auto ov = po.find(key);
            BOOST_TEST_MESSAGE("comparing "<< key);
            BOOST_CHECK_EQUAL(*ov, *iv);
        }
        
    }FC_LOG_AND_RETHROW() 

    BOOST_FIXTURE_TEST_CASE( modify_of_upsert_tests, contactbook_tester ) try {

        //==========// MODIFY

        auto person_i_1 = mvo()
            ("user", "sriaccount11") 
            ("first_name", "AAA") 
            ("last_name", "aaa")
            ("ph_num", "01089201111")
            ("email","AAAaaa@yahoomail.com");

        push_action( N(contactbook), N(upsert), N(sriaccount11), person_i_1);
        produce_blocks(1);

        person_t person_o_1;
        get_person( person_o_1, N(sriaccount11));
        //BOOST_TEST_MESSAGE( fc::json::to_pretty_string(person_i_1));
        //BOOST_TEST_MESSAGE( fc::json::to_pretty_string(person_o_1));
        
        auto person_i_2 = mvo()
            ("user", "sriaccount11") 
            ("first_name", "AAA2") 
            ("last_name", "aaa2")
            ("ph_num", "01089201112")
            ("email","AAAaaa2@gmail.com");

        push_action( N(contactbook), N(upsert), N(sriaccount11), person_i_2);
        produce_blocks(1);

        person_t person_o_2;
        get_person( person_o_2, N(sriaccount11));
        //BOOST_TEST_MESSAGE( fc::json::to_pretty_string(person_i_2));
        //BOOST_TEST_MESSAGE( fc::json::to_pretty_string(person_o_2));

        auto po1 = variant(person_o_1).get_object();
        auto po2 = variant(person_o_2).get_object();
        for (auto v : person_i_2) {
            auto key = v.key();
            auto iv = po1.find(key);
            auto ov = po2.find(key);
            BOOST_TEST_MESSAGE("comparing "<< key);            
           if(key == "user") 
            BOOST_CHECK(*ov==*iv);
           else 
            BOOST_CHECK(*ov!=*iv);
        }
        
    }FC_LOG_AND_RETHROW() 

    BOOST_FIXTURE_TEST_CASE( erase_of_upsert_tests, contactbook_tester ) try {

        //==========// ERASE

        auto person_i_1 = mvo()
            ("user", "testacc") 
            ("first_name", "AAA") 
            ("last_name", "aaa")
            ("ph_num", "01000001111")
            ("email","AAAaaa@gmail.com");

        push_action( N(contactbook), N(upsert), N(testacc), person_i_1);
        produce_block();

        push_action( N(contactbook), N(erase), N(testacc), mvo()
         ("user", "testacc"));
        
        BOOST_TEST_MESSAGE("\ntestacc Erased");

    }FC_LOG_AND_RETHROW() 

BOOST_AUTO_TEST_SUITE_END()
