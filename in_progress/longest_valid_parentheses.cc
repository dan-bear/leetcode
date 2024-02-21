/**
 * https://leetcode.com/problems/longest-valid-parentheses/
 * 
 */

class Solution {
public:
        
    int longestValidParentheses(string s){
        //int res = dpLongestValidParentheses(s);
        int res = bruteForceLongestValidParentheses(s);
        return res;
    }


private:
    //failed on test 228 out of 231 due to time-limit-exceeded error.
    int bruteForceLongestValidParentheses(const string& s){
        int res = 0;
        for(int firstIdx = 0; firstIdx < s.length(); firstIdx++){
            for(int lastIdx = firstIdx + 1; lastIdx < s.length(); lastIdx++){
                if(isValidParentheses(s, firstIdx, lastIdx)){
                    res = max(res, lastIdx - firstIdx + 1);
                }
            }            
        }
        return res;

    }
    
    bool isValidParentheses(const string& s, int firstIdx, int lastIdx){
        int openBrackets = 0;
        for(int idx = firstIdx; idx <= lastIdx && openBrackets >= 0; idx++){
            if(s[idx] == skOpenBracket){
                openBrackets++;
            }else{
                openBrackets--;
            }
        }
        return openBrackets == 0;
    }







    //This solution got run-time exceeded in a very long test
    //227 out of 231 tests.
    int dpLongestValidParentheses(string s) {
        vector<vector<bool>> isValidTbl = calcIsValidDpTbl(s);
        int tblDim = isValidTbl.size();
        int maxPareSubStrLen = 0;
        for(int rowIdx = 0; rowIdx < tblDim; rowIdx++){
            for(int colIdx = rowIdx + 1; colIdx < tblDim; colIdx++){
                if(isValidTbl[rowIdx][colIdx]){
                    maxPareSubStrLen = max(maxPareSubStrLen, colIdx - rowIdx + 1);
                }
            }
        }
        return maxPareSubStrLen;
    }

    vector<vector<bool>> calcIsValidDpTbl(string s){
        int sLen = s.length();
        vector<vector<bool>> isValidTbl(sLen, vector<bool>(sLen, false));
        for(int diagIdx = 0; diagIdx < sLen; diagIdx++){
            for(int rowIdx = 0; rowIdx < sLen - diagIdx; rowIdx++){
                int colIdx = rowIdx + diagIdx;
                isValidTbl[rowIdx][colIdx] = isValid(s, isValidTbl, rowIdx, colIdx);
            }
        }
        return isValidTbl;
    }


    /**
     * define isValid[i][j] to be true if s[i:j] is a valid
     * parentheses and false if s[i:j] is not.
     * 1: isValid[i][i+2*k] = false since s[i:i+2k] contains
     *    odd number of parentheses.
     * 2: isValid[i][i+1] = true <=> s[i:i+1] == "()"
     * 3: isValid[i][j] = true if:
     *    3.1: (j - i) % 2 == 1 //note it's index subtraction
     *    3.2: exists d in range {i, i+1 ,.. j} such that:
     *         s[i] = '(', s[d] = ')' isValid[i+1][d-1] and isValid[d+1][j]
     */
    bool isValid(const string& s, const vector<vector<bool>>& isValidTbl, int rowIdx, int colIdx){
        bool bRes = false;
        if(s[rowIdx] == skOpenBracket && (colIdx - rowIdx) % 2 == 1){
            if(colIdx - rowIdx == 1){
                bRes = (s[colIdx] == skCloseBracket);
            }else{
                for(int closePareIdx = rowIdx + 1; closePareIdx <= colIdx; closePareIdx+=2){
                    if(s[closePareIdx] == skCloseBracket){
                        if(closePareIdx == rowIdx + 1 || isValidTbl[rowIdx + 1][closePareIdx - 1]){
                            if(closePareIdx == colIdx || isValidTbl[closePareIdx + 1][colIdx]){
                                bRes = true;
                                break;
                            }
                        }
                    }
                }
            }
        }
        return bRes;
    }

    static constexpr char skOpenBracket = '(';
    static constexpr char skCloseBracket = ')';
};
