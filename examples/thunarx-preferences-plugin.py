from gi.repository import GObject, Gtk, Thunarx

class DialogExample(Gtk.Dialog):
    def __init__(self, parent):
        Gtk.Dialog.__init__(self, "My Dialog", parent, 0,
            (Gtk.STOCK_CANCEL, Gtk.ResponseType.CANCEL,
             Gtk.STOCK_OK, Gtk.ResponseType.OK))

        self.set_default_size(150, 100)

        label = Gtk.Label("This is a dialog to display additional information")

        box = self.get_content_area()
        box.add(label)
        self.show_all()

class ThunarxPreferencesPlugin(GObject.GObject, Thunarx.PreferencesProvider):
    def __init__(self):
        pass
    
    def get_preferences_menu_items(self, window):
        item = Thunarx.MenuItem(name="TPP:PrefItem", label="My Example Preferences", tooltip=None, icon=None)
        item.connect("activate", self.__open_preferences, window)
        return item,
    
    def __open_preferences(self, action, window):
        dialog = DialogExample(window)
        response = dialog.run()
        dialog.destroy()
