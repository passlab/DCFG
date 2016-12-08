// Example ParseAPI program; produces a graph (in DOT format) of the
// control flow graph of the provided binary. 
//
// Improvements by E. Robbins (er209 at kent dot ac dot uk)
// Improvements by Xiaozhu Meng (xmeng at cs dot wisc dot edu)

#include <stdio.h>
#include <map>
#include <vector>
#include <unordered_map>
#include <sstream>
#include "CodeObject.h"
#include "CFG.h"

#include "Instruction.h"
#include "InstructionDecoder.h"


using namespace std;
using namespace Dyninst;
using namespace ParseAPI;
using namespace InstructionAPI;

string binFileName;
string outFileName;
set<string> namePatterns;
bool decodeInsns = false;
FILE *out;

bool ParseCommandLine(int argc, char * argv[]) {
    int i;
    for (i = 1; i < argc; ++i)
        if (argv[i][0] == '-') {
	    switch (argv[i][1]) {
	        case 'i':
		    decodeInsns = true;
		    break;
		case 'n': {
		    ++i;
		    istringstream ins(string(argv[i]));
		    string name;
		    while (ins >> name) {
		        namePatterns.insert(name);		    
		    }
		    break;
		}
		case 'o':
		    ++i;
		    outFileName = string(argv[i]);
		    break;
		default:
		    return false;
	    }
	} else {
	    binFileName = string(argv[i]);
	    break;
	}
    if (binFileName != "") return true;
    return false;
}

void PrintUsage() {
    printf("Usage: ./CFG [options] binFile\n"
           "-i: Output the instructions in each basic blocks\n"
	   "-n patterns: filter functions by matching the function names using the specified pattern\n"
	   "Example: -n \"foo bar\" means only output CFG for functions with function names containing substring \"foo\" or \"bar\"\n"
	   "-o outFileName: Specify the output file name\n");
}

bool MatchPatterns(const char *name) {
    if (namePatterns.empty()) return true;
    for (auto pit = namePatterns.begin(); pit != namePatterns.end(); ++pit)
        if (strstr(name, pit->c_str()) != NULL) return true;
    return false;
}

void PrintBlockInfo(Block* b) {
    fprintf(out, "\t\t\"%lx\"", b->start());
    fprintf(out, "[shape=box,label=\"[%lx,%lx)", b->start(), b->end());
    if (decodeInsns) {
        const unsigned char* buf = (const unsigned char*) b->obj()->cs()->getPtrToInstruction(b->start());
	InstructionDecoder dec(buf, b->end() - b->start(), b->obj()->cs()->getArch());
	Instruction::Ptr insn;
	
	Address curAddr = b->start();
	// Decode all instructions in the basic block
	while ( (insn = dec.decode()) != NULL ) {
   	    fprintf(out, "\\n%lx : %s", curAddr, insn->format().c_str());
	    curAddr += insn->size();
	}	
    }
    fprintf(out, "\"];\n");   
}

void GetLoopInFunc(Function *f) { 
    // Get all loops in the function 
    vector<Loop*> loops;
    f->getLoops(loops);
    FILE * out = fopen(f->name().c_str(), "w");

    fprintf(out, "digraph G{\n"); 
    // Iterate over all loops
    for (auto lit = loops.begin(); lit != loops.end(); ++lit) {
        Loop *loop = * lit;
        // Get all the entry blocks of the loop
	vector<Block*> entries; 
        loop->getLoopEntries(entries);

        // Get all the blocks in the loop
        vector<Block*> blocks;
        loop->getLoopBasicBlocks(blocks);
        // Get all the back edges in the loop
        vector<Edge*> backEdges;
        loop->getBackEdges(backEdges);

    }
}

int main(int argc, char * argv[])
{
   if (!ParseCommandLine(argc, argv)) {
       PrintUsage();
       exit(-1);
   }
   map<Address, bool> seen;
   set<Block*> targetBlocks;
   set<pair<Block*, Block*> > printEdges;
   SymtabCodeSource *sts;
   CodeObject *co;

   if (outFileName == "") out = stdout;
   else out = fopen(outFileName.c_str(), "w");
   
   // Create a new binary code object from the filename argument
   sts = new SymtabCodeSource( (char*)binFileName.c_str() );
   co = new CodeObject( sts );
   
   // Parse the binary
   co->parse();

   for (auto fit = co->funcs().begin(); fit != co->funcs().end(); ++fit) {
       Function *f = *fit;
       if (!MatchPatterns(f->name().c_str())) continue;
       for (auto bit = f->blocks().begin(); bit != f->blocks().end(); ++bit) {
	   targetBlocks.insert(*bit);
       }
   }


   fprintf(out, "digraph G{\n"); 

   // Print the control flow graph
   const CodeObject::funclist& all = co->funcs();
   // Visit all functions
   auto fit = all.begin();
   for(int i = 0; fit != all.end(); ++fit) { // i is index for clusters
      Function *f = *fit;
      if (!MatchPatterns(f->name().c_str())) continue;
      ++i;
      // Make a cluster for nodes of this function
      fprintf(out, "\t subgraph cluster_%d {\n", i);
      fprintf(out, "\t\t label=\"%s\"\n", f->name().c_str());
      fprintf(out, "\t\t shape=box\n");
      if (f->retstatus() == NORETURN)
          fprintf(out, "\t\t color=red\n");
      else
          fprintf(out, "\t\t color=black\n");


      stringstream edgeoutput;
      
      // Visit all basic blocks in the function
      auto bit = f->blocks().begin();
      for( ; bit != f->blocks().end(); ++bit) {
         Block *b = *bit;
         // Don't revisit blocks in shared code
         if(seen.find(b->start()) != seen.end())
            continue;
         
         seen[b->start()] = true;

	 PrintBlockInfo(b);
         
	 // Enumerate all outgoing edges of the basic block
         auto it = b->targets().begin();
         for( ; it != b->targets().end(); ++it) {
	    if ((*it)->sinkEdge()) continue;
	    // We only draw an edge when both ends of the edge are in target functions
	    if (targetBlocks.find((*it)->trg()) == targetBlocks.end()) continue;
	    // We only draw one edge between from one basic block to another
	    if (printEdges.find(make_pair(b, (*it)->trg())) != printEdges.end()) continue;
	    printEdges.insert(make_pair(b , (*it)->trg()));
            
            std::string s = "";
            if((*it)->type() == CALL)
               s = " [color=blue]";
            else if((*it)->type() == RET)
               s = " [color=green]";

            // Store the edges somewhere to be printed outside of the cluster
            edgeoutput << "\t\"" 
                       << hex << (*it)->src()->start()
                       << "\" -> \""
                       << (*it)->trg()->start()
                       << "\"" << s << endl;
         }
      }
      // End cluster
      fprintf(out, "\t}\n");

      // Print edges
      fprintf(out, "%s\n", edgeoutput.str().c_str());
   }
   fprintf(out, "}\n");
}
