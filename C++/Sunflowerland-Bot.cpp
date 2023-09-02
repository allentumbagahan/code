#include <iostream>
#include <curl/curl.h>
#include <string>
#include <json/json.h>
#include <vector>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <random>
#include <cstdint>
#include <unordered_map>
#include <thread>
#include <fstream>
using namespace std;
struct ingridient {
    string food;
    unordered_map<string, int> ingridients;
    int cookingtime;
};
struct timeMinuteAndSecond{
    int Minute;
    int Second;
};
struct CropReward {
    string rewardName;
    int rewardAmount;
};
struct Stone {
    string stoneId;
    long long stoneAmount;
    long long minedAt;
    int timeleftMinute;
};
struct Tree {
    string treeId;
    long long treesAmount;
    long long choppedAt;
    int timeleftMinute;
};
struct Crop {
    string plotsId;
    Json::Value plotsValue;
    string plotsCropName; 
    string plotsCropAmount; 
    string plotsCropId; 
    long long plotsCropTimePlanted; 
    CropReward reward;
    bool readyPlot;
    int timeleftMinute;
    timeMinuteAndSecond timeLeft;
};
struct Request {
    string item;
    int qty;
    string type; //Seed, Tool
};

vector<string> crop = {
    "Sunflower",
    "Potato",
    "Pumpkin",
    "Carrot",
    "Cabbage", 
    "Beetroot", 
    "Cauliflower", 
    "Parsnip", 
    "Eggplant", 
    "Radish", 
    "Wheat",
    "Kale",
    "Blueberry",
    "Orange",
    "Apple",
};// convert to json

vector<string> resource = {
    "Wood",
    "Gold",
    "Iron",
    "Stone"
};
vector<string> livestock = {
    "Egg",
};
vector<string> other = {
    "Wild Mushroom"
};
vector<ingridient> foodIngridients = {
    {"Mashed Potato", {{"Potato", 10}}, 1},
    {"Pumpkin Soup", {{"Pumpkin", 10}}, 3},
    {"Bumpkin Broth", {{"Carrot", 10}, {"Cabbage", 5}}, 20},
    {"Boiled Eggs", {{"Egg", 5}}, 60},
    {"Kale Stew", {{"Kale", 10}}, 120},
    {"Mushroom Soup", {{"Wild Mushroom", 5}}, 10},
    {"Reindeer Carrot", {{"Carrot", 5}}, 5},
    {"Kale Omelette", {{"Egg", 20}, {"Kale", 5}}, 210},
    {"Cabbers n Mash", {{"Mashed Potato", 10}, {"Cabbage", 20}}, 40},
    {"Roast Veggies", {{"Cabbage", 15}, {"Carrot", 10}}, 120},
    {"Bumpkin Salad", {{"Beetroot", 20}, {"Parsnip", 10}}, 210},
    {"Goblin's Treat", {{"Pumpkin", 10}, {"Radish", 20}, {"Cabbage", 10}}, 360},
    {"Cauliflower Burger", {{"Cauliflower", 15}, {"Wheat", 5}}, 180},
    {"Pancakes", {{"Wheat", 5}}, 20},
    {"Club Sandwich", {{"Sunflower", 100}, {"Carrot", 25}, {"Wheat", 5}}, 180},
    {"Mushroom Jacket Potatoes", {{"Wild Mushroom", 10}, {"Potato", 5}}, 10},
    {"Sunflower Crunch", {{"Sunflower", 300}}, 10},
    {"Bumpkin Roast", {{"Mashed Potato", 20}, {"Roast Veggies", 5}}, 600},
    {"Goblin Brunch", {{"Boiled Eggs", 5}, {"Goblin's Treat", 1}}, 600},
    {"Fruit Salad", {{"Blueberry", 1}, {"Orange", 1}, {"Apple", 1}}, 30},
    {"Sunflower Cake", {{"Sunflower", 1000}, {"Wheat", 10}, {"Egg", 15}}, 360},
    {"Potato Cake", {{"Potato", 500}, {"Wheat", 10}, {"Egg", 15}}, 570},
    {"Pumpkin Cake", {{"Pumpkin", 130}, {"Wheat", 10}, {"Egg", 15}}, 570},
    {"Carrot Cake", {{"Carrot", 120}, {"Wheat", 10}, {"Egg", 15}}, 720},
    {"Cabbage Cake", {{"Cabbage", 90}, {"Wheat", 10}, {"Egg", 15}}, 0},
    {"Beetroot Cake", {{"Beetroot", 100}, {"Wheat", 10}, {"Egg", 15}}, 0},
    {"Cauliflower Cake", {{"Cauliflower", 60}, {"Wheat", 10}, {"Egg", 15}}, 0},
    {"Parsnip Cake", {{"Parsnip", 45}, {"Wheat", 10}, {"Egg", 15}}, 0},
    {"Radish Cake", {{"Radish", 25}, {"Wheat", 10}, {"Egg", 15}}, 0},
    {"Wheat Cake", {{"Wheat", 35}, {"Egg", 15}}, 0},
    {"Apple Pie", {{"Apple", 5}, {"Wheat", 10}, {"Egg", 10}}, 0},
    {"Kale & Mushroom Pie", {{"Wild Mushroom", 10}, {"Kale", 5}, {"Wheat", 5}}, 0},
    {"Orange Cake", {{"Orange", 5}, {"Wheat", 10}, {"Egg", 15}}, 0},
};
unordered_map<string, int> getIngridients(string food){
    for(ingridient item : foodIngridients){
        if(item.food == food){
            return item.ingridients;
        }
    }
    return {{"Not Defined", -1}};
}
Json::Value fetch(string);
timeMinuteAndSecond getCooldown(long long);
Json::Value getItemUsingKeyInJSON(Json::Value, string);
void showCropsPlanted(Json::Value);
Json::Value stringToJSOValue(string);
void showDelivery(Json::Value);
void showStones(Json::Value);
void showTrees();
Json::Value postData(string, string, string);
string decimalToUint256(uint64_t);
void buySeed(string, string);
Json::Value sendAction(string);
void updateData(string, Json::Value);
void updateEntitiesData();
void refreshSession();
void mineStone(string);
void chopTree(string);
void buyTool(string, string);
void buyToolSelection();
void addIngridient(string, int);
string randomString8Digit();
void harvestPlot(string);
void sendDelivery(string);
void collectPlotReward(string);
string getFoodBuildingId(string);
void cookFood(string);
void openBotV2();
string getFoodBuildingName(string foodName);
size_t WriteCallback(void* contents, size_t size, size_t nmemb, string* output)
{
    size_t totalSize = size * nmemb;
    output->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}
