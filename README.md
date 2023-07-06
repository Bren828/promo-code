# promo-code
Creating promo codes with categories in SAMP 

![Crosshair](https://raw.githubusercontent.com/Bren828/promo-code/main/preview.gif)

## Reference
* [Download](https://github.com/Bren828/promo-code#download)
* [Installation](https://github.com/Bren828/promo-code#installation)
* [Example](https://github.com/Bren828/promo-code#example)
* [Callbacks](https://github.com/Bren828/promo-code#callbacks)
* [Functions](https://github.com/Bren828/promo-code#functions)
* [Definition](https://github.com/Bren828/promo-code#definition)
* [Enum](https://github.com/Bren828/promo-code#enum)

## Download
[Releases page](https://github.com/Bren828/promo-code/releases)

## Installation

Include in your code and begin using the library:
```pawn
#include <promo-code>
```

## Example

```pawn
public OnGameModeInit()
{
    PromoCodeCategoryCreate("Skill TEC9");
    PromoCodeCategoryCreate("Money");
    return 1;
}


forward OnPlayerPromoCodeActivation(playerid, const name[], promo_code_id, activation_count, remaining_activation_count);
public OnPlayerPromoCodeActivation(playerid, const name[], promo_code_id, activation_count, remaining_activation_count)
{
    new category_value;
    if(GetPromoCodeCategoryName(promo_code_id, "Skill TEC9", category_value))
    {
        SetPlayerSkillLevel(playerid, 32, category_value);
    }
    if(GetPromoCodeCategoryName(promo_code_id, "Money", category_value))
    {
        GivePlayerMoney(playerid, category_value);
    }
    
    
    // Mysql R39-6 save example
    static const mysql_str[] = "UPDATE promo_code SET activation_count=%d,remaining_activation_count=%d WHERE name='%s' LIMIT 1";
    new string[ sizeof(mysql_str) + PC_MAX_NAME_SIZE + 10 + 10];

    mysql_format(mysql, string, sizeof(string), mysql_str, activation_count, remaining_activation_count, name);
    mysql_tquery(mysql, string);
    return 0;
}

forward OnPlayerPromoCodeCreate(playerid, const name[], remaining_activation_count, expiration_date, const category_names[], const category_value[]);
public OnPlayerPromoCodeCreate(playerid, const name[], remaining_activation_count, expiration_date, const category_names[], const category_value[])
{
    printf("Create --->>> name: %s | remaining_activation_count: %d | expiration_date: %d | category_names: '%s' | category_value: '%s' |", 
    name, remaining_activation_count, expiration_date, category_names, category_value);


    // Mysql R39-6 save example
    static const mysql_str[] = "INSERT INTO promo_code (`name`,`activation_count`,`remaining_activation_count`,`expiration_date`,`category_names`,`category_value`) VALUE ('%s','0','%d','%d','%s','%s')";
    new string[ sizeof(mysql_str) + PC_MAX_NAME_SIZE + 10 + 10 +( (PC_MAX_CATEGORY_NAME_SIZE+1) * PC_MAX_CATEGORY_IN_PROMO_CODE ) + ( 11 * PC_MAX_CATEGORY_IN_PROMO_CODE ) ];

    mysql_format(mysql, string, sizeof(string), mysql_str, name, remaining_activation_count, expiration_date, category_names, category_value);
    mysql_query(mysql, string);
    return 1;
}

forward OnPlayerPromoCodeEdit(playerid, const old_name[], const new_name[], remaining_activation_count, expiration_date, const category_names[], const category_value[]);
public OnPlayerPromoCodeEdit(playerid, const old_name[], const new_name[], remaining_activation_count, expiration_date, const category_names[], const category_value[])
{
    printf("Edit --->>> old_name: %s | new_name: %s | remaining_activation_count: %d | expiration_date: %d | category_names: '%s' | category_value: '%s' |", 
    old_name, new_name, remaining_activation_count, expiration_date, category_names, category_value);
	

    // Mysql R39-6 save example
    static const mysql_str[] = "UPDATE promo_code SET name='%s',remaining_activation_count=%d,expiration_date=%d,category_names='%s',category_value='%s' WHERE name='%s' LIMIT 1";
    new string[ sizeof(mysql_str) + PC_MAX_NAME_SIZE + 10 + 10 +( (PC_MAX_CATEGORY_NAME_SIZE+1) * PC_MAX_CATEGORY_IN_PROMO_CODE ) + ( 11 * PC_MAX_CATEGORY_IN_PROMO_CODE ) ];

    mysql_format(mysql, string, sizeof(string), mysql_str, new_name, remaining_activation_count, expiration_date, category_names, category_value, old_name);
    mysql_tquery(mysql, string);
    return 1;
}

forward OnPlayerPromoCodeDelete(playerid, const name[], promo_code_id);
public OnPlayerPromoCodeDelete(playerid, const name[], promo_code_id)
{
    printf("Delete --->>> name: %s | promo_code_id: %d |", 
        name, promo_code_id);


    // Mysql R39-6 save example
    static const mysql_str[] = "DELETE FROM promo_code WHERE name='%s' LIMIT 1";
    new string[sizeof(mysql_str) + PC_MAX_NAME_SIZE];

    mysql_format(mysql, string, sizeof(string), mysql_str, name);
    mysql_tquery(mysql, string);
    return 1;
}
```

## Callbacks
#### public OnPlayerPromoCodeActivation(playerid, const name[], promo_code_id, activation_count, remaining_activation_count)
> Called when the promo code is activated
> * `name[]` - Promo code name
> * `promo_code_id` - The ID of the code name
> * `activation_count` - Number of activations
> * `remaining_activation_count` - how many activations are left **(Returns: -1 if infinite)**
> * **NOTE: Always use 'return 0;' at the end if the promo code is activated**


#### public OnPlayerPromoCodeCreate(playerid, const name[], remaining_activation_count, expiration_date, const category_names[], const category_value[])
> Called when creating a promo code
> * `name[]` - Promo code name
> * `remaining_activation_count` - number of activations left **(Return: -1 if infinite)**
> * `expiration_date` -  validity period `gettime()`
> * `category_names[]` - category names
> * `category_value[]` - category values


#### public OnPlayerPromoCodeEdit(playerid, const old_name[], const new_name[], remaining_activation_count, expiration_date, const category_names[], const category_value[])
> Called when editing a promo code
> * `old_name[]` - old promo code name
> * `new_name[]` - new promo code name
> * `remaining_activation_count` - number of activations left **(Return: -1 if infinite)**
> * `expiration_date` - validity period `gettime()`
> * `category_names[]` - category names
> * `category_value[]` - category values


#### public OnPlayerPromoCodeDelete(playerid, const name[], promo_code_id)
> Called when the promo code is deleted
> * `name[]` - Promo code name
> * `promo_code_id` - The ID of the code name

## Functions

#### PromoCodeCreate(playerid)
> Create a promo code
 

#### PromoCodeList(playerid)
> List of promo codes


#### PromoCodeCategoryCreate(const name[])
> Create a promo code category
> * `name[]` - Category name
> * Returns (0) on failure or (1) on success


#### PromoCodeLoad(const name[], activation_count, remainin_activation_count, expiration_date, const category_names[], const category_values[])
> Load promo code
> * `name[]` - Promo code name
> * `activation_count` - how many activations
> * `remainin_activation_count` - number of activations left **(Return: -1 if infinite)**
> * `expiration_date` - validity period `gettime()`
> * `category_names[]` - category names
> * `category_values[]` - category values
> * Returns (0) on failure or promo code id


#### PromoCodeDelete(const name[])
> Delete promo code
> * `name[]` - Promo code name
> * `bool:callback` - call **'OnPlayerPromoCodeDelete'** on delete
> * Returns (0) on failure or promo code id


#### IsPromoCodeCreate(const name[])
> Check the promo code for creation
> * `name[]` - Promo code name
> * Returns (0) on failure or (1) on success


#### PromoCodeActivation(playerid, const name[], &errorid = 0)
> Activate a promo code
> * `name[]` - Promo code name
> * `errorid` - error number **(PROMO_CODE_ACTIVATIONS_ENDED (2) || PROMO_CODE_EXPIRED (3))**
> * Returns (0) on failure or (1) on success


#### GetPromoCodeCategoryName(promo_code_id, const find_category[], &category_value = 0)
> Check a promo code for a certain category
> * `promo_code_id` - The ID of the code name
> * `find_category[]` - name of the category to search for
> * `&category_value` - returns the category value
> * Returns (0) on failure or (1) on success


#### GetPromoCodeCompare(const name1[], const name2[])
> Compare the promo code name **( function analogue strcmp )**
> * `name1[]` - first name
> * `name2[]` - second name
> * Returns (0) on failure or (1) on success

## Definition
```pawn
#define PC_MAX_PROMO_CODE                       300

#define PC_MAX_NAME_SIZE                        32

#define PC_MAX_CATEGORY                         100

#define PC_MAX_CATEGORY_IN_PROMO_CODE           40

#define PC_MAX_CATEGORY_NAME_SIZE               30

#define PC_MAX_DIALOG_LISTITEM_SIZE             20 // max dialog list lines

#define PC_COLOR_1                              "{F5D742}" // 0xF5D742

#define PC_COLOR_2                              "{8fce00}" // 0x8fce00

#define PC_COLOR_3                              "{f44747}" // 0xf44747
```

## Enum
```pawn
PROMO_CODE_ACTIVATIONS_ENDED = 2,
PROMO_CODE_EXPIRED = 3
```
