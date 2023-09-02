#include <iostream>
#include <vector>
#include <iomanip>
#include <cctype>
#include <sstream>
#include <string>
#include <functional>
#include <fstream>

using namespace std;
int width = 85;
double totalBill = 0;
int quota;
int isLoop2 = 25;
struct type{
    string type;
    double addonPrice;
};
struct item {
    string category;
    string itemName;
    double itemPrice;
    vector<type> type;
};
struct receipt {
    string  itemAndPrice;
    double subtotal;
    int indexLastEachPrice;
    double itemPrice;
    double quota;
};

vector<item> items = {
    {"Apparel", "Blue Corner T-Shirt", 120.00, {{"Small", 0.00}, {"Large", 20.00}, {"XLarge", 30.00}, {"XXLarge", 35.00}}},
    {"Apparel", "Blouse", 150.00, {{"Small", 0.00}, {"Large", 15.50}, {"XLarge", 30.00}, {"XXLarge", 35.20}}},
    {"Apparel", "Cap", 200.00, {{"Adidas", 0.00}, {"Chicago", 20.00}, {"Trival", 25.00}}},
    {"Apparel", "Jogger Pants", 230.00, {{"Small", 0.00}, {"Large", 20.00}}},
    {"Apparel", "Skinny Jeans Black", 120.00, {{"25", 0.00}, {"26", 5.50}, {"27", 6.00}, {"28", 7.00}, {"29", 7.20}, {"30", 7.20}, {"31", 7.20}, {"32", 7.50}}},
    {"Apparel", "Skinny Jeans Blue", 120.00, {{"25", 0.00}, {"26", 5.50}, {"27", 6.00}, {"28", 7.00}, {"29", 7.20}, {"30", 7.20}, {"31", 7.20}, {"32", 7.50}}},
    {"Apparel", "Short", 80.00, {{"Taslan (unisex)", 0.00}, {"Urban (men)", 75.00}}},
    {"Apparel", "Pajama", 120.00, {{"Fit Size (women)", 00.00}, {"Fit Size (men)", 15.00}}},
    {"Apparel", "Skirt", 80.00, {{"Checkered", 0.00}, {"Classy Slit", 75.00}}},
    {"Apparel", "Jacket", 350.00, {{"Leather", 0.00}, {"Bomber", 0.00}, {"Baseball", 20.10}, {"Embroidery", 330.10}}},
    {"Apparel", "Coat", 240.00, {{"Vintage(women)", 0.00}, {"Trench(jacket)", 120.00}, {"Formal", 280.99}}},
    {"Apparel", "Sweater", 199.00, {{"Plain(unisex)", 0.00}, {"Longsleeves(unisex)", 20.10}}},
    {"Apparel", "belt", 25.00, {{"Leather", 0.00}, {"Korean-Style", 0.00}}},
    {"Apparel", "Scarves", 110.00, {{"Long-Blanket", 0.00},{"Checkered", 0.00}}},
    {"Stationery", "Pen",  8.00,{{"Fiber Castle", 0.00}, {"Panda", 1.50},{"Flexstick", 0.00}}},
    {"Stationery", "Marker",  15.00,{{"Black", 0.00}, {"Blue", 0.00},{"Red", 0.00}}},
    {"Stationery", "Bond paper",  10.00,{{"Small", 0.00}, {"Long", 2.00},{"A4", 5.00}}},
    {"Stationery", "Notebook",  10.00,{{"Small", 10.00}, {"Big", 15.00},{"Catleya", 0.00}}},
    {"Stationery", "Colored Paper",  15.00,{{"Assorted", 0.00}, {"One color", 2.00},{"Two color", 5.00}}},
    {"Stationery", "Folder",  9.00,{{"Short", 0.00}, {"Long", 2.00}}},
    {"Stationery", "Plastic Folder",  12.00,{{"Blue", 1.00}, {"Black", 0.00},{"Red", 1.00}}},
    {"Stationery", "Transparent Plastic Folder",  11.00, {{"Short", 0.00}, {"Long", 2.00}}},
    {"Stationery", "Mighty Bond", 20.00, {}},
    {"Stationery", "Oil Pastel", 55.00, {}},
    {"Stationery", "Crayon", 50.00, {}},
    {"Stationery", "Yellow Paper", 35.00, {}},
    {"Stationery", "Oslo Paper", 20.00, {}},
    {"Stationery", "Glue", 17.00, {}},
    {"Stationery", "Fastener", 17.00, {}},
    {"Stationery", "Erasure", 5.00, {}},
    {"Stationery", "Correction Tape", 25.00, {}},
    {"Stationery", "Poster Paint", 20.00, {}},
    {"Stationery", "Pencil", 8.00, {{"Mongol 1", 0.00}, {"Mongol 2", 0.50}, {"Mongol 3", 1.20}, {"fable-Castle", 1.50}}},
    {"Kitchen Ware", "Bread Toaster",  520.00,{{"Hanabishi", 0.00}, {"Panasonic", 330.00},{"Haier", 430.00}}},
    {"Kitchen Ware", "Oven",  1200.00,{{"Hanabishi", 0.00}, {"Panasonic", 249.00},{"Haier", 300.00}}},
    {"Kitchen Ware", "Blender",  350.00,{{"Hanabishi", 0.00}, {"Panasonic", 80.00},{"Haier", 150.00}}},
    {"Kitchen Ware", "Heater",  750.00,{{"Hanabishi", 0.00}, {"Panasonic", 30.00},{"Haier", 50.00}}},
    {"Kitchen Ware", "Electric Stove",  4000.00,{{"Hanabishi", 0.00}, {"Panasonic", 450.00},{"Haier", 800.00}}},
    {"Kitchen Ware", "Rice Cooker",  900.00,{{"Hanabishi", 0.00}, {"Panasonic", 130.00},{"Haier", 400.00}}},
    {"Kitchen Ware", "Coffee Maker",  2200.00,{{"Hanabishi", 0.00}, {"Panasonic", 300.00},{"Haier", 430.00}}},
    {"Kitchen Ware", "Coffee Grinder",  2500.00,{{"Hanabishi", 0.00}, {"Panasonic", 230.00},{"Haier", 250.00}}},
    {"Kitchen Ware", "Steamer",  720.00,{{"Hanabishi", 0.00}, {"Panasonic", 120.00},{"Haier", 230.00}}},
    {"Kitchen Ware", "Water Dispenser",  5999.00,{{"Hanabishi", 0.00}, {"Panasonic", 400.00},{"Haier", 700.00}}},
    {"Kitchen Ware", "Waffle Maker",  900.00,{{"Hanabishi", 0.00}, {"Panasonic", 330.00},{"Haier", 600.00}}},
    {"DIY Supplies", "Wrench",  120.00,{{"12", 0.00}, {"13", 20.00},{"14", 25.00}}}
};
vector<receipt> receipts;
int itemSize = items.size();
receipt thisReceipt;
int letterToNumber(char);
void ConsoleOutWithCustomWidth(string , char, char, int, bool margin = false, string customMarginLast = "||", string customMarginFirst= "||", string = "");
int processSelection(string, bool, const vector<function<void()>>, const vector<function<void()>> ErrorsAndOthers, char range = 'A');
void ErrorMessage();
void OutOfRangeMessage();
void categorySelection();
void HomePage();
int getIntegerInput();
void loadCart();
void saveCart();
void updateCart();
void viewCart();
void modifyOrder();

