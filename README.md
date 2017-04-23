# ofxChainableSetting

utility for setting structure

## How to use

```cpp
struct Setting : ofxChainableSetting<Setting> {
	Setting
	: register_types(name, radius, x, y) {}

	setter<std::string> name;
	setter<float> radius;
	setter<float> x;
	setter<float> y;
};

...

void drawCircle(Setting setting) {
	ofSetColor(255, 0, 0);
	ofDrawCircle(setting.x(), setting.y(), setting.radius());

	ofSetColor(255);
	ofDrawBitmapString(setting.name(), setting.x(), setting.y());
}

...

Setting setting;
drawCircle(setting.radius(40.0f).name("circle").x(10.0f).y(40.0f));
drawCircle(setting.y(300.0f).name("circle2")); // same radius, same x position

...

```

## Update histor

### 2017/04/24 ver 0.0.1

## License

MIT License.

## Author

* ISHII 2bit [bufferRenaiss co., ltd.]
* ishii[at]buffer-renaiss.com
