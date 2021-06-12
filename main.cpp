//#include "sources/BinaryTree.hpp"
//using namespace ariel;
//
//#include <algorithm>
//#include <cstdlib>
//#include <ctime>
//#include <functional>
//#include <iostream>
//#include <map>
//#include <memory>
//#include <string>
//#include <vector>
//using namespace std;
//
//const int max_rand = 1000;
//const int div_factor = 100;
//
//double NextDouble() {
//    return (double)((unsigned int)rand() % max_rand) / div_factor;
//}
//
//int NextInt() {
//    return (rand() % max_rand);
//}
//
//bool RandomBool() {
//    return rand() % 2 == 0;
//}
//
//enum class _order {
//    inorder,
//    postorder,
//    preorder,
//};
//
//template <typename T>
//BinaryTree<T> create_dummy(int adder = 0) {
//    BinaryTree<T> tree;
//
//    // create the following tree
//    //                    1
//    //              2          3
//    //         4        5
//    //               10   11
//    //             20       23
//    tree.add_root(1 + adder);
//    tree.add_left(1 + adder, 2 + adder);
//    tree.add_right(1 + adder, 3 + adder);
//    tree.add_left(2 + adder, 4 + adder);
//    tree.add_right(2 + adder, 5 + adder);
//    tree.add_left(5 + adder, 10 + adder);
//    tree.add_right(5 + adder, 11 + adder);
//    tree.add_left(10 + adder, 20 + adder);
//    tree.add_right(11 + adder, 23 + adder);
//
//    return tree;
//}
//
//template <typename T>
//bool isEqual(BinaryTree<T> &tree, vector<T> const &v2, _order order) {
//    // This function checks if a given tree order is equal to some vector.
//    if (order == _order::inorder) {
//        auto end = tree.end_inorder();
//        auto pair = std::mismatch(tree.begin_inorder(), tree.end_inorder(), v2.begin());
//        return (pair.first == end && pair.second == v2.end());
//    } else if (order == _order::postorder) {
//        auto end = tree.end_postorder();
//        auto pair = std::mismatch(tree.begin_postorder(), tree.end_postorder(), v2.begin());
//        return (pair.first == end && pair.second == v2.end());
//    }
//    auto end = tree.end_preorder();
//    auto pair = std::mismatch(tree.begin_preorder(), tree.end_preorder(), v2.begin());
//    return (pair.first == end && pair.second == v2.end());
//}
//
//
//class myString {
//public:
//    string val;
//    myString(int a) {
//        val = std::to_string(a);
//    }
//
//    myString &operator+(const myString &other) {
//        val += other.val;
//        return *this;
//    }
//
//    myString &operator+(int other) {
//        val += to_string(other);
//        return *this;
//    }
//
//    myString &operator+(double other) {
//        val += to_string(other);
//        return *this;
//    }
//
//    bool operator==(const myString &other) {
//        return this->val == other.val;
//    }
//
//    // need to define this for maps...
//    friend bool operator<(const myString &t, const myString &other) {
//        return t.val < other.val;
//    }
//
//    friend std::ostream &operator<<(std::ostream &os, const myString &c) {
//        return (os << c.val);
//    }
//};
//
//
//
//
//int main() {
//    srand(time(nullptr));
//    // create the following tree on i = 0
//    //                    1
//    //              2          3
//    //         4        5
//    //               10   11
//    //             20       23
//
//    auto print = [](myString n) { cout << ", " << n; };
//    // for_each(preorder.begin(), preorder.end(), print);
//
//    // Test inorder preorder postorder with match.
//
//    for (int i = 0; i < 5; i++) {
//        // create a tree that we can delete at any time!
//        BinaryTree<myString> *tree = new BinaryTree<myString>(create_dummy<myString>());
//        // inorder : 4, 10, 5, 11, 2, 1, 3
//        vector<myString> inorder = {4, 2, 20, 10, 5, 11, 23, 1, 3};
//        //postorder : 4, 20, 10, 23, 11, 5, 2, 3, 1
//        vector<myString> postorder = {4, 20, 10, 23, 11, 5, 2, 3, 1};
//        //preorder : 1, 2, 4, 5, 10, 20, 11, 23, 3
//        vector<myString> preorder = {1, 2, 4, 5, 10, 20, 11, 23, 3};
//
//        int randval = NextInt();
//
//        auto f = [](myString val, int add) {
//            return val + add;
//        };
//
//        // here we are creating a transformation function in order to update the tree and the vector.
//        auto f2 = bind(f, placeholders::_1, randval);
//
//        transform(inorder.begin(), inorder.end(), inorder.begin(), f2);
//        transform(preorder.begin(), preorder.end(), preorder.begin(), f2);
//        transform(postorder.begin(), postorder.end(), postorder.begin(), f2);
//        transform(tree->begin(), tree->end(), tree->begin(), f2);
//
//        // check if that tree even working?
//
//        cout<<isEqual(*tree, inorder, _order::inorder)<<endl;
//        cout<<isEqual(*tree, preorder, _order::preorder)<<endl;
//        cout<<isEqual(*tree, postorder, _order::postorder)<<endl;
//
//        BinaryTree<myString> tree3 = *tree;
//        BinaryTree<myString> tree4;
//        tree4.add_root(12312312);
//        tree4.add_left(12312312, 12312);
//        cout << "false" << endl;
//        cout<<isEqual(tree4, inorder, _order::inorder) <<endl;
//        cout<<isEqual(tree4, preorder, _order::preorder) <<endl;
//        cout<<isEqual(tree4, postorder, _order::postorder) <<endl;
//        tree4 = *tree;
//
//        // change values of the original again.
//        transform(tree->begin(), tree->end(), tree->begin(), f2);
//
//        cout<<isEqual(tree4, inorder, _order::inorder)<<endl;
//        cout<<isEqual(tree4, preorder, _order::preorder)<<endl;
//        cout<<isEqual(tree4, postorder, _order::postorder)<<endl;
//        delete tree;
//        //tree2.~BinaryTree();
//
//        tree3 = tree4;
//
//        cout<<isEqual(tree3, inorder, _order::inorder)<<endl;
//        cout<<isEqual(tree3, preorder, _order::preorder)<<endl;
//        cout<<isEqual(tree3, postorder, _order::postorder)<<endl;
//
//        ///
//        cout<<isEqual(tree4, inorder, _order::inorder)<<endl;
//        cout<<isEqual(tree4, preorder, _order::preorder)<<endl;
//        cout<<isEqual(tree4, postorder, _order::postorder)<<endl;
//
//        // transform tree4
//        transform(tree4.begin(), tree4.end(), tree4.begin(), f2);
//
//        // check that tree3 didn't change.
//        cout<<isEqual(tree3, inorder, _order::inorder)<<endl;
//        cout<<isEqual(tree3, preorder, _order::preorder)<<endl;
//        cout<<isEqual(tree3, postorder, _order::postorder)<<endl;
//
//        // update the check's and see if it mach tree4.
//        transform(inorder.begin(), inorder.end(), inorder.begin(), f2);
//        transform(preorder.begin(), preorder.end(), preorder.begin(), f2);
//        transform(postorder.begin(), postorder.end(), postorder.begin(), f2);
//
//        cout<<isEqual(tree4, inorder, _order::inorder)<<endl;
//        cout<<isEqual(tree4, preorder, _order::preorder)<<endl;
//        cout<<isEqual(tree4, postorder, _order::postorder)<<endl;
//    }
//}
//
//


