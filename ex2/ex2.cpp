
//data structures:
#include <unordered_map>
#include <map>
#include <iterator>
//io:
#include <iostream>
#include <fstream>
//other functionality:
#include <cmath>
#include <numeric>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>
//namespaces:
typedef boost::tokenizer<boost::char_separator<char>> tokenizer;

//constants:
/**
 * represents Os newline: in windows: \r\n. in linux: \n.
 */
#define OS_NL "\r\n"
#define USAGE_ERR "Usage: <frequent_words.txt> <unknown.txt> <author1.txt> .. <authorN.txt>"
#define FIO_ERR "Error: could not open or read one oor more of the files."

/**
 * gets a ifstream containing a list of frequent words, a ifstream representing an anonymus text.
 * can receive ifstreams of authored texts, and compute their distance from the anonymus text
 * in respect to the frequent words list.
 * can output the closest author text.
 */
class FrequenciesDetector
{
private:
    /**
     * represents a separator(to tell word bounds).
     */
    const boost::char_separator<char> _sep{"\";:! ," OS_NL};

    /**
     * holds the frequent words as lower-cased, no duplications. each has a unique int
     * (all int from 0 to numberOfUniqueWords - 1).
     */
    std::unordered_map<std::string, unsigned long> _fw; //unordered_map for more effective run

    /**
     * holds the vector representing the frequencies in regard to the unknown author.
     */
    std::vector<int> _base;

    /**
    * holds the names of the files and their distance from _base.
    */
    //Iv'e used multimap for finding the first of greatest elements, and maintain duplicaties
    // (according to school solution)
    std::multimap<std::string, double> _distances;

    /**
     * reads the words in <inFile>, and stores them in a _fw without duplications.
     * each word is associated to a unique, non-negative int.
     * those ints are consistent (all int from 0 to (numberOfUniqueWords - 1) appear).
     * assumption: the words in <inFile> are lowercased.
     * @param inFile: the file containing the words.
     */
    void _storeFrequentWords(std::ifstream &inFile)
    {
        std::string currentWord;
        if (inFile)
        {
            while (inFile >> currentWord)
            {
                if (_fw.end() == _fw.find(currentWord)) //not an error: https://youtrack.jetbrains.com/issue/CPP-11511
                {
                    _fw[currentWord] = _fw.size();
                }
            }
        }
    }

    /**
     * @param f: in-stream.
     * @return a vector representing the frequencies in f, according to _fw keying.
     */
    const std::vector<int> _getFrequency(std::ifstream &f)
    {
        std::vector<int> freqVec(_fw.size(), 0);
        std::string sentence;
        while (getline(f, sentence))
        {
            tokenizer wordsInSentence(sentence, _sep);
            for (const std::string &word : wordsInSentence)
            {
                std::string lowerWord = boost::algorithm::to_lower_copy(word);
                for (const auto &frequentWord : _fw)
                {
                    if (lowerWord == frequentWord.first)
                    {
                        ++freqVec[frequentWord.second - 1];
                    }
                }
            }
        }
        return freqVec;
    }

    /**
     * @param begin1: iterator that points at the first element in vec1.
     * @param end1: iterator that points at the end of vec1 (after last element).
     * @param begin2:  iterator that points at the first element in vec2.
     * @param end2: iterator that points at the end of vec2 (after last element).
     * @return: the distance between vec1 and vec2 in radians.
     */
    static const double _distBetweenVectors(std::vector<int> const& v1,
                                            std::vector<int> const& v2)
    {
        double innerProduct = std::inner_product(v1.begin(), v1.end(), v2.begin(), 0.0);
        double norm1 = sqrt(std::inner_product(v1.begin(), v1.end(), v1.begin(), 0.0));
        double norm2 = sqrt(std::inner_product( v2.begin(), v2.end(), v2.begin(), 0.0));
        return (norm1 * norm2 == 0) ? 0 : innerProduct / (norm1 * norm2);
    }

    /**
     * comparator to compare the values of pairs of the form: <key, value>.
     * @param p1: pair<std::string, double>.
     * @param p2: pair<std::string, double>.
     * @return true if the value of p2 is grater than the value of p1. false otherwise.
     */
    static const bool _valueComparator(const std::pair<std::string, double>& p1,
                                       const std::pair<std::string, double>& p2)
    {
        return p1.second < p2.second;
    }

public:

    /**
     * initializes a new FrequenciesDetector, that holds a map of frequent words given in <inFile>.
     * @param inFile stream holding the frequent words.
     */
    FrequenciesDetector(std::ifstream &inFile, std::ifstream &baseFile)
    {
        _storeFrequentWords(inFile);
        _base = _getFrequency(baseFile);
    }

    /**
     * computes the distance between this file and the base file.
     * prints it at the format: "<fName> <distance>\n".
     * @param f : in file stream.
     * @param fName : f's name (as given to the program).
     */
    void processFile(std::ifstream &f, const std::string &fName)
    {
        double dist = _distBetweenVectors(_base, _getFrequency(f));
        _distances.insert({fName, dist});

        std::cout << fName << " " << dist << std::endl;
    }

    /**
     * prints the greatest distanced file (among the files that has been entered up to this point)
     * in the format: "Best matching author is <fName> score <distance>\n".
     */
    void maxDistance() const
    {
        auto maxElement = std::max_element(_distances.begin(), _distances.end(), _valueComparator);
        // i assume frequent_words and unknown exists (so max element->first isn't " " like in school sol).
        std::cout << "Best matching author is " << maxElement->first <<
             " score " << maxElement->second << std::endl;
    }
};

/**
 * runs the find_the_author program
 * @param argc: number of program arguments
 * @param argv: list of program's argument (argv[0] = the name of the program).
 * @return 0 if succeed, prints informative error msg and exits with failure otherwise.
 */
int main(int argc, char* argv[])
{
    if (argc > 3)
    {
        std::ifstream frequentWordsFile(argv[1]);
        std::ifstream unknownFile(argv[2]);
        if (unknownFile && frequentWordsFile)
        {
            FrequenciesDetector fd(frequentWordsFile , unknownFile);
            unknownFile.close();
            frequentWordsFile.close();
            std::ifstream tmpFile;
            for (unsigned int i = 3; i < argc; ++i)
            {
                tmpFile.open(argv[i]);
                fd.processFile(tmpFile, argv[i]);
                if (tmpfile)
                {
                    tmpFile.close();
                }
                else
                {
                    std::cerr << FIO_ERR << std::endl;
                    exit(EXIT_FAILURE);
                }
            }
            fd.maxDistance();
            return 0;
        }
        std::cerr << FIO_ERR << std::endl;
        exit(EXIT_FAILURE);
    }
    std::cerr << USAGE_ERR << std::endl;
    exit(EXIT_FAILURE);
}