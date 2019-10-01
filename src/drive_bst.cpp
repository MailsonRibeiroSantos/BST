#include <iostream>   // cout, cin, endl
#include <utility>    // std::pair<>
#include <random>     // radom_device, mt19937, std::shuffle.
#include <iomanip>    // std::setw()
#include <string>     // std::string
#include <cassert>
#include <vector>
#include <algorithm>

#include "../include/bst.h"

int main()
{

    // Our BST will store strings with integer keys.
    typedef std::pair< size_t,std::string > test_type;

    // Input data
    test_type data[] = {
        { 0, "zero" },
        { 1, "one" },
        { 2, "two" },
        { 3, "three" },
        { 4, "four" },
        { 5, "five" },
        { 6, "six" },
        { 7, "seven" },
        { 8, "eight" },
        { 9, "nine" },
        { 10, "ten" }
    };


    // Print the input
    {
        size_t insertion_order[] = { 5, 1, 7, 0, 3, 2 };
        // The tree declaration.
#define USE_FUNCTOR
#ifdef USE_FUNCTOR
        struct CompareKey {
            bool operator()( const size_t & a, const size_t & b ) const
            {
                return a > b ;
            }
        }comp;
        
        BST< size_t, std::string, CompareKey > tree(comp);

#else // Use lambda
        auto compare_keys = []( const size_t &a, const size_t &b )->bool
        {
            return a > b ;
        };
        BST< size_t, std::string, decltype( compare_keys ) > tree( compare_keys );
	
#endif

        std::cout << ">>> Inserting data:\n";
        for( const auto & e : insertion_order )
        {
            std::cout << "< " << std::setw(3) << data[e].first << " , \"" << data[e].second << "\" >\n";
            tree.insert( data[e].first, data[e].second );

        }  
        // Teste find_minimo
        assert(tree.find_min()=="zero");
        // Teste find_maximo
        assert(tree.find_max()=="seven");
        std::cout<<"Teste construtor Copia:"<< std::endl;
        //Teste Construtor copia 
        auto tree2 = BST< size_t, std::string, CompareKey >(tree);
        assert(tree.size()==tree2.size());
        // Realiza impressão dos dados 
         auto print = [&]( const std::string & dado)-> void
        {
            std::cout << dado<< " ";
        };
        //inoder
        std::cout<<"tree inorder: "<<std::endl;
        std::cout<<"<<";
        tree.inorder(print);
        std::cout<<">>"<<std::endl;
        std::cout<<"tree2 inorder: "<<std::endl;
        std::cout<<"<<";
        tree2.inorder(print);
        std::cout<<">>"<<std::endl;
        //preorder
         std::cout<<"tree preorder: "<<std::endl;
        std::cout<<"<<";
        tree.preorder(print);
        std::cout<<">>"<<std::endl;
        std::cout<<"tree2 preorder: "<<std::endl;
        std::cout<<"<<";
        tree2.preorder(print);
        std::cout<<">>"<<std::endl;
        //postorder
         std::cout<<"tree postorder: "<<std::endl;
        std::cout<<"<<";
        tree.postorder(print);
        std::cout<<">>"<<std::endl;
        std::cout<<"tree2 postorder: "<<std::endl;
        std::cout<<"<<";
        tree2.postorder(print);
        std::cout<<">>"<<std::endl;
        //Teste clear
        tree2.clear();
        std::cout<<"Impressao da tree2 apos realizacao clear():"<<std::endl;
        std::cout<<"<<";
        tree2.inorder(print);
        std::cout<<">> \n";
        assert(tree2.size()==size_t(0));
        //Teste construtor Iterador 
        std::vector<test_type> v={
        { 0, "zero" },
        { 1, "one" },
        { 2, "two" },
        { 3, "three" },
        { 4, "four" },
        { 5, "five" },
        { 6, "six" },
        { 7, "seven" },
        { 8, "eight" },
        { 9, "nine" },
        { 10, "ten" }
    };
    std::cout<<"Construtor Iterador (begin(),end())! \n";
    tree2 = BST< size_t, std::string, CompareKey >(v.begin(), v.end());
    assert(v.size()==tree2.size());
    std::vector<std::string> v_save;
    auto save = [&]( const std::string & dado)-> void
        {
                v_save.push_back(dado);
        };
    tree2.inorder(save);
    // verrifica se todos os elementos foram inseridos 
    for (auto i(0u); i < tree2.size(); ++i)
    {
        assert(v[i].second==v_save[i]);
    }
    v_save.clear();
    v.clear();
    //Teste construtor com lista inicializadora 
    std::cout<<"Construtor Lista inicializadora {}! \n";
    BST< size_t, std::string, CompareKey > tree3{
        { 0, "zero" },
        { 1, "one" },
        { 2, "two" },
        { 3, "three" },
        { 4, "four" },
        { 5, "five" },
        { 6, "six" },
        { 7, "seven" },
        { 8, "eight" },
        { 10, "ten" }
    };
    v={
        { 0, "zero" },
        { 1, "one" },
        { 2, "two" },
        { 3, "three" },
        { 4, "four" },
        { 5, "five" },
        { 6, "six" },
        { 7, "seven" },
        { 8, "eight" },
        { 10, "ten" }
    };
    assert(tree3.size()==v.size());
    tree3.inorder(save);
    for (auto i(0u); i < tree2.size(); ++i)
    {
        assert(v[i].second==v_save[i]);
    }
    // Teste construtor sobrecarga do operador=
    std::cout<<"Teste sobrecarga operador= \n";
    tree3.clear();
    tree3=tree2;
    v_save.clear();
    std::vector<std::string> v_save2;
    tree2.inorder(save);
    v_save2=v_save;
    v_save.clear();
    tree3.inorder(save);
    // Compara valores da tree2 e tree3
    for (auto i(0u); i < v_save.size(); ++i)
    {
        assert(v_save[i]==v_save2[i]);
    }
    // Sobrecarga do operador= com lista {}
    std::cout<<"Teste construtor operador= com lista {}"<<std::endl;
    BST< size_t, std::string, CompareKey > tree4={
        { 0, "zero" },
        { 1, "one" },
        { 2, "two" },
        { 3, "three" },
    };
    assert(tree4.size()==size_t(4));
    for (auto  i(0u); i < tree4.size(); ++i)
    {
        assert(tree4.contains(i));
    }
    //Teste remover
    size_t size_tree = tree2.size();
    assert(tree2.contains(4));
    tree2.remove (size_t(4));
    assert((size_tree-1)==tree2.size());
    assert(!tree2.contains(4));
    // Teste retrieve
    std::string value;
    tree4.retrieve(size_t(0),value);
    assert(value=="zero");
    tree4.retrieve(size_t(1),value);
    assert(value=="one");
    tree4.retrieve(size_t(2),value);
    assert(value=="two");
    tree4.retrieve(size_t(3),value);
    assert(value=="three");

    } 


    return EXIT_SUCCESS;
}
