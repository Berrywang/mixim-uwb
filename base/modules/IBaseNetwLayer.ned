package org.mixim.base.modules;

// Interface for network layer modules
moduleinterface IBaseNetwLayer
{
    parameters:
        bool debug; // debug switch
        bool stats; // stats switch
        double headerLength @unit("bit"); // length of the network packet header (in bits)
    gates:
        input upperGateIn; // from application layer
        output upperGateOut; // to application layer
        input upperControlIn; // control from application layer
        output upperControlOut; // control to application layer
        input lowerGateIn; // from NIC
        output lowerGateOut; // to NIC
        input lowerControlIn; // control from NIC
        output lowerControlOut; // control to NIC
}