unordered_map<string, int> entityGrowTime = {
    {"Sunflower", 1},
    {"Potato", 5},
    {"Pumpkin", 30},
    {"Carrot", 60},
    {"Cabbage", 120},
    {"Beetroot", 240},
    {"Cauliflower", 480},
    {"Parsnip", 720},
    {"Eggplant", 960},
    {"Radish", 1440},
    {"Wheat", 1440},
    {"Kale", 2460}
};
int getRandomNumber(int min, int max) {
    // Seed the random number generator
    std::random_device rd;
    std::mt19937 gen(rd());

    // Define the range using a uniform distribution
    std::uniform_int_distribution<int> distribution(min, max);

    // Generate a random number within the range
    int randomNumber = distribution(gen);

    return randomNumber;
}
Json::Value sendAction(string , string);
string getUTCNow();
//global variable for special purposed
string deviceTrackerId; // it can be defined using session
string session;
vector<Json::Value> state; // state, balance, inventory, crops
string LandId;
vector<Crop> crops; 
vector<Stone> stones; 
vector<Tree> trees; 
string tokenId; // jwt
string cachedKey;
string clientVersion = "2023-06-21T03:04"; // update this every
string userAgent;
vector<string> actions;
string urlSaveSession = "https://api.sunflower-land.com/autosave/";
vector<pair<pair<string, string>, int>> foodRecipesToBeProcess;
vector<pair<pair<string, string>, int>> resourceToBeProcess; // wood, stone , iron gold
vector<pair<pair<string, string>, int>> HenHouseToBeProcess; // egg
bool sendingActionIdle = true;
chrono::milliseconds delayToSendData = 1000ms;
int main()
{ 
    while(1){
        Json::Value response; 
        bool isLoggedOut = false;
        string LandIdTo256int;
        string bodyDataTemp;
        Json::Value tempRes;
        Json::Value userAgentRes = fetch("https://useragents.io/random/__data.json?limit=1500&x-sveltekit-invalidated=_1");
        fstream f1, f2;
        string tokenLoaded, cacheLoaded;
        int min = 0;
        int max = 215;
        int randomNum = getRandomNumber(min, max);
        userAgent = (userAgentRes["nodes"][1]["data"][3 + (4 * randomNum)]).asString();
        cout << "Enter Your Land Id : ";
        cin >> LandId;
        string hostSFL = "https://api.sunflower-land.com/visit/" + LandId;
        f1.open("SFL-Bot_TokenId(" + LandId + ")", ios::in);
        if(!f1.eof()){
            getline(f1, tokenLoaded);
        }
        if(tokenLoaded == ""){
            cout << "Enter Your Token Id (0 if null)  : ";
        }else{
            cout << "Enter Your Token Id (0 if null or 1 load)  : ";
        }
        f1.close();
        cin >> tokenId;
        if(tokenId[0] == '1' && tokenLoaded != ""){
            tokenId = tokenLoaded;
            cout << tokenId << endl;
        }
        f2.open("SFL-Bot_CachedKeys(" + LandId + ")", ios::in);
        if(!f2.eof()){
            getline(f2, cacheLoaded);
        }
        if(cacheLoaded == ""){
            cout << "Enter Your Cached Key (0 if null)  : ";
        }else{
            cout << "Enter Your Cached Key (0 if null or 1 load)  : ";
        }
        f2.close();
        cin >> cachedKey;
        if(cachedKey[0] == '1' && cacheLoaded != ""){
            cachedKey = cacheLoaded;
            cout << cachedKey << endl;
        }
        response = fetch(hostSFL);
        updateData("state", response);
        if(tokenId.size() > 10){
            f1.open("SFL-Bot_TokenId(" + LandId + ")", ios::out);
            f1 << tokenId;
            f1.close();
            f2.open("SFL-Bot_CachedKeys(" + LandId + ")", ios::out);
            f2 << cachedKey;
            f2.close();
            LandIdTo256int = decimalToUint256(stoull(LandId));
            bodyDataTemp = ("{\"jsonrpc\":\"2.0\",\"id\":0,\"method\":\"eth_call\",\"params\":[{\"data\":\"0x6e19cb18" + LandIdTo256int + "\",\"to\":\"0x63ed5e7df3ef84b81dec5ac46d46a8fd86c452b4\"},\"latest\"]}");
            tempRes = postData("https://polygon-mainnet.g.alchemy.com/v2/AQDCMnCBkaW49yjgFLDYd4VPdtI47VwY", "", bodyDataTemp);
            session = tempRes["result"].asString();
            refreshSession();
        }
        system("pause");
        while(!(isLoggedOut)){
        int action;
        cout << "   [0] Balance " << endl;
        cout << "   [1] Plots " << endl;
        cout << "   [2] Delivery " << endl;
        cout << "   [3] Trees " << endl;
        cout << "   [4] Stones " << endl;
        cout << "   [5] Buy Seed " << endl;
        cout << "   [6] Buy Tools " << endl;
        cout << "   [7] Refresh " << endl;
        cout << "   [8] Log Out " << endl;
        cout << "   [9] Open Bot " << endl;
        cout << "Enter Action : ";
        cin >> action;
        if(action == 0){
            cout << "your balance id is : " <<  state[1] << endl;
            system("pause");
            system("cls");
        }else if(action == 1){
            showCropsPlanted(state[3]);
            system("pause");
            system("cls");
        }else if(action == 2){
            showDelivery(state[0]);
            system("pause");
            system("cls");
        }else if(action == 3){
            showTrees();
            system("pause");
            system("cls");
        }else if(action == 4){
            showStones(state[0]);
            system("pause");
            system("cls");
        }else if(action == 5){
            buySeed("Beetroot Seed", "5");
            Json::Value tempRes = sendAction(urlSaveSession + LandId);
            updateData("farm", tempRes);
            system("pause");
            system("cls");
        }else if(action == 7){
            cout << "Update Session : " << session << endl; 
            refreshSession();
            cout << "Session Updated : " << session << endl;
            system("pause");
            system("cls");
        }else if(action == 6){
            buyToolSelection();
            system("pause");
            system("cls");
        }else if(action == 8){
            cout << "Land Logged Out" << endl;
            isLoggedOut = true;
            system("pause");
            system("cls");
        }else if(action == 9){
            openBotV2();

        }else{
            action = -1;
        }
        }
    }
}
Json::Value fetch(string url)
{
    vector<Json::Value> valuetoBeReturn;
    Json::Value jsonResponse;
    Json::CharReaderBuilder reader;
    string parseErrors;

    CURL* curl;
    CURLcode res;
    string response;
    // Initialize cURL
    curl = curl_easy_init();
    if (curl)
    {
        // Set the URL to fetch
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        // Set the callback function to handle the response
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        // Perform the request
        res = curl_easy_perform(curl);

        // Check for errors
        if (res != CURLE_OK)
        {
            cerr << "cURL failed: " << curl_easy_strerror(res) << endl;
        }
        else
        {
            // Successful request, 'response' contains the fetched data
            
        }

        // Cleanup
        curl_easy_cleanup(curl);
        auto rawJson = response;
        istringstream responseStream(response);
        bool parsingSuccessful = Json::parseFromStream(reader, responseStream, &jsonResponse, &parseErrors);
        if (!parsingSuccessful)
        {
            cerr << "Failed to parse JSON: " << parseErrors << endl;
        }
    } 
    return jsonResponse;
}
timeMinuteAndSecond getCooldown(long long createdTimeInEpoch){
    timeMinuteAndSecond timeSpend;
    auto currentTime = chrono::system_clock::now();
    auto currentEpochTime = chrono::duration_cast<chrono::seconds>(currentTime.time_since_epoch()).count();
    long long timeDifference = currentEpochTime - (createdTimeInEpoch / 1000);
    int minutes = static_cast<int>(timeDifference / 60);
    int seconds = static_cast<int>(timeDifference % 60);
    //cout << createdTimeInEpoch << " Time Difference: " << minutes  << " minutes " << seconds << " seconds" << std::endl;
    timeSpend.Minute = minutes;
    timeSpend.Second = seconds;
    return timeSpend;
}
Json::Value getItemUsingKeyInJSON(Json::Value JSONtext, string key){
    Json::Value res;
    if (JSONtext.isMember(key))
    {
        res = JSONtext[key];
    }
    else
    {
        cerr << key + " key not found in JSON" << endl;
        res = "fail";
    }
    return res;
}
void showCropsPlanted(Json::Value jsonObject){
    updateEntitiesData();
    for(int i = 0; i < crops.size(); i++){
        if(crops[i].reward.rewardName == "No Reward"){
            if(crops[i].plotsCropName == ""){
                cout << "   plot " << i << ": No Crops Planted" << endl;
            }else{
                cout << "   plot " << i << ": "  << crops[i].plotsCropName << " x" << crops[i].plotsCropAmount ;
            }
        }else{
            cout << "   plot " << i << ": "  << crops[i].plotsCropName << " x" << crops[i].plotsCropAmount << " + " << crops[i].reward.rewardName << " x"  << crops[i].reward.rewardAmount;
        }
        cout << "     " <<crops[i].timeleftMinute <<"m" << endl;
    }

}
void showDelivery(Json::Value jsonObject){
    Json::Value  delivery = jsonObject["delivery"];
    for(int arr=0; arr < delivery["orders"].size(); arr++){
        string deliveryResourceName = delivery["orders"][arr]["items"].getMemberNames()[0];
        cout << deliveryResourceName << " x" << delivery["orders"][arr]["items"][deliveryResourceName] <<  endl;
    }

}
void showStones(Json::Value jsonObject){
    Json::Value inventory = jsonObject["inventory"];
    Stone tempStone;
    string axeCount;
    if(inventory.isMember("Pickaxe")){
        axeCount = inventory["Pickaxe"].asString();
        cout << "You Have x" << axeCount << " Pickaxe" << endl;
    }else{
        cout << "Your Not Able To Mine You Don't Have Pickaxe On Your Inventory" << endl;
        axeCount = "";
    }
    updateEntitiesData();
    for(int i = 0; i < stones.size(); i++){
        cout << "Stone " << i << " x" << stones[i].stoneAmount << "   ";
        if(stones[i].timeleftMinute > 0){
            cout << stones[i].timeleftMinute << "m left" << endl;
        }else{
            cout << "Ready To Mine" << endl;
        }
    }
    if(axeCount != "" && tokenId != "0"){
        cout << "You want to mine ? (1 if yes/ 0 if no) ";
        int isChop;
        cin >> isChop;
        if(isChop){
            int stoneNum;
            cout << "Enter Stone Number To be Mine ? ";
            cin >> stoneNum;
            mineStone(stones[stoneNum].stoneId);
            Json::Value tempRes = sendAction(urlSaveSession + LandId);
            updateData("farm", tempRes);
        }
    }
}
void showTrees(){
    Json::Value inventory = state[0]["inventory"];
    Json::Value treesJson = state[0]["trees"];
    Tree tempTree;
    string axeCount;
    updateEntitiesData();
    if(inventory.isMember("Axe")){
        axeCount = inventory["Axe"].asString();
        cout << "You Have x" << axeCount << " Axe" << endl;
    }else{
        cout << "Your Not Able To Chop You Don't Have Axe On Your Inventory" << endl;
        axeCount = "";
    }
    for(int i = 0; i < trees.size(); i++){
        cout << "Tree " << i << " x" << trees[i].treesAmount << "   ";
        if(trees[i].timeleftMinute > 0){
            cout << trees[i].timeleftMinute << "m left" << endl;
        }else{
            cout << "Ready To Chop" << endl;
        }
    }
    if(axeCount != "" && tokenId != "0"){
        cout << "You want to chop ? (1 if yes/ 0 if no) ";
        int isChop;
        cin >> isChop;
        if(isChop){
            int treeNum;
            cout << "Enter Tree Number To be Mine ? ";
            cin >> treeNum;
            chopTree(trees[treeNum].treeId);
            Json::Value tempRes = sendAction(urlSaveSession + LandId);
            updateData("farm", tempRes);
        }
    }
}
Json::Value stringToJSOValue(string jsonString){
    Json::Value jsonResponse;
    Json::CharReaderBuilder reader;
    string parseErrors;
    istringstream jsonToStream(jsonString);
    bool parsingSuccessful = Json::parseFromStream(reader, jsonToStream, &jsonResponse, &parseErrors);
    if (!parsingSuccessful)
    {
        cerr << "Failed to parse JSON: " << parseErrors << endl;
        return jsonResponse;
    }
    return jsonResponse;
}
Json::Value postData(string url, string tokenId, string data){
    Json::Value jsonResponse;
    Json::CharReaderBuilder reader;
    string parseErrors;
    CURL* curl;
    CURLcode res;

    // Initialize libcurl
    try{    
        curl_global_init(CURL_GLOBAL_DEFAULT);

        // Create a curl handle
        curl = curl_easy_init();
        if (curl) {
            string response;
            // Set the request URL
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            // Set the request method to POST
            curl_easy_setopt(curl, CURLOPT_POST, 1L);
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
            // Create a header list
            struct curl_slist* headers = nullptr;

            // Set the Authorization header
            if(tokenId != ""){
                string authHeader = "Authorization: Bearer " + tokenId;
                headers = curl_slist_append(headers, authHeader.c_str());
                headers = curl_slist_append(headers, "accept: application/json");
                headers = curl_slist_append(headers, "content-type: application/json;charset=UTF-8");
                curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
            }
            curl_easy_setopt(curl, CURLOPT_USERAGENT, userAgent.c_str());

            // Set the write callback function to capture the response
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

            // Perform the request
            res = curl_easy_perform(curl);
            if (res != CURLE_OK) {
                cerr << "Failed to perform the request: " << curl_easy_strerror(res) << endl;
            } else {
                long statusCode;
                curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &statusCode);
                /*cout << "Url: " << url.c_str() << endl;
                cout << "Request: " << data.c_str() << endl;
                cout << "header: " << headers << endl;
                cout << "Response Code: " << statusCode << endl;
                cout << "Response: " << response << endl;*/
            }

            // Clean up
            curl_easy_cleanup(curl);
            auto rawJson = response;
            istringstream responseStream(response);
            bool parsingSuccessful = Json::parseFromStream(reader, responseStream, &jsonResponse, &parseErrors);
        } 
    }catch(exception& err){
        cout << "Exception occurred: " << err.what() << endl;
    }
    return jsonResponse;

}
string decimalToUint256(uint64_t decimal) {
    stringstream ss;
    ss << hex << setfill('0') << setw(64) << decimal;
    return ss.str();
}
void plantPlot(string seedName, string plotId){
    Json::Value tempRes;
    string actionType = "seed.planted";
    string action;
    action = "{\"type\":\"" + actionType + "\",\"index\":\"" + plotId + "\",\"item\":\"" + seedName + "\",\"cropId\":\"" + randomString8Digit() + "\",\"createdAt\":\"" + getUTCNow() + "\"}";
    actions.push_back(action);
}
void sendDelivery(string orderId){
    Json::Value tempRes;
    string actionType = "order.delivered";
    string action;
    action = "{\"type\":\"" + actionType + "\",\"id\":\"" + orderId + "\",\"createdAt\":\"" + getUTCNow() + "\"}";
    actions.push_back(action);
}
string getFoodBuildingId(string foodName){
    int index = 0;
    for(ingridient tempIng : foodIngridients){
        if(foodName == tempIng.food){
            if(index < 9 && index > -1){
                return (state[0]["buildings"]["Fire Pit"][0]["id"].asString());
            }else if(index < 20 && index > 8){
                return (state[0]["buildings"]["Kitchen"][0]["id"].asString());
            }else{
                cout << "out of index";
            }
            break;
        }
        index++;
    }
    return "";
}
string getFoodBuildingName(string foodName){
    int index = 0;
    for(ingridient tempIng : foodIngridients){
        if(foodName == tempIng.food){
            if(index < 9 && index > -1){
                return "Fire Pit";
            }else if(index < 20 && index > 8){
                return "Kitchen";
            }else{
                cout << "out of index";
            }
            break;
        }
        index++;
    }
    return "";
}
void cookFood(string foodName){
    Json::Value tempRes;
    string actionType = "recipe.cooked";
    string action;
    action = "{\"type\":\"" + actionType + "\",\"item\":\"" + foodName + "\",\"buildingId\":\"" + getFoodBuildingId(foodName) + "\",\"createdAt\":\"" + getUTCNow() + "\"}";
    actions.push_back(action);
}
void collectFood(string foodName){
    Json::Value tempRes;
    string actionType = "recipe.collected";
    string action;
    action = "{\"type\":\"" + actionType + "\",\"building\":\"" + getFoodBuildingName(foodName) + "\",\"buildingId\":\"" + getFoodBuildingId(foodName) + "\",\"createdAt\":\"" + getUTCNow() + "\"}";
    actions.push_back(action);
}
void harvestPlot(string plotId){
    Json::Value tempRes;
    string actionType = "crop.harvested";
    string action;
    action = "{\"type\":\"" + actionType + "\",\"index\":\"" + plotId + "\",\"createdAt\":\"" + getUTCNow() + "\"}";
    actions.push_back(action);
}
void collectPlotReward(string plotId){
    Json::Value tempRes;
    string actionType = "cropReward.collected";
    string action;
    action = "{\"type\":\"" + actionType + "\",\"plotIndex\":\"" + plotId + "\",\"createdAt\":\"" + getUTCNow() + "\"}";
    actions.push_back(action);
}
void buySeed(string seedName, string quantity){
    Json::Value tempRes;
    string actionType = "seed.bought";
    string action;
    action = "{\"type\":\"" + actionType + "\",\"item\":\"" + seedName + "\",\"amount\":" + quantity + ",\"createdAt\":\"" + getUTCNow() + "\"}";
    actions.push_back(action);
}
void buyToolSelection(){
    system("cls");
    string select;
    string qty;
    cout<< "Buy Tools" << endl
        << " [0] Axe" << endl
        << " [1] Pickaxe" << endl
        << " [2] Stone Pickaxe" << endl
        << " [3] Iron Pickaxe" << endl;
    cout << "Select Tool : ";
    cin >> select;
    if(select.size() == 1){
        cout << "Quantity : ";
        cin >> qty;
        if(select[0] == '0' && state[0]["stock"].isMember("Axe")){
            if(state[0]["stock"]["Axe"] >= qty){
                buyTool("Axe", qty);
                Json::Value tempRes = sendAction(urlSaveSession + LandId);
                updateData("farm", tempRes);
            }else{
                cout << "Out of Stock" << endl;;
            }
        }else if(select[0] == '1' && state[0]["stock"].isMember("Pickaxe")){
            if(state[0]["stock"]["Pickaxe"] >= qty){
                buyTool("Pickaxe", qty);
                Json::Value tempRes = sendAction(urlSaveSession + LandId);
                updateData("farm", tempRes);
            }else{
                cout << "Out of Stock" << endl;;
            }
        }else if(select[0] == '2' && state[0]["stock"].isMember("Stone Pickaxe")){
            if(state[0]["stock"]["Stone Pickaxe"] >= qty){
                buyTool("Stone Pickaxe", qty);
                Json::Value tempRes = sendAction(urlSaveSession + LandId);
                updateData("farm", tempRes);
            }else{
                cout << "Out of Stock" << endl;;
            }
        }else if(select[0] == '3' && state[0]["stock"].isMember("Iron Pickaxe")){
            if(state[0]["stock"]["Iron Pickaxe"] >= qty){
                buyTool("Iron Pickaxe", qty);
                Json::Value tempRes = sendAction(urlSaveSession + LandId);
                updateData("farm", tempRes);
            }else{
                cout << "Out of Stock" << endl;;
            }
        }else{
            cout << "Invalid Selection" << endl;
        }
    }
}
void buyTool(string toolName, string quantity){
    Json::Value tempRes;
    string actionType = "tool.crafted";
    string action;
    action = "{\"type\":\"" + actionType + "\",\"tool\":\"" + toolName + "\",\"amount\":" + quantity + ",\"createdAt\":\"" + getUTCNow() + "\"}";
    actions.push_back(action);
}
void mineStone(string stoneId){
    Json::Value tempRes;
    string actionType = "stoneRock.mined";
    string action;
    action = "{\"type\":\"" + actionType + "\",\"index\":\"" + stoneId + "\",\"createdAt\":\"" + getUTCNow() + "\"}";
    actions.push_back(action);
}
void chopTree(string treeId){
    Json::Value tempRes;
    string actionType = "timber.chopped";
    string action;
    action = "{\"type\":\"" + actionType + "\",\"index\":\"" + treeId + "\",\"item\":\"Axe" +  "\",\"createdAt\":\"" + getUTCNow() + "\"}";
    actions.push_back(action);
}
Json::Value sendAction(string url){
    try{
        this_thread::sleep_for(delayToSendData);
        sendingActionIdle = false;
        Json::Value tempRes;
        string actionsData;
        int actionSize = actions.size();
        if(actionSize == 1){
            actionsData += actions[0];
        }else if(actionSize > 1){
            for(int i = 0; i < 2; i++){
                actionsData += actions[i];
                if((actionSize > 1) && (i != actionSize - 1)){
                    if(actions[i + 1] != ""){
                        actionsData += ", ";
                    }
                }   
            }
        }
        while(deviceTrackerId == "Empty"){
            refreshSession();
        }
        string tempData = "{\"sessionId\":\"" + session + "\",\"actions\":[" + actionsData + "],\"clientVersion\":\"" + clientVersion + "\",\"cachedKey\":\"" + cachedKey + "\",\"deviceTrackerId\":\"" + deviceTrackerId + "\"}";
        cout << tempData;
        tempRes = postData(url, tokenId, tempData);
        if(!(tempRes.isMember("state") || tempRes.isMember("farm"))){
            cout << endl << tempRes << endl;
            refreshSession();
            return tempRes;
        }else{
            actions.clear();
            cout << "Post Data Done." << endl ;
            this_thread::sleep_for(1000ms);
            return tempRes;
        }
    }catch (exception& e){
        Json::Value tempRes = R"({"failed" : "failed"})";
        return tempRes;
    }
}
string getUTCNow() {
    // Get the current UTC time
    auto currentTime = chrono::system_clock::now();
    auto utcTime = chrono::time_point_cast<chrono::milliseconds>(currentTime);

    // Convert the UTC time to a string in the desired format
    time_t time = chrono::system_clock::to_time_t(utcTime);
    tm* gmTime = gmtime(&time);

    // Format the string
    stringstream ss;
    ss << setfill('0') << setw(4) << gmTime->tm_year + 1900 << "-" << setw(2) << gmTime->tm_mon + 1 << "-" << setw(2) << gmTime->tm_mday << "T" << setw(2) << gmTime->tm_hour << ":" << setw(2) << gmTime->tm_min << ":" << setw(2) << gmTime->tm_sec << "." << setw(3) << utcTime.time_since_epoch().count() % 1000 << "Z";
    string formattedTime = ss.str();

    // Print the formatted UTC time
    return formattedTime;
}
void updateData(string masterKey, Json::Value updatedData){
    Json::Value balance;
    Json::Value bumpkin;
    Json::Value stateData;
    Json::Value inventory;
    Json::Value crops;
    cout << "Updating Data" << endl;
    if (updatedData.isMember(masterKey)){
        state.clear();
        stateData = updatedData[masterKey];
        bumpkin = stateData["bumpkin"];
        balance = stateData["balance"];
        inventory = stateData["inventory"];
        crops = stateData["crops"];
        state.push_back(stateData);
        state.push_back(balance);
        state.push_back(inventory);
        state.push_back(crops);
    }
    sendingActionIdle = true;
    delayToSendData = 1000ms;
    deviceTrackerId = (updatedData.isMember("deviceTrackerId"))? (updatedData["deviceTrackerId"].asString()) : "Empty";

}
void updateEntitiesData(){
    Stone tempStone;
    Tree tempTree;
    Crop tempCrop;
    stones.clear();
    for (const auto& key : state[0]["stones"].getMemberNames()){
        timeMinuteAndSecond tempStoneCooldown;
        tempStone.stoneId = key;
        tempStone.stoneAmount = stoll(state[0]["stones"][key]["stone"]["amount"].asString());
        tempStone.minedAt = stoll(state[0]["stones"][key]["stone"]["minedAt"].asString());
        tempStoneCooldown = getCooldown(tempStone.minedAt);
        tempStone.timeleftMinute = (240 - (tempStoneCooldown.Minute + (tempStoneCooldown.Second/60)));
        stones.push_back(tempStone);
    }
    trees.clear();
    for (const auto& key : state[0]["trees"].getMemberNames()){
        timeMinuteAndSecond tempTreeCooldown;
        tempTree.treeId = key;
        tempTree.treesAmount = stoll(state[0]["trees"][key]["wood"]["amount"].asString());
        tempTree.choppedAt = stoll(state[0]["trees"][key]["wood"]["choppedAt"].asString());
        tempTreeCooldown = getCooldown(tempTree.choppedAt);
        tempTree.timeleftMinute = (120 - (tempTreeCooldown.Minute + (tempTreeCooldown.Second/60)));
        trees.push_back(tempTree);
    }
    crops.clear();
    for (const auto& key : state[3].getMemberNames()) {
        tempCrop.plotsId = key;
        if(state[3][key].isMember("crop")){
            tempCrop.plotsCropName = state[3][key]["crop"]["name"].asString();
            tempCrop.readyPlot = false;
            tempCrop.plotsCropAmount = state[3][key]["crop"]["amount"].asString();
            tempCrop.plotsValue = state[3][key];
            if(state[3][key]["crop"].isMember("reward")){
                tempCrop.reward.rewardName = state[3][key]["crop"]["reward"]["items"][0]["name"].asString();
                tempCrop.reward.rewardAmount = stoi(state[3][key]["crop"]["reward"]["items"][0]["amount"].asString());
            }else{
                tempCrop.reward.rewardName = "No Reward";
                tempCrop.reward.rewardAmount = 0;
            }
            tempCrop.timeLeft = getCooldown(stoll(state[3][key]["crop"]["plantedAt"].asString()));
            tempCrop.timeleftMinute = entityGrowTime[tempCrop.plotsCropName] - (tempCrop.timeLeft.Minute + (tempCrop.timeLeft.Second/60));
        }else{
            tempCrop.plotsCropName = "";
            tempCrop.readyPlot = true;
        }
        crops.push_back(tempCrop);
    }
}
void refreshSession(){
    Json::Value requestBody;
    string jsonData;
    Json::Value tempResSession;
    requestBody["sessionId"] = session;
    requestBody["clientVersion"] = "2023-06-15T03:00";
    requestBody["wallet"] = "METAMASK";
    jsonData = requestBody.toStyledString();
    tempResSession = postData("https://api.sunflower-land.com/session/" + LandId, tokenId, jsonData);
    updateData("farm", tempResSession);
}
void openBotV2(){
    vector<string> readyPlots; //contaions plot id without crop
    vector<string> harvestPlots; //contaions plot id with crop
    this_thread::sleep_for(5000ms);
    Json::Value DeliveryProcess;
    bool firefitAvailable = true;
    bool kitchenAvailable = true;
    Json::Value orderDelivered; // clear every sync
    Json::Value plotHarvested;  // clear every sync
    Json::Value plotPlanted;  // clear every sync
    Json::Value treeChopped;  // clear every sync
    vector<Request> requestBuy;
        thread SyncToDB{[&](){
            while(1){
                Json::Value emptyJson;
                if(actions.size() > 0){
                    cout << "Data Sync " << endl;
                    Json::Value tempRes = sendAction(urlSaveSession + LandId);
                    if(!(tempRes.isMember("failed"))){
                        updateData("farm", tempRes);
                    }
                    actions.clear();
                    orderDelivered.clear(); // clear every sync
                    plotHarvested.clear();  // clear every sync
                    plotPlanted.clear();
                    treeChopped.clear();  // clear every sync
                    this_thread::sleep_for(5000ms);
                }
            } 
        }};
        SyncToDB.detach();
        while(1){
            thread fullfillOrderCompleted{[&](){
                //check all complete order and deliver
                cout << "Process Fulfillment Order " << endl ;
                if(state[0]["delivery"].isMember("orders")){
                    for(Json::Value Orders : state[0]["delivery"]["orders"]){
                        for( auto order : Orders["items"].getMemberNames()){
                            //check if ready to send
                            long long readyAt = stoll(Orders["readyAt"].asString());
                            timeMinuteAndSecond timeLeftMinute = getCooldown(readyAt);
                            int foodNeededInOrder = stoi(Orders["items"][order].asString());
                            int timeLeft = (timeLeftMinute.Minute + (timeLeftMinute.Second/60));
                            string orderId = (Orders["id"].asString());
                            cout << "order " << order << "Ready for " << ((timeLeft > 0)? "Order Ready" : ( timeLeft * 1 + "m")) << endl;
                            if(state[0]["inventory"].isMember(order)){
                                cout << order << ": you have x" << stoi(state[0]["inventory"][order].asString()) << " in bag and order needed " << foodNeededInOrder << endl; 
                                if(stoi(state[0]["inventory"][order].asString()) >= foodNeededInOrder && timeLeft > 0){
                                    cout << "send order" << endl;
                                    if(!(orderDelivered.isMember(orderId))){
                                        sendDelivery(orderId);
                                        orderDelivered[orderId] = "Delivered";
                                    }
                                }
                            }
                        }
                    }
                }
                this_thread::sleep_for(2000ms);
            }};
            thread foodCollect{[&](){
                cout << "Process Collectiong Food Order " << endl ;
                for(Json::Value Orders : state[0]["delivery"]["orders"]){
                    for( auto order : Orders["items"].getMemberNames()){
                        for(auto buildings : state[0]["buildings"].getMemberNames()){
                            if(state[0]["buildings"][buildings][0].isMember("crafting")){
                                if(state[0]["buildings"][buildings][0]["crafting"]["name"].asString() == order){
                                    string craftingFoodName = state[0]["buildings"][buildings][0]["crafting"]["name"].asString();
                                    long long foodReady = stoll(state[0]["buildings"][buildings][0]["crafting"]["readyAt"].asString());
                                    timeMinuteAndSecond timeLeftMinute = getCooldown(foodReady);
                                    int indexOfFood = 0;
                                    while(indexOfFood < foodIngridients.size()){
                                        if(foodIngridients[indexOfFood].food == craftingFoodName){
                                            break;
                                        }
                                        indexOfFood++;
                                    }
                                    int timeLeft = (timeLeftMinute.Minute + (timeLeftMinute.Second/60));
                                    cout << endl <<  "There is item on building : " <<  state[0]["buildings"][buildings][0]["crafting"]["name"].asString() << " Time Left " << timeLeft * -1 << "m" << endl;
                                    if(timeLeft > 0){
                                        collectFood(order);
                                        if(buildings == "Kitchen"){
                                            kitchenAvailable = true;
                                        }else if(buildings == "Fire Pit"){
                                            firefitAvailable = true;
                                        }
                                    }else{
                                        if(buildings == "Kitchen"){
                                            kitchenAvailable = false;
                                        }else if(buildings == "Fire Pit"){
                                            firefitAvailable = false;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                this_thread::sleep_for(1000ms);
            }};
            thread addOrdersRecipe {[&](){  
                try{
                    cout << "Process Adding Orders Recipe " << endl ;
                    cout << ((DeliveryProcess != state[0]["delivery"])? ("Updating Derlivery Data") : ("Data Stil Updated")) << endl;
                    if(DeliveryProcess != state[0]["delivery"]){
                        DeliveryProcess = state[0]["delivery"];
                        resourceToBeProcess.clear();
                        HenHouseToBeProcess.clear();
                        foodRecipesToBeProcess.clear(); 
                        for(Json::Value Orders : DeliveryProcess["orders"]){
                            for( auto order : Orders["items"].getMemberNames()){
                                //cout << order << endl; show orders
                                cout << "Order In Delivery : " << order << endl;
                                bool isResource = false;
                                for(string item : crop){
                                    if(item == order){
                                        foodRecipesToBeProcess.push_back(make_pair(make_pair(order, order), stoi(Orders["items"][order].asString())));
                                        break;
                                    }
                                }
                                for(auto item : foodIngridients){
                                    if(item.food == order){
                                        foodRecipesToBeProcess.push_back(make_pair(make_pair(order, order), stoi(Orders["items"][order].asString())));
                                        cout << "order " << order << endl;
                                        addIngridient(order, stoi(Orders["items"][order].asString()));
                                        break;
                                    }
                                }
                                for(string item : resource){
                                    if(item == order){
                                        resourceToBeProcess.push_back(make_pair(make_pair(order, order), stoi(Orders["items"][order].asString())));
                                        break;
                                    }
                                }
                                for(string item : livestock){
                                    if(item == order){
                                        HenHouseToBeProcess.push_back(make_pair(make_pair(order, order), stoi(Orders["items"][order].asString())));
                                        break;
                                    }
                                }                                                                          
                            }
                        }
                        cout << "Process Adding Orders Done. " << endl ;
                        cout << "Have x" << resourceToBeProcess.size() << " resouces to be process" << endl;
                        cout << "Have x" << foodRecipesToBeProcess.size() << " food to be process" << endl;
                        for(auto pair : foodRecipesToBeProcess){
                            cout << pair.first.first << " x" << pair.second << " for " << pair.first.second << " processing" << endl;
                        }
                    }
                }catch(exception& err){
                    cout << "Exception occurred: " << err.what() << endl;
                }
                this_thread::sleep_for(1000ms);
            }};
            thread ProcessAction{[&](){
                int foodRecipeIndex = 0;
                //<- define all plots
                //process foods
                for(auto pair : foodRecipesToBeProcess){
                    cout << pair.first.first << " x" << pair.second << " for " << pair.first.second << " processing" << endl;
                    //plant all plant
                    thread processCrop{[&](){
                        for(auto cropIndex : crop){
                            //cout << cropIndex << " is " << pair.first.first << endl;
                            if(cropIndex == pair.first.first){
                                cout <<  pair.first.first << " is processing" << endl;
                                if(readyPlots.size() == 0){
                                    //break no plot available
                                    cout << "No plot Available" << endl;
                                    break;
                                }
                                if(state[0]["inventory"].isMember(pair.first.first)){
                                    //have crop on inventory
                                    int cropsInInventory = stoi(state[0]["inventory"][pair.first.first].asString());
                                    int cropsNeeded = pair.second - cropsInInventory;
                                    if(cropsNeeded  > 0 && pair.first.second != "PLANT"){
                                        cout <<  pair.first.first << " is processing 2" << endl;
                                        //proceed have available plot
                                        if(state[0]["inventory"].isMember(pair.first.first + " Seed")){
                                            //have seed
                                            if(!(plotPlanted.isMember(readyPlots[readyPlots.size() - 1]))){
                                                cout << "Order : " << pair.first.first << " planted" << endl;
                                                plantPlot((pair.first.first + " Seed"), readyPlots[readyPlots.size() - 1]);
                                                plotPlanted[readyPlots[readyPlots.size() - 1]] = "Planted";
                                                readyPlots.pop_back();
                                                foodRecipesToBeProcess[foodRecipeIndex].second--;
                                                cropsNeeded--;
                                            }else{
                                                cout << readyPlots[readyPlots.size() - 1] << " already planted" << endl;
                                            }
                                        }else{
                                            Request request;
                                            cout << "Order : " << pair.first.first << " buying seeds" << endl;
                                            request.item = (pair.first.first + " Seed");
                                            request.qty = pair.second;
                                            request.type = " Seed";
                                            requestBuy.push_back(request);
                                            continue;
                                        }
                                    }
                                    if(pair.first.second == "PLANT"){
                                            cout << "Order : " << pair.first.first << " planted (PLANT)" << endl;
                                            if(!(plotPlanted.isMember(readyPlots[readyPlots.size() - 1]))){
                                                plantPlot((pair.first.first + " Seed"), readyPlots[readyPlots.size() - 1]);
                                                plotPlanted[readyPlots[readyPlots.size() - 1]] = "Planted";
                                                readyPlots.pop_back();
                                                foodRecipesToBeProcess[foodRecipeIndex].second--;
                                                cropsNeeded--;
                                            }else{
                                                cout << readyPlots[readyPlots.size() - 1] << " already planted" << endl;
                                            }
                                    }
                                }else{
                                    //plants
                                    cout << "have " << pair.first.first + " Seed in bag?" << endl;
                                     if(state[0]["inventory"].isMember(pair.first.first + " Seed")){
                                            //have seed
                                            //addd loop
                                                if(!(plotPlanted.isMember(readyPlots[readyPlots.size() - 1]))){
                                                    cout << "Order : " << pair.first.first << " planted" << endl;
                                                    plantPlot((pair.first.first + " Seed"), readyPlots[readyPlots.size() - 1]);
                                                    plotPlanted[readyPlots[readyPlots.size() - 1]] = "Planted";
                                                    readyPlots.pop_back();
                                                    foodRecipesToBeProcess[foodRecipeIndex].second--;
                                                }else{
                                                    cout << readyPlots[readyPlots.size() - 1] << " already planted" << endl;
                                                }
                                        }else{
                                            Request request;
                                            cout << "Order : " << pair.first.first << " buying seeds" << endl;
                                            request.item = (pair.first.first + " Seed");
                                            request.qty = pair.second;
                                            request.type = " Seed";
                                            requestBuy.push_back(request);
                                            break;
                                        }
                                    continue;
                                }
                            }
                        }
                    }};
                    thread processFood{[&](){                      
                    //cook all food
                        for(auto food : foodIngridients){
                            //cout << food.food << " is " << pair.first.second << endl;
                            if(food.food == pair.first.second){
                                //verify if food
                                //check inventory
                                if(!(state[0]["inventory"].isMember(pair.first.second))){
                                //have no food on inventory
                                    int ingridientCount = 0;
                                    int ingridientCountDone = 0;
                                    for(auto ingridientTemp : getIngridients(pair.first.second)){
                                        //check recipe in inventory if player have enough
                                        cout << "test 2" << endl;
                                        if(state[0]["inventory"].isMember(ingridientTemp.first)){
                                            cout << "Ingridient : " << ingridientTemp.first << " needed " << ingridientTemp.second << " have " << state[0]["inventory"][ingridientTemp.first].asString() << endl;
                                            if(stoi(state[0]["inventory"][ingridientTemp.first].asString()) >= ingridientTemp.second){
                                                ingridientCountDone++;
                                            }
                                        }
                                        ingridientCount++;
                                    }
                                    if((ingridientCount == ingridientCountDone) && ingridientCountDone != 0 && ingridientCount != 0){
                                        string building = getFoodBuildingName(pair.first.second);
                                        cout << "Cook Food : " << pair.first.second << " On " << building << endl;
                                        if(building == "Fire Pit"){
                                            if(firefitAvailable){
                                                firefitAvailable = false;
                                                cookFood(pair.first.second);
                                            }
                                        }
                                        if(building == "Kitchen"){
                                            if(kitchenAvailable){
                                                kitchenAvailable = false;
                                                cookFood(pair.first.second);
                                            }
                                        }
                                    }
                                }else{
                                    //if have food on bag but food is not enough for order
                                    if(stoi(state[0]["inventory"][pair.first.second].asString()) == pair.second){
                                        continue;
                                    }
                                    if(stoi(state[0]["inventory"][pair.first.second].asString()) < pair.second){
                                        string building = getFoodBuildingName(pair.first.second);
                                        cout << "Cook Food : " << pair.first.second << " On " << building << endl;
                                        if(building == "Fire Pit"){
                                            if(firefitAvailable){
                                                firefitAvailable = false;
                                                cookFood(pair.first.second);
                                            }
                                        }
                                        if(building == "Kitchen"){
                                            if(kitchenAvailable){
                                                kitchenAvailable = false;
                                                cookFood(pair.first.second);
                                            }
                                        }
                                    }
                                }
                                continue;
                            }
                            foodRecipeIndex++;
                        }
                        this_thread::sleep_for(1200ms);
                    }};
                    processCrop.detach();
                    processFood.detach();
                    this_thread::sleep_for(1000ms);
                }  
                this_thread::sleep_for(1000ms);
            }};
            thread harvestAllPlots{[&](){
                readyPlots.clear();
                harvestPlots.clear();
                //define all plots
                for(auto plot : state[0]["crops"].getMemberNames()){
                    if(state[0]["crops"][plot].isMember("crop")){
                        //found a plot with crop
                        long long foodReady = stoll(state[0]["crops"][plot]["crop"]["plantedAt"].asString());
                        timeMinuteAndSecond timeLeftMinute = getCooldown(foodReady);
                        int timeLeft = (entityGrowTime[(state[0]["crops"][plot]["crop"]["name"].asString())]) -(timeLeftMinute.Minute + (timeLeftMinute.Second/60));
                        cout << state[0]["crops"][plot]["crop"]["name"].asString() << " Time Left " << timeLeft << endl;
                        if(timeLeft < 0){
                            harvestPlots.push_back(plot);
                        }
                        // add harvest thread
                    }else{
                        readyPlots.push_back(plot);
                    }
                }
                for(int i = 0; i < harvestPlots.size(); i++){
                    if(!(plotHarvested.isMember(harvestPlots[i]))){
                        harvestPlot(harvestPlots[i]);
                        plotHarvested[harvestPlots[i]] = "Harvested";
                    }
                    this_thread::sleep_for(2000ms);
                }
                 this_thread::sleep_for(2000ms);

                
            }};
            thread processBuyRequests{[&](){
                if(requestBuy.size() > 0){
                    vector<Request> tempRequest;
                    tempRequest = requestBuy;
                    requestBuy.clear();
                    for(auto tempItemOnRequest : tempRequest){
                        if(tempItemOnRequest.type == " Seed"){
                            if(state[0]["stock"].isMember(tempItemOnRequest.item)){
                                if(stoi(state[0]["stock"][tempItemOnRequest.item].asString()) > tempItemOnRequest.qty){
                                    buySeed(tempItemOnRequest.item, to_string(tempItemOnRequest.qty));
                                }
                            }
                        }else if(tempItemOnRequest.type == " Tool"){
                            buyTool(tempItemOnRequest.item, to_string(tempItemOnRequest.qty));
                        }else{
                            cout << "Request Undefined";
                        }
                    }
                }
                this_thread::sleep_for(500ms);
        
            }};
            thread plantCropsNotBasedOnOrders{[&](){
                int seedIndex = crop.size() - 4;
                if(seedIndex < 0){
                    seedIndex = crop.size() - 4;
                }
                this_thread::sleep_for(1000ms);
                cout << "plantCropsNotBasedOnOrders" << endl;
                bool isOrderNeededCrop = false;
                for(auto orderCrop_Food : foodRecipesToBeProcess){
                    for(auto itemCrop : crop){
                        if(orderCrop_Food.first.first == itemCrop){
                            cout << "Order Needed Crop : " << orderCrop_Food.first.first << endl;
                            isOrderNeededCrop = true;
                            break;
                        }
                    }
                    if(isOrderNeededCrop){
                        break;
                    }
                }
                if(!isOrderNeededCrop && readyPlots.size() > 0){
                    cout << "Plant Crop based on stock" << endl;
                    // here the error happen
                    string cropName = crop[seedIndex];
                    cout << "CropName Defined" << endl;
                    if(state[0]["inventory"].isMember(cropName + " Seed")){
                        if(stoi(state[0]["inventory"][cropName + " Seed"].asString()) >= readyPlots.size()){
                            bool alreadyAdded = false;
                            for(auto foodProcess : foodRecipesToBeProcess){
                                if(foodProcess.first.first == cropName){
                                    alreadyAdded =true;
                                }
                            }
                            if(!alreadyAdded){
                                    for(int i = 0; i < readyPlots.size(); i++){
                                        foodRecipesToBeProcess.push_back(make_pair(make_pair(cropName, "PLANT"), 1));
                                    }
                            }
                        }else{
                            seedIndex--;
                        }
                    }else{
                        if(state[0]["stock"].isMember(cropName + " Seed")){
                            if(stoi(state[0]["stock"][cropName + " Seed"].asString()) < readyPlots.size()){
                                bool alreadyAdded = false;
                                for(auto foodProcess : foodRecipesToBeProcess){
                                    if(foodProcess.first.first == cropName){
                                        alreadyAdded =true;
                                    }
                                }
                                if(!alreadyAdded){
                                    Request request;
                                    request.item = cropName + " Seed";
                                    request.qty = readyPlots.size();
                                    request.type = " Seed";
                                    requestBuy.push_back(request);
                                    for(int i = 0; i < readyPlots.size(); i++){
                                        foodRecipesToBeProcess.push_back(make_pair(make_pair(cropName, "PLANT"), 1));
                                    }
                                }                                    
                            }
                        }else{
                            seedIndex--;
                        }
                    }
                }
                
            }};
            thread chopTrees{[&](){
                int axeCount;
                if(state[0]["inventory"].isMember("Axe")){
                    axeCount = stoi(state[0]["inventory"]["Axe"].asString());
                    updateEntitiesData();
                    cout << "You Have x" << axeCount << " Axe" << endl;
                }else{
                    cout << "Your Not Able To Chop You Don't Have Axe On Your Inventory" << endl;
                    axeCount = 0;
                }       
                for(int t = 0; t < trees.size(); t++){
                    if(axeCount == 0){
                        break;
                    }
                    if(trees[t].timeleftMinute < 0){
                        if(!(treeChopped.isMember(trees[t].treeId))){
                            chopTree(trees[t].treeId);
                            treeChopped[trees[t].treeId] = "Chopped";
                        }
                    }
                    this_thread::sleep_for(1000ms);
                }
                this_thread::sleep_for(1000ms);

            }};
            try{
            plantCropsNotBasedOnOrders.join();
            harvestAllPlots.join();
            fullfillOrderCompleted.join();
            foodCollect.join();
            addOrdersRecipe.join();
            ProcessAction.join();
            processBuyRequests.join();
            chopTrees.join();
            }catch(exception& err){
                cout << "Error";
            }
        }

    
}
void addIngridient(string foodName, int multiplier){
    unordered_map<std::string, int> tempIng = getIngridients(foodName);
    int index = 0;
    for(pair<string, int> recipeName : tempIng){
        bool isResource = false;
        bool isCrop = false;
        bool isValidFood = false;
        bool isLivestock = false;
        for(string item : resource){
            if(isValidFood || isLivestock || isCrop) {
                break;
            }
            if(recipeName.first == item){
                isResource = true;
            }
        }
        for(string item : crop){
            if(isValidFood || isLivestock || isResource) {
                break;
            }
            if(recipeName.first == item){
                isCrop = true;
            }
        }
        for(string item : livestock){
            if(isValidFood || isCrop || isResource) {
                break;
            }
            if(recipeName.first == item){
                isCrop = true;
            }
        }
        for(ingridient i : foodIngridients){
            if(isLivestock || isCrop || isResource) {
                break;
            }
            if(i.food == recipeName.first){
                isValidFood = true;
            }
        }
        if(isResource){
            for(int i = 0; i < multiplier; i++){
                resourceToBeProcess.push_back(make_pair(make_pair(recipeName.first, foodName), recipeName.second));
            }
        }else if(isCrop){
            for(int i = 0; i < multiplier; i++){
            foodRecipesToBeProcess.push_back(make_pair(make_pair(recipeName.first, foodName), recipeName.second));
            }
        }else if(isLivestock){
            for(int i = 0; i < multiplier; i++){
            HenHouseToBeProcess.push_back(make_pair(make_pair(recipeName.first, foodName), recipeName.second));
            }
        }else if(isValidFood){
                cout << recipeName.first << " : " << recipeName.second << endl;
                addIngridient(recipeName.first, recipeName.second);
                foodRecipesToBeProcess.push_back(make_pair(make_pair(recipeName.first, foodName), recipeName.second));
        }
        index++;
    }
}
string randomString8Digit(){
    string randomString;
    const string validCharacters = "0123456789abcdef";

    // Random number generation
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, validCharacters.size() - 1);

    // Generate 8-digit random string
    for (int i = 0; i < 8; ++i) {
        randomString += validCharacters[dis(gen)];
    }

    return randomString;
}