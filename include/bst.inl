#include "bst.h"
//Construtor Copia 
template < typename KeyType, typename ValueType, typename KeyTypeLess >  
BST<KeyType,ValueType,KeyTypeLess>::BST( const BST & other ): m_root( nullptr )
            , m_n_nodes(0)
{
	m_key_less=other.m_key_less;
	m_root=clone(other.m_root);
}
//Destrutor 
template < typename KeyType, typename ValueType, typename KeyTypeLess >
BST<KeyType,ValueType,KeyTypeLess>::~BST()
{
	clear(m_root);
}
// Construtor inicializado Iterator
template<typename KeyType , typename ValueType , typename KeyTypeLess >
template<typename InputItr >
BST<KeyType, ValueType, KeyTypeLess>::BST(InputItr  first, InputItr  	last, const KeyTypeLess & comp) : m_root( nullptr )
            , m_n_nodes(0)
            , m_key_less ( comp )
{
	auto it =first;
	auto i(0u);
	while(it !=last)
	{
		insert( it[i].first, it[i].second );
		++it;
	}
}
// Contrutor inicializado com lista 
template < typename KeyType, typename ValueType, typename KeyTypeLess > 
 BST<KeyType, ValueType, KeyTypeLess>::BST( std::initializer_list<node_content_type> init , const KeyTypeLess & comp): m_root( nullptr )
            , m_n_nodes(0)
            , m_key_less ( comp )
{
	auto it =init.begin();
	auto i(0u);
	m_key_less=comp; 
	while(it !=init.end())
	{
		insert( it[i].first, it[i].second );
		++it;
	}
}
//Contrutor inicializar sobreposicao do operador
template<typename KeyType , typename ValueType , typename KeyTypeLess >
BST< KeyType, ValueType, KeyTypeLess > & BST< KeyType, ValueType, KeyTypeLess >::operator=(const BST< KeyType, ValueType, KeyTypeLess > &  rhs) 	
{
	clear(m_root);
	m_key_less=rhs.m_key_less;
	m_root=clone(rhs.m_root);
	return *this;	
}
//Contrutor inicializar com lista sobreposicao do operador
template<typename KeyType , typename ValueType , typename KeyTypeLess >
BST< KeyType, ValueType, KeyTypeLess > & BST< KeyType, ValueType, KeyTypeLess >::operator=( std::initializer_list<node_content_type > ilist)
{
		auto it =ilist.begin();
		auto i(0u); 
		while(it !=ilist.end())
		{
			insert( it[i].first, it[i].second );
			++it;
		}
		return *this;
}
// Retorna o minimo 
 template<typename KeyType , typename ValueType , typename KeyTypeLess >
 const ValueType & BST< KeyType, ValueType, KeyTypeLess >::find_min(void) const
{
	auto root = m_root;
	while(root->left!=nullptr)
	{
		root=root->left;
	}
	return root->data;
}
// Retorna o maximo 
template<typename KeyType , typename ValueType , typename KeyTypeLess >
const ValueType & BST< KeyType, ValueType, KeyTypeLess >::find_max(void ) const
{
	auto root = m_root;
	while(root->right!=nullptr)
	{
		root=root->right;
	}
	return root->data;
	
}
//Verrifica se contem termo 
template < typename KeyType, typename ValueType, typename KeyTypeLess >
bool BST< KeyType, ValueType, KeyTypeLess >::contains (const KeyType & key) const
{
	return contains(m_root,key);
}
//Verrifica menbro privado para fazer recusao
template<typename KeyType , typename ValueType , typename KeyTypeLess >
bool BST< KeyType, ValueType, KeyTypeLess >::contains (const BTNode * root,const KeyType &  key) const
{
	if(root==nullptr)
	{
		return false;
	}else if(!m_key_less(root->key,key) && !m_key_less(key,root->key))
	{
		return true;
	}else if(m_key_less(key,root->key))
	{
		return contains(root->right,key);
	}else
	{
		return contains(root->left,key);
	}
}
//preorder
template<typename KeyType , typename ValueType , typename KeyTypeLess >
template<typename UnaryFunction >
void BST< KeyType, ValueType, KeyTypeLess >::preorder ( const UnaryFunction &  visit) 	const
{
	preorder(m_root,visit);
}
template<typename KeyType , typename ValueType , typename KeyTypeLess >
template<typename UnaryFunction >
void BST< KeyType, ValueType, KeyTypeLess >::preorder (const BTNode *  root,const UnaryFunction &  visit) const
{
	if (root!= nullptr )
    {
        visit( root->data ); 
        preorder( root->left, visit);
        preorder( root->right, visit);
    }
}
template<typename KeyType , typename ValueType , typename KeyTypeLess >
template<typename UnaryFunction >
void BST< KeyType, ValueType, KeyTypeLess >::postorder (const UnaryFunction &  visit)const
{
	postorder(m_root,visit);
}
template<typename KeyType , typename ValueType , typename KeyTypeLess >
template<typename UnaryFunction >
void BST< KeyType, ValueType, KeyTypeLess >::postorder 	(const BTNode *  root, const UnaryFunction &  visit ) const
{
	 if ( root != nullptr )
    {
        postorder( root->left, visit);
        postorder( root->right, visit);
        visit( root->data ); 
    }

} 
template<typename KeyType , typename ValueType , typename KeyTypeLess >
template<typename UnaryFunction >
void BST< KeyType, ValueType, KeyTypeLess >::inorder 	( 	const UnaryFunction &  	visit	) 	const
{
	inorder(m_root,visit); 
}
template<typename KeyType , typename ValueType , typename KeyTypeLess >
template<typename UnaryFunction >
void BST< KeyType, ValueType, KeyTypeLess >::inorder 	( 	const BTNode *  	root,const UnaryFunction &  	visit ) const
{
	 if ( root != nullptr )
    {
        inorder( root->left, visit);
        visit( root->data ); 
        inorder( root->right, visit);
    }
}
// Retorna ponteiro para elemento mais a esquerda
template<typename KeyType , typename ValueType , typename KeyTypeLess >
const typename  BST< KeyType, ValueType, KeyTypeLess >::BTNode * BST< KeyType, ValueType, KeyTypeLess >::get_smallest_leaf (const BTNode *  root) const
{
 	if ( root== nullptr ) return nullptr;

    while( root->left != nullptr ) 
    {
        root= root->left; 
    }
    return root;
} 
		
