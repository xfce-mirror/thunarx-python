class MenuProvider:
    def get_file_actions(self, window, files):
        """
        @param window the window it was sent from
        @type  window gtk.Window
        @param files  selected files
        @type  files  list of nautilus.FileInfo
        @returns      menu items to show
        @rtype        a sequence of nautilus.MenuItems
        """

    def get_folder_actions(self, window, file):
        """
        @param window the window it was sent from
        @type  window gtk.Window
        @param file   file that was clicked on
        @type  file   nautilus.FileInfo
        @returns      menu items to show
        @rtype        a sequence of nautilus.MenuItems
        """

    def get_dnd_actions(self, window, folder, files):
        """
        @param window the window it was sent from
        @type  window gtk.Window
        @param folder folder the user dropped files into
        @type  folder nautilus.FileInfo
        @param files  selected files
        @type  files  list of nautilus.FileInfo
        @returns      menu items to show
        @rtype        a sequence of nautilus.MenuItems
        """

class PropertyPageProvider:
    def get_property_pages(self, files):
        """
        @param files  selected files
        @type  files  list of nautilus.FileInfo
        @returns      property pages to show
        @rtype        a sequence of nautilus.PropertyPage

        Creates a property page for files
        """

class RenamerProvider:
    def get_renamers(self):
        """
        @rtype  list of thunarx.Renamer
        """
        pass

class PreferencesProvider:
    def get_preferences_actions(self, window):
        """
        @param  window the window it was sent from
        @type   window gtk.Window
        @rtype  list of gtk.Action
        """
        pass
        
class FileInfo:
    def get_name(self):
        """
        @rtype   string
        """
        pass

    def get_uri(self):
        """
        @rtype   string
        """
        pass

    def get_parent_uri(self):
        """
        @rtype   string
        """
        pass

    def get_uri_scheme(self):
        """
        @rtype   string
        """
        pass

    def get_mime_type(self):
        """
        @rtype   string
        """
        pass
    
    def has_mime_type(self, mime_type):
        """
        @type   mime_type   string
        @rtype  boolean
        """
        pass

    def is_directory(self):
        """
        @rtype   boolean
        """
        pass

    def get_file_info(self):
        """
        @rtype  gio.FileInfo
        """
        pass
     
    def get_filesystem_info(self):
        """
        @rtype  gio.FileInfo
        """
        pass
    
    def get_location(self):
        """
        @rtype  gio.File
        """
        pass

    def set_emblem(self, emblem):
        """
        @type   emblem  string or None
        """
        pass

    def changed(self):
        pass
    
    def renamed(self):
        pass
    
class PropertyPage:
    """
    Properties:
      label (string)
      label-widget (widget)
    """

    def __init__(self, label):
        pass

    def get_label(self):
        """
        @rtype string
        """
        pass
    
    def set_label(self, label):
        """
        @type   label   string
        """
        pass
    
    def get_label_widget(self):
        """
        @type gtk.Widget
        """
        pass
    
    def set_label_widget(self, widget):
        """
        @type   widget  gtk.Widget
        """
        pass
        
class Renamer:
    """
    In order to extend the bulk renamer, you must sub-class thunarx.Renamer as
    in the example plugin.  In order to have settings saved, they must be
    registered as gobject properties as in the example plugin.
    
    Properties:
        help-url (string)
        name (string)
    Signals:
        changed
    """
    
    def __init__(self):
        pass
    
    def get_help_url(self):
        """
        @rtype  string
        """
    
    def set_help_url(self, help_url):
        """
        @type   help_url    string
        @param  help_url    specify the url used by the help button
        """
    
    def get_name(self):
        """
        @rtype  string
        """
        
    def set_name(self, name):
        """
        @type   name    string
        @param  name    specify the name that appears in the renamer dropdown
        """
    
    def do_process(self, file, text, index):
        """
        Called automatically by Thunar to retrieve a preview of how the file
        will be renamed.
        
        @type   file    thunarx.FileInfo
        @param  file    The file to be renamed
        
        @type   text    string
        @param  text    The file name
        
        @type   index   int
        @param  index   The index of the file in the sequence
        
        @rtype      string
        @returns    A new file name    
        """
    
    def do_load(self, settings):
        """
        Called automatically by Thunar on initialization to provide the Renamer
        object with a dictionary of saved settings.
        
        @type   settings    dict
        @param  settings    A dictionary of saved settings/properties
        """
    
    def do_save(self, settings):
        """
        Called automatically by Thunar on "Rename" to retrieve a dictionary
        of settings/properties to save.
        
        @type   settings    dict
        @param  settings    A dictionary of settings/properties to save
        
        @rtype      dict
        @returns    A dictionary of settings/properties to save
        """
    
    def get_actions(self, window, files):
        """
        Called automatically by Thunar to retrieve a list of actions to show in
        the preview window's context menu.
        
        @type   window  gtk.Window
        @param  window  The associated window
        
        @type   files   list
        @param  files   list of thunarx.FileInfo
        
        @rtype      list
        @return     list of gtk.Action
        """
