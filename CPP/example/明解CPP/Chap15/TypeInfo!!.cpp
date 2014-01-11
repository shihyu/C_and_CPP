// type_info類別的定義範例

class type_info {
public:
	virtual ~type_info();
	bool operator==(const type_info&) const;
	bool operator!=(const type_info&) const;
	bool before(const type_info&) const;
	const char* name() const;

private:
	type_info(const type_info&);		// 讓複製建構子無效化
	type_info& operator=(const type_info&);	// 讓指定運算子無效化
};
