#include "qtcamvideosettings.h"

class QtCamVideoSettingsPrivate {
public:
  QString id;
  QString name;
  QSize capture;
  QSize preview;
  int numerator;
  int denominator;
};

QtCamVideoSettings::QtCamVideoSettings(const QString& id, const QString& name,
				       const QSize& capture, const QSize& preview,
				       int numerator, int denominator) :
  d_ptr(new QtCamVideoSettingsPrivate) {

  d_ptr->id = id;
  d_ptr->name = name;
  d_ptr->capture = capture;
  d_ptr->preview = preview;
  d_ptr->numerator = numerator;
  d_ptr->denominator = denominator;
}

QtCamVideoSettings::QtCamVideoSettings(const QtCamVideoSettings& other) :
  d_ptr(new QtCamVideoSettingsPrivate) {

  d_ptr->id = other.d_ptr->id;
  d_ptr->name = other.d_ptr->name;
  d_ptr->capture = other.d_ptr->capture;
  d_ptr->preview = other.d_ptr->preview;
  d_ptr->numerator = other.d_ptr->numerator;
  d_ptr->denominator = other.d_ptr->denominator;
}

QtCamVideoSettings::~QtCamVideoSettings() {
  delete d_ptr;
}

QtCamVideoSettings& QtCamVideoSettings::operator=(const QtCamVideoSettings&
								other) {
  d_ptr->id = other.d_ptr->id;
  d_ptr->name = other.d_ptr->name;
  d_ptr->capture = other.d_ptr->capture;
  d_ptr->preview = other.d_ptr->preview;
  d_ptr->numerator = other.d_ptr->numerator;
  d_ptr->denominator = other.d_ptr->denominator;

  return *this;
}

QString QtCamVideoSettings::id() const {
  return d_ptr->id;
}

QString QtCamVideoSettings::name() const {
  return d_ptr->name;
}

QSize QtCamVideoSettings::captureResolution() const {
  return d_ptr->capture;
}

QSize QtCamVideoSettings::previewResolution() const {
  return d_ptr->preview;
}

QPair<int, int> QtCamVideoSettings::frameRate() const {
  return qMakePair<int, int>(d_ptr->numerator, d_ptr->denominator);
}
