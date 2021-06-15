#ifndef _h_iaq_define_included__
#define _h_iaq_define_included__


namespace iaq{

/// 算法版本
enum Version{
    V1,  V2, V3, V4, V5, V6
};


struct AlgBase{
public:
    explicit AlgBase(Version ver)
    : version_(ver)
    {
    }

    /**
     * @brief 设置当前算法版本
     * 
     * @param ver 版本
     */
    void SetVersion(Version ver)
    {
        this->version_ = ver;
    }

    /**
     * @brief 支持最大版本
     * 
     * @return iaq::Version 返回版本号 
     */
    virtual iaq::Version GetSupportMaxVersion() const = 0;
protected:
    /// 当前指定版本
    iaq::Version version_;
};

}


#endif // _h_iaq_define_included__