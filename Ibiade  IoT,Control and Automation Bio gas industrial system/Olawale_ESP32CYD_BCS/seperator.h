
#define data_counter 15
int counter = 0;
String in_data[data_counter];

void separate_words(String str) {
  String word = "";
  int word_index = 0;

  for (auto x : str) {
    if (x == ',') {
      if (word_index < data_counter) {
        in_data[word_index] = word;
        word_index++;
      }
      word = "";
    } else {
      word += x;
    }
  }

  // Add the last word
  if (word_index < data_counter) {
    in_data[word_index] = word;
  }
  // Print out the Data
  // for (int i = 0; i < data_counter; i++) {
  //   Serial.println("output{" + String(i) + "}->" + in_data[i]);
  // }  
}