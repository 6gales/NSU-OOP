#include "TritSet.h"

Trit operator&(const Trit &a, const Trit &b)
{
	if ((a == Trit::False) || (b == Trit::False))
		return Trit::False;
	if ((a == Trit::True) && (b == Trit::True))
		return Trit::True;
	return Trit::Unknown;
}

Trit operator|(const Trit &a, const Trit &b)
{
	if ((a == Trit::False) && (b == Trit::False))
		return Trit::False;
	if ((a == Trit::True) || (b == Trit::True))
		return Trit::True;
	return Trit::Unknown;
}

Trit operator!(const Trit &a)
{
	if (a == Trit::True)
		return Trit::False;
	if (a == Trit::False)
		return Trit::True;
	return Trit::Unknown;
}

std::ostream& operator<<(std::ostream &os, const Trit &value)
{
	switch (value)
	{
	case Trit::False:
		os << "False";
		break;
	case Trit::Unknown:
		os << "Unknown";
		break;
	case Trit::True:
		os << "True";
		break;
	default:
		os << "";
		break;
	}
	return os;
}

std::ostream& operator<<(std::ostream &os, const TritSet &obj)
{
	for (uint i = 0; i < obj.length(); i++)
		os << "Trit number " << i << ": " << obj[i] << std::endl;
	return os;
}

uint formUnknown()
{
	uint u = 0;
	for (uint i = 0; i < (sizeof(uint) * 8); i++)
	{
		u <<= 1;
		if (i % 2)
			u |= 1;
	}
	return u;
}

void TwoBits::mSeg()
{
	if (intAdress >= pointer->intLen)
	{
		if (pointer->intLen)
		{
			uint *tmp = new uint[intAdress + 1];
			for (uint i = 0; i < pointer->intLen; i++)
				tmp[i] = pointer->p[i];
			delete[] pointer->p;
			pointer->p = tmp;

			uint u = formUnknown();
			for (uint i = pointer->intLen; i < intAdress + 1; i++)
				pointer->p[i] = u;

			pointer->intLen = intAdress + 1;
		}
		else
		{
			pointer->p = new uint[intAdress + 1];
			uint u = formUnknown();
			for (uint i = 0; i < intAdress + 1; i++)
				pointer->p[i] = u;
			pointer->intLen = intAdress + 1;
		}
	}
}

TwoBits::operator Trit() const
{
	if (intAdress >= pointer->intLen)
		return Trit::Unknown;

	uint toTrit = pointer->p[intAdress];
	for (uint i = ((sizeof(uint) * 8) / 2) - 1; i != tritAdress; i--)
		toTrit >>= 2;
	toTrit &= 3;

	switch (toTrit)
	{
	case 0:
		return Trit::False;
	case 1:
		return Trit::Unknown;
	case 2:
		return Trit::True;
	default:
		delete[] pointer->p;
		exit(1);
	}
}

TwoBits &TwoBits::operator=(Trit value)
{
	uint firstBitMask = 0, secondBitMask = 0;
	switch (value)
	{
	case Trit::False:
		for (uint i = 0; i < (sizeof(uint) * 8); i++)
		{
			firstBitMask <<= 1;
			if (!(i == (tritAdress * 2) || i == (tritAdress * 2 + 1)))
				firstBitMask |= 1;
		}

		mSeg();
		pointer->p[intAdress] &= firstBitMask;
		
		if (intAdress * (sizeof(uint) * 8 / 2) + tritAdress + 1 > pointer->logLen)
		{
			pointer->logLen = intAdress * (sizeof(uint) * 8 / 2) + tritAdress + 1;
			if (pointer->logLen > pointer->len)
				pointer->len = pointer->logLen;
		}
		break;

	case Trit::Unknown:
		if (intAdress < pointer->intLen)
		{
			for (uint i = 0; i < (sizeof(uint) * 8); i++)
			{
				firstBitMask <<= 1;
				secondBitMask <<= 1;
				if (!(i == tritAdress * 2))
					firstBitMask |= 1;
				if (i == (tritAdress * 2 + 1))
					secondBitMask |= 1;
			}
			pointer->p[intAdress] &= firstBitMask;
			pointer->p[intAdress] |= secondBitMask;

			if (intAdress * (sizeof(uint) * 8 / 2) + tritAdress + 1 == pointer->logLen)
			{
				uint i = pointer->logLen - 1;
				while ((*pointer)[i] == Trit::Unknown)
					i--;
				pointer->logLen = i + 1;
			}
		}
		break;

	case Trit::True:
		for (uint i = 0; i < (sizeof(uint) * 8); i++)
		{
			firstBitMask <<= 1;
			secondBitMask <<= 1;
			if (i == tritAdress * 2)
				firstBitMask |= 1;
			if (!(i == (tritAdress * 2 + 1)))
				secondBitMask |= 1;
		}

		mSeg();
		pointer->p[intAdress] |= firstBitMask;
		pointer->p[intAdress] &= secondBitMask;

		if (intAdress * (sizeof(uint) * 8 / 2) + tritAdress + 1 > pointer->logLen)
		{
			pointer->logLen = intAdress * (sizeof(uint) * 8 / 2) + tritAdress + 1;
			if (pointer->logLen > pointer->len)
				pointer->len = pointer->logLen;
		}
		break;

	default:
		delete[] pointer->p;
		exit(1);
	}
	return *this;
}

