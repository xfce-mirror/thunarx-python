import thunarx
import gtk
import gobject

class ThunarxPythonRenamer(thunarx.Renamer):
    __gtype_name__ = "ThunarxPythonRenamer"
    prefix = gobject.property(type=str)
    
    def __init__(self):
        thunarx.Renamer.__init__(self)

        # Set properties to be saved in the settings files
        self.set_property("prefix", "__")
        
        self.set_name("Example Python Renamer")
        self.set_help_url("http://www.google.com")
     
        hbox = gtk.HBox(0, False)
        
        label = gtk.Label("Prefix:")
        hbox.pack_start(label, False, False, 0)
        
        self.entry = gtk.Entry()
        self.entry.set_text(self.get_property("prefix"))
        self.entry.connect("changed", self.entry_changed)
        hbox.pack_start(self.entry, False, False, 0)
        
        label.show()
        self.entry.show()
        self.add(hbox)
        hbox.show()
    
    def do_process(self, file, text, index):
        prefix = self.entry.get_text()
        return prefix + text

    def entry_changed(self, widget):
        self.set_property("prefix", widget.get_text())
        
        # Emitting this will cause the do_process method to be called
        self.emit("changed")

    def do_get_actions(self, window, files):
        return [gtk.Action("TPR:SomeAction", "Some Action", None, gtk.STOCK_OPEN)]

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

class ThunarxRenamerPlugin(thunarx.RenamerProvider):
    def __init__(self):
        pass
    
    def get_renamers(self):
        return [ThunarxPythonRenamer()]
