#pragma once

class IrStmnt {
public:
};

class OpIrStmnt final: public IrStmnt {
public:
};

class IrCallStmnt final: public IrStmnt {
public:
};

class IrPhiStmnt final: public IrStmnt {
public:
};

class IrAllocStmnt final: public IrStmnt {
public:
};

class IrPrintStmnt final: public IrStmnt {
public:
};

class IrGetElStmnt final: public IrStmnt {
public:
};

class IrSetElStmnt final: public IrStmnt {
public:
};

class IrLoadStmnt final: public IrStmnt {
public:
};

class IrStoreStmnt final: public IrStmnt {
public:
};