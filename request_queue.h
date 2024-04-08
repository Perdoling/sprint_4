#pragma once
#include <vector>
#include <deque>
#include <algorithm>
#include "search_server.h"
#include "document.h"

class RequestQueue {
public:
    explicit RequestQueue(const SearchServer& search_server);
    // сделаем "обёртки" для всех методов поиска, чтобы сохранять результаты для нашей статистики
    template <typename DocumentPredicate>
    vector<Document> AddFindRequest(const string& raw_query, DocumentPredicate document_predicate) {
        vector<Document> find_document = search_server_.FindTopDocuments(raw_query, document_predicate);
        QueryResult query_result;
        
        query_result.search_find = !find_document.empty();

        if(requests_.size() >= min_in_day_) {
            requests_.pop_front();
        }
        
        requests_.push_back(query_result);

        return find_document;
        // напишите реализацию
    }
    vector<Document> AddFindRequest(const string& raw_query, DocumentStatus status) ;
    vector<Document> AddFindRequest(const string& raw_query) ;
    int GetNoResultRequests() const;
private:
    const SearchServer& search_server_;
    struct QueryResult {
        bool search_find;
        // определите, что должно быть в структуре
    };
    deque<QueryResult> requests_;
    const static int min_in_day_ = 1440;
    // возможно, здесь вам понадобится что-то ещё
};