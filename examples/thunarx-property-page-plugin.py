import hashlib

# A way to get unquote working with python 2 and 3
try:
    from urllib import unquote
except ImportError:
    from urllib.parse import unquote

from gi.repository import GObject, Gtk, Thunarx

class ThunarxPropertyPagePlugin(GObject.GObject, Thunarx.PropertyPageProvider):
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
        
        filename = unquote(file.get_uri()[7:])

        hbox = Gtk.HBox(0, False)
        hbox.show()

        label = Gtk.Label('MD5Sum:')
        label.show()
        hbox.pack_start(label, True, True, 0)

        value_label = Gtk.Label()
        hbox.pack_start(value_label, True, True, 0)

        md5sum = hashlib.md5(filename.encode("utf-8")).hexdigest()
        value_label.set_text(md5sum)
        value_label.show()

        page = Thunarx.PropertyPage()
        page.set_label("MD5")
        page.add(hbox)

        return [page]
