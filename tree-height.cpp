#include <algorithm>
#include <iostream>
#include <vector>
#include <stack>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

class Node;
class Node {
public:
    long key;
    Node *parent;
    std::vector<Node *> children;

    Node() {
      this->parent = NULL;
    }

    void setParent(Node *theParent) {
      parent = theParent;
      parent->children.push_back(this);
    }
};

long findHeight(Node* nodes);
int main_with_large_stack_space() {
  std::ios_base::sync_with_stdio(0);
  long n;
  std::cin >> n;
  long root;
  std::vector<Node> nodes;
  nodes.resize(n);
  for (long child_index = 0; child_index < n; child_index++) {
    long parent_index;
    std::cin >> parent_index;
	if(parent_index == -1)
		root = child_index;
    if (parent_index >= 0)
      nodes[child_index].setParent(&nodes[parent_index]);
    nodes[child_index].key = child_index;
  }
  ;
  std::cout << findHeight(&nodes[root]) << std::endl;
  return 0;
}

int main (int argc, char **argv)
{
#if defined(__unix__) || defined(__APPLE__)
  // Allow larger stack space
  const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
  struct rlimit rl;
  int result;

  result = getrlimit(RLIMIT_STACK, &rl);
  if (result == 0)
  {
      if (rl.rlim_cur < kStackSize)
      {
          rl.rlim_cur = kStackSize;
          result = setrlimit(RLIMIT_STACK, &rl);
          if (result != 0)
          {
              std::cerr << "setrlimit returned result = " << result << std::endl;
          }
      }
  }

#endif
  return main_with_large_stack_space();
}
long findHeight(Node* node){
	long maxHeight=0;
	if(node->children.empty())
		return 1;
	for(long i = 0; i<node->children.size(); i++){
		long nodeHeight = 1+findHeight(node->children[i]);
		if(nodeHeight > maxHeight)
			maxHeight = nodeHeight;
	}
	return maxHeight;
}