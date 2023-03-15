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
1
```

## Functions


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