/**
 * Demo file for the exercise on binary tree
 *
 * @author Erel Segal-Halevi
 * @since 2021-04
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
using namespace std;

#include "sources/BinaryTree.hpp"
using namespace ariel;

int main() {
    BinaryTree < char > tree;
    tree.add_root('f')
            .add_left('f', 'd')
            .add_right('f', 'i')
            .add_left('d', 'a')
            .add_right('d','e')
            .add_right('a','b')
            .add_right('b','c')
            .add_left('i','h')
            .add_right('i','j')
            .add_left('h', 'g')
            .add_right('j', 'k')
            .add_right('k', 'l')
            .add_right('l', 'm');
    cout<<tree<<endl<<endl;
    BinaryTree<int> tree_of_ints;
    tree_of_ints.add_root(1)
            .add_left(1, 9)      // Now 9 is the left child of 1
            .add_left(9, 4)      // Now 4 is the left child of 9
            .add_right(9, 5)     // Now 5 is the right child of 9
            .add_right(1, 3)// Now 3 is the right child of 1
            .add_left(1, 2);     // Now 2 is the left child of 1, instead of 9 (the children of 9 remain in place)

    cout << tree_of_ints << endl;  /* Prints the tree in a reasonable format. For example:
        1
        |--------|
        2        3
        |---|
        4   5
  */
//
//    for (auto it=tree_of_ints.begin_preorder(); it!=tree_of_ints.end_preorder(); ++it) {
//        cout << (*it) << " " ;
//    }  // prints: 1 2 4 5 3
//    for (auto it=tree_of_ints.begin_inorder(); it!=tree_of_ints.end_inorder(); ++it) {
//        cout << (*it) << " " ;
//    }  // prints: 4 2 5 1 3
//    for (auto it=tree_of_ints.begin_postorder(); it!=tree_of_ints.end_postorder(); ++it) {
//        cout << (*it) << " " ;
//    }  // prints: 4 5 2 3 1
//
//    for (int element: tree_of_ints) {  // this should work like inorder
//        cout << element << " " ;
//    }  // prints: 4 2 5 1 3
//
//
//    // The same should work with other types, e.g. with strings:
//
//    BinaryTree<string> tree_of_strings;
//    tree_of_strings.add_root("1")
//            .add_left("1", "9")      // Now 9 is the left child of 1
//            .add_left("9", "4")      // Now 4 is the left child of 9
//            .add_right("9", "5")     // Now 5 is the right child of 9
//            .add_right("1", "3")     // Now 3 is the right child of 1
//            .add_left("1", "2");     // Now 2 is the left child of 1, instead of 9 (the children of 9 remain in place)
//    cout << tree_of_strings << endl;
//
//    for (auto it=tree_of_strings.begin_preorder(); it!=tree_of_strings.end_preorder(); ++it) {
//        cout << (*it) << " " ;
//    }  // prints: 1 2 4 5 3
//    for (auto it=tree_of_strings.begin_inorder(); it!=tree_of_strings.end_inorder(); ++it) {
//        cout << (*it) << " " ;
//    }  // prints: 4 2 5 1 3
//    for (auto it=tree_of_strings.begin_postorder(); it!=tree_of_strings.end_postorder(); ++it) {
//        cout << (*it) << " " ;
//    }  // prints: 4 5 2 3 1
//
//    // demonstrate the arrow operator:
//    for (auto it=tree_of_strings.begin_postorder(); it!=tree_of_strings.end_postorder(); ++it) {
//        cout << it->size() << " " ;
//    }  // prints: 1 1 1 1 1
//
//
//    for (const string& element: tree_of_strings) {  // this should work like inorder
//        cout << element << " " ;
//    }   // prints: 4 2 5 1 3

}