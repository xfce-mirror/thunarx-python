import thunarx
import gtk

class ThunarxMenuProviderPlugin(thunarx.MenuProvider):
  def __init__(self):
    pass
  
  def get_file_actions(self, window, files):
    return [gtk.Action("TMP:TestFileAction", "PyFileAction", "Python File Action", gtk.STOCK_FILE)]
  
  def get_folder_actions(self, window, folder):
    return [gtk.Action("TMP:TestFolderAction", "PyFolderAction", "Python Folder Action", gtk.STOCK_DIRECTORY)]
