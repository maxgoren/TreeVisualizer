/*
MIT License

Copyright (c) 2023 Max Goren

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef TREEDRAW_HPP
#define TREEDRAW_HPP
#include <vector>
#include <limits>
#include <iostream>
#include <queue>
#include <SFML/Graphics.hpp>
#include "treenode.hpp"
#include <unordered_map>
using namespace std;

enum TREETYPE {
    AVLT,
    BST,
    REDBLACK,
};

template <class K, class V>
class TreeDraw {
    private:
        TREETYPE treeType;
        using nodeptr = rbnode<K,V>*;
        int X;
        int Y;
        nodeptr nilmarker;
        nodeptr head;
        unordered_map<K, pair<int,int>> coordsAndKeys;
        vector<sf::CircleShape> nodes;
        using sfLine = sf::Vertex*;
        vector<sfLine> edges;
        void mark(nodeptr h) {
            Y++;
            if (h != nilmarker) {
                mark(h->left);
                sf::CircleShape tmp(13);
                tmp.setPosition(((++X)*22), (Y*2)*22);
                if (h == head) {
                    tmp.setOutlineColor(sf::Color::Blue);
                    tmp.setOutlineThickness(5);
                }
                switch (treeType) {
                    case AVLT:       tmp.setFillColor(sf::Color::Blue);
                                    break;
                    case BST:       tmp.setFillColor(sf::Color::Green);
                                    break;
                    case REDBLACK:
                                    if (h->color) tmp.setFillColor(sf::Color(255,0,0));
                                    else tmp.setFillColor(sf::Color::Black);
                                    break;
                    default:
                                    tmp.setFillColor(sf::Color::Black);
                                    break;
                
                }
                nodes.push_back(tmp);
                coordsAndKeys[h->key] = make_pair((X)*22,(Y*2)*22);
                mark(h->right);
            }
            Y--;
        }
        void markEdges(nodeptr h) {
            queue<nodeptr> fq;
            fq.push(h);
            while (!fq.empty()) {
                h = fq.front();
                fq.pop();
                if (h != nilmarker) {
                    auto v = coordsAndKeys[h->key];
                    if (h->left != nilmarker) {
                        auto u = coordsAndKeys[h->left->key];
                        sfLine line = new sf::Vertex[2] { 
                            sf::Vertex(sf::Vector2f(v.first+5, v.second+5)), sf::Vertex(sf::Vector2f(u.first+5, u.second+5))
                        };
                        line[0].color = sf::Color::Black;
                        line[1].color = sf::Color::Black;
                        edges.push_back(line);
                    }
                    if (h->right != nilmarker) {
                        auto u = coordsAndKeys[h->right->key];
                        sfLine line = new sf::Vertex[2] { 
                            sf::Vertex(sf::Vector2f(v.first, v.second)), sf::Vertex(sf::Vector2f(u.first, u.second))
                        };   
                        line[0].color = sf::Color::Black;
                        line[1].color = sf::Color::Black;                   
                        edges.push_back(line);
                    }
                    fq.push(h->left);
                    fq.push(h->right);
                }
            }
        }
    public:
        TreeDraw() {
            
        }
        void mark(rbnode<K,V>* root, rbnode<K,V>* nil, TREETYPE treetype) {
            treeType = treetype;
            nilmarker = nil;
            head = root;
            X += 2;
            mark(root);
            markEdges(root);
        }
        void drawTree() {
            sf::RenderWindow window(sf::VideoMode(1790,500), "Self-Balanacing Binary Search Trees");
            while (window.isOpen()) {
                sf::Event event;
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        sf::Image screen = window.capture();
                        screen.saveToFile("tree.jpg");
                        window.close();
                    }
                }
                window.clear(sf::Color::White);
                for (auto edge: edges) {
                    window.draw(edge,2,sf::Lines);
                }
                for (auto node : nodes) {
                    window.draw(node);
                }
                window.display();
            }
        }
};

#endif