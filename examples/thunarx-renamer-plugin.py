from gi.repository import GObject, Gtk, Thunarx

class ThunarxPythonRenamer(Thunarx.Renamer):
    __gtype_name__ = "ThunarxPythonRenamer"
    prefix = GObject.property(type=str)
    
    def __init__(self):
        Thunarx.Renamer.__init__(self)

        # Set properties to be saved in the settings files
        self.set_property("prefix", "__")
        
        self.set_name("Example Python Renamer 2")
        self.set_help_url("http://www.google.com")
     
        hbox = Gtk.HBox(0, False)
        
        label = Gtk.Label("Prefix:")
        hbox.pack_start(label, False, False, 0)
        
        self.entry = Gtk.Entry()
        self.entry.set_text(self.get_property("prefix"))
        self.entry.connect("changed", self.entry_changed)
        hbox.pack_start(self.entry, False, False, 0)
        
        label.show()
        self.entry.show()
        self.add(hbox)
        hbox.show()
    
    def entry_changed(self, widget):
        self.set_property("prefix", widget.get_text())
        
        # Emitting this will cause the do_process method to be called
        self.emit("changed")

    def do_get_menu_items(self, window, files):
        print "python get menu items"
        return [Thunarx.MenuItem(name="TPR:SomeAction", label="Some Action", tooltip=None, icon=Gtk.STOCK_OPEN)]

    def do_load(self, settings):
        """
        Loads settings saved in ~/.config/Thunar/renamerrc
        """
        if settings.haskey("Prefix"):
            self.set_property("prefix", settings["Prefix"])
            self.entry.set_text(self.get_property("prefix"))

    def do_save(self, settings):
        """
        If do_save is overriden, you must rebuild the settings dictionary and then
        return it.
        """
        settings["Prefix"] = self.get_property("prefix")
        return settings

class ThunarxRenamerPlugin(GObject.GObject, Thunarx.RenamerProvider):
    def __init__(self):
        pass
    
    def get_renamers(self):
        return [ThunarxPythonRenamer()]
