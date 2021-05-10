#pragma once

typedef void (*ListenerCallBack)(void);

template <typename T>
class ToolboxListener
{
  private:
  T m_oldVariableValue;
  ListenerCallBack m_callback;

  public:
  T listenedVariable;

  ToolboxListener(T defaultValue, ListenerCallBack callback);
  void update(void);
};

template <typename T>
ToolboxListener<T>::ToolboxListener(T defaultValue, ListenerCallBack callback)
{
  listenedVariable = defaultValue;
  m_oldVariableValue = defaultValue;
  m_callback = callback;
}

template <typename T>
void ToolboxListener<T>::update(void)
{
  if (listenedVariable != m_oldVariableValue)
  {
    m_oldVariableValue = listenedVariable;
    m_callback();
  }
}
