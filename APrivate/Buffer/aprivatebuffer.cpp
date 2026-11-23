// ----------------------------------------------------------
/*!
	\class APrivateBuffer
	\title
	\brief Implicitly shared (copy-on-write) UTF-8 buffer for secrets.

	Copies share one APrivateBufferStorage. Any modifying call
	(mAppend(), mPopBack(), mReserve()) detaches first if the storage
	is shared, so editing one copy never changes another.
	Exception: mClear() wipes the shared storage for every copy.

	Growing reallocates into a new storage; the old one is cleansed
	by APrivateBufferStorage's destructor (OPENSSL_cleanse) as soon as
	no copy references it.

	Thread safety follows Qt implicit sharing: different copies may be
	used from different threads, one object must not be modified
	concurrently.

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
	\fn APrivateBuffer::APrivateBuffer(qsizetype inCapacity)

	Private: creates an empty buffer with at least \a inCapacity bytes.
*/

APrivateBuffer::APrivateBuffer(qsizetype inCapacity) {

	pStorageData = std::make_shared<APrivateBufferStorage>(inCapacity);
}


// -----------
/*!
	\fn APrivateBuffer::APrivateBuffer(QByteArray&& inByteArray)

	Takes the bytes and wipes \a inByteArray.
*/

APrivateBuffer::APrivateBuffer(QByteArray&& inByteArray) : APrivateBuffer(inByteArray.size()) {

	if (!inByteArray.isEmpty()) std::memcpy(pStorageData->mData(),inByteArray.constData(),size_t(inByteArray.size()));
	pStorageData->mSizeSet(inByteArray.size());

	mWipe(inByteArray);
}


// -----------
/*!
	\fn APrivateBuffer::APrivateBuffer(QString&& inString)

	Encodes \a inString as UTF-8 and wipes it.
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
	\fn APrivateBuffer::APrivateBuffer(QVariant&& inVariant)

	Accepts QString, QByteArray or APrivateBuffer and clears \a inVariant.
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
	\fn APrivateBuffer::APrivateBuffer(APrivateBuffer&& inOther) noexcept
*/

APrivateBuffer::APrivateBuffer(APrivateBuffer&& inOther) noexcept
	: pStorageData(std::move(inOther.pStorageData)),
	pPendingHighSurrogate(inOther.pPendingHighSurrogate) {

	APrivateBufferStorage::mZeroing(&inOther.pPendingHighSurrogate,sizeof(inOther.pPendingHighSurrogate));
}


// -----------
/*!
	\fn APrivateBuffer& APrivateBuffer::operator=(APrivateBuffer&& inOther) noexcept
*/

APrivateBuffer& APrivateBuffer::operator=(APrivateBuffer&& inOther) noexcept {

	if (this != &inOther) {
		pStorageData = std::move(inOther.pStorageData);
		pPendingHighSurrogate = inOther.pPendingHighSurrogate;
		APrivateBufferStorage::mZeroing(&inOther.pPendingHighSurrogate,sizeof(inOther.pPendingHighSurrogate));
	}
	return *this;
}


// -----------
/*!
	\fn APrivateBuffer::~APrivateBuffer(void)

	Storage is cleansed by APrivateBufferStorage when the last copy goes.
*/

APrivateBuffer::~APrivateBuffer(void) {

	APrivateBufferStorage::mZeroing(&pPendingHighSurrogate,sizeof(pPendingHighSurrogate));
}


// -----------
/*!
	\fn bool APrivateBuffer::mIsNull(void) const noexcept
*/

bool APrivateBuffer::mIsNull(void) const noexcept {

	return !pStorageData && !pPendingHighSurrogate;
}


// -----------
/*!
	\fn bool APrivateBuffer::mIsEmpty(void) const noexcept

	True if there are no bytes and no pending (half-entered) surrogate.
*/

bool APrivateBuffer::mIsEmpty(void) const noexcept {

	return mSize() == 0 && !pPendingHighSurrogate;
}


// -----------
/*!
	\fn qsizetype APrivateBuffer::mSize(void) const noexcept

	Size in UTF-8 bytes (a pending high surrogate is not counted).
*/

qsizetype APrivateBuffer::mSize(void) const noexcept {

	return pStorageData ? pStorageData->mSize() : 0;
}


// -----------
/*!
	\fn qsizetype APrivateBuffer::mSymbolCount(void) const noexcept

	Number of symbols (Unicode code points), counted directly in the
	secure storage without decoding, e.g. for rendering bullet masks
	in ATextEditMobile without calling mToQString().
	A pending high surrogate counts as one symbol, matching mPopBack().
*/

