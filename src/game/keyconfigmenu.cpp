// This file is part of Dust Racing 2D.
// Copyright (C) 2013 Jussi Lind <jussi.lind@iki.fi>
//
// Dust Racing 2D is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// Dust Racing 2D is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Dust Racing 2D. If not, see <http://www.gnu.org/licenses/>.

#include "keyconfigmenu.hpp"
#include "eventhandler.hpp"
#include "inputhandler.hpp"
#include "game.hpp"
#include "textmenuitemview.hpp"

#include <MenuItem>
#include <MenuItemAction>
#include <MenuItemView>
#include <MenuManager>

#include <MCAssetManager>
#include <MCLogger>
#include <MCTextureText>
#include <MCTextureFont>

#include <QObject> // For QObject::tr()

//! "Menu" to select a key.
class PressKeyMenu : public SurfaceMenu
{
public:

    //! Constructor.
    PressKeyMenu(std::string id, int width, int height);

    //! \reimp
    virtual void render();

private:

    std::string m_text;
};

PressKeyMenu::PressKeyMenu(std::string id, int width, int height)
: SurfaceMenu("helpBack", id, width, height, MTFH::Menu::MS_HORIZONTAL_LIST)
, m_text(QObject::tr("Press a key..").toStdString())
{
}

void PressKeyMenu::render()
{
    SurfaceMenu::render();

    MCTextureText text(m_text);
    MCTextureFont defaultMonospace = MCAssetManager::textureFontManager().font("default");

    const int shadowY = -2;
    const int shadowX =  2;

    text.setColor(MCGLColor(0.25, 0.75, 1.0, 1.0));
    text.setGlyphSize(20, 20);
    text.setShadowOffset(shadowX, shadowY);

    text.render(width() / 2 - text.width() / 2 + 20, height() / 2 + 60, nullptr, defaultMonospace);
}

static const char * PRESS_KEY_MENU_ID = "pressKeyMenu";

KeyConfigMenu::KeyConfigMenu(std::string id, int width, int height)
: SurfaceMenu("helpBack", id, width, height, Menu::MS_VERTICAL_LIST)
, m_pressKeyMenu(new PressKeyMenu(PRESS_KEY_MENU_ID, width, height))
{
    MTFH::MenuManager::instance().addMenu(*m_pressKeyMenu);

    addPlayerTwoConfig(width, height);
    addPlayerOneConfig(width, height);
}

void KeyConfigMenu::addPlayerOneConfig(int width, int height)
{
    const int itemHeight = height / 10;

    using MTFH::MenuItem;
    using MTFH::MenuManager;

    MenuItem * playerOneAccelerate =
        new MenuItem(width, itemHeight, QObject::tr("Player One Accelerate").toStdString());
    playerOneAccelerate->setView(new TextMenuItemView(20, *playerOneAccelerate), true);
    playerOneAccelerate->setAction(
        []()
        {
            Game::instance().eventHandler().enableCaptureMode(InputHandler::IA_UP, 0);
            MenuManager::instance().pushMenu(PRESS_KEY_MENU_ID);
        });

    MenuItem * playerOneBrake =
        new MenuItem(width, itemHeight, QObject::tr("Player One Brake").toStdString());
    playerOneBrake->setView(new TextMenuItemView(20, *playerOneBrake), true);
    playerOneBrake->setAction(
        []()
        {
            Game::instance().eventHandler().enableCaptureMode(InputHandler::IA_DOWN, 0);
            MenuManager::instance().pushMenu(PRESS_KEY_MENU_ID);
        });

    MenuItem * playerOneTurnLeft =
        new MenuItem(width, itemHeight, QObject::tr("Player One Turn Left").toStdString());
    playerOneTurnLeft->setView(new TextMenuItemView(20, *playerOneTurnLeft), true);
    playerOneTurnLeft->setAction(
        []()
        {
            Game::instance().eventHandler().enableCaptureMode(InputHandler::IA_LEFT, 0);
            MenuManager::instance().pushMenu(PRESS_KEY_MENU_ID);
        });

    MenuItem * playerOneTurnRight =
        new MenuItem(width, itemHeight, QObject::tr("Player One Turn Right").toStdString());
    playerOneTurnRight->setView(new TextMenuItemView(20, *playerOneTurnRight), true);
    playerOneTurnRight->setAction(
        []()
        {
            Game::instance().eventHandler().enableCaptureMode(InputHandler::IA_RIGHT, 0);
            MenuManager::instance().pushMenu(PRESS_KEY_MENU_ID);
        });

    addItem(*playerOneBrake,      true);
    addItem(*playerOneAccelerate, true);
    addItem(*playerOneTurnRight,  true);
    addItem(*playerOneTurnLeft,   true);
}

void KeyConfigMenu::addPlayerTwoConfig(int width, int height)
{
    const int itemHeight = height / 10;

    using MTFH::MenuItem;
    using MTFH::MenuManager;

    MenuItem * playerTwoAccelerate =
        new MenuItem(width, itemHeight, QObject::tr("Player Two Accelerate").toStdString());
    playerTwoAccelerate->setView(new TextMenuItemView(20, *playerTwoAccelerate), true);
    playerTwoAccelerate->setAction(
        []()
        {
            Game::instance().eventHandler().enableCaptureMode(InputHandler::IA_UP, 1);
            MenuManager::instance().pushMenu(PRESS_KEY_MENU_ID);
        });

    MenuItem * playerTwoBrake =
        new MenuItem(width, itemHeight, QObject::tr("Player Two Brake").toStdString());
    playerTwoBrake->setView(new TextMenuItemView(20, *playerTwoBrake), true);
    playerTwoBrake->setAction(
        []()
        {
            Game::instance().eventHandler().enableCaptureMode(InputHandler::IA_DOWN, 1);
            MenuManager::instance().pushMenu(PRESS_KEY_MENU_ID);
         });

    MenuItem * playerTwoTurnLeft =
        new MenuItem(width, itemHeight, QObject::tr("Player Two Turn Left").toStdString());
    playerTwoTurnLeft->setView(new TextMenuItemView(20, *playerTwoTurnLeft), true);
    playerTwoTurnLeft->setAction(
        []()
        {
            Game::instance().eventHandler().enableCaptureMode(InputHandler::IA_LEFT, 1);
            MenuManager::instance().pushMenu(PRESS_KEY_MENU_ID);
        });

    MenuItem * playerTwoTurnRight =
        new MenuItem(width, itemHeight, QObject::tr("Player Two Turn Right").toStdString());
    playerTwoTurnRight->setView(new TextMenuItemView(20, *playerTwoTurnRight), true);
    playerTwoTurnRight->setAction(
        []()
        {
            Game::instance().eventHandler().enableCaptureMode(InputHandler::IA_RIGHT, 1);
            MenuManager::instance().pushMenu(PRESS_KEY_MENU_ID);
        });

    addItem(*playerTwoBrake,      true);
    addItem(*playerTwoAccelerate, true);
    addItem(*playerTwoTurnRight,  true);
    addItem(*playerTwoTurnLeft,   true);
}

KeyConfigMenu::~KeyConfigMenu()
{
    delete m_pressKeyMenu;
}
