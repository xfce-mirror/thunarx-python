import thunarx
import gtk

class ThunarxPreferencesPlugin(thunarx.PreferencesProvider):
    def __init__(self):
        pass
    
    def get_preferences_actions(self, window):
        action = gtk.Action("TPP:PrefItem", "My Example Preferences", None, None)
        action.connect("activate", self.__open_preferences, window)
        return action,
    
    def __open_preferences(self, action, window):
        dialog = gtk.Dialog("My dialog",
            window,
            gtk.DIALOG_MODAL | gtk.DIALOG_DESTROY_WITH_PARENT,
            (gtk.STOCK_CANCEL, gtk.RESPONSE_REJECT,
            gtk.STOCK_OK, gtk.RESPONSE_ACCEPT))

        dialog.show()
        dialog.run()
        dialog.destroy()
