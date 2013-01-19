#include <iostream>
#include <list>
#include <string>

struct Ast
{
    std::string name;

    std::list< Ast * > children;

    Ast( std::string const & name, std::list< Ast * > children = std::list< Ast * >( ) )
    : name( name )
    , children( children )
    {
    }

    void print( int depth = 0 )
    {
        for ( int t = 0; t < depth; ++ t ) {
            std::cout << "\t";
        }

        std::cout << "- " << name << std::endl;

        for ( auto child : children ) {
            child->print( depth + 1 );
        }
    }
};

static Ast * root = nullptr;

#include "test.h"
#include "test.c"

int main( void )
{
    std::list< int > tokens {
        If, Expr, If, Expr, Ok, Else, Ok
    };

    yyTraceFILE = fopen("test.out", "w");
    auto pParser = ParseAlloc( malloc );

    while ( ! tokens.empty( ) ) {
        Parse( pParser, tokens.front( ), nullptr );
        tokens.pop_front( );
    }

    Parse( pParser, 0, nullptr );
    ParseFree( pParser, free );

    if ( root == nullptr ) {
        std::cerr << "No result" << std::endl;
        return 1;
    } else {
        root->print( );
        return 0;
    }
}