//clone
template < typename KeyType, typename ValueType, typename KeyTypeLess > 
typename BST<KeyType, ValueType, KeyTypeLess>::BTNode * BST< KeyType, ValueType, KeyTypeLess >::clone 	( const BTNode *  root) 	
{
	if(root == nullptr)
		return nullptr;
	BTNode * new_root = new BTNode(root->key,root->data);
	m_n_nodes++;
	new_root->left = clone(root->left);
	new_root->right = clone(root->right);
	return new_root;
}

// Inserir public recebe key e value e chama inserir privado 
template < typename KeyType, typename ValueType, typename KeyTypeLess >
void BST<KeyType,ValueType,KeyTypeLess>::insert( const KeyType & key , const ValueType & value )
{
	insert(m_root,key, value);
}
// Inserir private realiza insercao de forma recursiva  
template < typename KeyType, typename ValueType, typename KeyTypeLess >
void BST<KeyType,ValueType,KeyTypeLess>::insert( BTNode * & root, const KeyType & key, const ValueType & value )
{
	if(root==nullptr)
	{
		root = new BTNode(key,value);
		m_n_nodes++;
	} 	
	else if(m_key_less(key,root->key))
	{
		//verifica se key maior que root->key 
		insert(root->right,key, value);
		 
	}else
	{
		insert(root->left,key, value);
	}

}
 template<typename KeyType , typename ValueType , typename KeyTypeLess >
bool BST< KeyType, ValueType, KeyTypeLess >::retrieve 	( 	const KeyType &  	key, ValueType &  	value ) const
{
	return retrieve(m_root,key, value);	
}
template<typename KeyType , typename ValueType , typename KeyTypeLess >
void BST< KeyType, ValueType, KeyTypeLess >::clear(void) 	
{
	m_n_nodes=0;
	clear(m_root);
}
template<typename KeyType , typename ValueType , typename KeyTypeLess >
void BST< KeyType, ValueType, KeyTypeLess >::clear (BTNode *&  	root) 		
{
    if ( root== nullptr ) 
    	return;

    clear( root->left );
    clear( root->right );
    delete root;
    root = nullptr; 
}
template<typename KeyType , typename ValueType , typename KeyTypeLess >
bool BST< KeyType, ValueType, KeyTypeLess >::retrieve (const BTNode * root,const KeyType & key,ValueType &  value ) const
{
	if(root==nullptr)
	{
		return false;
	}else
	{
		if(!m_key_less(root->key,key) && !m_key_less(key,root->key))
		{
			value=root->data;
			return true;
		}else if(m_key_less(key,root->key))
		{
		retrieve(root->right,key, value);
		}else 
		{
		retrieve(root->left,key, value);
		}
	}
}
template<typename KeyType , typename ValueType , typename KeyTypeLess >
void BST< KeyType, ValueType, KeyTypeLess >::remove ( const KeyType &  	key) 
{
	remove(m_root,key);
}
template<typename KeyType , typename ValueType , typename KeyTypeLess >
void BST< KeyType, ValueType, KeyTypeLess >::remove ( BTNode *&  root,const KeyType &  	key) 	
{
    
    if ( root== nullptr )
        return; 
    // verrifica se chave é maior
    else if (m_key_less( key, root->key) ) 
    {
        return remove( root->right, key);
    }
    else if ( m_key_less( root->key, key) ) 
    {
        return remove( root->left, key);
    }
    //Encontrou a key que deve ser removida
    else 
    {
        if ( root->left != nullptr and root->right != nullptr )
        {
           
            auto aux = get_smallest_leaf( root->right );
            root->data = aux->data;
            root->key  = aux->key;
            remove( root->right, aux->key );
        }
        else 
        {
            auto aux = root;
            if(root->left !=nullptr)
            {
            	root=root->left;
            }else
            {
            	root=root->right;
            }
            //libera memoria 
            delete aux;
        }
        m_n_nodes--;
    }
}
