import thunarx
import gtk

"""
Thunarx Submenu Plugin
    This plugin shows an example of a MenuProvider plugin that implements
    sub-menus.    The example used here requires the developer to sub-class 
    gtk.Action and override the create_menu_item virtual method.
    
"""

class MyAction(gtk.Action):
    __gtype_name__ = "MyAction"
    
    def __init__(self, name, label, tooltip=None, stock_id=None, menu_handler=None):
        gtk.Action.__init__(self, name, label, tooltip, stock_id)
        self.menu_handler = menu_handler

    def create_menu_item(self):
        menuitem = gtk.MenuItem(self.get_label())
        
        if self.menu_handler is not None:
            menu = gtk.Menu()
            menuitem.set_submenu(menu)
            self.menu_handler(menu)
        
        return menuitem

    do_create_menu_item = create_menu_item

def PyFileActionMenu(menu):
    action = gtk.Action("TMP:Submenuitem1", "Submenuitem 1", None, None)
    subitem = action.create_menu_item()
    menu.append(subitem)
    subitem.show()

    action = MyAction("TMP:Submenuitem2", "Submenuitem 2", None, None, menu_handler=PyFileActionSubmenu)
    subitem = action.create_menu_item()
    menu.append(subitem)
    subitem.show()

def PyFileActionSubmenu(menu):
    action = gtk.Action("TMP:SubSubmenuitem1", "Subsubmenuitem 1", None, None)
    subitem = action.create_menu_item()
    menu.append(subitem)
    subitem.show()

    action = gtk.Action("TMP:SubSubmenuitem2", "Subsubmenuitem 2", None, None)
    subitem = action.create_menu_item()
    menu.append(subitem)
    subitem.show()

class ThunarxSubMenuProviderPlugin(thunarx.MenuProvider):
    def __init__(self):
        pass
    
    def get_file_actions(self, window, files):
        return [MyAction("TMP:TestFileAction", "PyFileAction", "Python File Action", 
            gtk.STOCK_FILE, menu_handler=PyFileActionMenu)]
    
    def get_folder_actions(self, window, folder):
        return [MyAction("TMP:TestFolderAction", "PyFolderAction", 
            "Python Folder Action", gtk.STOCK_DIRECTORY)]
