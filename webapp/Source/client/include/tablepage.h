#ifndef TABLE_PAGE_H
#define TABLE_PAGE_H

#include <Wt/WContainerWidget>
#include <Wt/WBreak>
#include <Wt/WLabel>
#include <Wt/WTable>

#include "page.h"

class TablePageWidget : public PageWidget {
protected:
	int row_counter;
public:
	Wt::WTable *table;

    TablePageWidget(std::string title_text, Wt::WContainerWidget *container);

    virtual void reset();
    virtual void add_header() = 0;
};

#endif /* TABLE_PAGE_H */