qsizetype APrivateBuffer::mSymbolCount(void) const noexcept {

	qsizetype oCount = pPendingHighSurrogate ? 1 : 0;
	for (const char oChar : mView()) {
		if ((static_cast<unsigned char>(oChar) & 0xC0) != 0x80) ++oCount;
	}
	return oCount;
}


// -----------
/*!
	\fn qsizetype APrivateBuffer::mCodePointCount(void) const noexcept

	Same as mSymbolCount().
*/

qsizetype APrivateBuffer::mCodePointCount(void) const noexcept {

	return mSymbolCount();
}


// -----------
/*!
	\fn qsizetype APrivateBuffer::mCapacity(void) const noexcept
*/

qsizetype APrivateBuffer::mCapacity(void) const noexcept {

	return pStorageData ? qsizetype(pStorageData->mCapacity()) : 0;
}


// -----------
/*!
	\fn bool APrivateBuffer::mIsLocked(void) const noexcept
*/

bool APrivateBuffer::mIsLocked(void) const noexcept {

	return pStorageData && pStorageData->mIsLocked();
}


// -----------
/*!
	\fn bool APrivateBuffer::mIsSecureHeap(void) const noexcept
*/

bool APrivateBuffer::mIsSecureHeap(void) const noexcept {

	return pStorageData && pStorageData->mIsHeap();
}


// -----------
/*!
	\fn bool APrivateBuffer::mDisableCoreDumps(void) noexcept
*/

bool APrivateBuffer::mDisableCoreDumps(void) noexcept {

	rlimit oLimit;
	oLimit.rlim_cur = 0;
	oLimit.rlim_max = 0;
	return ::setrlimit(RLIMIT_CORE,&oLimit) == 0;
}


// -----------
/*!
	\fn const char* APrivateBuffer::mConstData(void) const noexcept
*/

const char* APrivateBuffer::mConstData(void) const noexcept {

	return pStorageData ? pStorageData->mConstData() : nullptr;
}


// -----------
/*!
	\fn QByteArrayView APrivateBuffer::mView(void) const noexcept
*/

QByteArrayView APrivateBuffer::mView(void) const noexcept {

	return {mConstData(),mSize()};
}


// -----------
/*!
	\fn QByteArray APrivateBuffer::mToByteArray(void) const

	Note: the result lives in ordinary memory; wipe it with mWipe().
*/

QByteArray APrivateBuffer::mToByteArray(void) const {

	return QByteArray(mConstData(),mSize());
}


// -----------
/*!
	\fn QString APrivateBuffer::mToQString(void) const

	Note: the result lives in ordinary memory; wipe it with mWipe().
*/

QString APrivateBuffer::mToQString(void) const {

	if (mSize() == 0) return {};

	QString oOutput(mSize(),Qt::Uninitialized);

	QStringDecoder oDecoder(QStringDecoder::Utf8,QStringDecoder::Flag::Stateless);
	QChar* oDecodedSymbols = oDecoder.appendToBuffer(oOutput.data(),mView());
	oOutput.truncate(oDecodedSymbols - oOutput.constData());

	return oOutput;
}


// -----------
/*!
	\fn QVariant APrivateBuffer::mToVariant(void) const
*/

QVariant APrivateBuffer::mToVariant(void) const {

	return QVariant::fromValue(*this);
}


// -----------
/*!
	\fn bool APrivateBuffer::mIsEqual(const APrivateBuffer& inOther) const noexcept

	Constant-time comparison (CRYPTO_memcmp); only the length leaks.
*/

bool APrivateBuffer::mIsEqual(const APrivateBuffer& inOther) const noexcept {

	if (pPendingHighSurrogate != inOther.pPendingHighSurrogate) return false;
	return mIsEqual(inOther.mView());
}


// -----------
/*!
	\fn bool APrivateBuffer::mIsEqual(QByteArrayView inBytes) const noexcept

	Constant-time comparison (CRYPTO_memcmp); only the length leaks.
*/

bool APrivateBuffer::mIsEqual(QByteArrayView inBytes) const noexcept {

	if (!pStorageData) return inBytes.isEmpty();
	return pStorageData->mIsEqual(inBytes.data(),inBytes.size());
}


// -----------
/*!
	\fn void APrivateBuffer::mClear(void) noexcept

	Wipes the storage (for all copies sharing it) and releases it.
*/

