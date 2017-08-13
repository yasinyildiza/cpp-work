#ifndef SIGNIN_H
#define SIGNIN_H

#include <Wt/WContainerWidget>
#include <Wt/WBreak>
#include <Wt/WLabel>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>

#include "labeledinput.h"
#include "page.h"

class SigninWidget : public PageWidget {
private:
public:
	LabeledInputWidget *username;
	LabeledInputWidget *password;

    Wt::WPushButton *button_signin;
    Wt::WPushButton *button_signup;
    
    SigninWidget(Wt::WContainerWidget *container);
};

#endif /* SIGNIN_H */
