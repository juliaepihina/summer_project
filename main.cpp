#include <iostream>
#include <vector>

struct node
{
    char c;
    int v;
};

std::vector<int> nums_used(10);

bool check(node* node_array, const int count, std::string first, std::string second, std::string result)
{
    int first_num = 0, second_num = 0, result_num = 0;
    int m = 1, j, i;

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

    for (i = result.length() - 1; i >= 0; i--)
    {
        char ch = result[i];
        for (j = 0; j < count; j++)
            if (node_array[j].c == ch)
                break;

        result_num += m * node_array[j].v;
        m *= 10;
    }

    if (result_num == (first_num + second_num))
        return true;

    return false;
}

bool permutation(const int count, node* node_array, int n, std::string first, std::string second, std::string result)
{
    if (n == count - 1)
    {
        for (int i = 0; i < 10; i++)
        {
            if (nums_used[i] == 0)
            {
                node_array[n].v = i;
                if (check(node_array, count, first, second, result) == 1)
                {
                    for (int j = 0; j < count; j++)
                        std::cout << " " << node_array[j].c << " = "
                        << node_array[j].v << std::endl;
                    return true;
                }
            }
        }
        return false;
    }

    for (int i = 0; i < 10; i++)
    {
        if (nums_used[i] == 0)
        {
            node_array[n].v = i;
            nums_used[i] = 1;

            if (permutation(count, node_array, n + 1, first, second, result))
                return true;

            nums_used[i] = 0;
        }
    }
    return false;
}

bool solve(std::string first, std::string second, std::string result)
{
    int count = 0;

    int l1 = first.length();
    int l2 = second.length();
    int l3 = result.length();

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

    if (count > 10)
        return 0;

    node* node_array = new node[count];

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
    std::string first, second, result;
    std::cout << "Input first";
    std::cin >> first;
    std::cout << "Input second";
    std::cin >> second;
    std::cout << "Input result";
    std::cin >> result;

    if (solve(first, second, result) == false)
        std::cout << "No solution";

    return 0;
}

//Тестовые примеры: [DONALD,GERALD,ROBERT], [MASHA, DASHA, KATYA].  