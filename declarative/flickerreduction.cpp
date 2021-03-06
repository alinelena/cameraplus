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

#include "flickerreduction.h"

FlickerReduction::FlickerReduction(QtCamDevice *dev, QObject *parent) :
  Capability(parent),
  m_fr(new QtCamFlickerReduction(dev, this)) {

  setCapability(m_fr);

  QObject::connect(m_fr, SIGNAL(valueChanged()), this, SIGNAL(valueChanged()));
}

FlickerReduction::~FlickerReduction() {
  if (m_fr) {
    delete m_fr;
    m_fr = 0;
  }
}

FlickerReduction::FlickerReductionMode FlickerReduction::value() {
  return m_fr ? (FlickerReductionMode)m_fr->value() : FlickerReduction::Auto;
}

void FlickerReduction::setValue(const FlickerReduction::FlickerReductionMode& mode) {
  if (m_fr) {
    m_fr->setValue((QtCamFlickerReduction::FlickerReductionMode)mode);
  }
}

void FlickerReduction::prepareForDeviceChange() {
  if (m_fr) {
    delete m_fr;
    m_fr = 0;
  }
}
