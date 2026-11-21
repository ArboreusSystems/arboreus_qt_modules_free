// ----------------------------------------------------------
/*!
	\class APrivateBuffer
	\title
	\brief Template file files/cppheader/file.h

	\list
	\li @notice Template file classes/file.h
	\li @copyright Arboreus (http://arboreus.systems)
	\li @author Alexandr Kirilov (http://alexandr.kirilov.me)
	\li @created 21/11/2026 at 19:40:04
	\endlist
*/
// ----------------------------------------------------------

// Class header
#include "aprivatebuffer.h"

// Namespace
using namespace ARB;


// -----------
/*!
	\fn

	Doc.
*/

APrivateBuffer::APrivateBuffer(qsizetype inCapacity) {

	pStorageData = std::make_shared<APrivateBufferStorage>(inCapacity);
}


// -----------
/*!
	\fn

	Doc.
*/

APrivateBuffer::APrivateBuffer(QByteArray&& inByteArray) : APrivateBuffer(inByteArray.size()) {

	if (!inByteArray.isEmpty()) std::memcpy(pStorageData->mData(),inByteArray.constData(),size_t(inByteArray.size()));
	pStorageData->mSizeSet(inByteArray.size());

	mWipe(inByteArray);
}


// -----------
/*!
	\fn

	Doc.
*/

APrivateBuffer::APrivateBuffer(QString&& inString) {

	QStringEncoder oEncoder(QStringEncoder::Utf8,QStringEncoder::Flag::Stateless);
	pStorageData = std::make_shared<APrivateBufferStorage>(oEncoder.requiredSpace(inString.size()));
	if (!inString.isEmpty()) {
		char* oEncoded = oEncoder.appendToBuffer(pStorageData->mData(),inString);
		pStorageData->mSizeSet(oEncoded - pStorageData->mData());
	}

	mWipe(inString);
}


// -----------
/*!
	\fn

	Doc.
*/

APrivateBuffer::APrivateBuffer(QVariant&& inVariant) {

	if (auto* oString = get_if<QString>(&inVariant)) {
		*this = APrivateBuffer(std::move(*oString));
	} else if (auto* oBytes = get_if<QByteArray>(&inVariant)) {
		*this = APrivateBuffer(std::move(*oBytes));
	} else if (auto* oBuffer = get_if<APrivateBuffer>(&inVariant)) {
		*this = *oBuffer;
	}

	inVariant.clear();
}


// -----------
/*!
	\fn

	Doc.
*/

APrivateBuffer::~APrivateBuffer(void) {}


// -----------
/*!
	\fn

	Doc.
*/

bool APrivateBuffer::mIsNull() const noexcept {

	return !pStorageData;
}


// -----------
/*!
	\fn

	Doc.
*/

bool APrivateBuffer::mIsEmpty() const noexcept {

	return mSize() == 0;
}


// -----------
/*!
	\fn

	Doc.
*/

qsizetype APrivateBuffer::mSize() const noexcept {

	return pStorageData ? pStorageData->mSize() : 0;
}


// -----------
/*!
	\fn

	Doc.
*/

bool APrivateBuffer::mIsLocked() const noexcept {

	return pStorageData && pStorageData->mIsLocked();
}


// -----------
/*!
	\fn

	Doc.
*/

bool APrivateBuffer::mDisableCoreDumps() noexcept {

	rlimit rl;
	rl.rlim_cur = 0;
	rl.rlim_max = 0;
	return ::setrlimit(RLIMIT_CORE, &rl) == 0;
}


// -----------
/*!
	\fn

	Doc.
*/

const char* APrivateBuffer::mConstData() const noexcept {

	return pStorageData ? pStorageData->mConstData() : nullptr;
}


// -----------
/*!
	\fn

	Doc.
*/

QByteArrayView APrivateBuffer::mView() const noexcept {

	return {mConstData(),mSize()};
}


// -----------
/*!
	\fn

	Doc.
*/

QByteArray APrivateBuffer::mToByteArray() const {

	return QByteArray(mConstData(),mSize());
}


// -----------
/*!
	\fn

	Doc.
*/

QString APrivateBuffer::mToQString() const {

	if (mIsEmpty()) return {};

	QString oOutput(mSize(),Qt::Uninitialized);

	QStringDecoder oDecoded(QStringDecoder::Utf8, QStringDecoder::Flag::Stateless);
	QChar* oDecodedSymbols = oDecoded.appendToBuffer(oOutput.data(), mView());
	oOutput.truncate(oDecodedSymbols - oOutput.constData());

	return oOutput;
}


// -----------
/*!
	\fn

	Doc.
*/

QVariant APrivateBuffer::mToVariant() const {

	return QVariant::fromValue(*this);
}


// -----------
/*!
	\fn

	Doc.
*/

void APrivateBuffer::mClear() noexcept {

	if (pStorageData) pStorageData->mWipe();
	pStorageData.reset();
}


// -----------
/*!
	\fn

	Doc.
*/

void APrivateBuffer::mWipe(QByteArray& inBytes) {

	if (!inBytes.isEmpty()) APrivateBufferStorage::mZeroing(inBytes.data(),size_t(inBytes.size()));
	inBytes = QByteArray();
}


// -----------
/*!
	\fn

	Doc.
*/

void APrivateBuffer::mWipe(QString& inText) {

	if (!inText.isEmpty()) APrivateBufferStorage::mZeroing(inText.data(),size_t(inText.size()) * sizeof(QChar));
	inText = QString();
}

