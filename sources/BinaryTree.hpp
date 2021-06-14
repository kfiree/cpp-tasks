//
// Created by user on 23/05/2021.
//

#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <memory>
#include <string>
#include <map>
#include <vector>
#include <math.h>

using std::vector;
using std::ostream;
using std::invalid_argument;
using std::shared_ptr;
using std::make_shared;
using std::weak_ptr;
using std::unique_ptr;
using std::move;
using std::string;
using std::endl;

namespace ariel
{
    template<typename T>
    class BinaryTree
    {
    private:

        /**
         *        +++ Node Struct +++
         *
         *    _val = value of template type T
         *    _leftChild = shared pointer to left-child
         *    _rightChild = shared pointer to right-child
         *
         */
        struct Node {
            T _val;
            int _depth;
            std::weak_ptr<Node> _parent;
            std::shared_ptr<Node> _leftChild;
            std::shared_ptr<Node> _rightChild;

            explicit Node(T val): _val(val), _depth(0){}
        };

        enum Traversal {InOrder, PreOrder, PostOrder}; // traversal types
        unsigned int _treeSize= 0; //size of tree
        int _maxDepth= 0; //tree max depth
        shared_ptr<Node> _root; // tree's root

    public:

        class Iterator {
            Traversal _traversal = Traversal::InOrder; // traversal types
            shared_ptr<Node> _current;

        private:
            //      +++ ITERATOR AID +++

            /**
             * aid for traversal
             * @return true if _current is root
             */
            bool isRoot() const {
                auto parent = _current->_parent;
                return !parent.owner_before(weak_ptr<Node>{}) && !weak_ptr<Node>{}.owner_before(parent);
            }

            /**
             * aid for traversal
             * @return true if _current is left-child
             */
            bool isLeft() const {
                return !isRoot() && (_current == _current->_parent.lock()->_leftChild);
            }

            /**
             * aid for traversal
             * @return true if _current is right-child
             */
            bool isRight() const {
                return !isRoot() && (_current == _current->_parent.lock()->_rightChild);
            }

            /**
             * aid for traversal
             * @return true if _current has a left-child
             */
            bool hasLeft(){
                return _current->_leftChild != nullptr;
            }

            /**
             * aid for traversal.
             * @return true if _current has a righ- child
             */
            bool hasRight(){
                return _current->_rightChild != nullptr;
            }

            /**
             * aid for traversal.
             * move _current to the leftmost node
             * used by inorder and postorder traversal.
             */
            void goDownLeft(){
                while (hasLeft()) {
                    _current = _current->_leftChild;
                }
            }

            /**
              * aid for traversal.
              * while possible move _current to the leftmost node and then one right.
              * used by postorder traversal.
              */
            void goDownLeftAndRight(){
                do{
                    goDownLeft();

                    if(hasRight()){oneRight();}

                }while(hasLeft() || hasRight());
            }

            /**
              * aid for traversal.
              * move _current to the to current's right-child node
              */
            void oneRight(){
                _current = _current->_rightChild;
            }

            /**
              * aid for traversal.
              * move _current to the to current's left-child node
              */
            void oneLeft(){
                _current = _current->_leftChild;
            }

            /**
              * aid for traversal.
              * move _current to the to parent node
              */
            void oneUp(){
                _current = _current->_parent.lock();
            }

            /**
             * move current to next position - Inorder traversal.
             * @return iterator++
             */
            void inorder_Next(){

                if (hasRight()) {
                    _current = _current->_rightChild;

                    goDownLeft();
                } else if (isLeft()) {
                    oneUp();
                } else if (isRight()) {
                    do{
                        oneUp();
                    }while(isRight());

                    oneUp();
                }else{
                    this->_current = nullptr;
                }
            }

            /**
             * move current to next position - Preorder traversal.
             * @return iterator++
             */
            void preOrder_Next() {
                if (hasLeft()){
                    oneLeft();
                }else if(hasRight()){
                    oneRight();
                }else{
                    bool prevRight = false;

                    do{
                        prevRight = isRight();
                        oneUp();

                        if (_current == nullptr) {return;}

                    }while(prevRight || !hasRight());

                    oneRight();

                }
            }

            /**
             * move current to next position - Postorder traversal.
             * @return iterator++
             */
            void PostOrder_Next() {

                if(isRoot() || isRight()){
                    oneUp();
                }else if(isLeft()){
                    oneUp();

                    if(hasRight()){
                        oneRight();
                        goDownLeftAndRight();
                    }
                }
            }

            /**
             * increment iterator (inorder, preorder or postorder).
             * @return Iterator after increment
             */
            Iterator& next(){
                switch(_traversal) {
                    case Traversal::InOrder:
                        inorder_Next();
                        break;
                    case Traversal::PreOrder :
                        preOrder_Next();
                        break;
                    case Traversal::PostOrder :
                        PostOrder_Next();
                        break;
                }
                return *this;
            }

        public:
            //       +++ CONSTRUCTOR +++

