# Представление данных

Поговорим о том, как данные хранятся в памяти.

## Целые числа

Минимально адресуемой единицей является байт. Сколько бит в байте? 

Ответ содержится в константе `CHAR_BIT` из `limits.h`. По стандарту гарантируется, что хотя бы 8. Однобайтовый тип данных называется `char`.

Типы, которыми вы привыкли пользоваться, такие как `int` плохи тем, что на разных системах занимают разное число байт (на 32-битных обычно 4, на 64-битных 8).

Чтобы избежать всей этой путаницы, далее рекомендуется использовать типы с фиксированным числом бит: `int8_t`, `uint16_t` и так далее. Они определены в `stdint.h`.

Давайте с помощью небольшой демки (`print_int.c`) посмотрим на то, как эти числа хранятся в памяти.

Возьмём 8-битное беззнаковое число, как самый простой пример. В нём биты просто задают двоичное представление числа, начиная со старших разрядов.

На примере 8-битных знаковых мы видим, что первый бит отвечает за знак (0 для положительных, 1 для отрицательных). Далее для положительного числа представление не отличается. Для отрицательного оно получается из соображения, что `(-x)+x=0`. На самом деле происходит переполнение и старший бит отбрасывается. Для чисел с большей разрядностью просто добавляются старшие байты в начало. `x86` поэтому называется `Little-endian` архитектурой. При передаче по сети наоборот принято передавать старшие байты в начале, можно привести число к такому виду с помощью функции `htons` и убедиться, что порядок изменился.

## UBSAN

Переполнение знакового типа является неопределённым поведением по стандарту. Чтобы это отлавливать, можно использовать флаг ``-fsanitize=undefined`` при компиляции (см. ``overflow.c``).

## Вещественные числа

Два основных типа вещественных с плавающей точкой, которые определены стандартом языка Си, - это `float` (используется 4 байта для хранения) и `double` (используется 8 байт).

Для простоты далее будет рассматриать `float` (см. ``print_float.c``). Видимо, что старший бит вновь признак отрецательности числа. Следующие 8 бит называются экспонентой, а оставшиеся 23 - мантиссой.

Значение его может быть получено как:

```
Value = (-1)^S * 2^(E-B) * ( 1 + M / (2^(M_bits-1)) )
```
где `S` - бит знака, `E` - значение смещенной экспоненты, `B` - смещение (127 или 1023), а `M` - значение мантиссы, `M_bits` - количество бит в экспоненте.

Можно разбирать число с помощью ``union`` (см. ``print_union.c``).

> Красивый визуализатор: https://www.h-schmidt.net/FloatConverter/IEEE754.html

## Текстовые кодировки

![ASCII](ascii.png)

В середине 20 века возникла потребность как-то кодировать текст двоичными данными. Тогда решили, что 7 бит достаточно на цифры и латинский алфавит, так и появилась кодировка ASCII.

Позже один лишний бит позволил хранить в диапазоне от 128 до 255 символы национальных кодировок. В России, например, в 90-е была распространена `KOI8-R`.

Иметь отдельную кодировку под каждый язык всё ещё было не очень удобно, поэтому появилась `UTF-8`. Чтобы не занимать гарантированно 4 октета (будем называть так группы ), был придуман интересный дизайн. 

``echo 'C' | hexdump -C`` (`0a` отвечает за перевод строки, по сути есть один значащий байт `43` и код совпадает с ASCII)

То есть для самых частотных текстов, которые написаны латиницей, она занимает столько же место, сколько ASCII.

``echo 'Я' | hexdump -C`` (Байты `d0` `af` отвечают за `Я`)

Для большинства языков хватает двух байт.

``echo '😊' | hexdump -C`` 

4 байта нужно для каких-то специфических символов.

В общем случае кодирование подчиняется следующим шаблонам.

| Количество октетов | Шаблон |
|---|---|
|1|0xxxxxxx|
|2|110xxxxx 10xxxxxx|
|3|1110xxxx 10xxxxxx 10xxxxxx|
|4|11110xxx 10xxxxxx 10xxxxxx 10xxxxxx|
