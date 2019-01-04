# contactbook
This basically is a contract which takes an account holder’s contact details.

## version: 1.0

Dependencies:
* [eosio.cdt version : 1.4.1](https://github.com/eosio/eosio.cdt)
  * eosio.cdt includes libraries and build modules
* [eosio version : 1.4.4](https://github.com/EOSIO/eos)
  * eosio includes __unittest__ modules. unittest used boost test framework.
*  Boost version: 1.67.0

Prior to run the contract: 
* First,ensure that your system is updated with the appropriate dependencies as mentioned above.
* __eosio :__ eosio is built using ```./eosio_build.sh```  and installed using ``` sudo ./eosio_install.sh``` in __eos__ directory
* __eosio.cdt :__  eosio is built using ```./build.sh```  and installed using ``` sudo ./install.sh``` in __eosio.cdt__ directory 

To build the contract or unittests:
* Then run ```./build.sh ``` in ```contactbook``` directory.

To run the unittests:
* ```./build/tests/unit_test --log_level=all``` in ```contactbook``` directory.

After build:
* The unit tests executable is placed in the _build/tests_ and is named __unit_test__.
* The contracts are built in the _/\<contract name\>_ folder in their respective directories.
* Finally, simply use __cleos__ to _set contract_ by pointing to the previously mentioned directory.

Summary:
  This contract is made as am simple demonstration for begginers. This a similar example like addressbook explained in eosio Developer portal.

Account Parameters:
* Account name (reference Key) as "user"
* First name as "first_name"
* last Name as "last_name"
* Phone number as "ph_num"
* Email as "email"

Actions:
* This contract has 3 actions.

    * emplace : emplace a new account into a table.
    * modify  : modifies an exited account of the table
    * erase   : erases an existed account of the table

multi_index table name:
* people
