#include <iostream>
// Дуга представлена элементом списка, содержащим номера
// концов дуги и указатель на следующий элемент списка
struct Arc {
	int begin, end;
	Arc* next;

	// Конструктор дуги.
	Arc(int b, int e, Arc* n=nullptr)
	{
		begin = b; end = e; next = n;
	};

};

class ArcGraph {
public:
	// Список дуг представлен, как обычно, указателями на первый и последний элементы списка
	Arc* first, * last;

	int cyclomaticNubmer;
	int numberOfArcs;
	int arcs;
	// arcCount - счетчик числа дуг-элементов списка
	int arcCount;

	// vertexNumber - количество вершин графа, используемое в данном представлении только для контроля номеров вершин
	int vertexNumber;

	// Конструктор графа инициализирует пустой список и запоминает количество вершин графа.
	ArcGraph(int n)
	{
		first = last = nullptr; 
		arcCount = 0; 
		vertexNumber = n;
	}

	// Функция подсчета количества вершин выдает запомненное значение
	int vertexCoun() const { return vertexNumber-1; }

	// Операции над дугами:
	void addArc(int from, int to);
	bool hasArc(int from, int to) const;

	void getGraph();

	int DFS(int start,int n);
	int getNubmerOfArc();
};


//Реализация операции добавления дуги
void ArcGraph::addArc(int from, int to) {

	// Сначала проверяем правильность задания номеров вершин.
	if (from < 0 || to < 0 || from >= vertexNumber || to >= vertexNumber)
		return;

	Arc* newArc = new Arc(from, to);
	// Новая дуга добавляется в конец списка

	if (last) last->next = newArc; 
	else first = newArc;

	last = newArc;
	arcCount++;

}

// Реализация операции проверки наличия дуги.
bool ArcGraph::hasArc(int from, int to) const {

	// Необходимо просмотреть список дуг в поисках нужной.
	for (Arc* current = first; current; current = current->next) {
		if (current->begin == from && current->end == to)
		{
			return true;
		}
	}
	return false;
}

void ArcGraph::getGraph()
{
	for (Arc* current = first; current; current = current->next)
	{
		std::cout << current->begin << " " << current->end << std::endl;
	}
}

int ArcGraph::getNubmerOfArc()
{
	int i = 0;
	for (Arc* current = first; current; current = current->next)
	{
		i++;
	}
	i = (i/2)+1;
	return i;
}


int ArcGraph::DFS(int start,int n)
{
	static int visited[8] = { 0 };
	int j;

	if (visited[start] == 0)
	{
		printf("%d", start);
		visited[start] = 1;

		for (j = 1;j < n;j++)
		{
			//numberOfVertex++;
			if (hasArc(start, j) && visited[j] == 0)
			{
				numberOfArcs--;
				DFS(j, n);
			}
			else if (hasArc(start, j))
			{
				numberOfArcs++; //Счетчик скролько всего ребер (прибавляем если 
				//std::cout << start<<"\n";
				//arcs+=1; //считаем сколько раз алгоритм обошел дуги(в случае с нашим графом должны получить 42, т.к. всего он проверит n(n-1) раз)
			}
		}
	}
	
	return numberOfArcs+1-vertexCoun(); //(arcs/2 - так как каждое ребро относится к двум вершинам, 
	//при таком подсчете оно будет учитываться дважды,поэтому  делим на два - получаем 21),  
	//(numberOfVertex+1 - получаем количество вершин графа +1 тк алгоритм не заходит в if на последнем цикле),
	//делим первое число на второе и получаем цикломатическую сложность графа (наименьшее число рёбер, которое нужно удалить из данного графа, чтобы получить дерево (для связного графа))
}

int main()
{
	setlocale(LC_ALL, "Russian");
	ArcGraph g = ArcGraph(8);
	//g.addArc(1, 2);
	//g.addArc(1, 3);
	//g.addArc(1, 4);
	//g.addArc(2, 3);
	//g.addArc(2, 1);
	//g.addArc(3, 2);
	//g.addArc(3, 1);
	//g.addArc(3, 4);
	//g.addArc(4, 1);
	//g.addArc(4, 3);
	//g.addArc(4, 5);
	//g.addArc(5, 3);
	//g.addArc(5, 4);
	//g.addArc(5, 7);
	//g.addArc(5, 6);
	//g.addArc(6, 5);
	//g.addArc(7, 5);
	g.addArc(1,2);
	g.addArc(1,3);
	g.addArc(1,4 );
	g.addArc(1, 5);
	g.addArc(2, 3);
	g.addArc(2, 1);
	g.addArc(2, 4);
	g.addArc(2, 6);
	g.addArc(3, 2);
	g.addArc(3, 1);
	g.addArc(3, 4);
	g.addArc(4, 6);
	g.addArc(4, 2);
	g.addArc(4, 3);
	g.addArc(4, 1);
	g.addArc(4, 5);
	g.addArc(4, 7);
	g.addArc(5, 1);
	g.addArc(5, 4);
	g.addArc(5, 7);
	g.addArc(6, 2);
	g.addArc(6, 4);
	g.addArc(7, 4);
	g.addArc(7, 5);
	
	std::cout << "Список дуг" << std::endl;
	g.getGraph();
	std::cout << "Обход в глубину с первой вершины" << std::endl;
	std::cout << "\n\n\nЦикломатическое число графа: " << g.DFS(1, 8) << std::endl;

	
	
	//std::cout<< "\n\n" << g.getNubmerOfArc();
	return 0;
}