TwoBits &TwoBits::operator=(const TwoBits &value)
{
	uint firstBitMask = 0, secondBitMask = 0;
	switch (value)
	{
	case Trit::False:
		for (uint i = 0; i < (sizeof(uint) * 8); i++)
		{
			firstBitMask <<= 1;
			if (!(i == (tritAdress * 2) || i == (tritAdress * 2 + 1)))
				firstBitMask |= 1;
		}

		mSeg();
		pointer->p[intAdress] &= firstBitMask;

		if (intAdress * (sizeof(uint) * 8 / 2) + tritAdress + 1 > pointer->logLen)
		{
			pointer->logLen = intAdress * (sizeof(uint) * 8 / 2) + tritAdress + 1;
			if (pointer->logLen > pointer->len)
				pointer->len = pointer->logLen;
		}
		break;

	case Trit::Unknown:
		if (intAdress < pointer->intLen)
		{
			for (uint i = 0; i < (sizeof(uint) * 8); i++)
			{
				firstBitMask <<= 1;
				secondBitMask <<= 1;
				if (!(i == tritAdress * 2))
					firstBitMask |= 1;
				if (i == (tritAdress * 2 + 1))
					secondBitMask |= 1;
			}
			pointer->p[intAdress] &= firstBitMask;
			pointer->p[intAdress] |= secondBitMask;

			if (intAdress * (sizeof(uint) * 8 / 2) + tritAdress + 1 == pointer->logLen)
			{
				uint i = pointer->logLen - 1;
				while ((*pointer)[i] == Trit::Unknown)
					i--;
				pointer->logLen = i + 1;
			}
		}
		break;

	case Trit::True:
		for (uint i = 0; i < (sizeof(uint) * 8); i++)
		{
			firstBitMask <<= 1;
			secondBitMask <<= 1;
			if (i == tritAdress * 2)
				firstBitMask |= 1;
			if (!(i == (tritAdress * 2 + 1)))
				secondBitMask |= 1;
		}

		mSeg();
		pointer->p[intAdress] |= firstBitMask;
		pointer->p[intAdress] &= secondBitMask;

		if (intAdress * (sizeof(uint) * 8 / 2) + tritAdress + 1 > pointer->logLen)
		{
			pointer->logLen = intAdress * (sizeof(uint) * 8 / 2) + tritAdress + 1;
			if (pointer->logLen > pointer->len)
				pointer->len = pointer->logLen;
		}
		break;

	default:
		delete[] pointer->p;
		exit(1);
	}
	return *this;
}

TritSet::TritSet(uint n)
{
	len = n;
	intLen = (len / (sizeof(uint) * 8 / 2) + (len % (sizeof(uint) * 8 / 2) ? 1 : 0));
	logLen = 0;
	if (intLen)
	{
		uint u = formUnknown();
		p = new uint[intLen];
		for (uint i = 0; i < intLen; i++)
			p[i] = u;
	}
}

TritSet::TritSet(const std::initializer_list<Trit> &list)
{
	len = list.size();
	intLen = (len / (sizeof(uint) * 8 / 2) + (len % (sizeof(uint) * 8 / 2) ? 1 : 0));
	logLen = len;
	if (intLen)
	{
		uint u = formUnknown();
		p = new uint[intLen];
		for (uint i = 0; i < intLen; i++)
			p[i] = u;
	}
	uint j = 0;
	for (auto i = list.begin(); i != list.end(); i++)
	{
		(*this)[j] = (*i);
		j++;
	}
}

TritSet::TritSet(const TritSet &obj)
{
	len = obj.len;
	intLen = obj.intLen;
	logLen = obj.logLen;
	if (intLen)
	{
		p = new uint[intLen];
		for (uint i = 0; i < intLen; i++)
			p[i] = obj.p[i];
	}
}

void TritSet::shrink()
{
	if ((logLen / (sizeof(uint) * 8 / 2) + (logLen % (sizeof(uint) * 8 / 2) ? 1 : 0)) == intLen)
	{
		len = logLen;
		return;
	}
	intLen = logLen / (sizeof(uint) / 2) + (logLen % (sizeof(uint) / 2) ? 1 : 0);
	uint *tmp = new uint[intLen];
	for (uint i = 0; i < intLen; i++)
		tmp[i] = p[i];
	delete[] p;
	p = tmp;
	len = logLen;
}