void APrivateBuffer::mClear(void) noexcept {

	if (pStorageData) pStorageData->mWipe();
	pStorageData.reset();
	APrivateBufferStorage::mZeroing(&pPendingHighSurrogate,sizeof(pPendingHighSurrogate));
}


// -----------
/*!
	\fn void APrivateBuffer::mReserve(qsizetype inCapacity)

	Pre-allocates secure storage, e.g. mReserve(256) before password input,
	so typing does not reallocate.
*/

void APrivateBuffer::mReserve(qsizetype inCapacity) {

	const qsizetype oSize = mSize();
	const bool oShared = pStorageData && pStorageData.use_count() > 1;
	if (pStorageData && !oShared && inCapacity <= mCapacity()) return;
	mDetach(std::max({inCapacity,oSize,mCapacity()}),oSize);
}


// -----------
/*!
	\fn void APrivateBuffer::mAppend(QChar inSymbol)

	Appends one UTF-16 code unit. A high surrogate is held until the
	matching low surrogate arrives, so emoji etc. can be entered
	unit-by-unit. Unpaired surrogates become U+FFFD.
*/

void APrivateBuffer::mAppend(QChar inSymbol) {

	const char16_t oUnit = inSymbol.unicode();

	if (pPendingHighSurrogate) {
		if (QChar::isLowSurrogate(oUnit)) {
			const char32_t oCodePoint = QChar::surrogateToUcs4(pPendingHighSurrogate,oUnit);
			char oBytes[4];
			const qsizetype oLength = mEncodeUtf8(oCodePoint,oBytes);
			mAppendRaw(oBytes,oLength);
			APrivateBufferStorage::mZeroing(oBytes,sizeof(oBytes));
			APrivateBufferStorage::mZeroing(&pPendingHighSurrogate,sizeof(pPendingHighSurrogate));
			return;
		}
		mFlushPendingSurrogate();
	}

	if (QChar::isHighSurrogate(oUnit)) {
		pPendingHighSurrogate = oUnit;
		return;
	}

	mAppend(char32_t(oUnit));
}


// -----------
/*!
	\fn void APrivateBuffer::mAppend(char32_t inCodePoint)

	Appends one Unicode code point as UTF-8 (invalid -> U+FFFD).
*/

void APrivateBuffer::mAppend(char32_t inCodePoint) {

	mFlushPendingSurrogate();

	char oBytes[4];
	const qsizetype oLength = mEncodeUtf8(inCodePoint,oBytes);
	mAppendRaw(oBytes,oLength);
	APrivateBufferStorage::mZeroing(oBytes,sizeof(oBytes));
}


// -----------
/*!
	\fn void APrivateBuffer::mAppend(QStringView inText)

	Appends UTF-16 text (e.g. QKeyEvent::text() or one input-method commit).
	A trailing high surrogate is kept pending for the next call.
	The caller remains responsible for wiping the source string.
*/

void APrivateBuffer::mAppend(QStringView inText) {

	while (pPendingHighSurrogate && !inText.isEmpty()) {
		mAppend(inText.front());
		inText = inText.sliced(1);
	}
	if (inText.isEmpty()) return;

	char16_t oTrailing = 0;
	if (inText.back().isHighSurrogate()) {
		oTrailing = inText.back().unicode();
		inText.chop(1);
	}

	if (!inText.isEmpty()) {
		QStringEncoder oEncoder(QStringEncoder::Utf8,QStringEncoder::Flag::Stateless);
		char* oBegin = mPrepareAppend(oEncoder.requiredSpace(inText.size()));
		char* oEnd = oEncoder.appendToBuffer(oBegin,inText);
		pStorageData->mSizeSet(pStorageData->mSize() + (oEnd - oBegin));
	}

	pPendingHighSurrogate = oTrailing;
}


// -----------
/*!
	\fn void APrivateBuffer::mAppend(QByteArrayView inBytes)

	Appends raw bytes (expected to be UTF-8; not validated).
*/

void APrivateBuffer::mAppend(QByteArrayView inBytes) {

	mFlushPendingSurrogate();
	mAppendRaw(inBytes.data(),inBytes.size());
}


// -----------
/*!
	\fn void APrivateBuffer::mAppend(const APrivateBuffer& inOther)

	Appends another buffer (appending a buffer to itself is supported).
*/

