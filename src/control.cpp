#include "control.h"

Control::Control()
{
	//curr = nullptr;
	main_menu_list = createMainMenuList();
	printList(main_menu_list);
}

int Control::testFunc(const std::string& card)
{
	snd_ctl_t *ctl;

	if (snd_ctl_open(&ctl, card.c_str(), 0) < 0) {
		std::cerr << "failed to open this card: " << card << std::endl;
		snd_ctl_close(ctl);
		return -1;
	}
	else {
		std::cout << "opened: " << card << std::endl;
		snd_ctl_close(ctl);
		return 0;
	}
}

Node* Control::insertAtEnd(Node* head, inputType type)
{
	Node* newNode = new Node(type);

	if (!head) {
		newNode->next = newNode->prev = newNode;
		head = newNode;
	} else {
		Node* last = head->prev;

		newNode->next = head;
		newNode->prev = last;
		last->next = newNode;
		head->prev = newNode;
	}
	return head;
}

Node* Control::createMainMenuList()
{
	Node* head = nullptr;
	for (inputType i = inputType::airplay; i <= inputType::internet_radio; ++(int&)i){
		head = insertAtEnd(head, i);
	};
	return head;
}

void Control::printList(Node* head)
{
	if (!head) return;

	Node* curr = head;

	do {
		std::cout << curr->data << std::endl;
		curr = curr->next;
	} while (curr != head);
}

Node::Node(inputType type)
{
	data = type;
	next = nullptr;
	prev = nullptr;
}

int Control::setControlValue(const std::string& card, const std::string& controlName, long value)
{
	snd_ctl_t *ctl;
	snd_ctl_elem_id_t *id;
	snd_ctl_elem_value_t *control;

	if (snd_ctl_open(&ctl, card.c_str(), 0) < 0) {
		std::cerr << "Failed to open card: " << card << std::endl;
		return -1;
	}

	snd_ctl_elem_id_malloc(&id);
	snd_ctl_elem_id_set_interface(id, SND_CTL_ELEM_IFACE_MIXER);
	snd_ctl_elem_id_set_name(id, controlName.c_str());

	snd_ctl_elem_value_malloc(&control);
	snd_ctl_elem_value_set_id(control, id);

	if (snd_ctl_elem_read(ctl, control) < 0) {
		std::cerr << "Failed to read control element: " << controlName << std::endl;
		snd_ctl_close(ctl);
		return -1;
	}

	snd_ctl_elem_value_set_integer(control, 0, value);

	if (snd_ctl_elem_write(ctl, control) < 0) {
		std::cerr << "Failed to write value to control: " << controlName << std::endl;
		snd_ctl_close(ctl);
		return -1;
	}

	std::cout << "Set: " << controlName << " to " << value << std::endl;

	snd_ctl_elem_id_free(id);
	snd_ctl_elem_value_free(control);
	snd_ctl_close(ctl);

	return 0;
}






