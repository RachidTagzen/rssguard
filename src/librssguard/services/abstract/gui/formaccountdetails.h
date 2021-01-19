// For license of this file, see <project-root-folder>/LICENSE.md.

#ifndef FORMACCOUNTDETAILS_H
#define FORMACCOUNTDETAILS_H

#include <QDialog>

#include "ui_formaccountdetails.h"

class ServiceRoot;

class FormAccountDetails : public QDialog {
  Q_OBJECT

  public:
    explicit FormAccountDetails(const QIcon& icon, QWidget* parent = nullptr);

    template<class T>
    T* addEditAccount(T* account_to_edit = nullptr);

    template<class T>
    T* account() const;

  protected slots:

    // Applies changes.
    // NOTE: This must be reimplemented in subclasses. Also this
    // base implementation must be called first.
    virtual void apply();

  protected:
    void activateTab(int index);
    void clearTabs();
    void insertCustomTab(QWidget* custom_tab, const QString& title, int index);

    // Sets the account which will be edited.
    // NOTE: This must be reimplemented in subclasses. Also this
    // base implementation must be called first.
    virtual void setEditableAccount(ServiceRoot* editable_account);

  private:
    void createConnections();

  protected:
    Ui::FormAccountDetails m_ui;
    ServiceRoot* m_account;
};

template<class T>
inline T* FormAccountDetails::addEditAccount(T* account_to_edit) {
  if (account_to_edit == nullptr) {
    setWindowTitle(tr("Add new account"));
  }
  else {
    setEditableAccount(static_cast<ServiceRoot*>(account_to_edit));
  }

  exec();
  return account<T>();
}

template<class T>
inline T* FormAccountDetails::account() const {
  return qobject_cast<T*>(m_account);
}

#endif // FORMACCOUNTDETAILS_H