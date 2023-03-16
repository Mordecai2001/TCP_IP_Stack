#pragma once
class Protocol {
public:
    // Getters
    Protocol* getIn() const { return in; }
    Protocol* getOut() const { return out; }

    // Setters
    void setIn(Protocol* newIn) { in = newIn; }
    void setOut(Protocol* newOut) { out = newOut; }

protected:
    Protocol* in = nullptr;
    Protocol* out = nullptr;
};

