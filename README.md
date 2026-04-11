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

	std::string value; // from this->getUpdatedValue();
	std::vector<std::string> getValues();

	virtual std::string setValue(const std::string &value) = 0;

	std::string updateName(const std::string &updated); // Uses setValue

	std::string remove(); // Calls both removeEnvEntry and removeRelatedPathEntries

	virtual void refreshEnvironment() = 0;

	virtual void addSubDirToPath(std::string subDir) = 0;
	void addBinToPath(); // Calls addSubDirToPath

protected:
	int scope;
	std::string name;
	virtual std::string getUpdatedValue() = 0; // Unsplitted string version, unlike getValues()

	// Called by remove()
	virtual std::string removeEnvEntry() = 0;
	std::vector<int> removeRelatedPathEntries();
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