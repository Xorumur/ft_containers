#pragma once 

/*	Une Node contient une valeur, une couleur (ROUGE/NOIR)
	deux childs soit NULL soit remplit et une Node NIL 
	qui signifie la fin d'une branche 						*/

namespace ft {

	template<class T>
	class Node {
		public :
			Node(const T& Value) 
						: value(Value), right(NULL), left(NULL) { }
			Node(const Node & rhs) 
						: value(rhs.value), right(rhs.right), left(rhs.left) { }
			node(const node<type>& rhs) 
						: value(rhs.value), parent(rhs.parent), right(rhs.right), left(rhs.left) { } 

			~node() { }
			

			// La valeur de la Key
			T		value;

			// Pointer sur la Node parent
			node*	parent;

			// Pointeur sur le child de droite
			node*	right;

			// Pointeur sur le child de gauche
			node*	left;

			// Pointer sur la Node NIL
			node*	NIL;

			// Couleur Rouge/Noir
			bool	color;
	};
}