void APrivateBuffer::mAppend(const APrivateBuffer& inOther) {

	const char16_t oOtherPending = inOther.pPendingHighSurrogate;
	const std::shared_ptr<APrivateBufferStorage> oSource = inOther.pStorageData; // keeps source alive

	mFlushPendingSurrogate();
	if (oSource && oSource->mSize() > 0) {
		const qsizetype oCount = oSource->mSize();
		char* oTarget = mPrepareAppend(oCount);
		std::memcpy(oTarget,oSource->mConstData(),size_t(oCount));
		pStorageData->mSizeSet(pStorageData->mSize() + oCount);
	}
	pPendingHighSurrogate = oOtherPending;
}


// -----------
/*!
	\fn qsizetype APrivateBuffer::mPopBack(qsizetype inCount)

	Removes up to \a inCount symbols (Unicode code points) from the end,
	like Backspace. The removed bytes are cleansed immediately.
	Returns the number of symbols removed.

	Note: a symbol is a code point, not a grapheme cluster; composed
	emoji (ZWJ sequences, skin tones, flags) need several calls.
*/

qsizetype APrivateBuffer::mPopBack(qsizetype inCount) {

	if (inCount <= 0) return 0;

	qsizetype oRemoved = 0;
	if (pPendingHighSurrogate) {
		APrivateBufferStorage::mZeroing(&pPendingHighSurrogate,sizeof(pPendingHighSurrogate));
		++oRemoved;
	}

	const qsizetype oSize = mSize();
	if (oRemoved >= inCount || oSize == 0) return oRemoved;

	const unsigned char* oData = reinterpret_cast<const unsigned char*>(mConstData());
	qsizetype oNewSize = oSize;
	while (oRemoved < inCount && oNewSize > 0) {
		qsizetype oPosition = oNewSize - 1;
		while (oPosition > 0 && (oData[oPosition] & 0xC0) == 0x80 && oNewSize - oPosition < 4) {
			--oPosition;
		}
		oNewSize = oPosition;
		++oRemoved;
	}

	if (pStorageData.use_count() > 1) {
		mDetach(mCapacity(),oNewSize);
	} else {
		pStorageData->mSizeSet(oNewSize);
	}

	return oRemoved;
}


// -----------
/*!
	\fn void APrivateBuffer::mWipe(QByteArray& inBytes)

	Cleanses the whole allocation (incl. spare capacity) and empties it.

	Only an exclusively owned allocation is cleansed. If the data is
	shared with other QByteArray instances (or is fromRawData()),
	calling data() would detach, i.e. make yet another heap copy of the
	secret and cleanse only that copy. In that case \a inBytes just
	releases its reference; the remaining owners keep the data.
*/

void APrivateBuffer::mWipe(QByteArray& inBytes) {

	if (inBytes.isDetached()) {
		char* oData = inBytes.data();
		const qsizetype oCapacity = std::max(inBytes.capacity(),inBytes.size());
		APrivateBufferStorage::mZeroing(oData,size_t(oCapacity));
	}
	inBytes = QByteArray();
}


// -----------
/*!
	\fn void APrivateBuffer::mWipe(QString& inText)

	Cleanses the whole allocation (incl. spare capacity) and empties it.

	Only an exclusively owned allocation is cleansed (see the QByteArray
	overload); a shared one is just released.
*/

void APrivateBuffer::mWipe(QString& inText) {

	if (inText.isDetached()) {
		QChar* oData = inText.data();
		const qsizetype oCapacity = std::max(inText.capacity(),inText.size());
		APrivateBufferStorage::mZeroing(oData,size_t(oCapacity) * sizeof(QChar));
	}
	inText = QString();
}


// -----------
/*!
	\fn char* APrivateBuffer::mPrepareAppend(qsizetype inExtraBytes)

	Ensures unshared storage with room for \a inExtraBytes more bytes and
	returns the write position (end of data). Grows geometrically.
*/

char* APrivateBuffer::mPrepareAppend(qsizetype inExtraBytes) {

	constexpr qsizetype oMax = std::numeric_limits<qsizetype>::max();

	const qsizetype oSize = mSize();
	if (inExtraBytes < 0 || inExtraBytes > oMax - oSize) qBadAlloc();
	const qsizetype oRequired = oSize + inExtraBytes;

	const qsizetype oCapacity = mCapacity();
	const bool oShared = pStorageData && pStorageData.use_count() > 1;

	if (!pStorageData || oShared || oCapacity < oRequired) {
		qsizetype oNewCapacity = std::max(oRequired,pMinimumGrowth);
		if (oCapacity < oRequired) {
			const qsizetype oDoubled = oCapacity > oMax / 2 ? oMax : oCapacity * 2;
			oNewCapacity = std::max(oNewCapacity,oDoubled);
		} else {
			oNewCapacity = std::max(oNewCapacity,oCapacity);
		}
		mDetach(oNewCapacity,oSize);
	}

	return pStorageData->mData() + oSize;
}


