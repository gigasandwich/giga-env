**This is a OS environment variables setup program**:

What it does:
- [x] Env var CRUD
- [x] Path variable CRUD (since it technically contains many values)
- [x] Automatic *"Add to path"*
    - After adding a new env with the format `ENV_HOME`, add option to add to path `ENV_HOME/bin`
- [ ] Data suggestion based on history
- [ ] Data backup
- [ ] GUI For all of the above features

---

Linux implementation of the above features is yet to be done, but should be easy to test with `Docker` and the existing base classes:

```cpp
class EnvVar {
public:
	char separator;

	// Expected scope values are in util/util.h
	EnvVar(int scope, std::string name, char separator);
	
	std::string value; // from this->getValue();
	virtual std::string getValue() = 0; // Unsplitted string version, only called in the constructor for performance reasons :) (Why did I not make it a protected/private method ?)
	std::vector<std::string> getValues();

	virtual std::string setValue(const std::string& value) = 0;

	std::string updateName(const std::string& updated); // Uses setValue

	virtual std::string remove() = 0;

	virtual void refreshEnvironment() = 0;

protected:
	int scope;
	std::string name;
};

class PathVarHandler {
public:
    PathVarHandler(int scope); // Expected scope values are defined in util/util.h
    
    std::vector<std::string> getValues();
    std::string append(std::string newValue);
    std::string update(int index, std::string newValue);
    std::string remove(int index);

    std::string toString(); // It's like getValues().implode() of php
private:
    EnvVar* pathEnvVar;
    std::vector<std::string> values;
    void persist();
};
```

> I am not responsible for any of your future *OS reinstallation*