int main(){
        while(1){
            system("cls");
            ConsoleOutWithCustomWidth("",'c', '-', width);
            ConsoleOutWithCustomWidth(" GCST Dry Goods Store Ordering System. ",'c', ' ', width, true, "||", "||", "\033[32m");
            ConsoleOutWithCustomWidth("",'c', '-', width);
            ConsoleOutWithCustomWidth("Welcome to GCST Dry Goods Store",'c', ' ', width, true);
            ConsoleOutWithCustomWidth("Your One-Stop Solution for Easy,",'c', ' ', width, true);
            ConsoleOutWithCustomWidth("Convenient, and Hassle-Free Shopping!",'c', ' ', width, true);
            ConsoleOutWithCustomWidth("",'c', '-', width);
            system("pause");
            HomePage();
        }
}
int processSelection(string s, bool isExecuteFunction, const vector<function<void()>> func, const vector<function<void()>> ErrorsAndOthers, char range ) {
    // ErrorsAndOthers == {back, error, out of range}
    if(s.size() == 1 && !(s[0] > 47 && s[0] < 58)){
        char selected;
        selected = s[0];
        if(selected == '<'){
            //back
            return -1;
        }else{
            int corresOption = letterToNumber(selected);
            if((func.size() + 1) > corresOption && isExecuteFunction){
                func[corresOption - 1]();
            }else{
                if(isExecuteFunction){
                    ErrorsAndOthers[0]();
                    return 0;
                }else{
                    if(corresOption > letterToNumber(range)){
                        ErrorsAndOthers[0]();
                        return 0;
                    }
                }
            }
            return corresOption;
        }
    }else{
        // error
        ErrorsAndOthers[1]();
        return 0;
    }
}
void ErrorMessage(){
        ConsoleOutWithCustomWidth("",'c', '-', width);
        ConsoleOutWithCustomWidth("Entered Option is not Valid",'c', ' ', width, true);
        ConsoleOutWithCustomWidth("",'c', '-', width);
        cout << endl;
}
void OutOfRangeMessage(){
        ConsoleOutWithCustomWidth("",'c', '-', width);
        ConsoleOutWithCustomWidth("Out of Range",'c', ' ', width, true);
        ConsoleOutWithCustomWidth("",'c', '-', width);
        cout << endl;
}
void BackOrCancel(){
        ConsoleOutWithCustomWidth("",'c', '-', width);
        ConsoleOutWithCustomWidth("Are sure to back or cancel",'c', ' ', width, true);
        ConsoleOutWithCustomWidth("",'c', '-', width);
        cout << endl;
        system("pause");
}
void HomePage(){
    bool isContinue = true;
    system("cls");
    while(isContinue){
        string option;
        ConsoleOutWithCustomWidth("",'c', '-', width);
        ConsoleOutWithCustomWidth(" GCST Variety Shop Ordering System.",'c', ' ', width, true, "||", "||  (<) Back", "");
        ConsoleOutWithCustomWidth("",'c', '-', width);
        ConsoleOutWithCustomWidth("How may I assist you today?",'c', ' ', width, true);
        ConsoleOutWithCustomWidth("           (A) Order Now ",'l', ' ', width, true);
        ConsoleOutWithCustomWidth("           (B) View Cart ",'l', ' ', width, true);
        ConsoleOutWithCustomWidth("           (C) Modify My Order ",'l', ' ', width, true);
        ConsoleOutWithCustomWidth("",'c', '-', width);
        cout << "I Want To : ";
        cin >> option;
        vector<function<void()>> selections = {categorySelection, viewCart, modifyOrder};
        vector<function<void()>> warnings = {OutOfRangeMessage, ErrorMessage};
        int process = processSelection(option, true, selections, warnings);
        if(process == -1){
            isContinue = false;
        }
    }
}
void categoryPage(){

}
void categorySelection(){
    bool isContinue = true;
    bool isItemSelection = true;
    system("cls");
    while(isContinue){
        system("cls");
        int process2, process3;
        string selectedCategory = "";
        string category = "";
        char categoryChoices = 'A';
        int categorySize = 0;
        totalBill = 0;
        string order;
        string categoryShow;
        char isLoop1;
        char option = 'A';
        string typeName ;
        double typePrice;
        int selectedItemPrice;
        vector<string> categoriesList;
        ConsoleOutWithCustomWidth("",'c', '-', width);
        ConsoleOutWithCustomWidth(" Shop Now. ",'c', ' ', width, true, ("Cart [" + to_string(receipts.size()) + "]  ||"), "||  (<) Back", "");
        ConsoleOutWithCustomWidth("",'c', '-', width);
        for(int categoryIndex = 0; categoryIndex < itemSize; categoryIndex++){
            if(category != items[categoryIndex].category){
                categoriesList.push_back(items[categoryIndex].category);
                categorySize++;
                category = items[categoryIndex].category;
                string str = "              (" +  string(1, categoryChoices) + ") " + category;
                ConsoleOutWithCustomWidth(str,'l', ' ', width, true);
                categoryChoices++;
            }
        }
        ConsoleOutWithCustomWidth("",'c', '-', width);
        cout << "Choose Category (A-" <<--categoryChoices <<") : "  ;
        cin>> selectedCategory;
        vector<function<void()>> selections1 = {};
        vector<function<void()>> warnings1 = {OutOfRangeMessage, ErrorMessage};
        int process1 = processSelection(selectedCategory, false, selections1, warnings1, categoryChoices);
        if(process1 == -1){
            isContinue = false;
            system("cls");
        }else if(process1 > 0 && process1 <= categorySize ){
            system("cls");
            isItemSelection = true;
            while(isItemSelection){
                ConsoleOutWithCustomWidth("",'c', '-', width);
                ConsoleOutWithCustomWidth((categoriesList[process1 - 1]),'c', ' ', width, true, ("Cart [" + to_string(receipts.size()) + "]  ||"), "||  (<) Back", "");
                ConsoleOutWithCustomWidth("",'c', '-', width);
                vector<int> itemSelectedCategoryIndexList;
                char itemChoices = 'A';
                for(int itemIndex = 0; itemIndex < itemSize; itemIndex++){
                    if(items[itemIndex].category == categoriesList[process1 - 1]){
                        itemSelectedCategoryIndexList.push_back(itemIndex);
                        string str = "              (" +  string(1, itemChoices) + ") " + items[itemIndex].itemName;
                        ConsoleOutWithCustomWidth(str,'l', ' ', width, true);
                        itemChoices++;
                    }
                }
                cout<< setfill('-') << setw(width) << ""<<endl;
                cout << "Choose Item (A-" <<--itemChoices <<") : "  ;
                cin>> order;
                process2 = processSelection(order, false, selections1, warnings1, itemChoices);
                bool processOrder = false;
                bool haveType = false;
                string selectedType;
                string orderItemNameWithType = "";
                if(process2 == -1){
                    isItemSelection = false;
                    system("cls");
                }else if(process2 > 0 && process2 < (items.size() + 1)){
                    if(items[itemSelectedCategoryIndexList[process2 - 1]].type.size() > 0){
                        bool isTypeSelection = true;
                        system("cls");
                        while(isTypeSelection){
                            char typeChoices = 'A';
                            string typeSelected;
                            ConsoleOutWithCustomWidth("",'c', '-', width);
                            ConsoleOutWithCustomWidth((items[itemSelectedCategoryIndexList[process2 - 1]].itemName),'c', ' ', width, true, ("Cart [" + to_string(receipts.size()) + "]  ||"), "||  (<) Back", "");
                            ConsoleOutWithCustomWidth("",'c', '-', width);
                            typeName = "";
                            typePrice = 0;
                            selectedItemPrice = 0;
                            int typeSize = items[itemSelectedCategoryIndexList[process2 - 1]].type.size();
                            for(int typeIndex = 0; typeIndex < typeSize; typeIndex++){
                                typeName = items[itemSelectedCategoryIndexList[process2 - 1]].type[typeIndex].type;
                                typePrice = items[itemSelectedCategoryIndexList[process2 - 1]].itemPrice + items[itemSelectedCategoryIndexList[process2 - 1]].type[typeIndex].addonPrice ;
                                string typePriceToString = (to_string(typePrice)).substr(0, (to_string(typePrice).size() - 4));
                                string strTypeNAmeWithSelection = "              (" +  string(1, typeChoices) + ") " + typeName;
                                string strTypePriceWithCurrency = typePriceToString + "Php each ||";
                                ConsoleOutWithCustomWidth(strTypeNAmeWithSelection,'l', ' ', width, true, strTypePriceWithCurrency);
                                typeChoices++;
                            }
                            ConsoleOutWithCustomWidth("",'c', '-', width);
                            cout << "Choose Item (A-" <<--typeChoices <<") : "  ;
                            cin>> typeSelected;
                            process3 = processSelection(typeSelected, false, selections1, warnings1, typeChoices);
                            if(process3 == -1){
                                isTypeSelection = false;
                                system("cls");
                            }else if(process3 > 0){
                                isTypeSelection = false;
                                processOrder = true;
                                haveType = true;
                                selectedType = items[itemSelectedCategoryIndexList[process2 - 1]].type[process3 - 1].type;
                            }
                        }
                    }else{
                        processOrder = true;
                    }
                    if(processOrder){
                        bool isSuccessfullyOrder = false;
                        if(haveType){
                            orderItemNameWithType = items[itemSelectedCategoryIndexList[process2 - 1]].itemName + " " + selectedType;
                            while(!(isSuccessfullyOrder)){
                                cout<<"You Ordered " << orderItemNameWithType <<endl;
                                cout<<" --> How Many Order/s? ";
                                quota = getIntegerInput();
                                if(quota > 0){
                                thisReceipt.quota = quota;
                                double selectedTypePriceCalculated = items[itemSelectedCategoryIndexList[process2 - 1]].itemPrice + items[itemSelectedCategoryIndexList[process2 - 1]].type[process3 - 1].addonPrice;
                                thisReceipt.subtotal = selectedTypePriceCalculated * quota;
                                thisReceipt.itemAndPrice = ("    " + items[itemSelectedCategoryIndexList[process2 - 1]].itemName + " " + selectedType + " x " + to_string(quota));
                                ConsoleOutWithCustomWidth("",'c', '-', width);
                                ConsoleOutWithCustomWidth("Review Order",'c', ' ', width, true);
                                ConsoleOutWithCustomWidth("",'c', '-', width);
                                thisReceipt.indexLastEachPrice = (to_string(items[process2 - 1].itemPrice)).size() - 4;
                                thisReceipt.itemPrice = selectedTypePriceCalculated;
                                receipts.push_back(thisReceipt);
                                totalBill += receipts[receipts.size() - 1].subtotal;
                                stringstream subTotalFixedDecimal;
                                subTotalFixedDecimal << fixed << setprecision(2) << receipts[receipts.size() - 1].subtotal;
                                stringstream selectedPriceFixedDecimal;
                                selectedPriceFixedDecimal << fixed << setprecision(2) << selectedTypePriceCalculated;
                                ConsoleOutWithCustomWidth(receipts[receipts.size() - 1].itemAndPrice,'l', ' ', width, true, (selectedPriceFixedDecimal.str() + "Php " + "each ||"));
                                ConsoleOutWithCustomWidth(("    --> Total" ),'l', ' ', width, true, (subTotalFixedDecimal.str() + "Php ||"));
                                ConsoleOutWithCustomWidth("",'c', '-', width);
                                ConsoleOutWithCustomWidth("Order Successfully Added to your Cart",'c', ' ', width, true);
                                ConsoleOutWithCustomWidth("",'c', '-', width);
                                system("pause");
                                system("cls");
                                isSuccessfullyOrder = true;
                                }
                            }
                        }else{
                            orderItemNameWithType = items[itemSelectedCategoryIndexList[process2 - 1]].itemName;
                            while(!(isSuccessfullyOrder)){
                                cout<<"You Ordered " << orderItemNameWithType <<endl;
                                cout<<" --> How Many Order/s? ";
                                quota = getIntegerInput();
                                if(quota > 0){
                                    thisReceipt.quota = quota;
                                    double selectedTypePriceCalculated = items[itemSelectedCategoryIndexList[process2 - 1]].itemPrice;
                                    stringstream selectedPriceFixedDecimal;
                                    selectedPriceFixedDecimal << fixed << setprecision(2) << selectedTypePriceCalculated;
                                    thisReceipt.subtotal = selectedTypePriceCalculated * quota;
                                    thisReceipt.itemAndPrice = ("    " + items[itemSelectedCategoryIndexList[process2 - 1]].itemName + " " + " x " + to_string(quota));
                                    ConsoleOutWithCustomWidth("",'c', '-', width);
                                    ConsoleOutWithCustomWidth("Order/s Overview",'c', ' ', width, true);
                                    ConsoleOutWithCustomWidth("",'c', '-', width);
                                    thisReceipt.indexLastEachPrice = (to_string(items[process2 - 1].itemPrice)).size() - 4;
                                    thisReceipt.itemPrice = items[itemSelectedCategoryIndexList[process2 - 1]].itemPrice;;
                                    receipts.push_back(thisReceipt);
                                    totalBill += receipts[receipts.size() - 1].subtotal;
                                    stringstream subTotalFixedDecimal;
                                    subTotalFixedDecimal << fixed << setprecision(2) << receipts[receipts.size() - 1].subtotal;
                                    ConsoleOutWithCustomWidth(receipts[receipts.size() - 1].itemAndPrice,'l', ' ', width, true, (selectedPriceFixedDecimal.str() + "Php " + "each ||"));
                                    ConsoleOutWithCustomWidth(("    --> Total" ),'l', ' ', width, true, (subTotalFixedDecimal.str() + "Php ||"));
                                    ConsoleOutWithCustomWidth("",'c', '-', width);
                                    ConsoleOutWithCustomWidth("Order Successfully Added to your Cart",'c', ' ', width, true);
                                    ConsoleOutWithCustomWidth("",'c', '-', width);
                                    system("pause");
                                    system("cls");
                                    isSuccessfullyOrder = true;
                                }
                            }
                        
                            

                        }
                        saveCart();
                    }
                }
            }
        }
    }

    /*
    if (isLoop2==14){
        double serviceCharge = totalBill*0.06;            
        cout<<"Your Bill is Php  "<<totalBill;
        cout<<" + Service Charge (6%) of your bill is Php  "<<serviceCharge<<endl;
        cout<<"Your Total Bill is Php  "<< totalBill + serviceCharge <<endl;
        cout<<" THANK YOU VERY MUCH! "<<endl;
    }
    else{
        cout<<"Invalid Choice, Please Restart" << endl;
    }*/

    /*
        for(int r = 0; r < receipts.size(); r++){
        totalBill += receipts[r].subtotal;
        ConsoleOutWithCustomWidth(receipts[r].itemAndPrice,'l', ' ', width, true, ((to_string(receipts[r].itemPrice)).substr(0, receipts[r].indexLastEachPrice) + "Php " + "each ||"));
        ConsoleOutWithCustomWidth(("    --> Sub-Total" ),'l', ' ', width, true, ("Php " + (to_string(receipts[r].subtotal)) + ".00   ||")); 
        }
    int totalIndexLAst = (to_string(totalBill)).size() - 4; 
    */
}
int letterToNumber(char letter) {
    letter = toupper(letter);
    if (isalpha(letter)) {
        return letter - 'A' + 1;
    }

    // Return 0 if the character is not a letter
    return 0;
}

