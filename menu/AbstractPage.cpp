#include "AbstractPage.h"

const string AbstractPage::getInstructions() {
	return ("use arrows for navigation: \nleft and right for moving between folders on the same level," \
		"\n down and up for moving between layers" \
		"\n enter to edit a value" \
		"\n ESC to undo changes in value"
		"\n and arrows for editing value's digits" );
}

void AbstractPage::showPage() {
	system("cls");
	cout << getInstructions << endl;
	cout << getContent() << endl;
}