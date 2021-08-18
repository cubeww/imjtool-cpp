import os

for root, dirs, files in os.walk("textures/", topdown=False):
    for name in files:
        fname = os.path.join(root, name)
        tname = os.path.splitext(name)[0]
        print('resourceManager.createTexture("%s", "%s");'%(tname,fname))
        #print('resourceManager.createSprite("%s").addSheet("%s");'%(tname,tname))
    
