/*
*
*
*
*   ---------------------------------------------------
*
*	Creater - @Bren828 					
*									16 March 2023
*
*   Version: 1.0
*
*   ---------------------------------------------------
*
*
*	https://github.com/Bren828/promo-code
*
*
*
* Открывает диалог с созданием промокода
*      PromoCodeCreate(playerid)
*
*
* Открывает диалог с списком созданных промокодов
*      PromoCodeList(playerid)
*
*
* Создать категорию промокода   
*       PromoCodeCategoryCreate(const name[])
*     
*       * name[]: название категории
*       * Вернет: 0 при неудачи
*       * Вернет: 1 при успехе
*
*
* Загрузить промокод
*       PromoCodeLoad(const name[], activation_count, remaining_activation_count, expiration_date, const category_names[], const category_values[])
*       * name[]: название промокода
*       * activation_count: число, сколько было активаций
*       * remaining_activation_count: число, сколько осталось активаций (Вернет: -1 если бесконечно)
*       * expiration_date: срок действия промокода ( gettime() )
*       * category_names[]: названия категорий  
*       * category_values[]: значения категорий
*       * Вернет: 0 при неудачи
*       * Вернет: ID созданного промокода
*  
*
* Удалить промокод
*       PromoCodeDelete(const name[])
*     
*       * name[]: название промокода
*       * bool:callback: вызывать 'OnPlayerPromoCodeDelete' при удаление 
*       * Вернет: 0 при неудачи
*       * Вернет: ID созданного промокода
*
*
* Проверить промокод на создание
*       IsPromoCodeCreate(const name[])
*     
*       * name[]: название промокода
*       * Вернет: 0 при неудачи
*       * Вернет: 1 при успехе
*
*
* Активировать промокод
*       PromoCodeActivation(playerid, const name[], &errorid = 0)
*     
*       * name[]: название промокода
*       * errorid: вернет номер ошибки (PROMO_CODE_ACTIVATIONS_ENDED (2) || PROMO_CODE_EXPIRED (3))
*       * Вернет: 0 при неудачи
*       * Вернет: 1 при успехе
*     
*
* Проверить промокод на определенную категорию
*       GetPromoCodeCategoryName(promo_code_id, const find_category[], &category_value = 0)
* 
*       * promo_code_id: ID промокода
*       * find_category[]: название категории для поиска
*       * &category_value: возвращает значение категории
*       * Вернет: 0 при неудачи
*       * Вернет: 1 при успехе
*
*
* Сравнить первое название промокода со вторым названием промокода ( аналог функции strcmp )
*       GetPromoCodeCompare(const name1[], const name2[])
*     
*       * name1[]: первое название промокода для сравнения
*       * name2[]: второе название промокода для сравнения
*       * Вернет: 0 при неудачи
*       * Вернет: 1 при успехе
* 
*  
* Вызывается при активации промокода
*       public OnPlayerPromoCodeActivation(playerid, const name[], promo_code_id, activation_count, remaining_activation_count)
*
*       * name[]: название промокода
*       * promo_code_id: ID промокода
*       * activation_count: число, сколько было активаций
*       * remaining_activation_count: число, сколько осталось активаций (Вернет: -1 если бесконечно)
*       * ПРИМЕЧАНИЕ: Всегда используйте в конце 'return 0;', если промокод активирован
* 
*
* Вызывается при создании промокода
*       public OnPlayerPromoCodeCreate(playerid, const name[], remaining_activation_count, expiration_date, const category_names[], const category_value[])
*     
*       * name[]: название промокода
*       * remaining_activation_count: число, сколько осталось активаций (Вернет: -1 если бесконечно)
*       * expiration_date: срок действия промокода ( gettime() )
*       * category_names[]: названия категорий
*       * category_value[]: значения категорий
* 
*
* Вызывается при редактирование промокода
*       public OnPlayerPromoCodeEdit(playerid, const old_name[], const new_name[], remaining_activation_count, expiration_date, const category_names[], const category_value[])
*     
*       * old_name[]: старое название промокода
*       * new_name[]: новое название промокода
*       * remaining_activation_count: число, сколько осталось активаций (Вернет: -1 если бесконечно)
*       * expiration_date: срок действия промокода ( gettime() )
*       * category_names[]: названия категорий
*       * category_value[]: значения категорий
* 
*
* Вызывается при удалении промокода
*       public OnPlayerPromoCodeDelete(playerid, const name[], promo_code_id)
*     
*       * name[]: название промокода
*       * promo_code_id: ID промокода
* 
* 
*/

#if defined _promo_code_included
	#endinput
#endif
#define _promo_code_included


#if !defined PC_MAX_PROMO_CODE
	#define PC_MAX_PROMO_CODE                       300 // максимальное количество промокодов
#endif

#if !defined PC_MAX_NAME_SIZE
	#define PC_MAX_NAME_SIZE                        32 // максимальная длина названия промокода
#endif

#if !defined PC_MAX_CATEGORY
	#define PC_MAX_CATEGORY                         100 // максимальное количество категорий для промокодов
#endif

#if !defined PC_MAX_CATEGORY_IN_PROMO_CODE
	#define PC_MAX_CATEGORY_IN_PROMO_CODE           40 // максимальное количество категорий в одном промокоде
#endif

#if !defined PC_MAX_CATEGORY_NAME_SIZE
	#define PC_MAX_CATEGORY_NAME_SIZE               30 // максимальная длина названия категорий промокода
#endif

#if !defined PC_MAX_DIALOG_LISTITEM_SIZE
    #define PC_MAX_DIALOG_LISTITEM_SIZE             20 // количество строк в диалоге, после которых отображается кнопка 'Дальше'
#endif

#if !defined PC_COLOR_1
    #define PC_COLOR_1                              "{F5D742}" // 0xF5D742
#endif

#if !defined PC_COLOR_2
    #define PC_COLOR_2                              "{8fce00}" // 0x8fce00
#endif

#if !defined PC_COLOR_3
    #define PC_COLOR_3                              "{f44747}" // 0xf44747
#endif

#if PC_MAX_CATEGORY < PC_MAX_CATEGORY_IN_PROMO_CODE

	#error '#define PC_MAX_CATEGORY_IN_PROMO_CODE' can't be more than '#define PC_MAX_CATEGORY'

#endif 

enum
{
    PROMO_CODE_ACTIVATIONS_ENDED = 2,
    PROMO_CODE_EXPIRED = 3
}

