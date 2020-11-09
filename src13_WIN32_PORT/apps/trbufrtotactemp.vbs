option explicit

dim fso,tf,tfo,i,j,lines,ogimet_dane,ttxxdate,header(2),iw,ttxx
dim sourcefile,targetfile


IncludeFileabs("count_lines_withCRLF.vbs")

sourcefile=WScript.Arguments.Item(0)

if fso.FileExists(sourcefile)=FALSE then 
 wscript.quit
end if

if fso.GetFile(sourcefile).size=0 Then
 wscript.quit
end if

targetfile=WScript.Arguments.Item(1)

lines=count_lines_withCRLF(sourcefile)
'wscript.echo lines
'wscript.quit
redim ogimet_dane(lines)
redim iw(lines)

set tf=fso.OpenTextFile(sourcefile)
set tfo=fso.CreateTextFile(targetfile)

header(0)="123"
header(1)=tf.ReadLine

for i=1 to lines-1
 ogimet_dane(i)=tf.ReadLine
 iw(i)=split(ogimet_dane(i)," ")(2)
 iw(i)=right(iw(i),1)
 'wscript.echo iw(i)
 'wscript.echo ogimet_dane(i)
next
tf.close

for i=1 to lines-1
 if ogimet_dane(i)<>"" then

  ttxx=split(ogimet_dane(i)," ")(1) 
  if ttxx="TTAA" or ttxx="TTBB" or ttxx="TTCC" or ttxx="TTDD" then
  'wscript.echo ttxx

  ttxxdate=split(ogimet_dane(i)," ")(0)
  ttxxdate=right(ttxxdate,6)
  ttxxdate=left(ttxxdate,4)

  tfo.write chr(1) & chr(13) & chr(13) & chr(10)
  tfo.write header(0) & chr(13) & chr(13) & chr(10) 
  tfo.write header(1) & chr(13) & chr(13) & chr(10)
  tfo.write ttxx & " "
  tfo.write ttxxdate & iw(i) & " "
  tfo.write Mid(ogimet_dane(i),25,len(ogimet_dane(i))) & chr(10)
  tfo.write chr(13) & chr(13) & chr(10) & chr(3)
  tfo.write chr(13) & chr(10)
  end if 

 end if 'if ogimet_dane(i)<>"" then
next

tfo.close

Private Sub IncludeFileAbs (ByVal FileName)
 dim fsoincl: set fsoincl=CreateObject("Scripting.FileSystemObject")
 Const ForReading = 1
' msgbox    FileName
 Dim f: set f = fsoincl.OpenTextFile(FileName,ForReading)   
 Dim s: s = f.ReadAll()   
 f.close
 set fsoincl= nothing
ExecuteGlobal s   
End Sub