// -----------
/*!
	\fn void APrivateBuffer::mDetach(qsizetype inCapacity,qsizetype inKeepBytes)

	Moves the first \a inKeepBytes bytes into a new, unshared storage.
	The old storage is cleansed when its last owner releases it.
	Strong exception guarantee: on failure nothing changes.
*/

void APrivateBuffer::mDetach(qsizetype inCapacity,qsizetype inKeepBytes) {

	Q_ASSERT(inKeepBytes >= 0 && inKeepBytes <= mSize() && inKeepBytes <= inCapacity);

	auto oNew = std::make_shared<APrivateBufferStorage>(inCapacity);
	if (inKeepBytes > 0) std::memcpy(oNew->mData(),mConstData(),size_t(inKeepBytes));
	oNew->mSizeSet(inKeepBytes);
	pStorageData.swap(oNew);
}


// -----------
/*!
	\fn void APrivateBuffer::mAppendRaw(const char* inBytes,qsizetype inSize)
*/

void APrivateBuffer::mAppendRaw(const char* inBytes,qsizetype inSize) {

	if (!inBytes || inSize <= 0) return;

	std::shared_ptr<APrivateBufferStorage> oKeepAlive;
	if (pStorageData && mOverlaps(inBytes,pStorageData->mConstData(),pStorageData->mSize())) {
		oKeepAlive = pStorageData;
	}

	char* oTarget = mPrepareAppend(inSize);
	std::memmove(oTarget,inBytes,size_t(inSize));
	pStorageData->mSizeSet(pStorageData->mSize() + inSize);
}


// -----------
/*!
	\fn void APrivateBuffer::mFlushPendingSurrogate(void)

	An unpaired high surrogate is committed as U+FFFD.
*/

void APrivateBuffer::mFlushPendingSurrogate(void) {

	if (!pPendingHighSurrogate) return;

	char oBytes[4];
	const qsizetype oLength = mEncodeUtf8(pReplacementCharacter,oBytes);
	mAppendRaw(oBytes,oLength);
	APrivateBufferStorage::mZeroing(&pPendingHighSurrogate,sizeof(pPendingHighSurrogate));
}


// -----------
/*!
	\fn qsizetype APrivateBuffer::mEncodeUtf8(char32_t inCodePoint,char* inOutBytes) noexcept

	Private: encodes one code point as UTF-8 into \a outBytes (at least
	4 bytes) and returns the length. Invalid values become U+FFFD.
*/

qsizetype APrivateBuffer::mEncodeUtf8(char32_t inCodePoint,char* inOutBytes) noexcept {

	if (inCodePoint > 0x10FFFF || (inCodePoint >= 0xD800 && inCodePoint <= 0xDFFF)) {
		inCodePoint = pReplacementCharacter;
	}

	if (inCodePoint < 0x80) {
		inOutBytes[0] = char(inCodePoint);
		return 1;
	}

	if (inCodePoint < 0x800) {
		inOutBytes[0] = char(0xC0|(inCodePoint >> 6));
		inOutBytes[1] = char(0x80|(inCodePoint & 0x3F));
		return 2;
	}

	if (inCodePoint < 0x10000) {
		inOutBytes[0] = char(0xE0|(inCodePoint >> 12));
		inOutBytes[1] = char(0x80|((inCodePoint >> 6) & 0x3F));
		inOutBytes[2] = char(0x80|(inCodePoint & 0x3F));
		return 3;
	}

	inOutBytes[0] = char(0xF0|(inCodePoint >> 18));
	inOutBytes[1] = char(0x80|((inCodePoint >> 12) & 0x3F));
	inOutBytes[2] = char(0x80|((inCodePoint >> 6) & 0x3F));
	inOutBytes[3] = char(0x80|(inCodePoint & 0x3F));
	return 4;
}


// -----------
/*!
	\fn bool APrivateBuffer::mOverlaps(const char* inPointer,const char* inBegin,qsizetype inSize) noexcept

	Private: true if \a inPointer lies within [inBegin, inBegin + inSize).
*/

bool APrivateBuffer::mOverlaps(const char* inPointer,const char* inBegin,qsizetype inSize) noexcept {

	if (!inPointer || !inBegin || inSize <= 0) return false;
	const std::less_equal<const char*> oLessEqual;
	const std::less<const char*> oLess;
	return oLessEqual(inBegin,inPointer) && oLess(inPointer,inBegin + inSize);
}