enum PROMO_CODE_EN
{
    bool:pc_Create,
    pc_Name[PC_MAX_NAME_SIZE],
    pc_ActivationCount, 
    pc_RemainingActivationCount, 
    pc_ExpirationDate,
    pc_Category_Value[PC_MAX_CATEGORY_IN_PROMO_CODE]
}
static promo_code[PC_MAX_PROMO_CODE][PROMO_CODE_EN];
static promo_code_category_names[PC_MAX_PROMO_CODE][PC_MAX_CATEGORY_IN_PROMO_CODE][PC_MAX_CATEGORY_NAME_SIZE];

enum PROMO_CODE_CATEGORY_EN
{
    bool:pcc_Create,
    pcc_Name[PC_MAX_CATEGORY_NAME_SIZE]
}
static promo_code_category[PC_MAX_CATEGORY][PROMO_CODE_CATEGORY_EN];
static promo_code_category_max;

enum PROMO_CODE_PLAYER_EN
{
    pcp_Name[PC_MAX_NAME_SIZE],
    pcp_CategoryID[PC_MAX_CATEGORY_IN_PROMO_CODE],
    pcp_CategoryValues[PC_MAX_CATEGORY_IN_PROMO_CODE],
    pcp_RemainingActivationCount,
    pcp_ExpirationDate,
    pcp_DialogListitem,
    pcp_DialogListitemIDs[PC_MAX_DIALOG_LISTITEM_SIZE],

    pcp_Page, pcp_PageBackButton,
    pcp_CategoryPage, pcp_CategoryPageBackButton,
    bool:pcp_CategoryUsed[PC_MAX_CATEGORY],

    bool:pcp_EditPromoCode[2],
    pcp_ListPage,
    pcp_ListBackButton,
    pcp_ListSlotID,
    pcp_ListDialogListitemIDs[PC_MAX_DIALOG_LISTITEM_SIZE]
}
static promo_code_player[MAX_PLAYERS][PROMO_CODE_PLAYER_EN];


stock PromoCodeCategoryCreate(const name[])
{
    if(promo_code_category_max >= PC_MAX_CATEGORY) return printf("promo-code --->>> | PromoCodeCategoryCreate | error, while creating '%s' | increase the value '#define PC_MAX_CATEGORY'", name) & 0;
    if(strlen(name) < 3 || strlen(name) >= PC_MAX_CATEGORY_NAME_SIZE) return printf("promo-code --->>> | PromoCodeCategoryCreate | error, while creating '%s' | wrong name length (length from 3 to %d)", name, PC_MAX_CATEGORY_NAME_SIZE) & 0;

    promo_code_category[ promo_code_category_max ][pcc_Create] = true;
    format(promo_code_category[ promo_code_category_max ][pcc_Name], PC_MAX_CATEGORY_NAME_SIZE, name);

    promo_code_category_max++;
    return 1;
}

