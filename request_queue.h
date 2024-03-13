#pragma once
#include <vector>
#include <deque>
#include <algorithm>
#include "search_server.h"
#include "document.h"

class RequestQueue {
public:
    explicit RequestQueue(const SearchServer& search_server)
    : search_server_(search_server)
    {        // напишите реализацию
    }
    // сделаем "обёртки" для всех методов поиска, чтобы сохранять результаты для нашей статистики
    template <typename DocumentPredicate>
    vector<Document> AddFindRequest(const string& raw_query, DocumentPredicate document_predicate) {
        vector<Document> find_document = search_server_.FindTopDocuments(raw_query, document_predicate);
        QueryResult true_false;
        true_false.search_find = !find_document.empty();

        if(requests_.size() >= min_in_day_) {
            requests_.pop_front();
        }
        
        requests_.push_back(true_false);
        return find_document;
        // напишите реализацию
    }
    vector<Document> AddFindRequest(const string& raw_query, DocumentStatus status) {
        return AddFindRequest(
            raw_query, [status](int document_id, DocumentStatus document_status, int rating) {
                return document_status == status;
            });
        // напишите реализацию
    }
    vector<Document> AddFindRequest(const string& raw_query) {
        return AddFindRequest(raw_query, DocumentStatus::ACTUAL);
        // напишите реализацию
    }
    int GetNoResultRequests() const {
        return count_if(begin(requests_), end(requests_), [](QueryResult finder){
            return finder.search_find == false;
        });
        // напишите реализацию
    }
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