            /**
             *
             * @param curr start position of iterator
             * @param type traversalType
             */
            explicit Iterator(shared_ptr<Node> curr = nullptr, Traversal type = Traversal::InOrder): _current(curr), _traversal(type) {
                if(_current) {
                    switch (type) {
                        case Traversal::InOrder:
                            goDownLeft();
                            break;
                        case Traversal::PostOrder:
                            goDownLeftAndRight();
                            break;
                        case Traversal::PreOrder:
                            break;
                    }
                }
            }

            //       +++ GETTER +++

            /**
             * @return node hold by iterator.
             */
            shared_ptr<Node> &getCurr(){
                return _current;
            }

            //   +++ OPERATOR OVERLOADING +++

            /**
             * overloading operator *
             * @return value of Iterator current position
             */
            T &operator*(){
                return _current->_val;
            }

            /**
             * overloading operator ->
             * @return value of Iterator current position by reference
             */
            T *operator->() const {
                return &_current->_val;
            }

            /**
             * overloading operator prefix ++ (++i)
             * @return incremented value of iterator
             */
            Iterator& operator++() {
                next();
                return *this;
            }

            /**
             * overloading operator postfix ++ (i++).
             *
             * @return original value of iterator before increment.
             */
            Iterator operator++(int) {
                Iterator temp = *this;
                ++*this;
                return temp;
            }

            /**
             * overloading operator ==.
             * compare 2 iterator by their values.
             *
             * @param other iterator to compare this to
             * @return true if iterators values equal
             */
            bool operator==(const Iterator& other) const {
                return _current == other._current;
            }

            /**
             * overloading operator !=.
             * compare 2 iterator by their values
             *
             * @param other iterator to compare this to
             * @return true if iterators values equal
             */
            bool operator!=(const Iterator& other) const {
                return !(*this==other);
            }

        };

        //      +++ BT CONSTRUCTORS +++

        /**
         * empty constructor.
         */
        BinaryTree():_treeSize(0), _root(nullptr){}
        ~BinaryTree(){}

        /**
         * move constructor.
         * @param other - BT to move here.
         */
        BinaryTree<T>(BinaryTree<T>&& other) noexcept {
            *this = move(other);
        }

        /**
         * aid to copy constructor.
         * iteratively deep copy subtree of given node.
         *
         * @param node root of sub tree.
         */
        void copySubTreeOf(shared_ptr<Node> node){

            if(node->_leftChild) {
                add_left(node->_val, node->_leftChild->_val);
                copySubTreeOf(node->_leftChild);
            }

            if(node->_rightChild) {
                add_right(node->_val, node->_rightChild->_val);
                copySubTreeOf(node->_rightChild);
            }
        }

        /**
         * copy constructor.
         * @param other - BT to copy.
         */
        BinaryTree(BinaryTree<T> &other)
        {
            if(!other._root){
                this->_root = nullptr;
            }else{
                _root = make_shared<Node>(other._root->_val);
                copySubTreeOf(other._root);
            }
        }

        //      +++ GETTERS +++

        /**
         * getter of tree-size.
         *
         * @return size of tree
         */
        unsigned int size(){return this->_treeSize;}

        /**
         * return node struct with value.
         *
         * @param val value of node
         * @return node struct
         */
        shared_ptr<Node> getNode(T val)
        {

            for (auto itr = begin(); itr != end(); itr++){
                if (*itr == val){
                    return itr.getCurr();
                }
            }

            return nullptr;
        }

        //      +++ UPDATE TREE +++

        /**
         * update node depth and max depth of tree
         */
        void updateDepth(shared_ptr<Node> node){
            node->_depth = node->_parent.lock()->_depth+1;
            _maxDepth = std::max(_maxDepth,node->_depth);
        }

        /**
         * add to BT a new root or replace value of existed one.
         *
         * @param val root value
         * @return updated BT
         */
        BinaryTree<T>& add_root(const T &val){
            if (!_root){
                _root = make_shared<Node>(val);
                _root->_depth = 0;
                _treeSize++;
            }else{
                _root->_val = val;
            }
            return *this;
        }

        /**
         * parent = the node with the given parent value.
         * add to parent a new left-child or replace value of existed one.
         *
         * @param parentVal value of new parent node.
         * @param childVal value of new child
         * @return updated BT
         */
        BinaryTree<T>& add_left(const T &parentVal, const T &childVal){
            shared_ptr<Node> parent = getNode(parentVal);
            if (parent == nullptr){
                throw invalid_argument("Error! Parent value not in tree.");
            }

            if (parent->_leftChild == nullptr){
                parent->_leftChild = make_shared<Node>(childVal);
                _treeSize++;
            }else{
                parent->_leftChild->_val = childVal;
            }

            weak_ptr<Node> weakPtr = parent;
            parent->_leftChild->_parent = weakPtr;

            updateDepth(parent->_leftChild);

            parent->_leftChild->_val = childVal;

            return *this;
        }

