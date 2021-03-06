/*
 * Copyright (C) 2009-2015,
 * Intelligent Robotics and Intelligent Systems (IRIS) Lab
 * CAMBADA robotic soccer team – http://robotica.ua.pt/CAMBADA/
 * University of Aveiro, Portugal
 *
 * This file is part of the CAMBADA BASESTATION
 *
 * CAMBADA BASESTATION is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * CAMBADA BASESTATION is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this package.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __FULLINFOWINDOW_H
#define __FULLINFOWINDOW_H


#include "ui_FullInfoWindow_WG.h"
#include <QtGui>
#include "Robot.h"

class FInfoWind : public QMainWindow , public Ui::FullInfoWindow_WG
{
	Q_OBJECT

public:
	FInfoWind(QMainWindow *parent =0);
	~FInfoWind();
	void get_info_pointer( DB_Robot_Info * rw);

private:
	bool fullscreenflag;
	QMainWindow *fullinfowindow;
	DB_Robot_Info *Robots_info;


public slots:
	void WindowFullScreenMode (void);
	void ChangeTextSize(int size);

protected:
	bool eventFilter(QObject *obj, QEvent *event);

};

#endif
