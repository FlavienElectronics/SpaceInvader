#include "Utilitaires.h"

Utilitaires::Utilitaires(){}
Utilitaires::~Utilitaires(){}

String Utilitaires::UTILITAIRE_ExtractCommand(const String &message){
  int startIdx = message.indexOf('[');
  int endIdx = message.indexOf(']');
  // Vérifie si les indices sont valides et que la commande est bien formée
  if (startIdx != -1 && endIdx != -1 && endIdx > startIdx + 1) {
    return message.substring(startIdx + 1, endIdx);
  } else {
    return "";
  }
}

String Utilitaires::UTILITAIRE_ExtractValue(const String &message){
  int endIdx = message.indexOf(']');
  if (endIdx != -1 && endIdx < message.length() - 1) {
    return message.substring(endIdx + 1);
  } else {
    return "";
  }
}