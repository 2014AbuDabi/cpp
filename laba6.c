#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Определение структуры для хранения данных о письме
struct Letter {
    char *adr1;    // Указатель на строку с адресом получателя
    char *fam1;    // Указатель на строку с фамилией получателя
    char *name1;   // Указатель на строку с именем получателя
    char *adr2;    // Указатель на строку с адресом отправителя
    char *fam2;    // Указатель на строку с фамилией отправителя
    char *name2;   // Указатель на строку с именем отправителя
    double cost;   // Стоимость письма
};

// Функция для добавления нового письма в базу данных
// Принимает указатель на базу данных (массив структур) и количество писем в базе
// Возвращает обновленное количество писем в базе
int add_letter(struct Letter **letters, int count) {
    // Выделяем память под новую структуру письма, увеличивая размер массива
    *letters = (struct Letter *)realloc(*letters, (count + 1) * sizeof(struct Letter));
    // Получаем указатель на новую структуру письма
    struct Letter *new_letter = &(*letters)[count];

    // Ввод данных о письме с клавиатуры
    char buffer[1024]; // Буфер для временного хранения вводимых строк
    printf("Введите адрес получателя: "); // Вывод сообщения для пользователя
    fgets(buffer, sizeof(buffer), stdin); // Чтение строки с клавиатуры в буфер
    buffer[strcspn(buffer, "\n")] = 0; // Удаляем символ новой строки из буфера
    new_letter->adr1 = strdup(buffer); // Копируем строку из буфера в динамическую память и сохраняем указатель

    printf("Введите фамилию получателя: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    new_letter->fam1 = strdup(buffer);

    printf("Введите имя получателя: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    new_letter->name1 = strdup(buffer);

    printf("Введите адрес отправителя: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    new_letter->adr2 = strdup(buffer);

    printf("Введите фамилию отправителя: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    new_letter->fam2 = strdup(buffer);

    printf("Введите имя отправителя: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    new_letter->name2 = strdup(buffer);

    printf("Введите стоимость письма: ");
    scanf("%lf", &new_letter->cost); // Чтение вещественного числа с клавиатуры
    getchar(); // Очищаем буфер ввода от символа новой строки

    return count + 1; // Возвращаем обновленное количество писем
}

// Функция для печати информации о письме в виде строки таблицы
// Принимает указатель на структуру письма
void print_letter_row(struct Letter *letter) {
    printf("| %-18s   %-28s  %-26s  %-18s  %-28s  %-26s  %-9.2lf \n", 
           letter->adr1, letter->fam1, letter->name1, letter->adr2, letter->fam2, letter->name2, letter->cost);
}
// Функция для печати разделителя таблицы
void print_table_separator() {
    printf("+--------------------+----------------------+----------------------+--------------------+----------------------+----------------------+-----------+\n");
}
// Функция для печати заголовка таблицы
void print_table_header() {
    print_table_separator();
    printf("| Адрес получателя   | Фамилия получателя   | Имя получателя       | Адрес отправителя  | Фамилия отправителя  | Имя отправителя      | Стоимость |\n");
    print_table_separator();
}
// Функция для печати всей базы данных писем в виде таблицы
// Принимает указатель на базу данных (массив структур) и количество писем в базе
void print_letters_table(struct Letter *letters, int count) {
    if (count == 0) { // Проверка на пустую базу данных
        printf("База данных пуста.\n");
        return;
    }

    print_table_header();
    for (int i = 0; i < count; i++) { // Цикл по всем письмам в базе
        print_letter_row(&letters[i]); // Вывод информации о текущем письме
        print_table_separator();
    }
}

// Функция для поиска письма по фамилии и имени отправителя
// Принимает указатель на базу данных, количество писем, фамилию и имя для поиска
// Выводит на экран найденные письма
void find_by_sender(struct Letter *letters, int count, char *fam2, char *name2) {
    int found = 0; // Флаг, указывающий, было ли найдено хотя бы одно письмо
    print_table_header();
    for (int i = 0; i < count; i++) { // Цикл по всем письмам в базе
        // Сравнение фамилии и имени отправителя с заданными значениями
        if (strcmp(letters[i].fam2, fam2) == 0 && strcmp(letters[i].name2, name2) == 0) {
            print_letter_row(&letters[i]); // Вывод информации о найденном письме
            found = 1; // Установка флага, что письмо найдено
            print_table_separator();
        }
    }
    if (!found) { // Если ни одного письма не найдено
        printf("Письма от %s %s не найдены.\n", fam2, name2); // Вывод сообщения об отсутствии писем
    }
}

// Функция для поиска писем со стоимостью выше заданной
// Принимает указатель на базу данных, количество писем и минимальную стоимость
// Выводит на экран найденные письма
void find_by_cost(struct Letter *letters, int count, double min_cost) {
    int found = 0; // Флаг, указывающий, было ли найдено хотя бы одно письмо
    print_table_header();
    for (int i = 0; i < count; i++) { // Цикл по всем письмам в базе
        if (letters[i].cost > min_cost) { // Сравнение стоимости письма с заданным значением
            print_letter_row(&letters[i]); // Вывод информации о найденном письме
            found = 1; // Установка флага, что письмо найдено
            print_table_separator();
        }
    }
    if (!found) { // Если ни одного письма не найдено
        printf("Письма дороже %.2lf не найдены.\n", min_cost); // Вывод сообщения об отсутствии писем
    }
}

// Функция для сравнения двух писем по стоимости (для qsort)
int compare_letters_by_cost(const void *a, const void *b) {
    double cost_a = ((struct Letter *)a)->cost; // Получение стоимости первого письма
    double cost_b = ((struct Letter *)b)->cost; // Получение стоимости второго письма
    return (cost_b - cost_a); // Возвращаем разницу стоимостей для сортировки по убыванию
}
 
// Функция для сортировки базы данных по убыванию стоимости
// Принимает указатель на базу данных и количество писем
void sort_by_cost(struct Letter *letters, int count) {
    qsort(letters, count, sizeof(struct Letter), compare_letters_by_cost); // Сортировка массива структур
    printf("База данных отсортирована по убыванию стоимости.\n"); // Вывод сообщения о завершении сортировки
}

int main() {
    struct Letter *letters = NULL; // Указатель на базу данных писем (изначально NULL)
    int count = 0; // Количество писем в базе (изначально 0)
    int choice; // Переменная для хранения выбора пользователя

    // Цикл меню
    while (1) { // Бесконечный цикл, пока пользователь не выберет выход
        printf("Меню:\n"); // Вывод меню на экран
        printf("1. Добавить письмо\n");
        printf("2. Распечатать базу данных\n");
        printf("3. Поиск по отправителю\n");
        printf("4. Поиск по стоимости\n");
        printf("5. Сортировать по стоимости\n");
        printf("6. Выход\n");
        printf("Выберите действие: ");
        scanf("%d", &choice); // Чтение выбора пользователя с клавиатуры
        getchar(); // Очищаем буфер ввода от символа новой строки

        switch (choice) { // Ветвление в зависимости от выбора пользователя
            case 1: // Добавление письма
                count = add_letter(&letters, count); // Вызов функции добавления письма
                break; // Выход из switch
            case 2: // Печать базы данных
                print_letters_table(letters, count); // Вызов функции печати базы данных
                break; // Выход из switch
            case 3: { // Поиск по отправителю
                char fam2[1024], name2[1024]; // Буферы для хранения фамилии и имени отправителя
                printf("Введите фамилию отправителя: ");
                fgets(fam2, sizeof(fam2), stdin); // Чтение фамилии отправителя с клавиатуры
                fam2[strcspn(fam2, "\n")] = 0; // Удаление символа новой строки из буфера
                printf("Введите имя отправителя: ");
                fgets(name2, sizeof(name2), stdin); // Чтение имени отправителя с клавиатуры
                name2[strcspn(name2, "\n")] = 0; // Удаление символа новой строки из буфера
                find_by_sender(letters, count, fam2, name2); // Вызов функции поиска по отправителю
                break; // Выход из switch
            }
            case 4: { // Поиск по стоимости
                double min_cost; // Переменная для хранения минимальной стоимости
                printf("Введите минимальную стоимость: ");
                scanf("%lf", &min_cost); // Чтение минимальной стоимости с клавиатуры
                getchar(); // Очищаем буфер ввода от символа новой строки
                find_by_cost(letters, count, min_cost); // Вызов функции поиска по стоимости
                break; // Выход из switch
            }
            case 5: // Сортировка по стоимости
                sort_by_cost(letters, count); // Вызов функции сортировки по стоимости
                break; // Выход из switch
            case 6: // Выход из программы
                // Освобождаем память перед выходом
                for (int i = 0; i < count; i++) { // Цикл по всем письмам в базе
                    free(letters[i].adr1); // Освобождение памяти, выделенной под адрес получателя
                    free(letters[i].fam1); // Освобождение памяти, выделенной под фамилию получателя
                    free(letters[i].name1); // Освобождение памяти, выделенной под имя получателя
                    free(letters[i].adr2); // Освобождение памяти, выделенной под адрес отправителя
                    free(letters[i].fam2); // Освобождение памяти, выделенной под фамилию отправителя
                    free(letters[i].name2); // Освобождение памяти, выделенной под имя отправителя
                }
                free(letters); // Освобождение памяти, выделенной под массив структур
                return 0; // Завершение программы
            default: // Неверный выбор
                printf("Неверный выбор.\n"); // Вывод сообщения об ошибке
        }
    }
}