# contactbook
## version: 1

Dependencies:
* [Eosio cdt Version : 1.4.1](https://github.com/eosio/eosio.cdt)
* [Eosio Version : 1.4.4](https://github.com/eosio/eo)
*  Boost version: 1.67.0


To build the unit tests:
* Run ./build.sh 

After build:
* The unit tests executable is placed in the _build/tests_ and is named __unit_test__.
* The contracts are built in the _/\<contract name\>_ folder in their respective directories.
* Finally, simply use __cleos__ to _set contract_ by pointing to the previously mentioned directory.

Summary:
  This contract is made as am simple demonstartion for begginers. This a similar example like addressbook explained in eosio Developer portal.

Account Parameters:
* Account name (reference Key) as "user"
* First name as "first_name"
* last Name as "last_name"
* Phone number as "ph_num"
* Email as "email"

Actions:
* This contract has 3 actions.

    * emplace : emplace a new account into a table "person".
    * modify  : modifies an exited account of the table's multi-index "people"
    * erase   : erases an existed account of the table's multi_index "people"

Table name:
* person

Multi index of the table name:
* people

