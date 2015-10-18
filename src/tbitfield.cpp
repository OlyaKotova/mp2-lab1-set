// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int _bitSize) //len-bitsize
{
	bitSize = _bitSize;
	size = bitSize/(sizeof(TELEM)*8)+1;
	mas = new TELEM[size];
	for(int i = 0; i<size; i++)
	mas[i] = 0;
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	size = bf.size;
	mas = new TELEM[size];
	for(int i = 0; i<size; i++)
	mas[i] = bf.mas[i];
}

TBitField::~TBitField()
{
	delete []mas;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	return(n/sizeof(TELEM)*8);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	int n = n%(sizeof(int)*8);
	TELEM mask  = 1<<n;
	return mask;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return bitSize;
}

void TBitField::SetBit(const int n) // установить бит
{
	int tmp=n;
	mas[GetMemIndex(tmp)]=mas[GetMemIndex(tmp)]|GetMemMask(tmp);
}

void TBitField::ClrBit(const int n) // очистить бит
{
	mas[GetMemIndex(n)]&=~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	int temp = mas[GetMemIndex(n)];
	return(temp);
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	TBitField tmp(bitSize);
	for (int i=0;i<size;i++)
	{
		tmp.mas[i]=mas[i]|bf.mas[i];
	}
	return (tmp);
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	int tmp = 0;
	if (bitSize != bf.bitSize)
		return 0;
	else
	if (bitSize == bf.bitSize)
	{
		for (int i = 0; i < size; i++)
		{
			if (mas[i] == bf.mas[i])
				tmp = 0;
			else
			{
				tmp = 1;
				break;
			}
		}
		if (tmp == 0)
			return 1;
		else return 0;
	}
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	int tmp = 0;
	if (bitSize != bf.bitSize)
		return 1;
	else
	if (bitSize == bf.bitSize)
	{
		for (int i = 0; i < size; i++)
		{
			if (mas[i] == bf.mas[i])
				tmp = 1;
			else
			{
				tmp = 0;
				break;
			}
		}
		if (tmp == 0)
			return 1;
		else return 0;
	}
}


TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	TBitField tmp(bitSize);
	for (int i=0;i<size;i++)
		tmp.mas[i]=mas[i];
	for (int i = 0; i < bf.bitSize; i++)
		tmp.mas[i] |= bf.mas[i];
	return (tmp);
}


TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	TBitField tmp(bitSize);
	for (int i=0;i<size;i++)
		tmp.mas[i]=mas[i];
	for (int i = 0; i < bf.bitSize; i++)
		tmp.mas[i] &= bf.mas[i];
	return (tmp);
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField tmp(bitSize);
	for (int i=0;i<size;i++)
	{
		tmp.mas[i]=mas[i]=~mas[i];
	}
	return (tmp);
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	int i = 0;
	while ((i >= 0) && (i < bf.bitSize))
	{
		bf.SetBit(i); 
		istr >> i;
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (int i = 0; i < bf.bitSize; i++)
		ostr << bf.GetBit(i);
	return ostr;
}
