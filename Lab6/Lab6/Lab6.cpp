#include <iostream>
#include <vector>
#include <string>
#include <math.h>

//допускаемые дробные значения  1/2    1/3     1/4   1/5    1/6     1/7      1/8    1/9    
const std::vector<float> values{0.5f, 0.333f, 0.25f, 0.2f, 0.167f, 0.143f, 0.125f, 0.111f};

//вывовдит ошибку
void invalidInput()
{		
	std::cout << "Некорректный ввод." << std::endl;
	std::cin.clear();
	std::cin.ignore(std::cin.rdbuf()->in_avail());
}
//структура определяющая критерий; id - идентификатор; value  - сумма отношений(при промежуточных вычислениях), весовой коэффициент(в конце вычислений)
struct hierarchyMember
{
	std::string id;
	float value;
};

int main()
{
	setlocale(LC_ALL, "Rus");
	int criterionNumber = 0;
	while (true)
	{
		std::cout << "Введите количество критериев " << std::endl;
		std::cin >> criterionNumber;
		if (std::cin.fail() || std::cin.peek() != '\n' || criterionNumber <= 0)
		{
			invalidInput();
		}
		else break;
	}
	//создается вектор критериев и заполняются поля id
	std::vector<hierarchyMember> hierarchyMembers(criterionNumber);
	//введеная матрица
	std::vector<float> matrix(criterionNumber * criterionNumber);
	for (size_t i = 0; i < hierarchyMembers.size(); i++)
	{
		std::string name;
		std::cout << "\nВведите индентификатор для " << i + 1 << " элемента: " << std::endl;
		std::cin >> name;
		hierarchyMembers.at(i).id = name;
	}
	float sum = 0; //сумма значений матрицы
	//заполняется матрица отношений
	for (size_t i = 0; i < hierarchyMembers.size(); i++)
	{
		float valueSum = 0; //сумма отношений
		for (size_t j = 0; j < hierarchyMembers.size(); j++)
		{
			if (j == i)
			{
				valueSum++;
				matrix.at(i * criterionNumber + j) = 1;
			}
			else if (j < i) 
			{
				matrix.at(i * criterionNumber + j) = 1 / matrix.at(j * criterionNumber + i);
				valueSum += matrix.at(i * criterionNumber + j);
			}
			else
			{
				float value = 0;
				while (true)
				{					
					std::cout << "Введите отношение " << hierarchyMembers.at(i).id << " к " << hierarchyMembers.at(j).id << 
						" (дробные значения вводить, округленными до тысячных)" << std::endl;
					std::cin >> value;
					if (std::cin.fail() || std::cin.peek() != '\n' || value <= 0 || value > 9 || (floorf(value) != value &&
						!(std::find(values.begin(), values.end(), value) != values.end())))
					{
						invalidInput();
					}
					else break;
				}
				valueSum += value;
				matrix.at(i * criterionNumber + j) = value;
			}
		}
		hierarchyMembers.at(i).value = valueSum;
		sum += valueSum;
	}
	//сумма отношений критерия преобразовывается в весовой коэффициент
	for (auto& element : hierarchyMembers)
	{
		element.value = element.value / sum;
		std::cout << element.id << " = " << round(element.value * 100) / 100 << std::endl;
	}
	return 0;
}