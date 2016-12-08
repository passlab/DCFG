#! /usr/bin/env python
# @ORIGINAL_AUTHOR: Robert Muth
#
# python.org has useful info about the Python programming language
#
# The Python library is described here: http://docs.python.org/lib/lib.html
# An the index for the library here: http://docs.python.org/lib/genindex.html

import sys
import os
import getopt
import re
import string
import copy

#######################################################################
# Version
#######################################################################

def Version():
    
    (l,v,x) = string.split('$Revision: 1.5 $')
    return v

#######################################################################
# Usage
#######################################################################

def Usage():
    print "<!--Usage: flowgraph.py [OPTION]+ assembler-listing edge-profile-->"
    print
    print "<!--flowgraph converts a disassembled routine into a flowgraph which can be rendered using vcg-->" 
    print
    print "<!--assembler-listing is a textual disassembler listing generated with-->"
    print "<!--objdump-routine.csh or directly with objdump-->"
    print
    print "<!--edge-profile is a profile generated with the edgcnt Pin tool-->"

    
    return -1

#######################################################################
# Messages
#######################################################################

def Info(str):
    print >> sys.stderr,"I:",str
    return

def Warning(str):
    print >> sys.stderr,"W:", str
    return

def Error(str):
    print >> sys.stderr, "E:",str
    sys.exit(-1)


#######################################################################
# 
#######################################################################
#  402d05:       41 56                   push   %r14

PatternNoFallthrough = re.compile(r'call|ret|jmp')
PatternCall = re.compile(r'call')

class INS:
    def __init__(self, addr, opcode ):
        self._addr = addr
        self._opcode = opcode
        self._next = None
        self._leader = 0
        self._bbl = None
        return

    def get_opcode(self):
        return self._opcode
 
    def set_next(self,next):
        self._next = next
        return

    def get_next(self):
        return self._next
                   
    def get_addr(self):
        return self._addr

    def get_leader(self):
        return self._leader
                   
    def set_leader(self,leader):
        self._leader = leader

    def get_bbl(self):
        return self._bbl
                   
    def set_bbl(self,bbl):
        self._bbl = bbl

    def has_no_fallthru(self):
        return PatternNoFallthrough.search(self._opcode)

    def is_call(self):
        return PatternCall.search(self._opcode)
                   
#######################################################################
##
#######################################################################

ALL_INS = {}

PatternAssemler = re.compile(r'^\s*([0-9a-fA-F]+):\s*(?:[0-9a-fA-F][0-9a-fA-F] )+\s*(.+)$')


def ProcessAssemblerListing(lines):
    last_ins = None

    for l in lines:
        match =  PatternAssemler.match(l)
        if not match:
#            print "bad line ",l
            continue
        addr = long(match.group(1),16)
        ins = INS( addr,  match.group(2) )
        ALL_INS[addr] = ins
        if last_ins:
           last_ins.set_next(ins)
        last_ins = ins  
    return

#######################################################################
#  0x0000000000400366 0x0000000000402300         2182

PatternEdge2 = re.compile(r'^\s*0x([0-9a-fA-F]+)\s+0x([0-9a-fA-F]+)\s+([0-9]+)\s*$')
PatternEdge3 = re.compile(r'^\s*0x([0-9a-fA-F]+)\s+0x([0-9a-fA-F]+)\s+([a-zA-Z])\s+([0-9]+)\s*$')
PatternEdge4 = re.compile(r'^\s*0x([0-9a-fA-F]+)\s+0x([0-9a-fA-F]+)\s+([a-zA-Z])\s+([0-9]+)\s+0x([0-9a-fA-F]+)$')

