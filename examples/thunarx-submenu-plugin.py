from gi.repository import GObject, Gtk, Thunarx

class ThunarxSubMenuProviderPlugin(GObject.GObject, Thunarx.MenuProvider):
    def __init__(self):
        pass
    
    def get_file_menu_items(self, window, files):
        item = Thunarx.MenuItem(name="TMP:Item1", label="Python File Action", tooltip='', icon=Gtk.STOCK_FILE)

        submenu = Thunarx.Menu()
        subitem1 = Thunarx.MenuItem(name='TMP::Subitem1', 
                                         label='Subitem1', 
                                         tooltip='First tip',
                                         icon=Gtk.STOCK_DND)
        subitem1.connect("activate", self.__subitem1_callback, window)
        submenu.append_item(subitem1)

        subitem2 = Thunarx.MenuItem(name='TMP::Subitem2', 
                                         label='Subitem2', 
                                         tooltip='Second tip',
                                         icon=Gtk.STOCK_FULLSCREEN)
        subitem2.connect("activate", self.__subitem2_callback, window)
        submenu.append_item(subitem2)
                                         
        item.set_menu(submenu)
        
        item2 = Thunarx.MenuItem(name='TMP::Item2', 
                                         label='Another item', 
                                         tooltip='',
                                         icon=Gtk.STOCK_OK)
    
        return item,item2

    def __subitem1_callback(self, item, window):
        print "Subitem1 call"
        
    def __subitem2_callback(self, item, window):
        print "Subitem2 call"
