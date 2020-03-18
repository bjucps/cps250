#!/usr/bin/python

import cgitb; cgitb.enable()
import cgi


class Comment(object):
    __slots__  = ('text', 'name', 'email')
    
    def __init__(self, text, name, email):
        self.text = text
        self.name = name
        self.email = email
        
    def makeComment(fileline):
        values = fileline.split("`")
        if len(values) == 3:
            com = Comment(values[0], values[1], values[2])
            return com
        else:
            return None
        
    makeComment = staticmethod(makeComment)
        
    def serialize(self):
        return self.text + "`" + self.name + "`" + self.email + "\n"
        
    def render(self):
        return """
            <p>
                <b>%s (%s) wrote:</b>
                <blockquote>%s</blockquote>
            </p>
        """ % (self.name, self.email, self.text)

# Get collection of query string parameters
form = cgi.FieldStorage(keep_blank_values=True)

#messages = [
#        Comment('Nice site!', 'Fred', 'fjones@somehwere.net'),
#        Comment('Nice site!', 'Hilda', 'hilda@anywhere.com'),
#        Comment('Nice site!', 'Bob', 'bjones@nowhere.net'),
#]

messages = []

f = file('messages.txt','r')
for line in f:
    com = Comment.makeComment(line)
    if com:
        messages.append(com)
f.close()

# Extract username value
action = form.getfirst('action')
if action:
    messages.append(
        Comment(
            form.getfirst('text'),
            form.getfirst('name'),
            form.getfirst('email')
        )
    )
    
    f = file('messages.txt','w')
    for msg in messages:
        f.write(msg.serialize())
        
    f.close()
    

entries = ""
for msg in messages:
    entries = entries + msg.render()
    

    
# ------------- Print response -----------------------
    
# The content-type header line
print "Content-type: text/html\n"
    
# The HTML response
print """
    <html>
    <body>
    <h2>Welcome to the Guestbook!</h2>
    %s
    
    <form>
      <table>
        <tr>
            <td>Name:</td>
            <td><input type='text' name='name'></td>
        </tr>
        <tr>
            <td>Email:</td>
            <td><input type='text' name='email'></td>
        </tr>
        <tr>
            <td>Remarks (be kind):</td>
            <td><input type='text' name='text'></td>
        </tr>
      </table>
      <input type='submit' name='action' value='Post Comments'>
    </form>
    </body>
    </html>
"""  % entries
