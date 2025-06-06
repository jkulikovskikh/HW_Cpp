template <typename T>
class SerialContainer { 
public:
	SerialContainer() : m_size{0} {
		m_region = new T{};
	}

	// добавление нового элемента
	void push_back (T value) {
		insert_to_end(value);
	}

	// вставка элемента в начало контейнера
	void insert_to_begin(T value) {
		size_t new_size = m_size + 1;
		T* new_region = new T[new_size]; 
		new_region[0] = value; 			
		for (size_t i = 1; i < new_size; ++i) {
			new_region[i] = m_region[i - 1]; 		
		}		
		if (m_size != 0)
			delete [] m_region;			
		m_region = new_region; 					
		m_size = new_size; 							
	}

	// вставка элемента в конец контейнера
	void insert_to_end(T value) {
		T* new_region = new T[m_size + 1]; 		
		for (size_t i = 0; i < m_size; ++i) {
			new_region[i] = m_region[i]; 		
		}
		new_region[m_size] = value; 			
		if (m_size != 0)
			delete [] m_region;
		m_region = new_region; 					
		m_size += 1;  							
	}

	// вставка элемента в контейнер в произвольную позицию (на вход функции значение элемента и позиция)
	void insert_to_position(T value, size_t pos) {
		if(pos > m_size + 1) {
			std::cout << pos << " is not in the container. Insertion is not possible." << std::endl;
		}
		else {
			size_t new_size = m_size + 1;
			T* new_region = new T[new_size]; 
			new_region[pos] = value;
			size_t shift = 0;			
			for (size_t i = 0; i < new_size; ++i) {
				if (i == pos) {
					shift = 1;
					continue;
				}
				new_region[i] = m_region[i - shift]; 		
			}		
			if (m_size != 0)
				delete [] m_region;				
			m_region = new_region; 					
			m_size = new_size; 		
		}
	}

	// удаление элементов из контейнера (на вход функции - массив позиций элементов для удаления)
	void erase_positions (size_t pos[], size_t size_pos) {
		size_t size_ = 0;
		for (size_t i = 0; i < size_pos; i++) {
			if(pos[i] >= m_size) {
				std::cout << pos[i] << " is not in the container. Remove is not possible." << std::endl;
			}
			else {
				size_++;
			}
		}
		if(size_ != 0) {
			size_t new_size = m_size - size_;
			T* new_region = new T[new_size];
			size_t k = 0;
			size_t j = 0;
			for (size_t i = 0; i < m_size; i++) {
				if (i == pos[j] - 1) {
					j++;
					continue;
				}
				new_region[k] = m_region[i];
				k++;
			}
			if (m_size > 1) 
				delete [] m_region;
			else 
				delete m_region;
			m_region = new_region; 					
			m_size = new_size; 
		}
	}

	// удаление элементов из контейнера (на вход функции - массив значений элементов для удаления)
	void erase_values (T value[], size_t size_value) {
		size_t size_ = 0;
		for (size_t i = 0; i < size_value; i++) {
			for (size_t j = 0; j < m_size; j++) {
				if (value[i] == m_region[j]) {
					size_ ++;
					break;
				}
			}
		}
		if(size_ != 0) {
			size_t new_size = m_size - size_;
			T* new_region = new T[new_size];
			size_t k = 0;
			size_t j = 0;
			for (size_t i = 0; i < m_size; i++) {
				if (i == value[j]) {
					j++;
					continue;
				}
				new_region[k] = m_region[i];
				k++;
			}
			if (m_size > 1) 
				delete [] m_region;
			else 
				delete m_region;	
			m_region = new_region; 					
			m_size = new_size; 
		}
	}

	// получение текущего размера контейнера
	size_t size() const {
			return m_size;
		}

	// вывод содержимого контейнера на экран
	void print() const {
		for (size_t i = 0; i < m_size; ++i) {
			if (i != 0) std::cout << ' ';
			std::cout <<  m_region[i];
		}
	}

    ~SerialContainer() {
        if (m_size != 0)
            delete [] m_region;
		else
			delete m_region;
    }

private:
	size_t m_size;
	T* m_region;
};


template <typename T>
class ListTypeContainer {
public:
	ListTypeContainer() : m_size{0} {
		m_first = m_last = new Node{};

		m_last->next = nullptr;
		m_last->prev = nullptr;
	}

	// добавление нового элемента
	void push_back (T value) {
		insert_to_end(value);
	}

	// вставка элемента в начало контейнера
	void insert_to_begin (T value) {
		Node *new_node = new Node{};
		new_node->next = m_first;
		new_node->prev = nullptr;
		new_node->data = value;
		m_first->prev = new_node;
		m_first = new_node;
		m_size += 1;	
	}

	// вставка элемента в конец контейнера
	void insert_to_end (T value) {
		if (m_first == m_last) {
			insert_to_begin (value);
		}
		else {
			Node *new_node = new Node{};
			new_node->next = m_last;
			new_node->prev = m_last ->prev;
			new_node->data = value;
			m_last->prev -> next =  new_node;
			m_last->prev =  new_node;
			m_size += 1;
		}
	}

	// вставка элемента в контейнер в произвольную позицию (на вход функции значение элемента и предыдущее значение элемента)
	void insert_to_before_value (T value, T prev_value) {
		for (Node *m_node = m_first; m_node!= m_last; m_node = m_node->next) {
			if (prev_value == m_first->data) {
				insert_to_begin(value);
				break;
			}
			else if (m_node->data == prev_value) {
				Node *new_node = new Node{};
				new_node->next = m_node;
				new_node->prev = m_node -> prev;
				new_node->data = value;
				m_node->prev -> next = new_node;
				m_node->prev = new_node;
				m_size += 1;	
				break;
			}
		}
	} 

	// удаление элементов из контейнера (на вход функции - массив значений элементов для удаления)
	void erase_values (T value[], size_t size_value) {
		for (size_t i = 0; i < size_value; i++) {
			for (Node *m_node = m_first; m_node!= m_last; m_node = m_node->next) {
				if (m_node -> data == value[i]) {
					if(m_first -> data != value[i]) {
						m_node->prev->next = m_node->next;
						m_node->next->prev = m_node->prev;
					}
					else {
						m_first = m_node->next;
						m_first->prev = 0;
					}
					delete m_node;
					m_size -= 1;
					break;
				}
			}
		}
	}

	// получение текущего размера контейнера
	size_t size() const {
		return m_size;
	} 

	// вывод содержимого контейнера на экран
	void print() const {
		for (Node *m_node = m_first; m_node!= m_last; m_node = m_node->next) {
			std::cout << m_node->data << " " ;
		}
	}

	~ListTypeContainer() {
		Node *node = m_first;
		for (Node *m_node = node; m_node!= m_last;) 
		{
			m_node = m_node->next;
			delete node;
			node = m_node;
		}
		delete node;
	}

private:
	size_t m_size;

	struct Node {
		Node* next; 			
		Node* prev; 			
		T data; 				
	};

	Node *m_first;
	Node *m_last;
};
