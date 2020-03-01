type make rainbow to compile rainbow table generator
./rainb file.txt will create hash values from password file file.txt and safe them in file.txt.sha256

make will compile only the brute force application
./brutef file.txt.sha256 somepassword will decrypt some summy data with somepassword's hash value and then try to decript it using hashes in file.txt.sha256