stock PromoCodeLoad(const name[], activation_count, remaining_activation_count, expiration_date, const category_names[], const category_values[])
{
    if(strlen(name) < 3 || strlen(name) >= PC_MAX_NAME_SIZE) return printf("promo-code --->>> | PromoCodeLoad | error, while creating '%s' | wrong name length (length from 3 to %d)", name, PC_MAX_NAME_SIZE) & 0;
    new promo_code_id;
    for(new x = 1; x < PC_MAX_PROMO_CODE; x ++)
	{
		if(promo_code[x][pc_Create] == true) continue;
		promo_code_id = x;
		break;
	}
	if(!promo_code_id) return print("promo-code --->>> | PromoCodeLoad | not all promo-code were created! | increase the value '#define PC_MAX_PROMO_CODE'") & 0;

    promo_code[promo_code_id][pc_Create] = true;
    format(promo_code[promo_code_id][pc_Name], PC_MAX_NAME_SIZE, name);
    promo_code[promo_code_id][pc_ActivationCount] = activation_count;
    promo_code[promo_code_id][pc_RemainingActivationCount] = remaining_activation_count;
    promo_code[promo_code_id][pc_ExpirationDate] = expiration_date;

    new _category_name[PC_MAX_CATEGORY_IN_PROMO_CODE][PC_MAX_CATEGORY_NAME_SIZE+1];
    sscanf(category_names,  "p<,>a<s[*]>[*]", sizeof(_category_name), sizeof(_category_name[]), _category_name);
    sscanf(category_values, "p<,>a<d>["#PC_MAX_CATEGORY_IN_PROMO_CODE"]", promo_code[promo_code_id][pc_Category_Value]);
    for(new x; x < PC_MAX_CATEGORY_IN_PROMO_CODE; x ++) format(promo_code_category_names[promo_code_id][x], PC_MAX_CATEGORY_NAME_SIZE, _category_name[x]);
    
    return promo_code_id;
}

stock PromoCodeActivation(playerid, const name[], &errorid = 0)
{
    if(strlen(name) < 3 || strlen(name) >= PC_MAX_NAME_SIZE) return 0;
    errorid = 0;
    for(new x = 1; x < PC_MAX_PROMO_CODE; x ++)
	{
		if(promo_code[x][pc_Create] == false) continue;
        if(strcmp(name, promo_code[x][pc_Name], false)) continue;
        if(promo_code[x][pc_RemainingActivationCount] == 0)
        {
            errorid = PROMO_CODE_ACTIVATIONS_ENDED;
            break;
        }
        if(promo_code[x][pc_ExpirationDate] != 0 && promo_code[x][pc_ExpirationDate] <= gettime())
        {
            errorid = PROMO_CODE_EXPIRED;
            break;
        }
        errorid = 1;

        new check = CallLocalFunction("OnPlayerPromoCodeActivation", "dsddd", playerid, promo_code[x][pc_Name], x, promo_code[x][pc_ActivationCount]+1, (promo_code[x][pc_RemainingActivationCount] >= 1) ? (promo_code[x][pc_RemainingActivationCount]-1):(-1));
        if(check == 0)
        {
            promo_code[x][pc_ActivationCount]++;
            if(promo_code[x][pc_RemainingActivationCount] >= 1) promo_code[x][pc_RemainingActivationCount] --;
        }
		break;
	}
    return errorid;
}

stock GetPromoCodeCategoryName(promo_code_id, const find_category[], &category_value = 0)
{
    if(promo_code_id < 0 || promo_code_id >= PC_MAX_PROMO_CODE) return 0;
    if(promo_code[promo_code_id][pc_Create] == false) return 0;   
    new slot; 
    for(new x; x < PC_MAX_CATEGORY_IN_PROMO_CODE; x ++)
    {
        if(strlen(promo_code_category_names[promo_code_id][x]) <= 0) continue;
        if(strcmp(find_category, promo_code_category_names[promo_code_id][x], false)) continue;

        category_value = promo_code[promo_code_id][pc_Category_Value][x];
        slot = 1;
        break;
    }
    return slot;
}

stock GetPromoCodeCompare(const name1[], const name2[])
{
    return !strcmp(name1, name2, false);
}

stock IsPromoCodeCreate(const name[])
{
    if(strlen(name) < 3 || strlen(name) >= PC_MAX_NAME_SIZE) return 0;
    new slot;
    for(new x = 1; x < PC_MAX_PROMO_CODE; x ++)
	{
		if(promo_code[x][pc_Create] == false) continue;
        if(strcmp(name, promo_code[x][pc_Name], false)) continue;
		slot = 1;
		break;
	}
    return slot;
}

stock PromoCodeDelete(playerid, const name[], bool:callback = true)
{
    if(strlen(name) < 3 || strlen(name) >= PC_MAX_NAME_SIZE || playerid < 0) return 0;
    new promo_code_id;
    for(new x = 1; x < PC_MAX_PROMO_CODE; x ++)
	{
		if(promo_code[x][pc_Create] == false) continue;
        if(strcmp(name, promo_code[x][pc_Name], false)) continue;
		promo_code_id = x;
		break;
	}
	if(!promo_code_id) return 0;
    promo_code[promo_code_id][pc_Create] = false;
    promo_code[promo_code_id][pc_Name][0] = EOS;
    if(callback == true)
    {
        #if defined OnPlayerPromoCodeDelete
            OnPlayerPromoCodeDelete(playerid, name, promo_code_id);
        #endif
    }
    return promo_code_id;
}


stock PromoCodeCreate(playerid)
{
    format(promo_code_player[playerid][pcp_Name], PC_MAX_NAME_SIZE, "No name");
    promo_code_player[playerid][pcp_RemainingActivationCount] = -1;
    promo_code_player[playerid][pcp_ExpirationDate] = 0;

    promo_code_player[playerid][pcp_Page] = 0;
    promo_code_player[playerid][pcp_PageBackButton] = 0;

    promo_code_player[playerid][pcp_CategoryPage] = 0;
    promo_code_player[playerid][pcp_CategoryPageBackButton] = 0;

    for(new x; x < PC_MAX_CATEGORY_IN_PROMO_CODE; x ++)
    {
        if(x < PC_MAX_CATEGORY)
        {
            promo_code_player[playerid][pcp_CategoryID][x] = x;
            promo_code_player[playerid][pcp_CategoryValues][x] = 1000000989;
        }
        promo_code_player[playerid][pcp_CategoryUsed][x] = false;
    }
    promo_code_player[playerid][pcp_EditPromoCode][0] = false;
    promo_code_player[playerid][pcp_EditPromoCode][1] = false;

    Dialog_Show(playerid, Dialog:_promo_code_Create);
    return 1;
}

DialogCreate:_promo_code_Create(playerid)
{
    new string[208+PC_MAX_NAME_SIZE+14+31 + (PC_MAX_CATEGORY_NAME_SIZE+10+18)*PC_MAX_DIALOG_LISTITEM_SIZE ], activation[14] = "Бесконечно", expiration_date[31] = "Бессрочный", caption[55+10] = "Создание промокода";
    for(new x; x < PC_MAX_DIALOG_LISTITEM_SIZE; x ++) promo_code_player[playerid][pcp_DialogListitemIDs][x] = -1;
    
    if(promo_code_player[playerid][pcp_RemainingActivationCount] != -1) 
    {
        if(promo_code_player[playerid][pcp_EditPromoCode][0] == false || promo_code_player[playerid][pcp_RemainingActivationCount] >= 1) format(activation, sizeof(activation), "%d", promo_code_player[playerid][pcp_RemainingActivationCount]);
        else format(activation, sizeof(activation), "Закончились");
    }
    if(promo_code_player[playerid][pcp_ExpirationDate] != 0) 
    {
        if(promo_code_player[playerid][pcp_EditPromoCode][0] == false || promo_code_player[playerid][pcp_EditPromoCode][0] == true && promo_code[promo_code_player[playerid][pcp_ListSlotID]][pc_ExpirationDate] != promo_code_player[playerid][pcp_ExpirationDate]) format(expiration_date, sizeof(expiration_date), "%d дней(я)", promo_code_player[playerid][pcp_ExpirationDate]);
        else 
        {
            if(promo_code_player[playerid][pcp_ExpirationDate] != 0 && promo_code_player[playerid][pcp_ExpirationDate] <= gettime()) format(expiration_date, sizeof(expiration_date), "Истек");
            else format(expiration_date, sizeof(expiration_date), "осталось %s", _promo_code_convert(promo_code_player[playerid][pcp_ExpirationDate]- gettime()) );
        }
    }
    format(string, sizeof(string),
        "%s\t\n\
        Название промокода\t"PC_COLOR_1"%s\n\
        Количество активаций\t"PC_COLOR_1"%s\n\
        Срок действия\t"PC_COLOR_1"%s\n\
        {000000}\n\
        Добавить категорию\t\n\
        "PC_COLOR_1"Содержит категории\t"PC_COLOR_1"Количество:\n",
    (promo_code_player[playerid][pcp_EditPromoCode][0] == false) ? (""PC_COLOR_2"Создать промокод"):(""PC_COLOR_3"Удалить промокод"),
    promo_code_player[playerid][pcp_Name],
    activation,
    expiration_date);

    new line_max, block_back_button;
    for(new x = (promo_code_player[playerid][pcp_Page] * PC_MAX_DIALOG_LISTITEM_SIZE); x < (promo_code_player[playerid][pcp_Page] * PC_MAX_DIALOG_LISTITEM_SIZE)+PC_MAX_DIALOG_LISTITEM_SIZE+1; x ++)
    {
        if(x >= PC_MAX_CATEGORY_IN_PROMO_CODE || promo_code_player[playerid][pcp_CategoryID][x] == -1) break;
        if(line_max <= PC_MAX_DIALOG_LISTITEM_SIZE-1)
        {
            promo_code_player[playerid][pcp_DialogListitemIDs][line_max] = x;
            format(string, sizeof(string), "%s%s\t"PC_COLOR_1"%d\n", string, promo_code_category[ promo_code_player[playerid][pcp_CategoryID][x] ][pcc_Name], promo_code_player[playerid][pcp_CategoryValues][x]);

            if(x >= PC_MAX_CATEGORY_IN_PROMO_CODE -1)
            {
                if(promo_code_player[playerid][pcp_Page] >= 1) block_back_button = 1;
                break;
            }
        }
        line_max ++;
        if(line_max >= PC_MAX_DIALOG_LISTITEM_SIZE+1)
        {
            block_back_button = 2;
            strcat(string, "> Дальше\n");
            if(promo_code_player[playerid][pcp_Page] >= 1) strcat(string, "< Назад\n");
            break;
        }
    }
    if(promo_code_player[playerid][pcp_Page] >= 1 && block_back_button == 0 || block_back_button == 1)
    {
        strcat(string, "< Назад\n");
        promo_code_player[playerid][pcp_PageBackButton] = line_max + ((block_back_button == 0) ? (1):(2));
    }

    if(promo_code_player[playerid][pcp_EditPromoCode][0] == true) format(caption, sizeof(caption), "Редактирование промокода | "PC_COLOR_1"Кол-во активаций: %d", promo_code[ promo_code_player[playerid][pcp_ListSlotID] ][pc_ActivationCount]);
    Dialog_Open(playerid, Dialog:_promo_code_Create, DIALOG_STYLE_TABLIST, caption, string, "Выбрать", (promo_code_player[playerid][pcp_EditPromoCode][0] == false) ? ("Отмена"):("Назад"));
    return 1;
}

stock _promo_code_convert(number)
{
	new string[30], timers[3];
    timers[0] = floatround(number/3600);
	if(timers[0] <= 23)
	{
        timers[1] = floatround((number/60)-(timers[0]*60));
        timers[2] = floatround(number-((timers[0]*3600)+(timers[1]*60)));

        if(timers[0] < 0 || timers[0] >= 1) format(string, sizeof(string), "%02d часов %02d минут", timers[0], timers[1]);
        else if(timers[1] >= 1) format(string, sizeof(string), "%02d минут %02d секунд", timers[1], timers[2]);
        else format(string, sizeof(string), "%d секунд", timers[2]);
    }
	else format(string, sizeof(string), "%d дней(я)", timers[0]/24);
	return string;
}

DialogResponse:_promo_code_Create(playerid, response, listitem, inputtext[])
{
    if(!response) 
    {
        if(promo_code_player[playerid][pcp_EditPromoCode][0] == true) 
        {
            if(promo_code_player[playerid][pcp_EditPromoCode][1] == true)
            {
                Dialog_Open(playerid, Dialog:_promo_code_Savechanges, DIALOG_STYLE_MSGBOX, "Принятие изменений",  
                    "{FFFFFF}Были найдены изменения желаете их сохранить ?", "Да", "Нет");
                return 1;
            }
            Dialog_Show(playerid, Dialog:_promo_code_List);
        }
        return 1;
    }
    switch(listitem)
    {
        case 0:
        {
            if(promo_code_player[playerid][pcp_EditPromoCode][0] == true)
            {
                new string[60+PC_MAX_NAME_SIZE];
                format(string, sizeof(string), "{FFFFFF}Вы действительно желаете удалить промокод "PC_COLOR_1"%s", promo_code_player[playerid][pcp_Name]);
                Dialog_Open(playerid, Dialog:_promo_code_Delete, DIALOG_STYLE_MSGBOX, "Удалить промокод", string, "Удалить", "Назад");
                return 1;
            }
            if(IsPromoCodeCreate(promo_code_player[playerid][pcp_Name]))
            {
                Dialog_Open(playerid, Dialog:_promo_code_CreateError, DIALOG_STYLE_MSGBOX, "Создание промокода", 
                    "{FFFFFF}Промокод с данным названием уже есть.", "Закрыть", "Назад");
                return 1;
            }
            new category_names [(PC_MAX_CATEGORY_NAME_SIZE+1) * PC_MAX_CATEGORY_IN_PROMO_CODE],
                category_values[11 * PC_MAX_CATEGORY_IN_PROMO_CODE],
                max_category; 

            for(new x; x < PC_MAX_CATEGORY_IN_PROMO_CODE; x ++)
            {
                if(promo_code_player[playerid][pcp_CategoryID][x] == -1) continue;

                format(category_names, sizeof(category_names), "%s%s,", category_names, promo_code_category[ promo_code_player[playerid][pcp_CategoryID][x] ][pcc_Name]);
                format(category_values, sizeof(category_values), "%s%d,", category_values, promo_code_player[playerid][pcp_CategoryValues][x]);
                max_category++;
            }
            if(max_category == 0)
            {
                Dialog_Open(playerid, Dialog:_promo_code_CreateError, DIALOG_STYLE_MSGBOX, "Создание промокода", 
                    "{FFFFFF}Промокод не может быть создан без категорий.", 
                "Закрыть", "Назад");
                return 1;
            }

            new check = PromoCodeLoad(promo_code_player[playerid][pcp_Name], 0, promo_code_player[playerid][pcp_RemainingActivationCount], (promo_code_player[playerid][pcp_ExpirationDate] == 0) ? (0):(gettime() + (promo_code_player[playerid][pcp_ExpirationDate] * 86400)), category_names, category_values);
            if(!check)
            {
                Dialog_Open(playerid, Dialog:_promo_code_CreateError, DIALOG_STYLE_MSGBOX, "Создание промокода", 
                    "{FFFFFF}Достигнут лимит по количеству созданих промокодов.", 
                "Закрыть", "Назад");
                return 1;
            }

            new string[47+PC_MAX_NAME_SIZE];
            format(string, sizeof(string), "{FFFFFF}Промокод "PC_COLOR_1"%s {FFFFFF}был создан.", promo_code_player[playerid][pcp_Name]);
            Dialog_Message(playerid, "Создание промокода", string, "Закрыть");

            #if defined OnPlayerPromoCodeCreate
		        OnPlayerPromoCodeCreate(playerid, promo_code_player[playerid][pcp_Name], promo_code_player[playerid][pcp_RemainingActivationCount], (promo_code_player[playerid][pcp_ExpirationDate] == 0) ? (0):(gettime() + (promo_code_player[playerid][pcp_ExpirationDate] * 86400)), category_names, category_values);
	        #endif
            return 1;
        }
        case 1:
        {
            Dialog_Open(playerid, Dialog:_promo_code_Name, DIALOG_STYLE_INPUT, "Название промокода", "{FFFFFF}Введите название промокода от 3 до "#PC_MAX_NAME_SIZE" символов:", "Дальше", "Назад");
            return 1;
        }
        case 2://Количество активаци
        {
            Dialog_Open(playerid, Dialog:_promo_code_Activation, DIALOG_STYLE_INPUT, "Количество активаци", "{FFFFFF}Введите количество активаций промокода:\nИспользуйте число 0 для бесконечного количества активаций.", "Дальше", "Назад");
            return 1;
        }
        case 3://Срок действия
        {
            Dialog_Open(playerid, Dialog:_promo_code_ExpirationDate, DIALOG_STYLE_INPUT, "Срок действия", "{FFFFFF}Введите срок действия промокода в днях:\nИспользуйте число 0 для бесконечного срока действия.", "Дальше", "Назад");
            return 1;
        }
        case 4: return Dialog_Show(playerid, Dialog:_promo_code_Create);//пропуск
        case 5://Добавить категорию
        {
            Dialog_Show(playerid, Dialog:_promo_code_SelectCategory);
            return 1;
        }
        case 6: return Dialog_Show(playerid, Dialog:_promo_code_Create);//пропуск
        case PC_MAX_DIALOG_LISTITEM_SIZE + 7://кнопка далее
        {
            if(promo_code_player[playerid][pcp_PageBackButton] >= 1 && promo_code_player[playerid][pcp_PageBackButton] == listitem-7 +1 && promo_code_player[playerid][pcp_Page] >= 1)
            {
                promo_code_player[playerid][pcp_Page] --;
                promo_code_player[playerid][pcp_PageBackButton] = 0;
            }
            else promo_code_player[playerid][pcp_Page] ++;

            Dialog_Show(playerid, Dialog:_promo_code_Create);
            return 1;
        }
        case PC_MAX_DIALOG_LISTITEM_SIZE+ 7 + 1://кнопка назад
        {
            if(promo_code_player[playerid][pcp_Page] >= 1)
            {
                promo_code_player[playerid][pcp_Page] --;
                Dialog_Show(playerid, Dialog:_promo_code_Create);
            }
            return 1;
        }
        default:
        {
            if(promo_code_player[playerid][pcp_PageBackButton] >= 1 && promo_code_player[playerid][pcp_PageBackButton] == listitem-7 +1 && promo_code_player[playerid][pcp_Page] >= 1)
            {
                promo_code_player[playerid][pcp_Page] --;
                promo_code_player[playerid][pcp_PageBackButton] = 0;
                Dialog_Show(playerid, Dialog:_promo_code_Create);
                return 1;
            }
            new slot = promo_code_player[playerid][pcp_DialogListitemIDs][listitem-7];
            promo_code_player[playerid][pcp_DialogListitem] = slot;

            new string[112+PC_MAX_CATEGORY_NAME_SIZE];
            format(string, sizeof(string), 
                "{FFFFFF}Введите значение категории "PC_COLOR_1"%s{FFFFFF}:\n\
                Используйте число 0, для удаления данной категории.", 
            promo_code_category[ promo_code_player[playerid][pcp_CategoryID][slot] ][pcc_Name]);
            Dialog_Open(playerid, Dialog:_promo_code_ValueEdit, DIALOG_STYLE_INPUT, "Изменение значения категории", string, "Дальше", "Назад");    
            return 1;
        }
    }
    return 1;
}

DialogResponse:_promo_code_CreateError(playerid, response, listitem, inputtext[])
{
    if(!response) return Dialog_Show(playerid, Dialog:_promo_code_Create);
    return 1;
}

DialogResponse:_promo_code_Name(playerid, response, listitem, inputtext[])
{
    if(!response) return Dialog_Show(playerid, Dialog:_promo_code_Create);
    if(strlen(inputtext) < 3 || strlen(inputtext) >= PC_MAX_NAME_SIZE) return Dialog_Open(playerid, Dialog:_promo_code_Name, DIALOG_STYLE_INPUT, "Название промокода", "{FFFFFF}Введите название промокода от {FF0000}3 до "#PC_MAX_NAME_SIZE" {FFFFFF}символов:", "Дальше", "Назад");

    if(promo_code_player[playerid][pcp_EditPromoCode][0] == true) promo_code_player[playerid][pcp_EditPromoCode][1] = true;
    format(promo_code_player[playerid][pcp_Name], PC_MAX_NAME_SIZE, inputtext);
    Dialog_Show(playerid, Dialog:_promo_code_Create);
    return 1;
}

DialogResponse:_promo_code_Activation(playerid, response, listitem, inputtext[])
{
    if(!response) return Dialog_Show(playerid, Dialog:_promo_code_Create);
    if(strval(inputtext) < 0) return Dialog_Open(playerid, Dialog:_promo_code_Activation, DIALOG_STYLE_INPUT, "Количество активаци", "{FFFFFF}Введите количество активаций промокода:\nИспользуйте число 0 для бесконечного количества активаций.", "Дальше", "Назад");

    if(promo_code_player[playerid][pcp_EditPromoCode][0] == true) promo_code_player[playerid][pcp_EditPromoCode][1] = true;
    promo_code_player[playerid][pcp_RemainingActivationCount] = (strval(inputtext) <= 0) ? (-1):(strval(inputtext));
    Dialog_Show(playerid, Dialog:_promo_code_Create);
    return 1;
}

DialogResponse:_promo_code_ExpirationDate(playerid, response, listitem, inputtext[])
{
    if(!response) return Dialog_Show(playerid, Dialog:_promo_code_Create);
    if(strval(inputtext) < 0) return Dialog_Open(playerid, Dialog:_promo_code_ExpirationDate, DIALOG_STYLE_INPUT, "Срок действия", "{FFFFFF}Введите срок действия промокода в днях:\nИспользуйте число 0 для бесконечного срока действия.", "Дальше", "Назад");

    if(promo_code_player[playerid][pcp_EditPromoCode][0] == true) promo_code_player[playerid][pcp_EditPromoCode][1] = true;
    promo_code_player[playerid][pcp_ExpirationDate] = strval(inputtext);
    Dialog_Show(playerid, Dialog:_promo_code_Create);
    return 1;
}

DialogCreate:_promo_code_SelectCategory(playerid)
{
    new string[ (PC_MAX_CATEGORY_NAME_SIZE+20+9) * PC_MAX_DIALOG_LISTITEM_SIZE ]; 
    new line_max, block_back_button;

    for(new x = (promo_code_player[playerid][pcp_CategoryPage] * PC_MAX_DIALOG_LISTITEM_SIZE); x < PC_MAX_CATEGORY; x ++)
    {
        if(x >= PC_MAX_CATEGORY || promo_code_category[x][pcc_Create] == false) break;
        if(line_max <= PC_MAX_DIALOG_LISTITEM_SIZE-1)
        {
            format(string, sizeof(string), "%s%s\t%s\n", string, promo_code_category[x][pcc_Name], (promo_code_player[playerid][pcp_CategoryUsed][x] == true) ? (""PC_COLOR_1"Используется"):(""));
            if(x >= PC_MAX_CATEGORY -1)
            {
                if(promo_code_player[playerid][pcp_CategoryPage] >= 1) block_back_button = 1;
                break;
            }
        }
        line_max ++;
        if(line_max >= PC_MAX_DIALOG_LISTITEM_SIZE+1)
        {
            block_back_button = 2;
            strcat(string, "> Дальше\n");
            if(promo_code_player[playerid][pcp_CategoryPage] >= 1) strcat(string, "< Назад\n");
            break;
        }
    }
    if(promo_code_player[playerid][pcp_CategoryPage] >= 1 && block_back_button == 0 || block_back_button == 1)
    {
        strcat(string, "< Назад\n");
        promo_code_player[playerid][pcp_CategoryPageBackButton] = line_max + ((block_back_button == 0) ? (1):(2));
    }

    if(line_max == 0) return Dialog_Open(playerid, Dialog:_promo_code_CategoryNo, DIALOG_STYLE_MSGBOX, "Добавить категорию", "{FFFFFF}Нет созданных категорий.", "Закрыть", "Назад");
    Dialog_Open(playerid, Dialog:_promo_code_SelectCategory, DIALOG_STYLE_TABLIST, "Добавить категорию", string, "Выбрать", "Назад");
    return 1;
}

DialogResponse:_promo_code_CategoryNo(playerid, response, listitem, inputtext[])
{
    if(response) return 1;
    Dialog_Show(playerid, Dialog:_promo_code_Create);
    return 1;
}

DialogResponse:_promo_code_SelectCategory(playerid, response, listitem, inputtext[])
{
    if(!response) return Dialog_Show(playerid, Dialog:_promo_code_Create);

    switch(listitem)
    {
        case PC_MAX_DIALOG_LISTITEM_SIZE:
        {
            if(promo_code_player[playerid][pcp_CategoryPageBackButton] >= 1 && promo_code_player[playerid][pcp_CategoryPageBackButton] == listitem+1 && promo_code_player[playerid][pcp_CategoryPage] >= 1)
            {
                promo_code_player[playerid][pcp_CategoryPage] --;
                promo_code_player[playerid][pcp_CategoryPageBackButton] = 0;
            }
            else promo_code_player[playerid][pcp_CategoryPage] ++;
            
            Dialog_Show(playerid, Dialog:_promo_code_SelectCategory);
            return 1;
        }
        case PC_MAX_DIALOG_LISTITEM_SIZE+1:
        {
            if(promo_code_player[playerid][pcp_CategoryPage] >= 1)
            {
                promo_code_player[playerid][pcp_CategoryPage] --;
                Dialog_Show(playerid, Dialog:_promo_code_SelectCategory);
            }
            return 1;
        }
        default:
        {
            if(promo_code_player[playerid][pcp_CategoryPageBackButton] >= 1 && promo_code_player[playerid][pcp_CategoryPageBackButton] == listitem+1 && promo_code_player[playerid][pcp_CategoryPage] >= 1)
            {
                promo_code_player[playerid][pcp_CategoryPage] --;
                promo_code_player[playerid][pcp_CategoryPageBackButton] = 0;
                Dialog_Show(playerid, Dialog:_promo_code_SelectCategory);
                return 1;
            }
            new slot = (promo_code_player[playerid][pcp_CategoryPage] * PC_MAX_DIALOG_LISTITEM_SIZE) + listitem;
            promo_code_player[playerid][pcp_DialogListitem] = slot;
            
            new string[54+PC_MAX_CATEGORY_NAME_SIZE];
            format(string, sizeof(string), "{FFFFFF}Введите значение категории "PC_COLOR_1"%s{FFFFFF}:", promo_code_category[slot][pcc_Name]);
            Dialog_Open(playerid, Dialog:_promo_code_Value, DIALOG_STYLE_INPUT, "Добавить категорию", string, "Дальше", "Назад");
            return 1;
        }
    }
    return 1;
}

stock _PromoCodeCategoryUpdate(playerid)
{
    new slot[PC_MAX_CATEGORY_IN_PROMO_CODE][2], max_category;

    for(new x; x < PC_MAX_CATEGORY_IN_PROMO_CODE; x ++)
    {
        if(promo_code_player[playerid][pcp_CategoryID][x] == -1) continue;
        slot[max_category][0] = promo_code_player[playerid][pcp_CategoryID][x];
        slot[max_category][1] = promo_code_player[playerid][pcp_CategoryValues][x];

        promo_code_player[playerid][pcp_CategoryID][x] = -1;
        promo_code_player[playerid][pcp_CategoryValues][x] = 0;
        max_category++;
    }

    for(new x; x < max_category; x ++)
    {
        promo_code_player[playerid][pcp_CategoryID][x] = slot[x][0];
        promo_code_player[playerid][pcp_CategoryValues][x] = slot[x][1];
    }
    return 1;
}

DialogResponse:_promo_code_Value(playerid, response, listitem, inputtext[])
{
    if(!response) return Dialog_Show(playerid, Dialog:_promo_code_SelectCategory);

    new categoryID = promo_code_player[playerid][pcp_DialogListitem];
    new newSlot = -1;
    for(new x; x < PC_MAX_CATEGORY_IN_PROMO_CODE; x ++)
    {
        if(promo_code_player[playerid][pcp_CategoryID][x] == -1) 
        {
            if(newSlot == -1) newSlot = x;//поиск пустого слота
            continue;
        }
        if(promo_code_player[playerid][pcp_CategoryID][x] == categoryID) //если категория уже была добавлена 
        {
            newSlot = x;
            break;
        }
    }
    if(newSlot != -1)
    {
        if(promo_code_player[playerid][pcp_EditPromoCode][0] == true) promo_code_player[playerid][pcp_EditPromoCode][1] = true;
        promo_code_player[playerid][pcp_CategoryID][newSlot] = categoryID;
        promo_code_player[playerid][pcp_CategoryValues][newSlot] = strval(inputtext);
        promo_code_player[playerid][pcp_CategoryUsed][categoryID] = true;
    }
    else 
    {
        Dialog_Open(playerid, Dialog:_promo_code_CategoryNo, DIALOG_STYLE_MSGBOX, "Добавить категорию", "{FFFFFF}Достигнут лимит по количеству добавления категорий.", "Закрыть", "Назад");
        return 1;
    }

    Dialog_Show(playerid, Dialog:_promo_code_Create);
    return 1;
}

DialogResponse:_promo_code_ValueEdit(playerid, response, listitem, inputtext[])
{
    if(!response) return Dialog_Show(playerid, Dialog:_promo_code_Create);
    new slot = promo_code_player[playerid][pcp_DialogListitem];
    
    if(strval(inputtext) <= 0)
    { 
        promo_code_player[playerid][pcp_CategoryUsed][ promo_code_player[playerid][pcp_CategoryID][slot] ] = false;

        promo_code_player[playerid][pcp_CategoryID][slot] = -1;
        promo_code_player[playerid][pcp_CategoryValues][slot] = 0;
        _PromoCodeCategoryUpdate(playerid);
        
        if(promo_code_player[playerid][pcp_Page] >= 1 && promo_code_player[playerid][pcp_DialogListitemIDs][0] != -1 && promo_code_player[playerid][pcp_DialogListitemIDs][1] == -1) promo_code_player[playerid][pcp_Page] --;
    }
    else promo_code_player[playerid][pcp_CategoryValues][slot] = strval(inputtext);
    if(promo_code_player[playerid][pcp_EditPromoCode][0] == true) promo_code_player[playerid][pcp_EditPromoCode][1] = true;

    Dialog_Show(playerid, Dialog:_promo_code_Create);
    return 1;
}


// -----------------


stock PromoCodeList(playerid)
{
    promo_code_player[playerid][pcp_ListPage] = 0;
    promo_code_player[playerid][pcp_ListBackButton] = 0;
    promo_code_player[playerid][pcp_EditPromoCode][0] = true;
    promo_code_player[playerid][pcp_EditPromoCode][1] = false;

    Dialog_Show(playerid, Dialog:_promo_code_List);
    return 1;
}

DialogCreate:_promo_code_List(playerid)
{
    new string[ ((PC_MAX_NAME_SIZE+19+19+21) * PC_MAX_DIALOG_LISTITEM_SIZE) + 75 ] = "{FFFFFF}Номер\t{FFFFFF}Название\t{FFFFFF}Кол-во активаций\t{FFFFFF}Статус\n", activation[11+10];
    for(new x; x < PC_MAX_DIALOG_LISTITEM_SIZE; x ++) promo_code_player[playerid][pcp_ListDialogListitemIDs][x] = -1;

    new line_max, block_back_button;
    for(new x = (promo_code_player[playerid][pcp_ListPage] * PC_MAX_DIALOG_LISTITEM_SIZE)+1; x < PC_MAX_PROMO_CODE; x ++)
    {
        if(x >= PC_MAX_PROMO_CODE) break;
        if(promo_code[x][pc_Create] == false) continue;
        if(line_max <= PC_MAX_DIALOG_LISTITEM_SIZE-1)
        {
            promo_code_player[playerid][pcp_ListDialogListitemIDs][line_max] = x;
            if(promo_code[x][pc_RemainingActivationCount] != -1) format(activation, sizeof(activation), "Осталось %d", promo_code[x][pc_RemainingActivationCount]);
            else format(activation, sizeof(activation), "%d активаций", promo_code[x][pc_ActivationCount]);

            format(string, sizeof(string), "%s#%d\t%s\t%s\t%s\n", 
                string, 
                line_max+1+(promo_code_player[playerid][pcp_ListPage] * PC_MAX_DIALOG_LISTITEM_SIZE), 
                promo_code[x][pc_Name], 
                activation,
                (promo_code[x][pc_ExpirationDate] != 0 && promo_code[x][pc_ExpirationDate] <= gettime()) ? (""PC_COLOR_3"Истек") : (promo_code[x][pc_RemainingActivationCount] == 0) ? (""PC_COLOR_3"Закончился"):(""PC_COLOR_2"Активный")
            );

            if(x >= PC_MAX_PROMO_CODE -1)
            {
                if(promo_code_player[playerid][pcp_ListPage] >= 1) block_back_button = 1;
                break;
            }
        }
        line_max ++;
        if(line_max >= PC_MAX_DIALOG_LISTITEM_SIZE+1)
        {
            block_back_button = 2;
            strcat(string, "> Дальше\n");
            if(promo_code_player[playerid][pcp_ListPage] >= 1) strcat(string, "< Назад\n");
            break;
        }
    }
    if(promo_code_player[playerid][pcp_ListPage] >= 1 && block_back_button == 0 || block_back_button == 1)
    {
        strcat(string, "< Назад\n");
        promo_code_player[playerid][pcp_ListBackButton] = line_max + ((block_back_button == 0) ? (1):(2));
    }
    if(line_max == 0) return Dialog_Message(playerid, "Список созданных промокодов", "{FFFFFF}Нет созданных промокодов.", "Закрыть");
    Dialog_Open(playerid, Dialog:_promo_code_List, DIALOG_STYLE_TABLIST_HEADERS, "Список созданных промокодов", string, "Выбрать", "Отмена");
    return 1;
}

DialogResponse:_promo_code_List(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;
    switch(listitem)
    {
        case PC_MAX_DIALOG_LISTITEM_SIZE:
        {
            if(promo_code_player[playerid][pcp_ListBackButton] >= 1 && promo_code_player[playerid][pcp_ListBackButton] == listitem+1 && promo_code_player[playerid][pcp_ListPage] >= 1)
            {
                promo_code_player[playerid][pcp_ListPage] --;
                promo_code_player[playerid][pcp_ListBackButton] = 0;
            }
            else promo_code_player[playerid][pcp_ListPage] ++;

            Dialog_Show(playerid, Dialog:_promo_code_List);
            return 1;
        }
        case PC_MAX_DIALOG_LISTITEM_SIZE+1:
        {
            if(promo_code_player[playerid][pcp_ListPage] >= 1)
            {
                promo_code_player[playerid][pcp_ListPage] --;
                Dialog_Show(playerid, Dialog:_promo_code_List);
            }
            return 1;
        }
        default:
        {
            if(promo_code_player[playerid][pcp_ListBackButton] >= 1 && promo_code_player[playerid][pcp_ListBackButton] == listitem+1 && promo_code_player[playerid][pcp_ListPage] >= 1)
            {
                promo_code_player[playerid][pcp_ListPage] --;
                promo_code_player[playerid][pcp_ListBackButton] = 0;
                Dialog_Show(playerid, Dialog:_promo_code_List);
                return 1;
            }
            new promo_code_id = promo_code_player[playerid][pcp_ListDialogListitemIDs][listitem];
            promo_code_player[playerid][pcp_ListSlotID] = promo_code_id;

            format(promo_code_player[playerid][pcp_Name], PC_MAX_NAME_SIZE, promo_code[promo_code_id][pc_Name]);
            promo_code_player[playerid][pcp_RemainingActivationCount] = promo_code[promo_code_id][pc_RemainingActivationCount];
            promo_code_player[playerid][pcp_ExpirationDate] = promo_code[promo_code_id][pc_ExpirationDate];

            promo_code_player[playerid][pcp_Page] = 0;
            promo_code_player[playerid][pcp_PageBackButton] = 0;

            promo_code_player[playerid][pcp_CategoryPage] = 0;
            promo_code_player[playerid][pcp_CategoryPageBackButton] = 0;

            for(new x; x < PC_MAX_CATEGORY; x ++)
            {
                if(x < PC_MAX_CATEGORY_IN_PROMO_CODE)
                {
                    promo_code_player[playerid][pcp_CategoryID][x] = -1;
                    promo_code_player[playerid][pcp_CategoryValues][x] = 0;
                }
                promo_code_player[playerid][pcp_CategoryUsed][x] = false;
            }
            promo_code_player[playerid][pcp_EditPromoCode][1] = false;

            new max_category;
            for(new x; x < PC_MAX_CATEGORY; x ++)//поиск ID категории
            {
                if(promo_code_category[x][pcc_Create] == false) break;

                for(new str_x; str_x < PC_MAX_CATEGORY_IN_PROMO_CODE; str_x ++)
                {
                    if(strlen(promo_code_category_names[promo_code_id][str_x]) <= 0) continue;
                    if(strcmp(promo_code_category_names[promo_code_id][str_x], promo_code_category[x][pcc_Name], false)) continue;
  
                    promo_code_player[playerid][pcp_CategoryID][max_category] = x;
                    promo_code_player[playerid][pcp_CategoryValues][max_category] = promo_code[promo_code_id][pc_Category_Value][str_x];
                    promo_code_player[playerid][pcp_CategoryUsed][x] = true;

                    max_category++;
                    break;
                }
            }

            Dialog_Show(playerid, Dialog:_promo_code_Create);
            return 1;
        }
    }
    return 1;
}

DialogResponse:_promo_code_Delete(playerid, response, listitem, inputtext[])
{
    if(!response) return Dialog_Show(playerid, Dialog:_promo_code_Create);
    PromoCodeDelete(playerid, promo_code_player[playerid][pcp_Name]);

    if(promo_code_player[playerid][pcp_ListPage] >= 1 && promo_code_player[playerid][pcp_ListDialogListitemIDs][0] != -1 && promo_code_player[playerid][pcp_ListDialogListitemIDs][1] == -1) promo_code_player[playerid][pcp_ListPage] --;
    Dialog_Show(playerid, Dialog:_promo_code_List);
    return 1;
}

DialogResponse:_promo_code_Savechanges(playerid, response, listitem, inputtext[])
{
    if(response && promo_code_player[playerid][pcp_EditPromoCode][1] == true)
    {
        new category_names [(PC_MAX_CATEGORY_NAME_SIZE+1) * PC_MAX_CATEGORY_IN_PROMO_CODE],
            category_values[11 * PC_MAX_CATEGORY_IN_PROMO_CODE],
            max_category,
            promo_code_id = promo_code_player[playerid][pcp_ListSlotID],
            old_name[PC_MAX_NAME_SIZE];

        for(new x; x < PC_MAX_CATEGORY_IN_PROMO_CODE; x ++)
        {
            if(promo_code_player[playerid][pcp_CategoryID][x] == -1) continue;

            format(category_names, sizeof(category_names), "%s%s,", category_names, promo_code_category[ promo_code_player[playerid][pcp_CategoryID][x] ][pcc_Name]);
            format(category_values, sizeof(category_values), "%s%d,", category_values, promo_code_player[playerid][pcp_CategoryValues][x]);
            max_category ++;
        }
        if(max_category == 0)
        {
            Dialog_Open(playerid, Dialog:_promo_code_CreateError, DIALOG_STYLE_MSGBOX, "Принятие изменений", 
                "{FFFFFF}Промокод не может быть сохранен без категорий.", 
            "Закрыть", "Назад");
            return 1;
        }

        format(old_name, PC_MAX_NAME_SIZE, promo_code[promo_code_id][pc_Name]);
        format(promo_code[promo_code_id][pc_Name], PC_MAX_NAME_SIZE, promo_code_player[playerid][pcp_Name]);
        
        promo_code[promo_code_id][pc_RemainingActivationCount] = promo_code_player[playerid][pcp_RemainingActivationCount];
        if(promo_code[promo_code_id][pc_ExpirationDate] != promo_code_player[playerid][pcp_ExpirationDate]) 
        {
            if(promo_code_player[playerid][pcp_ExpirationDate] != 0) promo_code[promo_code_id][pc_ExpirationDate] = gettime() + (promo_code_player[playerid][pcp_ExpirationDate] * 86400);
            else promo_code[promo_code_id][pc_ExpirationDate] = 0;
        }

        max_category = 0;
        for(new x; x < PC_MAX_CATEGORY_IN_PROMO_CODE; x ++)
        {
            format(promo_code_category_names[promo_code_id][x], PC_MAX_CATEGORY_NAME_SIZE, " ");
            promo_code[promo_code_id][pc_Category_Value][x] = 0;
            if(promo_code_player[playerid][pcp_CategoryID][x] == -1) continue;

            format(promo_code_category_names[promo_code_id][max_category], PC_MAX_CATEGORY_NAME_SIZE, promo_code_category[ promo_code_player[playerid][pcp_CategoryID][x] ][pcc_Name]);
            promo_code[promo_code_id][pc_Category_Value][max_category] = promo_code_player[playerid][pcp_CategoryValues][x];
            max_category++;
        }

        #if defined OnPlayerPromoCodeEdit
            OnPlayerPromoCodeEdit(playerid, old_name, promo_code[promo_code_id][pc_Name], promo_code[promo_code_id][pc_RemainingActivationCount], promo_code[promo_code_id][pc_ExpirationDate], category_names, category_values);
        #endif
    }

    promo_code_player[playerid][pcp_EditPromoCode][1] = false;
    Dialog_Show(playerid, Dialog:_promo_code_List);
    return 1;
}