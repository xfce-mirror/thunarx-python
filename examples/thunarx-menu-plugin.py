from gi.repository import GObject, Gtk, Thunarx

class ThunarxMenuProviderPlugin(GObject.GObject, Thunarx.MenuProvider):
    def __init__(self):
        pass
    
    def get_file_menu_items(self, window, files):
        item = Thunarx.MenuItem(name="TMP:TestFileAction", label="Python File Action", tooltip='', icon=Gtk.STOCK_FILE)
        item.connect("activate", self.__do_something, window)

        return [item]

    def get_folder_menu_items(self, window, folder):
        return [Thunarx.MenuItem(name="TMP:TestFolderAction", label="Python Folder Action", tooltip='', icon=Gtk.STOCK_OPEN)]

    def __do_something(self, item, window):
        print "Doing something"
