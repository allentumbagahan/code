#include <iostream>
#include <curl/curl.h>

size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* response) {
    size_t totalSize = size * nmemb;
    response->append((char*)contents, totalSize);
    return totalSize;
}

std::string getRandomUserAgent() {
    std::string url = "https://www.randomuseragent.com/";
    std::string userAgent;

    CURL* curl;
    CURLcode res;

    // Initialize libcurl
    curl_global_init(CURL_GLOBAL_DEFAULT);

    // Create a curl handle
    curl = curl_easy_init();
    if (curl) {
        std::string response;
        // Set the request URL
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        // Set the write callback function to capture the response
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        // Perform the request
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "Failed to perform the request: " << curl_easy_strerror(res) << std::endl;
        } else {
            // Extract the User-Agent string from the response
            std::size_t startPos = response.find("<span class=\"user-agent\">") + 25;
            std::size_t endPos = response.find("</span>", startPos);
            userAgent = response.substr(startPos, endPos - startPos);
        }

        // Clean up
        curl_easy_cleanup(curl);
    }

    // Cleanup libcurl
    curl_global_cleanup();

    return userAgent;
}

int main() {
    std::string userAgent = getRandomUserAgent();
    std::cout << "Random User-Agent: " << userAgent << std::endl;

    return 0;
}