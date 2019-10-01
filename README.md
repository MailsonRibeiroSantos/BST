# BST
Autor: Mailson Ribeiro Santos 

Descrição projeto: 
O projeto consiste na implementação de árvore binária de busca(BST) de forma genérica utilizando template. Temos como interface da nossa árvore os seguintes métodos: 
BST( KeyTypeLess comp = KeyTypeLess() )
BST( InputIt first, InputIt last )
BST( const BST& other ),
BST( std::initializer_list<T> ilist )
∼BST( )
 BST& operator=( const BST& other )
BST& operator=( std::initializer_list<T> ilist )
 const KeyType & find_min() const
const KeyType & find_max() const
bool contains( const KeyType & key ) const
size_type size() const
bool retrieve( const KeyType & key, DataType & value ) const
void clear( void ) 
void insert( const KeyType & key, const DataType & value )
void remove( const KeyType & key ) 

Para compilar o código o usuário deve acessar a pasta via terminal e digitar o seguinte comando "make". Para executar o usuário deve entrar no seguinte caminho /BST/build/bin e executar o seguinte comando:  "./driver_bst"

Para utilização da classe de forma genérica o usuário deve fornecer um função de comparação de keys. A documentação da classe encontrar-se no seguinte diretório /BST/docs/html.  
