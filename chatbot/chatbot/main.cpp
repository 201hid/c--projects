#include <iostream>
#include <fstream>
#include <string>
#include <nlohmann/json.hpp>
#include <cpprest/http_client.h>

using namespace std;
// using json = nlohmann::json; // Removed to avoid global namespace pollution
using namespace web;
using namespace web::http;
using namespace web::http::client;

// Function to read JSON data from file
nlohmann::json readJsonFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        exit(1);
    }
    nlohmann::json j;
    file >> j;
    file.close();
    return j;
}

// Function to ask question to GPT API
string askGPT(const string& question, const string& apiKey) {
    string apiUrl = "https://api.openai.com/v1/completions";
    http_client client(apiUrl);
    uri_builder builder;
    builder.append_query("model", "text-davinci-003");
    http_request request(methods::POST);
    request.headers().add("Authorization", "Bearer " + apiKey);
    request.headers().set_content_type("application/json");
    nlohmann::json requestBody = {
        {"prompt", question},
        {"max_tokens", 50}
    };
    request.set_body(requestBody.dump());
    http_response response = client.request(request).get();
    if (response.status_code() != status_codes::OK) {
        cerr << "Error querying GPT API: " << response.status_code() << endl;
        exit(1);
    }
    return response.extract_string().get();
}

int main() {
    // Read JSON data from file
    nlohmann::json transactionData = readJsonFromFile("transaction_data.json");

    // Ask questions and get answers
    string apiKey = "YOUR_API_KEY"; // Replace with your OpenAI API key
    string question;
    cout << "Ask a question: ";
    getline(cin, question);
    string answer = askGPT(question, apiKey);
    cout << "Answer: " << answer << endl;

    return 0;
}