def ProcessEdgProfile(lines):

    
    version = string.split(lines[0])

    if version[0] != "EDGCOUNT":
        Error("files is not an edge profile")

    if version[1] == "2.0":
        v = 2
    elif version[1] == "3.0":
        v = 3
    elif version[1] == "4.0":
        v = 4 
    else:
        Error("unsupported  edge profile version")
        
    edg_list = []

    for l in lines[1:]:
        if v == 2:
            match = PatternEdge2.match(l)
        elif v==3:
            match = PatternEdge3.match(l)
        elif v==4:
            match = PatternEdge4.match(l)

        if not match: continue

        if v == 2:
            src = long(match.group(1),16)
            dst = long(match.group(2),16)
            count = long(match.group(3))
            type = "u"
        elif v == 3 or v == 4:
            src = long(match.group(1),16)
            dst = long(match.group(2),16)
            type = match.group(3)
            count = long(match.group(4))

        if ALL_INS.has_key(src):
            next = ALL_INS[src].get_next()
            if next: next.set_leader(1)

        if ALL_INS.has_key(dst):    
            ins = ALL_INS[dst]
            ins.set_leader(1)

        if ALL_INS.has_key(src) or ALL_INS.has_key(dst):
            edg_list.append( (src,dst,count,type) )            
    return edg_list

#######################################################################
# 
#######################################################################
class EDG:
    def __init__(self,src,dst,count, type):
        self._src = src
        self._dst = dst
        self._count = count
        self._type = type
        return

    def is_fallthru(self):
        return self._fallthru
    
    def StringVCG(self, threshold = 100000000000L):
        s = ""
        if self._count > threshold:
            s += "\t" + "nearedge:\n"
        else:
            s += "\t" + "edge:\n"
        
        s += "\t{\n"    
        s += "\t\t" + "sourcename: \"" + hex(self._src._start) + "\"\n"
        s += "\t\t" + "targetname: \"" + hex(self._dst._start) + "\"\n"
        if self._type == "F" or self._type == "L":
            s += "\t\t" + "thickness: 4\n"
        else:
            s += "\t\t" + "thickness: 2\n"

        s += "\t\t" + "label: \"%s(%d)\"\n" % (self._type,self._count)
            
#        s += "\t\t" + "priority: %d\n" % self._count                        
        s += "\t}\n" 
	   
        return s

############################################################################################################

    def StringGraphML(self, threshold = 100000000000L):
        s = ""
	
	s +="<edge id=\"%s(%d)\"" % (self._type,self._count) + " source=\"" + hex(self._src._start) + "\" target=\"" + hex(self._dst._start) + "\">\n"
   	s +="<data key=\"d9\"/>\n"
      	s +="<data key=\"d10\">\n"
        s +="<y:PolyLineEdge>\n"
        s +="<y:Path sx=\"0.0\" sy=\"0.0\" tx=\"0.0\" ty=\"0.0\"/>\n"
        s +="<y:LineStyle color=\"#000000\" type=\"line\" width=\"3.0\"/>\n"
        s +="<y:Arrows source=\"none\" target=\"standard\"/>\n"
        s +="<y:EdgeLabel alignment=\"center\" configuration=\"AutoFlippingLabel\" distance=\"2.0\" fontFamily=\"Dialog\" fontSize=\"23\" fontStyle=\"plain\" hasBackgroundColor=\"false\" hasLineColor=\"false\" height=\"17.96875\" horizontalTextPosition=\"center\" iconTextGap=\"4\" modelName=\"custom\" preferredPlacement=\"anywhere\" ratio=\"0.5\" textColor=\"#000000\" verticalTextPosition=\"bottom\" visible=\"true\" width=\"45.44921875\" x=\"-52.724609375\" y=\"51.55029296875\">"
	if self._type == "F" or self._type == "L":
		s +="4<y:LabelModel>\n"
	else:
		s +="2<y:LabelModel>\n"
        s +="<y:SmartEdgeLabelModel autoRotationEnabled=\"false\" defaultAngle=\"0.0\" defaultDistance=\"10.0\"/>\n"
        s +="</y:LabelModel>\n"
        s +="<y:ModelParameter>\n"
        s +="<y:SmartEdgeLabelModelParameter angle=\"0.0\" distance=\"30.0\" distanceToCenter=\"true\" position=\"right\" ratio=\"0.5\" segment=\"0\"/>\n"
        s +="</y:ModelParameter>\n"
        s +="<y:PreferredPlacementDescriptor angle=\"0.0\" angleOffsetOnRightSide=\"0\" angleReference=\"absolute\" angleRotationOnRightSide=\"co\" distance=\"-1.0\" frozen=\"true\" placement=\"anywhere\" side=\"anywhere\" sideReference=\"relative_to_edge_flow\"/>\n"
        s +="</y:EdgeLabel>\n"
        s +="<y:BendStyle smoothed=\"false\"/>\n"
        s +="</y:PolyLineEdge>\n"
      	s +="</data>\n"
    	s +="</edge>\n"

        return s





    def StringDOT(self, threshold = 100000000000L):
        s = ""
        return s
        
