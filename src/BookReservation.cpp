#include "../include/BookReservation.h"
#include "../include/LExceptions.h"

ReservationRecord::ReservationRecord(std::string& patronID, std::string& bookISBN)
{
	this->patronID = patronID;
	this->bookISBN = bookISBN;
}

ReservationRecord::ReservationRecord(const Patron& patron, const Book& book)
{
	this->patronID = patron.ID;
	this->bookISBN = book.ISBN;
}

BookReservationManagementSystem::BookReservationManagementSystem(int maxPendingReservations)
{
	this->maxPendingReservations = maxPendingReservations;
	pendingReservations = CircularQueue<ReservationRecord>(this->maxPendingReservations);
	fulfilledReservations = Stack<ReservationRecord>();
}

void BookReservationManagementSystem::indexBookToDB(const Book& book)
{
	booksDB.push_back(book);
}

void BookReservationManagementSystem::enqueueReservation(const Patron& patron, const Book& book)
{
	if (pendingReservations.size() < maxPendingReservations)
	{
		pendingReservations.enqueue({ patron, book });
	}
}

ReservationRecord BookReservationManagementSystem::processReservation()
{
	size_t uniqueReservations = pendingReservations.size();

	for (size_t i = uniqueReservations; i > 0; i--)
	{
		auto& record = pendingReservations.front();

		pendingReservations.dequeue();

		for (auto it = booksDB.begin(); it != booksDB.end(); it++)
		{
			if (it->ISBN == record.bookISBN)
			{
				if (it->copies > 0)
				{
					it->copies--;
					fulfilledReservations.push(record);
					return record;
				}
			}
		}

		pendingReservations.enqueue(record);
	}

	throw ReservationRecordUnavailable();
}