Trit TritSet::operator[](uint n) const
{
	uint intAdress = n / ((sizeof(int) * 8) / 2);
	uint tritAdress = n % ((sizeof(int) * 8) / 2);
	if (intAdress >= intLen)
		return Trit::Unknown;

	uint toTrit = p[intAdress];
	for (uint i = ((sizeof(uint) * 8) / 2) - 1; i != tritAdress; i--)
		toTrit >>= 2;
	toTrit &= 3;

	switch (toTrit)
	{
	case 0:
		return Trit::False;
	case 1:
		return Trit::Unknown;
	case 2:
		return Trit::True;
	default:
		delete[] p;
		exit(1);
	}
}

TwoBits TritSet::operator[](uint n)
{
	uint intAdress = n / ((sizeof(int) * 8) / 2);
	uint tritAdress = n % ((sizeof(int) * 8) / 2);

	TwoBits value(intAdress, tritAdress, this);
	return value;
}


bool TritSet::operator==(const TritSet &obj) const
{
	if (logLen != obj.logLen)
		return false;
	for (uint i = 0; i < intLen; i++)
		if (p[i] != obj.p[i])
			return false;
	return true;
}

bool TritSet::operator!=(const TritSet &obj) const
{
	return !(*this == obj);
}

TritSet TritSet::operator&(const TritSet &obj) const
{
	TritSet result = ((this->logLen >= obj.logLen) ? *this : obj);
	uint maxLogLen = ((this->logLen >= obj.logLen) ? this->logLen : obj.logLen);
	for (uint i = 0; i < maxLogLen; i++)
	{
		if ((*this)[i] == Trit::False || obj[i] == Trit::False)
			result[i] = Trit::False;
		else if ((*this)[i] == Trit::True && obj[i] == Trit::True)
			result[i] = Trit::True;
		else result[i] = Trit::Unknown;
	}
	result.trim(result.logLen);
	return result;
}

TritSet TritSet::operator|(const TritSet &obj) const
{
	TritSet result = ((this->logLen >= obj.logLen) ? *this : obj);
	uint maxLogLen = ((this->logLen >= obj.logLen) ? this->logLen : obj.logLen);
	for (uint i = 0; i < maxLogLen; i++)
	{
		if ((*this)[i] == Trit::False && obj[i] == Trit::False)
			result[i] = Trit::False;
		else if ((*this)[i] == Trit::True || obj[i] == Trit::True)
			result[i] = Trit::True;
		else result[i] = Trit::Unknown;
	}
	result.trim(result.logLen);
	return result;
}

TritSet &TritSet::operator&=(const TritSet &obj)
{
	uint maxLogLen = ((this->logLen >= obj.logLen) ? this->logLen : obj.logLen);
	for (uint i = 0; i < maxLogLen; i++)
	{
		if ((*this)[i] == Trit::False || obj[i] == Trit::False)
			(*this)[i] = Trit::False;
		else if ((*this)[i] == Trit::True && obj[i] == Trit::True)
			(*this)[i] = Trit::True;
		else (*this)[i] = Trit::Unknown;
	}
	trim(logLen);
	return *this;
}

TritSet &TritSet::operator|=(const TritSet &obj)
{
	uint maxLogLen = ((this->logLen >= obj.logLen) ? this->logLen : obj.logLen);
	for (uint i = 0; i < maxLogLen; i++)
	{
		if ((*this)[i] == Trit::False && obj[i] == Trit::False)
			(*this)[i] = Trit::False;
		else if ((*this)[i] == Trit::True || obj[i] == Trit::True)
			(*this)[i] = Trit::True;
		else (*this)[i] = Trit::Unknown;
	}
	trim(logLen);
	return *this;
}

TritSet TritSet::operator!() const
{
	TritSet result = *this;
	for (uint i = 0; i < logLen; i++)
	{
		if (result[i] == Trit::True)
			result[i] = Trit::False;
		else if (result[i] == Trit::False)
			result[i] = Trit::True;
	}
	return result;
}

TritSet &TritSet::operator=(const TritSet &obj)
{
	if (this == &obj)
		return *this;
	delete[] p;
	len = obj.len;
	intLen = obj.intLen;
	logLen = obj.logLen;
	if (intLen)
	{
		p = new uint[intLen];
		for (uint i = 0; i < intLen; i++)
			p[i] = obj.p[i];
	}
	return *this;
}

size_t TritSet::cardinality(Trit value) const
{
	uint count = 0;
	for (uint i = 0; i < logLen; i++)
	{
		if ((*this)[i] == value)
			count++;
	}
	return count;
}

std::unordered_map<Trit, int, EnumClassHash> TritSet::cardinality() const
{
	uint count[3] = { 0 };
	for (uint i = 0; i < logLen; i++)
		count[(uint)(*this)[i]]++;

	std::unordered_map<Trit, int, EnumClassHash> result;
	for (int i = 0; i < 3; i++)
		result.insert({ Trit(i), count[i] });
	
	return result;
}

void TritSet::trim(size_t lastIndex)
{
	if (lastIndex < logLen)
	{
		for (uint i = lastIndex; i < logLen; i++)
			(*this)[i] = Trit::Unknown;
		while (((*this)[lastIndex] == Trit::Unknown) && lastIndex >= 0)
			lastIndex--;
		logLen = lastIndex + 1;
	}
}
