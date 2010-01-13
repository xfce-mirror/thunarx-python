import thunarx
import gtk
import gobject

class ThunarxPythonRenamer(thunarx.Renamer):
    __gtype_name__ = "ThunarxPythonRenamer"
    test = gobject.property(type=str)
    
    def __init__(self):
        thunarx.Renamer.__init__(self)

        # Set properties to be saved in the settings files
        self.set_property("test", "blah")
        
        self.set_name("Adam's Renamer")
        self.set_help_url("http://www.google.com")
     
        hbox = gtk.HBox(0, False)
        
        label = gtk.Label("Setting 1:")
        hbox.pack_start(label, False, False, 0)
        
        entry = gtk.Entry()
        entry.connect("changed", self.do_changed)
        hbox.pack_start(entry, False, False, 0)
        
        label.show()
        entry.show()
        self.add(hbox)
        hbox.show()
    
    def do_process(self, file, text, index):
        if text.startswith("__"):
            return text.replace("__", "")
        else:
            return "__" + text

    def do_changed(self, widget):
        pass

    def do_get_actions(self, window, files):
        return [gtk.Action("TPR:SomeAction", "Some Action", None, gtk.STOCK_OPEN)]

    def do_load(self, settings):
        """
        Loads settings saved in ~/.config/Thunar/renamerrc
        """
        print "loading settings"

    def do_save(self, settings):
        """
        If do_save is overriden, you must rebuild the settings dictionary and then
        return it.
        """
        settings["test"] = "blah"
        
        return settings

class ThunarxRenamerPlugin(thunarx.RenamerProvider):
    def __init__(self):
        pass
    
    def get_renamers(self):
        return [ThunarxPythonRenamer()]
