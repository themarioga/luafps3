negro = Screen.color(0,0,0)
i=0
y=30
sel=0
while true do
	pad = Controls.read(0)
	System.getDir()
	maxd = System.getMaxDir() - 1
	Screen.print(30, 300, "El directorio actual es: "..System.getPathDir()..". En el hay "..maxd.." archivos y carpetas")
	while i <= maxd do
		if System.getType(i) == 0 then
			if i == sel then
				Screen.print(30, y, "->"..System.getName(i))
			else
				Screen.print(30, y, System.getName(i))
			end
		else
			if i == sel then
				Screen.print(30, y, "-><D>"..System.getName(i))
			else
				Screen.print(30, y, "<D>"..System.getName(i))
			end
		end
		i=i+1
		y=y+15
	end
	Screen.flip()
	if Controls.up(pad) == 1 and sel > 0 then
		sel=sel-1
		i=0
		y=35
		Screen.clear(negro)
	end
	if Controls.down(pad) == 1 and sel < maxd then
		sel=sel+1
		i=0
		y=35
		Screen.clear(negro)
	end
	if Controls.cross(pad) == 1 then
		Screen.clear(negro)
		if System.getType(sel) == 1 then
			System.getDir(sel)
			sel = 0
		else
			curdir = System.getPathDir().."/"..System.getName(sel)
			if System.isExt(".PNG", sel) == 1 or System.isExt(".png", sel) == 1 then
				Screen.imageLoadinOne(1, 1, curdir)
				Screen.flip()
				Screen.delay(5)
			elseif System.isExt(".JPG", sel) == 1 or System.isExt(".jpg", sel) == 1 then
				Screen.imageLoadinOne(1, 1, curdir)
				Screen.flip()
				Screen.delay(5)
			elseif System.isExt(".JPEG", sel) == 1 or System.isExt(".jpeg", sel) == 1 then
				Screen.imageLoadinOne(1, 1, curdir)
				Screen.flip()
				Screen.delay(5)
			elseif System.isExt(".BMP", sel) == 1 or System.isExt(".bmp", sel) == 1 then
				Screen.imageLoadinOne(1, 1, curdir)
				Screen.flip()
				Screen.delay(5)
			elseif System.isExt(".TIF", sel) == 1 or System.isExt(".tif", sel) == 1 then
				Screen.imageLoadinOne(1, 1, curdir)
				Screen.flip()
				Screen.delay(5)
			elseif System.isExt(".TIFF", sel) == 1 or System.isExt(".tiff", sel) == 1 then
				Screen.imageLoadinOne(1, 1, curdir)
				Screen.flip()
				Screen.delay(5)
			elseif System.isExt(".GIF", sel) == 1 or System.isExt(".gif", sel) == 1 then
				Screen.imageLoadinOne(1, 1, curdir)
				Screen.flip()
				Screen.delay(5)
			elseif System.isExt(".LUA", sel) == 1 or System.isExt(".lua", sel) == 1 then
				dofile(curdir)
			end
		end
		i=0
		y=35
	end
	if Controls.circle(pad) == 1 then
		System.exit()
	end
end
