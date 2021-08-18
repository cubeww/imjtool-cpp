name=input("name: ")

def to_snake(s):
    n = ""
    for k, i in enumerate(s):
        if i.isupper():
            n+=('_' if k!=0 else "") +i.lower()
        else:
            n+=i
    return n

h = f'''#pragma once
#include "Object.h"
class {name} :
    public Object
{{
public:
    {name}();

    void update() override;
}};
'''

cpp = f'''#include "{name}.h"

{name}::{name}()
{{
	setSprite("{to_snake(name)}");
}}

void {name}::update()
{{
	drawSelf();
}}
'''

with open(f"{name}.h",'w') as f:
    f.write(h)

with open(f"{name}.cpp",'w') as f:
    f.write(cpp)
