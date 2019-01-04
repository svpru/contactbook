
#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>

using namespace eosio;

class [[eosio::contract]] contactbook : public eosio::contract {

public:
  using contract::contract;
  
  contactbook(name receiver, name code,  datastream<const char*> ds): contract(receiver, code, ds) {}

  [[eosio::action]]
  
  // insert a new contact 

  void upsert(name user, std::string first_name, std::string last_name, std::string ph_num, std::string email) {
    require_auth( user );

    contact_index contacts(_code, _code.value);

    auto iterator = contacts.find(user.value);
    if( iterator == contacts.end() )
    {
      contacts.emplace(user, [&]( auto& row ) {
       row.key = user;
       row.first_name = first_name;
       row.last_name = last_name;
       row.ph_num = ph_num;
       row.email = email;
      });
      send_summary(user, "successfully emplaced record to contactbook");
    }
    else {
      std::string changes;

      // modify the contact
      
      contacts.modify(iterator, user, [&]( auto& row ) {
        row.key = user;
        row.first_name = first_name;
        row.last_name = last_name;
        row.ph_num = ph_num;
        row.email = email;
      });
      send_summary(user, "successfully modified record to contactbook");
    }
  }

  [[eosio::action]]
  
  //erase an existing contact

  void erase(name user) {
    require_auth(user);
    contact_index contacts(_self, _code.value);
    auto iterator = contacts.find(user.value);
    eosio_assert(iterator != contacts.end(), "Record does not exist");
    contacts.erase(iterator);
    send_summary(user, "successfully erased record from contactbook");
  }

  [[eosio::action]]
  void notify(name user, std::string msg) {
    require_auth(get_self());
    require_recipient(user);
  }

private:
  
  struct [[eosio::table]] person {
    name key;
    std::string first_name;
    std::string last_name;
    std::string ph_num;
    std::string email;
    uint64_t primary_key() const { return key.value; }
  };

  typedef eosio::multi_index<"people"_n, person> contact_index;

  void send_summary(name user, std::string message) {
    action(
      permission_level{get_self(),"active"_n},
      get_self(),
      "notify"_n,
      std::make_tuple(user, name{user}.to_string() + message)
    ).send();
  };

};

EOSIO_DISPATCH( contactbook, (upsert)(notify)(erase) )    