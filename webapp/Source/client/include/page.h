#ifndef PAGE_H
#define PAGE_H

#include <Wt/WContainerWidget>
#include <Wt/WBreak>
#include <Wt/WLabel>

class PageWidget : public Wt::WContainerWidget {
protected:
	Wt::WLabel *title_label;
public:
    PageWidget(std::string title_text, Wt::WContainerWidget *container);
};

#endif /* PAGE_H */
