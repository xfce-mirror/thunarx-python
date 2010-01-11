import hashlib
import urllib

import thunarx
import gtk

class ThunarxPropertyPagePlugin(thunarx.PropertyPageProvider):
    def __init__(self):
        pass

    def get_property_pages(self, files):
        if len(files) != 1:
            return
        
        file = files[0]
        if file.get_uri_scheme() != 'file':
            return

        if file.is_directory():
            return

        filename = urllib.unquote(file.get_uri()[7:])

        self.hbox = gtk.HBox(0, False)
        self.hbox.show()

        label = gtk.Label('MD5Sum:')
        label.show()
        self.hbox.pack_start(label)

        self.value_label = gtk.Label()
        self.hbox.pack_start(self.value_label)

        md5sum = hashlib.md5(filename).hexdigest()
        self.value_label.set_text(md5sum)
        self.value_label.show()

        page = thunarx.PropertyPage("MD5")

        page.add(self.hbox)

        return [page]
