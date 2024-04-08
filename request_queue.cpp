#include "request_queue.h"

RequestQueue::RequestQueue(const SearchServer& search_server)
    : search_server_(search_server)
    {        // напишите реализацию
    }

vector<Document> RequestQueue::AddFindRequest(const string &raw_query, DocumentStatus status)
{
    return AddFindRequest(
        raw_query, [status](int document_id, DocumentStatus document_status, int rating)
        { return document_status == status; });
    // напишите реализацию
}
vector<Document> RequestQueue::AddFindRequest(const string &raw_query)
{
    return AddFindRequest(raw_query, DocumentStatus::ACTUAL);
    // напишите реализацию
}

int RequestQueue::GetNoResultRequests() const
{
    return count_if(begin(RequestQueue::requests_), end(requests_), [](QueryResult finder)
                    { return finder.search_find == false; });
    // напишите реализацию
}