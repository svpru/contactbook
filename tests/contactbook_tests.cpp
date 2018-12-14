#include <boost/test/unit_test.hpp>
#include <eosio/testing/tester.hpp>
#include <eosio/chain/abi_serializer.hpp>
#include "Runtime/Runtime.h"
#include <fc/variant_object.hpp>

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
        return get_table_entry(person, N(contactbook), N(contactbook), N(details), user, false);   
    }
};

BOOST_AUTO_TEST_SUITE(contactbook_tests)

    BOOST_FIXTURE_TEST_CASE( upsert_tests, contactbook_tester ) try {
        
        //============// UPSERT

        auto person_i_1 = mvo()
            ("user", "testacc") 
            ("first_name", "AAA") 
            ("last_name", "aaa")
            ("ph_num", "01000001111")
            ("email","AAAaaa@gmail.com")            
            ("status", false);

        push_action( N(contactbook), N(upsert), N(testacc), person_i_1);
        produce_block();

        person_t person_o_1;
        get_person( person_o_1, N(testacc));
        BOOST_TEST_MESSAGE( fc::json::to_pretty_string(person_o_1));

        //==========// MODIFY

        auto person_i_2 = mvo()
            ("user", "sriaccount11") 
            ("first_name", "AAA") 
            ("last_name", "aaa")
            ("ph_num", "01089201111")
            ("email","AAAaaa@yahoomail.com")            
            ("status", false);

        push_action( N(contactbook), N(upsert), N(sriaccount11), person_i_2);
        produce_blocks(1);

        person_t person_o_2;
        get_person( person_o_2, N(sriaccount11));
        BOOST_TEST_MESSAGE( fc::json::to_pretty_string(person_o_2));

        auto person_i_3 = mvo()
            ("user", "sriaccount11") 
            ("first_name", "AAA") 
            ("last_name", "aaa")
            ("ph_num", "01089201111")
            ("email","AAAaaa@gmail.com")            
            ("status", false);

        push_action( N(contactbook), N(upsert), N(sriaccount11), person_i_3);
        produce_blocks(1);

        person_t person_o_3;
        get_person( person_o_3, N(sriaccount11));
        BOOST_TEST_MESSAGE( fc::json::to_pretty_string(person_o_3));

        //==========// ERASE

        push_action( N(contactbook), N(erase), N(testacc), mvo() ("user", "testacc") );
        produce_blocks(1);
    
    }FC_LOG_AND_RETHROW() 

BOOST_AUTO_TEST_SUITE_END()
