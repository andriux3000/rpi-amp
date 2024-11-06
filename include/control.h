#ifndef CONTROL_H
#define CONTROL_H

#include <stdio.h>
#include <alsa/asoundlib.h>
#include <iostream>
#include <string>

enum inputType {
	airplay,
	bluetooth,
	aux_first,
	aux_second,
	internet_radio,
};

class Node
{
	public:
		inputType data;
		Node* next;
		Node* prev;

		Node(inputType type);
};

class Control
{
	int current_screen, screen_id, input_id;
	Node *main_menu_list;
	Node *curr;
	Node *head;

	int setControlValue(const std::string& card, const std::string& controlName, long value);
	void updateScreen(int screen_id = 0);
	void printList(Node* head);

	Node* insertAtEnd(Node* head, inputType type);
	Node* createMainMenuList();

	public:
		Control();
		int testFunc(const std::string& card);
};

#endif
