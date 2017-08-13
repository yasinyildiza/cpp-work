#include "../include/signin.h"

SigninWidget::SigninWidget(Wt::WContainerWidget *container):PageWidget("Sign in", container) {
    username = new LabeledInputWidget("username: ", this);
    password = new LabeledInputWidget("password: ", this);

    button_signin = new Wt::WPushButton("Sign in", this);
    button_signup = new Wt::WPushButton("Sign up", this);

    username->lineedit->setFocus();
}