#######################################################################



class BBL:
    def __init__(self,start):
        self._start = start
        self._ins = []
        self._in = []
        self._out = []
        self._count = 0
        self._in_count = 0
        self._out_count = 0
        self._next = None
        return
    
    def add_ins(self,ins):
        self._ins.append(ins)
        self._end = ins.get_addr()
        return

    def set_count(self,count):
        assert( self._count == 0 )
        self._count = count
        return

    def add_out_edg(self, edg ):
        self._out.append(edg)
        return
                             
    def add_in_edg(self, edg ):
        self._in.append(edg)
        return

    def add_in_count(self, count ):
        self._in_count += count
        return

    def add_out_count(self, count ):
        self._out_count += count
        return

    def count_in(self):
        count = self._in_count
        for e in  self._in: count += e._count
        return count

    def count_out(self):
        count = self._out_count
        for e in  self._out: count += e._count
        return count

    def set_next(self,next):
        self._next = next
        return

    def get_next(self):
        return self._next

    def get_start(self):
        return self._start

    def is_call(self):
        return  self._ins[-1].is_call()

    def has_no_fallthru(self):
        return  self._ins[-1].has_no_fallthru()



    def String(self):
        s = "BBL  at %x  count %d   (i: %d  o: %d)\n" % (self._start, self._count, self._in_count, self._out_count)

        s += "i:  "
        for edg in self._in:
            s += "%x (%d)  " % (edg._src.get_start(),edg._count)
        s += "\n"

        s += "o:  "
        for edg in self._out:
            s += "%x (%d)  " % (edg._dst.get_start(),edg._count)
        s += "\n"

        for ins in self._ins:
            s += "%x %s\n" % (ins.get_addr(),ins.get_opcode())
        return s


    def StringVCG(self,threshold=1000):
        s = "\t" + "node:\n"
        s += "\t" + "{\n"
        if self._count > threshold:
            s += "\t\t" + "color: red\n"            
        s += "\t\t" + "title: \"" + hex(self._start) + "\"\n"
        s += "\t\t" + "label: \"" + hex(self._start) + " (" + str(self._count) + ")\\n"
        for ins in self._ins:             s += "%x: %s\\n" % (ins.get_addr(),ins.get_opcode())
        s += "\"\n"
        s += "\t" + "}\n"
 	
        return s
#####################################################################################################################
    def StringGraphML(self, threshold = 1000):
	s = ""
        o = ""
	s +="<node id=\""+ hex(self._start) +"\">\n"
	s +="<data key=\"d5\"/>\n"
	s +="<data key=\"d6\">\n"
	s +="<y:GenericNode configuration=\"ShinyPlateNode3\">\n"
	s +="<y:Geometry height=\"179.0\" width=\"343.0\" x=\"338.5\" y=\"330.5\"/>\n"
	s +="<y:Fill color=\"#FF8368\" transparent=\"false\"/>\n"
	s +="<y:BorderStyle color=\"#0000FF\" type=\"line\" width=\"2.0\"/>\n"
	s +="<y:NodeLabel alignment=\"left\" autoSizePolicy=\"node_size\" configuration=\"CroppingLabel\" fontFamily=\"Dialog\" fontSize=\"23\" fontStyle=\"plain\" hasBackgroundColor=\"false\" hasLineColor=\"false\" height=\"150\" horizontalTextPosition=\"center\" iconTextGap=\"4\" modelName=\"custom\" textColor=\"#000000\" verticalTextPosition=\"bottom\" visible=\"true\" width=\"150\" x=\"148.8017578125\" y=\"80.515625\">"+ hex(self._start) + "(" + str(self._count) + ")" 
	for ins in self._ins:   
		o = ins.get_opcode()     
		o = string.replace(o, "<" , "&lt;")  
		o = string.replace(o, ">" , "&gt;")
		s += " \n %x : %s " % (ins.get_addr(),o)
	s +="<y:LabelModel>\n"
	s +="<y:SmartNodeLabelModel distance=\"4.0\"/>\n"
	s +="</y:LabelModel>\n"
	s +="<y:ModelParameter>\n"
	s +="<y:SmartNodeLabelModelParameter labelRatioX=\"0.0\" labelRatioY=\"0.0\" nodeRatioX=\"0.0\" nodeRatioY=\"0.0\" offsetX=\"0.0\" offsetY=\"0.0\" upX=\"0.0\" upY=\"-1.0\"/>\n"
	s +="</y:ModelParameter>\n"
	s +="</y:NodeLabel>\n"
	s +="</y:GenericNode>\n"
	s +="</data>\n"
	s +="</node>\n"
	#for ins in self._ins:             s += "%x: %s\\n" % (ins.get_addr(),ins.get_opcode())
        return s


    def StringDOT(self, threshold = 1000):
        s = ""
        return s
    
