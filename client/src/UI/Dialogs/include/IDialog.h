class IDialog{
    public:
    IDialog() = default;
    virtual ~IDialog() = default;
    
    virtual void Open() { m_isOpen = true; };
    virtual void Close() { m_isOpen = false; };
    bool IsOpen(){ return m_isOpen; }

    protected:
    bool m_isOpen = false;
};