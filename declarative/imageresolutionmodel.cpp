/*!
 * This file is part of CameraPlus.
 *
 * Copyright (C) 2012-2013 Mohammed Sameer <msameer@foolab.org>
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

#include "imageresolutionmodel.h"
#include "qtcamimagesettings.h"
#include <QDebug>

ImageResolutionModel::ImageResolutionModel(QtCamImageSettings *settings, QObject *parent) :
  QAbstractListModel(parent), m_settings(settings) {

  m_roles[IdRole] = "resolutionId";
  m_roles[NameRole] = "resolutionName";
  m_roles[CaptureRole] = "captureResolution";
  m_roles[PreviewRole] = "previewResolution";
  m_roles[FpsRole] = "frameRate";
  m_roles[NightFpsRole] = "nightFrameRate";
  m_roles[MegaPixelsRole] = "megaPixels";
  m_roles[AspectRatioRole] = "resolutionAspectRatio";

  m_resolutions = m_settings->resolutions(m_aspectRatio);
}

ImageResolutionModel::~ImageResolutionModel() {
  m_settings = 0;
}

int ImageResolutionModel::rowCount(const QModelIndex& parent) const {
  if (!parent.isValid()) {
    return m_resolutions.size();
  }

  return 0;
}

QVariant ImageResolutionModel::data(const QModelIndex& index, int role) const {
  if (index.row() < 0 || index.row() >= m_resolutions.size()) {
    return QVariant();
  }

  const QtCamImageResolution& res = m_resolutions[index.row()];

  switch (role) {
  case IdRole:
    return res.id();

  case NameRole:
    return res.name();

  case CaptureRole:
    return res.captureResolution();

  case PreviewRole:
    return res.previewResolution();

  case FpsRole:
    return res.frameRate();

  case NightFpsRole:
    return res.nightFrameRate();

  case MegaPixelsRole:
    return res.megaPixels();

  case AspectRatioRole:
    return res.aspectRatio();

  default:
    return QVariant();
  }
}

QString ImageResolutionModel::aspectRatio() const {
  return m_aspectRatio;
}

void ImageResolutionModel::setAspectRatio(const QString& aspectRatio) {
  if (aspectRatio != m_aspectRatio) {

    m_aspectRatio = aspectRatio;

    beginResetModel();

    m_resolutions = m_settings->resolutions(m_aspectRatio);

    endResetModel();

    emit aspectRatioChanged();
  }
}

QHash<int, QByteArray> ImageResolutionModel::roleNames() const {
  return m_roles;
}
