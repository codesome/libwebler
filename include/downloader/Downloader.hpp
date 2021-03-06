#ifndef __WEBLER_DOWNLOADER__

#define __WEBLER_DOWNLOADER__

#include <fstream>
#include <cstring>
#include <thread>
#include <mutex>
#include <cmath>
#include <ctime>
#include <vector>
#include <iterator>
#include <algorithm>
#include <curl/curl.h>

#ifndef MAX_NO_OF_THREADS
#define MAX_NO_OF_THREADS 10
#endif

using namespace std;

namespace webler {


  class Downloader
  {
    private:
      string finalUrl;
      string tempName;
      string extension;
      string oFilePath;
      char *contentType;
      ofstream *outPipe;
      int fileSizeResult;
      string downloaddir;
      double fullFileSize;
      vector<string> fileRanges;
      string tempFileNames[MAX_NO_OF_THREADS];
      ofstream tempOutputFiles[MAX_NO_OF_THREADS];
      thread fileThreadsToDownload[MAX_NO_OF_THREADS];
      void (*progressCallback)(double);

      auto FileRanges() -> void;                                                     //Function to calculate the ranges of each file partition.
      auto getDownloadProgress() -> void;                                            //Function to calculate the total download progress.
      auto DetermineFileExtension()  -> void;                                        //Function to determine the extension of the file.
      auto FileSize(const char *url) -> int;                                         //Function to determine the file size.
      auto MergeDownloadedPartitions() -> void;                                      //Function to merge all the downlaoded parts.
      auto getSizeToEnd(ifstream& is) -> streampos;                                  //Function to write into the buffer and then read from the buffer.
      auto GetRandomString(const int len) -> string;                                 //Function to generate random naems for temporary files.
      auto WriteTemporaryPartitions(int index) -> void;                              //Function to write into the temporary partition.
      auto DownloadFile(const char *url, const char *outFile) -> int;                //Function to initiate the download of the file.

    public:
      Downloader();                                                                  //Constructor for the class.
      auto download(string url, string outFile="") -> bool;                          //Functon to take the user-input,
      auto SetProgressCallback(void (*callback)(double)) -> void;                    //Function to set the progress callback

  };

}

#endif