#######################################################################
#
#######################################################################
ALL_BBL = {}
ALL_EDG = []


#######################################################################
#
#######################################################################

def CreateCFG(edg_list):
    no_interproc_edges = 1

    ins_list = ALL_INS.items()
    ins_list.sort() # by addr

    bbl_list = []

    Info("BBL create")

    last = None
    for (a,ins) in ins_list:

        if ins.get_leader():
           start = ins.get_addr()
           bbl = BBL(start)               
           bbl_list.append(bbl)
           ALL_BBL[start] = bbl
           if last: last.set_next( bbl )
           last = bbl
               
        last.add_ins( ins )
        ins.set_bbl( last )

        if ins.has_no_fallthru():
           next = ins.get_next()
           if next: next.set_leader(1)

    Info( "Created %d bbls" % len(bbl_list))     
#    for bbl in bbl_list: print bbl.String()

    Info( "EDG create")
    
    for (src,dst,count,type) in edg_list:

        if ALL_INS.has_key(src):
            bbl_src = ALL_INS[src].get_bbl()
        else:
            assert( ALL_BBL.has_key(dst) )
            if no_interproc_edges:
                ALL_BBL[dst].add_in_count(count)
                continue             
            bbl_src = BBL(src)
            ALL_BBL[src] = bbl_src

        if ALL_BBL.has_key(dst):
            bbl_dst = ALL_BBL[dst]
        else:
            if no_interproc_edges:
                bbl_src.add_out_count(count)
                continue             
        
            bbl_dst = BBL(dst)
            ALL_BBL[dst] = bbl_dst

                
        edg = EDG( bbl_src, bbl_dst, count, type)
        ALL_EDG.append( edg )
        bbl_src.add_out_edg( edg )
        bbl_dst.add_in_edg( edg )


    Info("propagate counts and add fallthrus")

    for bbl in bbl_list:
        count = bbl.count_in()
        bbl.set_count(count)
        count -= bbl.count_out()        
        if count < 0:
            Warning("negative fallthru count")
            count = 0        

        next = bbl.get_next() 
                        
        if count > 0:
           if bbl.has_no_fallthru():
              Info("losing flow %d\n" % count)
           elif next:               
                edg = EDG(bbl,next,count,"F")
                ALL_EDG.append( edg )
                bbl.add_out_edg( edg )
                next.add_in_edg( edg )

        if bbl.is_call() and next:
            edg = EDG(bbl,next, 0,"L")
            ALL_EDG.append( edg )
            bbl.add_out_edg( edg )
            next.add_in_edg( edg )

#    for bbl in bbl_list: print bbl.String()
    return bbl_list

def DumpVCG():
    start = 0
    end = 0 
    print  "// ###################################################################################"
    print  "// VCG Flowgraph for %x - %x" % (start,end)
    print  "// ###################################################################################"
 
    print  "graph:"
    print  "{";

    print "title: \"Control Flow Graph for rtn %x - %x \"" % (start,end);
    print "label: \"Control Flow Graph for rtn %x - %x \"" % (start,end);
    print "display_edge_labels: yes"
    print "layout_downfactor: 100"
    print "layout_nearfactor: 10"
    print "layout_upfactor: 1"
