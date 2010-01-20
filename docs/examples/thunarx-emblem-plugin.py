import thunarx
import gtk

class ThunarxEmblemPlugin(thunarx.MenuProvider):
    def __init__(self):
        pass
        
    def get_file_actions(self, window, files):
        action = gtk.Action("ET::ShowEmblem1", "Show Emblem", "Show Emblem", None)
        action.connect("activate", self.show_emblem, files)

        action2 = gtk.Action("ET::ShowEmblem2", "Hide Emblem", "Hide Emblem", None)
        action2.connect("activate", self.hide_emblem, files)
        return [action,action2]
        
    def show_emblem(self, action, files):
        files[0].set_emblem("default")

    def hide_emblem(self, action, files):
        files[0].set_emblem(None)
