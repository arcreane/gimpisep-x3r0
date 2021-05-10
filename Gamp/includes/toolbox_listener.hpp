/**
 * @file toolbox_listener.hpp
 * @author Yohann Martin
 * @author Mathias Géroudet
 * @author Timothee Pionnier
 * @author Oscar Mc Auliffe
 * @brief The file contains a class to listen to the changes of a variable.
 * @version 1.0
 * @date 2021-05-10
 *
 * @copyright Copyright (c) Gamp Project 2021
 */

#pragma once

/**
 * @brief A callback called when the value of the listened variable change.
 */
typedef void (*ListenerCallBack)(void);

/**
 * @brief A class allowing to listen to the changes of a variable and to call
 * a callback function when the value of this variable changes.
 */
template <typename T>
class ToolboxListener
{
  private:
  /**
   * @brief The old value of the listened variable.
   */
  T m_oldVariableValue;

  /**
   * The callback to call when the value of the listened variable change.
   */
  ListenerCallBack m_callback;

  public:
  /**
   * @brief The variable to listen.
   */
  T listenedVariable;

  /**
   * @brief Construct a new listener with a default value for the listened
   * variable and the callback the call when the value of the variable change.
   *
   * @param defaultValue The first (default) value of the listened variable.
   * @param callback The callback function to call when the value of the
   * listened variable change.
   */
  ToolboxListener(T defaultValue, ListenerCallBack callback);

  /**
   * This method check for any change in the listened variable and call the
   * callback function if the value has changed.
   */
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
