Language: **English** or [Russian](https://github.com/Bren828/promo-code/blob/main/README.md)

# promo-code
Текс

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


forward OnPlayerPromoCodeActivation(playerid, name[], promo_code_id, activation_count, remaining_activation_count);
public OnPlayerPromoCodeActivation(playerid, name[], promo_code_id, activation_count, remaining_activation_count)
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
> Вызывается при активации промокода
> * `name[]` - название промокода
> * `promo_code_id` - ID промокода
> * `activation_count` - число, сколько было активаций
> * `remaining_activation_count` - число, сколько осталось активаций **(Вернет: -1 если бесконечно)**
> * **ПРИМЕЧАНИЕ: Всегда используйте в конце 'return 0;', если промокод активирован**


#### public OnPlayerPromoCodeCreate(playerid, const name[], remaining_activation_count, expiration_date, const category_names[], const category_value[])
> Вызывается при создании промокода
> * `name[]` - название промокода
> * `remaining_activation_count` - число, сколько осталось активаций **(Вернет: -1 если бесконечно)**
> * `expiration_date` - срок действия промокода `gettime()`
> * `category_names[]` - названия категорий
> * `category_value[]` - значения категорий


#### public OnPlayerPromoCodeEdit(playerid, const old_name[], const new_name[], remaining_activation_count, expiration_date, const category_names[], const category_value[])
> Вызывается при редактирование промокода
> * `old_name[]` - старое название промокода
> * `new_name[]` - новое название промокода
> * `remaining_activation_count` - число, сколько осталось активаций **(Вернет: -1 если бесконечно)**
> * `expiration_date` - срок действия промокода `gettime()`
> * `category_names[]` - названия категорий
> * `category_value[]` - значения категорий


#### public OnPlayerPromoCodeDelete(playerid, const name[], promo_code_id)
> Вызывается при удалении промокода
> * `name[]` - название промокода
> * `promo_code_id` - ID промокода

## Functions

#### PromoCodeCreate(playerid)
> Открывает диалог с созданием промокода
 

#### PromoCodeList(playerid)
> Открывает диалог с списком созданных промокодов


#### PromoCodeCategoryCreate(const name[])
> Создать категорию промокода   
> * `name[]` - название категории
> * Вернет: 0 при неудачи
> * Вернет: 1 при успехе


#### PromoCodeLoad(const name[], activation_count, remainin_activation_count, expiration_date, const category_names[], const category_values[])
> Загрузить промокод
> * `name[]` - название промокода
> * `activation_count` - число, сколько было активаций
> * `remainin_activation_count` - число, сколько осталось активаций **(Вернет: -1 если бесконечно)**
> * `expiration_date` - срок действия промокода `gettime()`
> * `category_names[]` - названия категорий  
> * `category_values[]` - значения категорий
> * Вернет: 0 при неудачи
> * Вернет: ID созданного промокода


#### PromoCodeDelete(const name[])
> Удалить промокод
> * `name[]` - название промокода
> * `bool:callback` - вызывать **'OnPlayerPromoCodeDelete'** при удаление 
> * Вернет: 0 при неудачи
> * Вернет: ID созданного промокода


#### IsPromoCodeCreate(const name[])
> Проверить промокод на создание
> * `name[]` - название промокода
> * Вернет: 0 при неудачи
> * Вернет: 1 при успехе


#### PromoCodeActivation(playerid, const name[], &errorid = 0)
> Активировать промокод
> * `name[]` - название промокода
> * `errorid` - вернет номер ошибки **(PROMO_CODE_ACTIVATIONS_ENDED (2) || PROMO_CODE_EXPIRED (3))**
> * Вернет: 0 при неудачи
> * Вернет: 1 при успехе


#### GetPromoCodeCategoryName(promo_code_id, const find_category[], &category_value = 0)
> Проверить промокод на определенную категорию
> * `promo_code_id` - ID промокода
> * `find_category[]` - название категории для поиска
> * `&category_value` - возвращает значение категории
> * Вернет: 0 при неудачи
> * Вернет: 1 при успехе


#### GetPromoCodeCompare(const name1[], const name2[])
> Сравнить первое название промокода со вторым названием промокода **( аналог функции strcmp )**
> * `name1[]` - первое название промокода для сравнения
> * `name2[]` - второе название промокода для сравнения
> * Вернет: 0 при неудачи
> * Вернет: 1 при успехе

## Definition
```pawn
#define PC_MAX_PROMO_CODE                       500 // максимальное количество промокодов

#define PC_MAX_NAME_SIZE                        32 // максимальная длина названия промокода

#define PC_MAX_CATEGORY                         100 // максимальное количество категории для промокодов

#define PC_MAX_CATEGORY_IN_PROMO_CODE           50 // максимальное количество категории в одном промокоде

#define PC_MAX_CATEGORY_NAME_SIZE               30 // максимальная длина названия категории промокода

#define PC_MAX_DIALOG_LISTITEM_SIZE             20 // количество строк в диалоге, после которых отображается кнопка 'Дальше'

#define PC_COLOR_1                              "{F5D742}" // 0xF5D742

#define PC_COLOR_2                              "{8fce00}" // 0x8fce00

#define PC_COLOR_3                              "{f44747}" // 0xf44747
```

## Enum
```pawn
PROMO_CODE_ACTIVATIONS_ENDED = 2,
PROMO_CODE_EXPIRED = 3
```
