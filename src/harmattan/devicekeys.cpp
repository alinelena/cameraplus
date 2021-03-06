/*!
 * This file is part of CameraPlus.
 *
 * Copyright (C) 2012-2014 Mohammed Sameer <msameer@foolab.org>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "devicekeys.h"
#include <QDebug>

DeviceKeys::DeviceKeys(QObject *parent) :
  QObject(parent),
  m_keys(0),
  m_repeating(true) {

}

DeviceKeys::~DeviceKeys() {
  setActive(false);
}

bool DeviceKeys::isActive() const {
  return m_keys != 0;
}

void DeviceKeys::setActive(bool active) {
  if (active == isActive()) {
    return;
  }

  if (!active) {
    m_keys->deleteLater();
    m_keys = 0;
    m_stats.clear();
  }
  else {
    m_keys = new MeeGo::QmKeys(this);
    QObject::connect(m_keys, SIGNAL(keyEvent(MeeGo::QmKeys::Key, MeeGo::QmKeys::State)),
		     this, SLOT(keyEvent(MeeGo::QmKeys::Key, MeeGo::QmKeys::State)));
  }

  emit activeChanged();
}

void DeviceKeys::keyEvent(MeeGo::QmKeys::Key key, MeeGo::QmKeys::State state) {
  if (!setStats(key, state)) {
    return;
  }

  if (key == MeeGo::QmKeys::VolumeUp) {
    if (state == MeeGo::QmKeys::KeyUp) {
      emit volumeUpReleased();
    }
    else if (state == MeeGo::QmKeys::KeyDown) {
      emit volumeUpPressed();
    }
  }
  else if (key == MeeGo::QmKeys::VolumeDown) {
    if (state == MeeGo::QmKeys::KeyUp) {
      emit volumeDownReleased();
    }
    else if (state == MeeGo::QmKeys::KeyDown) {
      emit volumeDownPressed();
    }
  }
}

bool DeviceKeys::setStats(MeeGo::QmKeys::Key key, MeeGo::QmKeys::State state) {
  if (m_repeating) {
    return true;
  }

  if (!m_stats.contains(key)) {
    m_stats.insert(key, state);
    return true;
  }

  if (m_stats[key] != state) {
    m_stats[key] = state;
    return true;
  }

  return false;
}

bool DeviceKeys::isRepeating() {
  return m_repeating;
}

void DeviceKeys::doRepeat(bool repeat) {
  if (repeat != m_repeating) {
    m_repeating = repeat;
    emit repeatChanged();
  }
}
