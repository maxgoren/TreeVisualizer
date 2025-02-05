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
        int XSCALER = 12;
        int YSCALER = 12;
        int NODESIZE = 12;
        TREETYPE treeType;
        using nodeptr = rbnode<K,V>*;
        int X;
        int Y;
        nodeptr nilmarker;
        nodeptr head;
        unordered_map<K, pair<int,int>> coordsAndKeys;
        vector<sf::CircleShape> nodes;
        vector<sf::Text> labels;
        using sfLine = sf::Vertex*;
        vector<sfLine> edges;
        int id;
        void mark(nodeptr h) {
            Y++;
            if (h != nilmarker) {
                mark(h->left);
                h->id = ++id;
                sf::CircleShape tmp(NODESIZE);
                tmp.setPosition(((++X)*XSCALER), (Y*2)*YSCALER);
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
                int nx = (X)*XSCALER;
                int ny = (Y*2)*YSCALER;
                coordsAndKeys[h->id] = make_pair(nx,ny);
                sf::Text label;
                label.setFont(font);
                string _str = to_string(h->info.key());
                label.setString(_str);
                label.setCharacterSize(18);
                if (treeType == REDBLACK) {
                   if (h->color == true) {
                        label.setColor(sf::Color::Black);
                   } else {
                        label.setColor(sf::Color::White);
                   }

                } else label.setColor(sf::Color::Black);
                label.setOrigin(0,0);
                label.setPosition(nx+2, ny);
                labels.push_back(label);
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
                    auto v = coordsAndKeys[h->id];
                    if (h->left != nilmarker) {
                        auto u = coordsAndKeys[h->left->id];
                        int offy = 6;
                        int offx = 7;
                        if (v.first < u.first) offx *= -1;
                        sfLine line = new sf::Vertex[2] {
                            sf::Vertex(sf::Vector2f(v.first+offx, v.second+offy)), sf::Vertex(sf::Vector2f(u.first+offx, u.second+offy))
                        };
                        line[0].color = sf::Color::Black;
                        line[1].color = sf::Color::Black;
                        edges.push_back(line);
                    }
                    if (h->right != nilmarker) {
                        auto u = coordsAndKeys[h->right->id];
                        int offy = 6;
                        int offx = 6;
                        if (v.first > u.first) offx *= -1;
                        sfLine line = new sf::Vertex[2] { 
                            sf::Vertex(sf::Vector2f(v.first+offx, v.second+offy)), sf::Vertex(sf::Vector2f(u.first+offx, u.second+offy))
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
        int height(rbnode<K,V>* h) {
            if (h == nullptr) return 0;
            return 1 + max(height(h->left), height(h->right));
        }
        sf::Font font;
        int treenum;
        int row;
    public:
        TreeDraw() {
            treenum = 0;
            id = 0;
            row = 1;
        }
        void mark(rbnode<K,V>* root, rbnode<K,V>* nil, TREETYPE treetype) {
            treenum++;
            treeType = treetype;
            nilmarker = nil;
            head = root;
            X += 2;
             if (X > 125) {
                    X = 2;
                    Y = (height(head) + 1) * row;
                    row++;
            }
            mark(root);
            markEdges(root);
        }
        void reset() {
            id = 0;
            X = 0;
            Y = 0;
            nodes.clear();
            edges.clear();
            labels.clear();
            coordsAndKeys.clear();
        }
        void drawTree() {
            sf::RenderWindow window(sf::VideoMode(1750,700), "Self-Balanacing Binary Search Trees");
            window.setVerticalSyncEnabled(true); //little lion so rough
            if (!font.loadFromFile("./font.ttf")) {
                std::cerr<<"Nah dog, couldnt open that font my G."<<endl;
                return;
            }
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
                for (auto label : labels) {
                    window.draw(label);
                }
                window.display();
            }
        }
};



#endif
