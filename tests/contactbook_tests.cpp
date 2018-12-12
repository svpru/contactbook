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
        produce_blocks( 2 );

        create_account( N(contactbook));
        produce_blocks(1);

        set_code( N(contactbook), contracts::contactbook_wasm() );
        set_abi( N(contactbook), contracts::contactbook_abi().data() );

        create_account( N(testacc));
        produce_blocks(1);
        set_code( N(testacc), contracts::contactbook_wasm() );
        set_abi( N(testacc), contracts::contactbook_abi().data() );

        create_account( N(sriaccount11));
        produce_blocks(1);
        set_code( N(sriaccount11), contracts::contactbook_wasm() );
        set_abi( N(sriaccount11), contracts::contactbook_abi().data() );

        produce_blocks(3); 
        BOOST_TEST_MESSAGE( "Accoounts created");
    }

   void init_abi_ser(abi_serializer& abi_ser, account_name name) {
        const auto& accnt = control->db().get<account_object,by_name>( name );
        abi_def abi;
        // BOOST_REQUIRE_EQUAL(abi_serializer::to_abi(accnt.abi, abi), true);
        abi_serializer::to_abi(accnt.abi, abi);
        abi_ser.set_abi(abi, abi_serializer_max_time);
    }

};


BOOST_AUTO_TEST_SUITE(contactbook_tests)


    BOOST_FIXTURE_TEST_CASE( upsert_tests, contactbook_tester ) try {
        push_action( N(contactbook), N(upsert), N(testacc), mvo()
                ("user", "testacc") 
                ("first_name", "AAA") 
                ("last_name", "aaa")
                ("ph_num", "01000001111")
                ("email","AAAaaa@gmail.com")            
                ("status", false)
        );
        produce_blocks(1);

        person_t person1;

        BOOST_TEST_MESSAGE("person 1 created");
    
        push_action( N(contactbook), N(upsert), N(testacc), mvo()
                ("user", "testacc") 
                ("first_name", "AAA") 
                ("last_name", "aaa")
                ("ph_num", "01000001111")
                ("email","AAAaaa@yahoomail.com")            // different email.
                ("status", false)
        );
        BOOST_TEST_MESSAGE( "New Record Upserted" );

        person_t person2;
    
        BOOST_TEST_MESSAGE("person 2 created");
            
        if ( person2.key == person1.key)  BOOST_TEST_MESSAGE("Successfully Existed Record Modified");

    }FC_LOG_AND_RETHROW()


  //===========================================================================================================//
    //Emplacing a new Record.

    BOOST_FIXTURE_TEST_CASE( upsert_tests1, contactbook_tester ) try {
        push_action( N(contactbook), N(upsert), N(testacc), mvo()
                ("user", "testacc") 
                ("first_name", "AAA") 
                ("last_name", "aaa")
                ("ph_num", "01000001111")
                ("email","AAAaaa@gmail.com")            
                ("status", false)
            );
            BOOST_TEST_MESSAGE( "Record Upserted");
        produce_blocks(1);

        person_t person1;

        BOOST_TEST_MESSAGE("person 1 created");
    
    
        push_action( N(contactbook), N(upsert), N(sriaccount11), mvo()
                ("user", "sriaccount11") 
                ("first_name", "SSS") 
                ("last_name", "sss")
                ("ph_num", "01000003333")
                ("email","SSSsss@gmail.com")
                ("status", false)
            );

        BOOST_TEST_MESSAGE( "New Record Userted" );

        person_t person2;
    
        BOOST_TEST_MESSAGE("person 2 created");
            
        if ( person2.key != person1.key)    BOOST_TEST_MESSAGE("Successfully New Record Emplaced"); 
    
    
    }FC_LOG_AND_RETHROW()

//===============================================================================================//

    // Erasing Person Record.
    
    BOOST_FIXTURE_TEST_CASE( erase_tests, contactbook_tester ) try { 

        push_action( N(contactbook), N(upsert), N(testacc), mvo()
                ("user", "testacc") 
                ("first_name", "AAA") 
                ("last_name", "aaa")
                ("ph_num", "01000001111")
                ("email","AAAaaa@gmail.com")            
                ("status", false)
            );
        produce_blocks(1); 

        push_action( N(contactbook), N(erase), N(testacc), mvo()
            ("user", "testacc")
            );
        produce_blocks(1);
        BOOST_TEST_MESSAGE("Successfully Existed Record Erased");

    }FC_LOG_AND_RETHROW()

BOOST_AUTO_TEST_SUITE_END()
