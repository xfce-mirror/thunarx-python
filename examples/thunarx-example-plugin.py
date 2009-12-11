import thunarx

class ThunarxExamplePlugin(thunarx.MenuProvider):
  def __init__(self):
    print "ThunarxExamplePlugin init"
  
  def get_file_actions(self, window, files):
    print "in get_file_actions"
  
  def get_folder_actions(self, window, folder):
    print "in get_folder_actions"
