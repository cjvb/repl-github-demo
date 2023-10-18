git git staggit st#include <fstream>
#include <iostream>
#include <string.h>
#include <string>

using namespace std;

class Rec {
public:
  char orderDate[16];
  char region[16];
  char rep[16];
  char item[64];
  int units;
  float price;

  Rec() {}

  Rec(int u) { units = u; }

  float total() { return units * price; }

  friend ostream &operator<<(ostream &cout, Rec r) {
    return cout << r.orderDate << "," << r.rep << "," << r.item << endl;
  }

  Rec &operator+( const Rec &rb) {
    Rec temp = *this;
    temp.units = this->units + rb.units;
    return temp;
  }

  bool operator==(Rec eq) {
    if (strcmp(orderDate, eq.orderDate) == 0 && strcmp(rep, eq.rep) == 0 &&
        strcmp(item, eq.item) == 0) {
      return true;
    } else {
      return false;
    }
  }
};

int main() {
  std::cout << "Hello More Sales Data!  :)\n";

  ifstream file("SalesDataP5.csv");
  if (!file.is_open()) {
    cout << "Error: Unable to open file.\n";
    return 1;
  }

  const int maxRecords = 50; // Maximum number of records
  Rec records[maxRecords];   // Use a standard array for storing records
  int recordCount = 0;       // Counter for the number of records read

  string tempLine;
  while (getline(file, tempLine)) {
    if (recordCount < maxRecords) {
      // Assuming CSV format: orderDate,region,rep,item,unit,price
      Rec &rec = records[recordCount];
      if (sscanf(tempLine.c_str(), "%[^,],%[^,],%[^,],%[^,],%d,%f",
                 &rec.orderDate[0], &rec.region[0], &rec.rep[0], &rec.item[0],
                 &rec.units, &rec.price) == 6) {
        recordCount++;
      }
    } else {
      cout << "Warning: Maximum record limit reached.\n";
      break;
    }
  }

  file.close();

  for (int i = 0; i < recordCount; i++) {
    bool flag = false;
    for (int j = i + 1; j < recordCount; j++) {
      if (records[i] == records[j] && !flag) {
        records[i] = records[i] + records[j];
        flag = true;
      }
    }
  }

  Rec *cord[recordCount];
  for (int i = 0; i < recordCount; i++) {
    if (records[i].price != 0)
      cord[i] = &records[i];
  }

  for (int i = 0; i < recordCount; i++) {
    for (int j = i; j < recordCount; j++) {
      if (cord[i]->total() < cord[j]->total()) {
        Rec *p = cord[i];
        cord[i] = cord[j];
        cord[j] = p;
      }
    }
  }

  for (int i = 0; i < recordCount - 2; i++) {
    if (cord[i]->price != 0)
      cout << *cord[i];
  }

  return 0;
}