void ConsoleOutWithCustomWidth(string message, char alignment, char symbol, int width, bool margin, string customMarginLast, string customMarginFirst, string color){
    if(message.size() % 2 == 1){
        message += " ";
    }
    int halfWidth = (width - message.size())/2 ;
    int customMarginLastSizeSpacing, customMarginFirstSizeSpacing;
    customMarginLastSizeSpacing = halfWidth - customMarginLast.size();
    customMarginFirstSizeSpacing = halfWidth - customMarginFirst.size() + 2;
    if(alignment == 'c' || alignment == 'C'){
        if(!(margin)){
            cout<< setfill(symbol) << setw(halfWidth) << "" ;
            cout << color << message << "\033[0m";
            cout << setfill(symbol) << setw(halfWidth + 1) ;
            cout << "\n";
        }else{
            cout << customMarginFirst << setfill(symbol) << setw(customMarginFirstSizeSpacing - 1 ) << "" ;
            cout << color << message << "\033[0m" ;
            cout << setfill(symbol) << setw(customMarginLastSizeSpacing - 1) << "" << customMarginLast;
            cout << "\n";
        }
    }else if(alignment == 'l' || alignment == 'L'){
        if(!(margin)){
            cout << color << message << "\033[0m";
            cout<< setfill(symbol) << setw(halfWidth) << "" ;
            cout << setfill(symbol) << setw(halfWidth + 1) << "";
            cout << "\n";
        }else{
            cout << customMarginFirst << color << message << "\033[0m";
            cout << setfill(symbol) << setw(customMarginFirstSizeSpacing - 1 ) << "" ;
            cout << setfill(symbol) << setw(customMarginLastSizeSpacing - 1) << "" << customMarginLast ;
            cout << "\n";
        }
    }
    
}
int getIntegerInput(){
    string input;
    cin >> input;
    if(input[0] == '<' && input.size() == 1){
        return -1;
    }
    if(input.size() > 0){
        for(int c = 0; c < input.size(); c++){
            for(int l = 0; l <= 127; l++){
                char ch = l;
                if(!((l > 48 && l < 57) || l == 57 || l == 48)){
                    if(input[c] == ch){
                        ErrorMessage();
                        return -2;
                    }
                }
            }
        }
        int processInput = stoi(input);
        return processInput;
    }
}
void loadCart(){
    receipts.clear();
    fstream filestream1;
    string stringInLine;
    filestream1.open("GCST-Shopping-Cart.txt");
    if(!filestream1.fail()){
        while(!filestream1.eof()){
                getline(filestream1, stringInLine);
                    if (!stringInLine.empty()) {
                    receipt receiptTemp;
                    string subtotalTemp, itemPriceTemp, quotaTemp;
                    stringstream ss(stringInLine);
                    getline(ss, receiptTemp.itemAndPrice, ',');
                    getline(ss, subtotalTemp, ',');
                    getline(ss, itemPriceTemp, ',');
                    getline(ss, quotaTemp, ',');
                    receiptTemp.subtotal = stod(subtotalTemp);
                    receiptTemp.itemPrice = stod(itemPriceTemp);
                    receiptTemp.quota = stoi(quotaTemp);
                    receipts.push_back(receiptTemp);  // Add the account to the vector
                }
            }
        filestream1.close();
    }
}
void saveCart(){
    fstream fileStreamer;
    fileStreamer.open("GCST-Shopping-Cart.txt", ios::out | ios::app);
    if(!fileStreamer.fail()){
        fileStreamer << thisReceipt.itemAndPrice << ", "
                     << thisReceipt.subtotal << ", "
                     << thisReceipt.itemPrice << ","
                     << thisReceipt.quota << endl;
    }
    fileStreamer.close();
}
void updateCart(){
    fstream fileStreamer;
    int receiptsSize = receipts.size();
    fileStreamer.open("GCST-Shopping-Cart.txt", ios::out | ios::trunc);
    fileStreamer.close();
    fileStreamer.open("GCST-Shopping-Cart.txt", ios::out | ios::app);
    if(!fileStreamer.fail()){
        for(int l = 0; l < receiptsSize; l++){
            fileStreamer << receipts[l].itemAndPrice << ", "
                     << receipts[l].subtotal << ", "
                     << receipts[l].itemPrice << ","
                     << receipts[l].quota << endl;
        }
    }
    fileStreamer.close();
}
void viewCart(){
    double totalBill;
    loadCart();
    system("cls");
    ConsoleOutWithCustomWidth("",'c', '-', width);
    ConsoleOutWithCustomWidth("Your Cart    ",'c', ' ', width, true, "||", "||  (<) Back", "");
    ConsoleOutWithCustomWidth("",'c', '-', width);
    for(int i = 0; i < receipts.size(); i++){
        ConsoleOutWithCustomWidth(receipts[i].itemAndPrice,'l', ' ', width, true, (to_string(receipts[i].itemPrice).substr(0, (to_string(receipts[i].itemPrice).size() - 4)) + "Php " + "each ||"));
        ConsoleOutWithCustomWidth(("    --> Sub-Total" ),'l', ' ', width, true, (to_string(receipts[i].subtotal).substr(0, (to_string(receipts[i].subtotal).size() - 4)) + "Php ||"));
        ConsoleOutWithCustomWidth("",'c', '-', width);
        totalBill += receipts[i].subtotal;
    }
    if(!(receipts.size() > 0)){
        ConsoleOutWithCustomWidth("",'c', '-', width);
        ConsoleOutWithCustomWidth("Empty Cart",'c', ' ', width, true, "||", "||", "\033[31m");
        ConsoleOutWithCustomWidth("",'c', '-', width);
    }
    cout << endl;
    ConsoleOutWithCustomWidth("",'c', '-', width);
    ConsoleOutWithCustomWidth(("Your Total bill is Php  " + (to_string(totalBill).substr(0, to_string(totalBill).size() - 4))),'c', ' ', width, true, "||", "||", "\033[32m" );
    ConsoleOutWithCustomWidth("",'c', '-', width);
    system("pause");
    system("cls");
}

