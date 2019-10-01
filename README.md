# BST
Autor: Mailson Ribeiro Santos 

Descrição projeto: 
O projeto consiste na implementação de árvore binária de busca(BST) de forma genérica utilizando template. Temos como interface da nossa árvore os seguintes métodos: <br/>
<ul>
<li>BST( KeyTypeLess comp = KeyTypeLess() )</li>
<li>BST( InputIt first, InputIt last )</li>
<li>BST( const BST& other ) </li>
<li>BST( std::initializer_list<T> ilist )</li>
<li>∼BST( )</li>
<li>BST& operator=( const BST& other )</li>
<li>BST& operator=( std::initializer_list<T> ilist )</li>
<li>const KeyType & find_min() const </li>
<li>const KeyType & find_max() const </li>
<li>bool contains( const KeyType & key ) const </li>
<li>size_type size() const </li>
<li>bool retrieve( const KeyType & key, DataType & value ) const </li>
<li>void clear( void ) </li>
<li>void insert( const KeyType & key, const DataType & value ) </li>
<li>void remove( const KeyType & key ) </li>
</ul>
<br/>
Para compilar o código o usuário deve acessar a pasta via terminal e digitar o seguinte comando "make". Para executar o usuário deve entrar no seguinte caminho /BST/build/bin e executar o seguinte comando:  "./driver_bst"

