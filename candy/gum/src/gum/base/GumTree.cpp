#include <gum/base/GumTree.hpp>

namespace Candy::Gum
{
  GumTree::GumTree()
  {
    root = new GumObject();
  }
  GumTree::~GumTree()
  {
  
  }
  
  GumObject& GumTree::GetRoot()
  {
    return *root;
  }
}