void modifyOrder(){
    bool isProcessModification = true;
    while(isProcessModification){
        int modifyItem, quantity;
        loadCart();
        system("cls");
        ConsoleOutWithCustomWidth("",'c', '-', width);
        ConsoleOutWithCustomWidth("Modify Your Cart    ",'c', ' ', width, true, "||", "||  (<) Back", "");
        ConsoleOutWithCustomWidth("",'c', '-', width);
        ConsoleOutWithCustomWidth("   Selection             ItemName",'l', ' ', width, true, "Total Price ||");
        ConsoleOutWithCustomWidth("",'c', '-', width);
        for(int i = 0; i < receipts.size(); i++){
            string tempItem = (receipts[i].itemAndPrice).substr(4, (receipts[i].itemAndPrice).size() - 4);
            ConsoleOutWithCustomWidth("     (" + to_string(i + 1) + ")              " + tempItem,'l', ' ', width, true, (to_string(receipts[i].subtotal).substr(0, (to_string(receipts[i].subtotal).size() - 4)) + "Php ||"));
            ConsoleOutWithCustomWidth("",'c', '-', width);
        }
        if(receipts.size() > 0){
            if(receipts.size() == 1){
                cout << "I Want To Modify (1) : " ;
            }else{
                cout << "I Want To Modify (1-" + to_string(receipts.size()) + ") : " ;
            }
            modifyItem = getIntegerInput();
            if(modifyItem == -1){
                isProcessModification = false;
                system("cls");
            }else{
                modifyItem--;
                if(modifyItem >= 0 && modifyItem < receipts.size()){
                cout << "Modify " << (receipts[modifyItem].itemAndPrice).substr(4, (receipts[modifyItem].itemAndPrice).size() - 8) << endl;
                cout << "Change Quantity (0 if remove): ";
                quantity = getIntegerInput();
                    if(quantity > 0){
                        receipts[modifyItem].quota = quantity;
                        receipts[modifyItem].itemAndPrice = (receipts[modifyItem].itemAndPrice).substr(0, (receipts[modifyItem].itemAndPrice).size() - 4) + " x " + to_string(quantity);
                        receipts[modifyItem].subtotal = receipts[modifyItem].itemPrice * quantity;
                        updateCart();
                        cout << endl;
                        ConsoleOutWithCustomWidth(" Applied Changes",'c', '-', width);
                        ConsoleOutWithCustomWidth(receipts[modifyItem].itemAndPrice,'l', ' ', width, true, (to_string(receipts[modifyItem].itemPrice).substr(0, (to_string(receipts[modifyItem].itemPrice).size() - 4)) + "Php " + "each ||"));
                        ConsoleOutWithCustomWidth(("    --> Total" ),'l', ' ', width, true, (to_string(receipts[modifyItem].subtotal).substr(0, (to_string(receipts[modifyItem].subtotal).size() - 4)) + "Php ||"));
                        ConsoleOutWithCustomWidth("",'c', '-', width);
                        system("pause");
                        system("cls");
                    }else if(quantity == 0){
                        receipts.erase(receipts.begin() + modifyItem);
                        updateCart();
                        ConsoleOutWithCustomWidth("",'c', '-', width);
                        ConsoleOutWithCustomWidth(" Item Successfully Remove ",'c', '-', width);
                        ConsoleOutWithCustomWidth("",'c', '-', width);
                        system("pause");
                        system("cls");
                    }else if(quantity == -1){
                        isProcessModification = false;
                        system("cls");
                    }else{
                        system("pause");
                        system("cls");
                    }
                }else{
                    system("pause");
                    system("cls");
                }
            }
        }else{
            ConsoleOutWithCustomWidth("",'c', '-', width);
            ConsoleOutWithCustomWidth("Empty Cart",'c', ' ', width, true, "||", "||", "\033[31m");
            ConsoleOutWithCustomWidth("",'c', '-', width);
            system("pause");
            system("cls");
        }
    }
}