        /**
         * parent = the node with the given parent value.
         * add to parent a new right-child or replace value of existed one.
         *
         * @param parentVal value of new parent node.
         * @param childVal value of new child
         * @return updated BT
         */
        BinaryTree<T>& add_right(T parentVal, T childVal){
            auto parent = getNode(parentVal);

            if (parent == nullptr){
                throw invalid_argument("Parent not found");
            }

            if ( parent->_rightChild == nullptr){
                parent->_rightChild = make_shared<Node>(childVal);
                _treeSize++;
            }else{
                parent->_rightChild->_val = childVal;
            }

            weak_ptr<Node> weakPtr = parent;
            parent->_rightChild->_parent = weakPtr;

            updateDepth( parent->_rightChild);

            parent->_rightChild->_val = childVal;

            return *this;
        }

        //      +++ INIT ITERATORS +++

        /**
         * @return iterator pointing on the begin position of preorder traversal.
         */
        Iterator begin_preorder() const {
            auto itr = Iterator{_root, Traversal::PreOrder};
            return itr;
        }

        /**
         * @return iterator pointing on the end position of preorder traversal.
         */
        Iterator end_preorder() const {
            return end();
        }

        /**
         * @return iterator pointing on the begin position of inorder traversal.
         */
        Iterator begin_inorder() const {
            auto itr = Iterator{_root, Traversal::InOrder};
            return itr;
        }

        /**
         * @return iterator pointing on the end position of inorder traversal.
         */
        Iterator end_inorder() const {
            return end();
        }

        /**
         * @return iterator pointing on the begin position of postorder traversal.
         */
        Iterator begin_postorder() const {
            auto itr = Iterator{_root, Traversal::PostOrder};
            return itr;
        }

        /**
         * @return iterator pointing on the end position of postorder traversal.
         */
        Iterator end_postorder() const {
            return end();
        }

        /**
         * @return iterator pointing on the begin position of default traversal - inorder.
         */
        Iterator begin() const {
            auto itr = Iterator{_root, Traversal::InOrder};
            return itr;
        }

        /**
         * @return iterator pointing on the end position of default traversal - inorder.
         */
        Iterator end() const {
            return Iterator();
        }

        // +++ OPERATORS OVERLOADING +++

        /**
         * operator overloading =.
         * @param other BT
         * @return updated BT
         */
        BinaryTree<T> &operator=( const BinaryTree<T> &other)
        {
            if(&other == this){return *this;}

            add_root(other._root->_val);

            copySubTreeOf(other._root);

            return *this;
        }

        /**
         * operator overloading =. (move)
         *
         * @param other BT
         * @return updated BT
         */
        BinaryTree &operator=(BinaryTree<T> &&other) noexcept
        {
            *this = move(other);

            return *this;
        }

        /**
         * aid function of << operator overload.
         * build ostream representation of tree.
         *
         * @param prefix string of branches
         * @param node
         * @param isLeft left child flag
         * @param treeStream ostream object
         * @return
         */
        static ostream& buildTreeStream(const std::string& prefix, shared_ptr<Node> node, bool isLeft,  ostream& treeStream)
        {
            if( node != nullptr )
            {
                treeStream << prefix;

                string yellowLeft = "\x1B[93m├──\033[0m";
                string blueRight = "\x1B[34m└──\033[0m";
                treeStream << (isLeft ? yellowLeft : blueRight  );

                treeStream << "\033[3;43;30m(" <<  node->_val <<  ")\033[0m"<<endl;

                string yellowBranch = "\x1B[93m│   \033[0m";
                string blueBranch = "\x1B[34m│   \033[0m";
                buildTreeStream( prefix + (isLeft ? yellowBranch : "    "), node->_leftChild, true, treeStream);
                buildTreeStream( prefix + (isLeft ? blueBranch: "    "), node->_rightChild, false, treeStream);
            }
            return treeStream;
        }
        static ostream& buildTreeStream(shared_ptr<Node> node, ostream& treeStream)
        {
            return buildTreeStream("", node, false, treeStream)<<endl;
        }

        /**
         * operator overloading of <<.
         *
         * @param out ostream object
         * @param BT binary tree
         * @return ostream of tree
         */
        friend ostream &operator<<(ostream &out, const BinaryTree<T> &BT){
            out<<endl;

            buildTreeStream(BT._root, out);

            out <<"                  ----BINARY TREE----"<<endl<<endl<<"* Preorder  -> ";

            for (auto it=BT.begin_preorder(); it!=BT.end_preorder(); ++it) {
                out << (*it) << " " ;
            }
            out <<endl<<"* Inorder   -> ";
            for (auto it=BT.begin_inorder(); it!=BT.end_inorder(); ++it) {
                out << (*it) << " " ;
            }
            out <<endl<<"* Postorder -> ";
            for (auto it=BT.begin_postorder(); it!=BT.end_postorder(); ++it) {
                out << (*it) << " " ;
            }
            return out;
        }
    };
}
