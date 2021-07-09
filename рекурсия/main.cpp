#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>

//структура node для хранения буквы и соответствующего ей целого числа
struct node
{
    char c;
    int v;
};

std::vector<int> nums_used(10);
std::vector<node*> nodes_used;

std::ofstream out("output.txt");

//проверка, являются ли одинаковыми решения
bool same_nodes(node* nd1, node* nd2, int count)
{
    for (int i = 0; i < count; i++)
        if (nd1[i].c != nd2[i].c || nd1[i].v != nd2[i].v)
            return false;
    return true;
}

//проверка, использовалось ли уже решение
bool is_used(node* nd, int count)
{
    for (auto i : nodes_used)
        if (same_nodes(i, nd, count))
            return true;
    return false;
}

//проверка на правильность решения
bool check(node* node_array, const int count, std::string first, std::string second, std::string result)
{
    int first_num = 0, second_num = 0, result_num = 0;
    int m = 1, j, i;

    //вычисление числа, которое соответствует первому слову
    for (i = first.length() - 1; i >= 0; i--)
    {
        char ch = first[i];
        for (j = 0; j < count; j++)
            if (node_array[j].c == ch)
                break;

        first_num += m * node_array[j].v;
        m *= 10;
    }
    m = 1;


    //вычисление числа, которое соответствует второму слову
    for (i = second.length() - 1; i >= 0; i--)
    {
        char ch = second[i];
        for (j = 0; j < count; j++)
            if (node_array[j].c == ch)
                break;

        second_num += m * node_array[j].v;
        m *= 10;
    }
    m = 1;

    //вычисление числа, которое соответствует третьему слову
    for (i = result.length() - 1; i >= 0; i--)
    {
        char ch = result[i];
        for (j = 0; j < count; j++)
            if (node_array[j].c == ch)
                break;

        result_num += m * node_array[j].v;
        m *= 10;
    }

    //проверка суммы
    if (result_num == (first_num + second_num))
        return true;

    return false;
}


//рекурсивная функция, которая проверяет решение для всех перестановок
bool permutation(const int count, node* node_array, int n, std::string first, std::string second, std::string result)
{
    if (n == count - 1)
    {
        //проверка для всех цифр, которые еще не использованы
        for (int i = 0; i < 10; i++)
        {
            //если еще не использованы
            if (nums_used[i] == 0)
            {
                //букве по индексу присваиваем целое число i
                node_array[n].v = i;
                //если нашли решение
                if (check(node_array, count, first, second, result) == 1)
                {
                    for (int j = 0; j < count; j++) {
                        out << " " << node_array[j].c << " = "
                            << node_array[j].v << std::endl;
                        std::cout << " " << node_array[j].c << " = "
                            << node_array[j].v << std::endl;
                    }
                    nodes_used.push_back(node_array);
                    out << std::endl;
                    return true;
                }
            }
        }
        return false;
    }

    for (int i = 0; i < 10; i++)
    {
        //если число еще не использовано
        if (nums_used[i] == 0)
        {
            //букве по индексу присваиваем целое число i
            node_array[n].v = i;
            //делаем его недоступным для других букв
            nums_used[i] = 1;

            //вызов рекурсивной функции
            if (permutation(count, node_array, n + 1, first, second, result) && !is_used(node_array, count))
                return true;

            //возврат ко всем другим возможным решениям
            nums_used[i] = 0;
        }
    }
    return false;
}

bool solve(std::string first, std::string second, std::string result)
{
    //переменная для подсчитывания количества уникальных символов
    int count = 0;

    int l1 = first.length();
    int l2 = second.length();
    int l3 = result.length();

    //вектор будет хранить частоту каждой буквы
    std::vector<int> freq(26);

    for (int i = 0; i < l1; i++)
        freq[first[i] - 'A']++;

    for (int i = 0; i < l2; i++)
        freq[second[i] - 'A']++;

    for (int i = 0; i < l3; i++)
        freq[result[i] - 'A']++;

    for (int i = 0; i < 26; i++)
        if (freq[i] > 0)
            count++;

    //если уникальных символов больше 10, то решения нет
    if (count > 10)
        return 0;

    node* node_array = new node[count];

    //все уникальные символы сохраняются в node_array
    for (int i = 0, j = 0; i < 26; i++)
    {
        if (freq[i] > 0)
        {
            node_array[j].c = char(i + 'A');
            j++;
        }
    }
    return permutation(count, node_array, 0, first, second, result);
}

int main()
{
    srand(time(0));
    std::string first;
    std::string second;
    std::string result;
    std::ifstream f("test2.txt");
    f >> first;
    f >> second;
    f >> result;
    f.close();
    while (solve(first, second, result))
        ;
    if (nodes_used.empty()) {
        std::cout << "No solution";
    }
    std::cout << "runtime = " << clock() / 1000.0 << std::endl;    
    out << "runtime = " << clock() / 1000.0 << std::endl;
    out.close();
    return 0;
}