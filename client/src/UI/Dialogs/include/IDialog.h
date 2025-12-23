class IDialog{
    public:
    IDialog() = default;
    virtual ~IDialog() = default;
    
    virtual void Open() = 0;
    virtual void Close() = 0;
    bool IsOpen(){ return m_isOpen; }

    virtual void Update() = 0;
    virtual void Draw() = 0;
    protected:
    bool m_isOpen = false;
};