import thunarx
import gtk

class ThunarxPythonRenamer(thunarx.Renamer):
    __gtype_name__ = "ThunarxPythonRenamer"
    
    def __init__(self):
        thunarx.Renamer.__init__(self)
        
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
        return "__" + text

    def do_changed(self, widget):
        pass

    def do_get_actions(self, window, files):
        return [gtk.Action("TPR:SomeAction", "Some Action", None, gtk.STOCK_OPEN)]

class ThunarxRenamerPlugin(thunarx.RenamerProvider):
    def __init__(self):
        pass
    
    def get_renamers(self):
        return [ThunarxPythonRenamer()]
