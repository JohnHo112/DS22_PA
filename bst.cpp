#include <algorithm>
#include <iostream>
#include <vector>
#include <fstream>
#include <queue>

using namespace std;

class Node
{
public:
    Node *left;
    Node *right;
    int key;

    Node() : left(0), right(0), key(0){};
    Node(int a) : left(0), right(0), key(a){};
};

class BST
{
public:
    Node* root;

    BST(): root(0){};

    Node* constructBST(vector<int> postorderArray, int start, int end){
        if (start > end) return NULL;
        Node* node = new Node(postorderArray[end]);
        int i;
        for (i = end; i >= start; i--){
            if (postorderArray[i] < node->key) break;
        }
        node->right = constructBST(postorderArray, i+1, end-1);
        node->left = constructBST(postorderArray, start, i);
        return node;
    }

    int treeHeight(Node* root){
        if (root == NULL) return 0;
        int leftSubtreeHeight = treeHeight(root->left);
        int rightSubtreeHegiht = treeHeight(root->right);
        return max(leftSubtreeHeight, rightSubtreeHegiht) + 1;
    }

    void findLevelMaxValue_r(vector<int>& ans, Node* root, int h){
        if (root == NULL) return;
        if (ans.size() == h) ans.push_back(root->key);
        else{
            ans[h] = max(ans[h], root->key);
        }
        findLevelMaxValue_r(ans, root->left, h+1);
        findLevelMaxValue_r(ans, root->right, h+1);
    }

    vector<int> findLevelMaxValue(Node* root){
        vector<int> ans;
        findLevelMaxValue_r(ans, root, 0);
        return ans;
    }

    void preorder(Node* root, vector<int>& preorderArray){
        if (root == NULL) return;
        preorderArray.push_back(root->key);
        preorder(root->left, preorderArray);
        preorder(root->right, preorderArray);
    }
    
};

int main(int argc, char *argv[])
    {
        ifstream infile;
        infile.open(argv[1]);
        ofstream outfile;
        outfile.open(argv[2]);

        // TODO: Please code here
        int treeN;
        vector<vector<int>> data;
        vector<int> temp;
        int nodeN, t;

        // get tree number
        infile >> treeN;

        // storage to data of 2D array
        for (int i = 0; i < treeN; i++)
        {
            temp = {};
            infile >> nodeN;
            for (int j = 0; j < nodeN; j++)
            {
                infile >> t;
                temp.push_back(t);
            }
            data.push_back(temp);
        }
        
        // write file
        for (int i = 0; i < treeN; i++){
            // construct tree
            vector<int> preorder;
            BST ans = BST();
            Node* root = ans.constructBST(data[i], 0, data[i].size()-1);
            ans.preorder(root, preorder);

            for (int j = 0; j < preorder.size(); j++){
                outfile << preorder[j] << " ";
            }

            outfile << "\n";

            // print tree height
            int height = ans.treeHeight(root);
            outfile << height << "\n";

            vector<int> res = ans.findLevelMaxValue(root);
            for (int k = 0; k < res.size(); k++){
                outfile << res[k] << "\n";
            }
        }
        

        infile.close();
        outfile.close();
    }