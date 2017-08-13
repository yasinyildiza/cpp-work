#include "../include/page.h"

PageWidget::PageWidget(std::string title_text, Wt::WContainerWidget *container):Wt::WContainerWidget(container) {
	title_label = new Wt::WLabel(title_text, this);
	addWidget(new Wt::WBreak());
	addWidget(new Wt::WBreak());
}
