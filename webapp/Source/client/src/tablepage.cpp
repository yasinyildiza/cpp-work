#include "../include/tablepage.h"

TablePageWidget::TablePageWidget(std::string title_text, Wt::WContainerWidget *container):PageWidget(title_text, container) {
	row_counter = 0;
    table = new Wt::WTable(this);
}

void TablePageWidget::reset() {
	row_counter = 0;
	table->clear();
    table->setHeaderCount(1);
    add_header();
}