#    print "dirty_edge_labels: yes"
    print "layout_algorithm: mindepth"
    print "manhatten_edges: yes"
    print "edge.arrowsize: 15"
    print "late_edge_labels: yes"    

    for e in ALL_EDG:
        print e.StringVCG()

    bbl_list = ALL_BBL.items()
    bbl_list.sort()
    for (x,b) in bbl_list: 
        print b.StringVCG()

    print "}";
    print "// eof"
    return

def DumpGraphML():
  print "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>"
  print "<graphml xmlns=\"http://graphml.graphdrawing.org/xmlns\" xmlns:java=\"http://www.yworks.com/xml/yfiles-common/1.0/java\" xmlns:sys=\"http://www.yworks.com/xml/yfiles-common/markup/primitives/2.0\"" 
  print "xmlns:x=\"http://www.yworks.com/xml/yfiles-common/markup/2.0\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:y=\"http://www.yworks.com/xml/graphml\" xmlns:yed=\"http://www.yworks.com/xml/"
  print "yed/3\" xsi:schemaLocation=\"http://graphml.graphdrawing.org/xmlns http://www.yworks.com/xml/schema/graphml/1.1/ygraphml.xsd\">"
  print "<key attr.name=\"Description\" attr.type=\"string\" for=\"graph\" id=\"d0\"/>"
  print "<key for=\"port\" id=\"d1\" yfiles.type=\"portgraphics\"/>"
  print "<key for=\"port\" id=\"d2\" yfiles.type=\"portgeometry\"/>"
  print "<key for=\"port\" id=\"d3\" yfiles.type=\"portuserdata\"/>"
  print "<key attr.name=\"url\" attr.type=\"string\" for=\"node\" id=\"d4\"/>"
  print "<key attr.name=\"description\" attr.type=\"string\" for=\"node\" id=\"d5\"/>"
  print "<key for=\"node\" id=\"d6\" yfiles.type=\"nodegraphics\"/>"
  print "<key for=\"graphml\" id=\"d7\" yfiles.type=\"resources\"/>"
  print "<key attr.name=\"url\" attr.type=\"string\" for=\"edge\" id=\"d8\"/>"
  print "<key attr.name=\"description\" attr.type=\"string\" for=\"edge\" id=\"d9\"/>"
  print "<key for=\"edge\" id=\"d10\" yfiles.type=\"edgegraphics\"/>"
  print "<graph edgedefault=\"directed\" id=\"G\">"
  print "<data key=\"d0\"/>\n"

  bbl_list = ALL_BBL.items()
  bbl_list.sort()
  for (x,b) in bbl_list: 
         print b.StringGraphML()
 
  for e in ALL_EDG:
         print e.StringGraphML()
  
  print "</graph>"
  print " <data key=\"d7\">"
  print "<y:Resources/>"
  print "</data>"
  print "</graphml>"

  return

def DumpDOT():
    return

#######################################################################
# Main
#######################################################################

def Main(argv):

    if len(argv) != 2:
        Usage()
        return -1
    
    Info( "Reading listing")

    filename = argv[0]
    try:
        input = open(filename, "r")
        lines = input.readlines()
        input.close()
    except:
        Error("cannot read data " + filename)

    ProcessAssemblerListing(lines)

    Info( "Reading edges")
    
    filename = argv[1]
    try:
        input = open(filename, "r")
        lines = input.readlines()
        input.close()
    except:
        Error("cannot read data " + filename)

    edg_list = ProcessEdgProfile(lines)

    Info("Read %d edges" % len(edg_list))

    bbl_list = CreateCFG( edg_list)

    Info("Dump VCG to stdout")    
        
  #  DumpVCG()
    DumpGraphML()
    DumpDOT()
        
    return 0

#######################################################################
# 
#######################################################################

if __name__ == "__main__":
    sys.exit( Main( sys.argv[1:]) )

#######################################################################
# eof
#######################################################################
