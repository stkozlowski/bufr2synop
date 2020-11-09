option explicit

dim fso,tf,tfo,i,j,lines,ogimet_dane,aaxx,aaxxdate
dim nrst,iw,tmp,header(2),bbxx
dim sourcefile,sourcefileship,targetfile

Set fso = CreateObject("Scripting.FileSystemObject") 

IncludeFileabs("count_lines_withCRLF.vbs")

sourcefile=WScript.Arguments.Item(0)

if (fso.FileExists(sourcefile)=FALSE or fso.GetFile(sourcefile).size=0) Then

wscript.quit

end if

targetfile=WScript.Arguments.Item(1)

sourcefileship=split(sourcefile,".")(0) & ".shp"

'wscript.echo sourcefileship

'if (fso.FileExists(sourcefileship)=FALSE or fso.GetFile(sourcefileship).size=0) Then
'wscript.echo fso.GetFile(sourcefileship).size
'wscript.quit
'end if

'wscript.quit

lines=count_lines_withCRLF(sourcefile)
'wscript.echo lines
'wscript.quit
redim ogimet_dane(lines)
redim iw(lines)

set tf=fso.OpenTextFile(sourcefile)
set tfo=fso.CreateTextFile(targetfile)

header(0)="123"
header(1)=tf.ReadLine

'wscript.echo header(0)
'wscript.echo header(1)

for i=1 to lines-1
 ogimet_dane(i)=tf.ReadLine
 nrst=split(ogimet_dane(i)," ")(2)
 iw(i)=split(ogimet_dane(i)," ")(3)
 iw(i)=right(iw(i),1)
 'wscript.echo nrst & " " & iw(i)
 'wscript.echo ogimet_dane(i)
next
tf.close
'wscript.quit

for i=1 to lines-1
 if ogimet_dane(i)<>"" then
  'wscript.echo i
 aaxx=right(ogimet_dane(i),len(ogimet_dane(i))-13)
 'wscript.echo aaxx
 'wscript.quit
 aaxxdate=split(ogimet_dane(i)," ")(0)
 aaxxdate=right(aaxxdate,6)
 aaxxdate=left(aaxxdate,4)
 aaxxdate=aaxxdate & iw(i)
 'wscript.echo aaxxdate
 'wscript.quit
 bbxx=split(ogimet_dane(i)," ")(1)
 nrst=split(ogimet_dane(i)," ")(2)

 tfo.write chr(1) & chr(13) & chr(13) & chr(10)
 tfo.write header(0) & chr(13) & chr(10)

  tfo.write header(1) & chr(13) & chr(10)
  tfo.write bbxx  & chr(13) & chr(10)
  tfo.write nrst & " " & aaxxdate & " "

  'wscript.echo ogimet_dane(i)

  'aaxx=split(ogimet_dane(i),",")(6)

  tmp=split(aaxx," ")(0)
  aaxx=Mid(aaxx,len(tmp)+2,len(aaxx))
  tmp=split(aaxx," ")(0)
  aaxx=Mid(aaxx,len(tmp)+2,len(aaxx))
  tmp=split(aaxx," ")(0)
  aaxx=Mid(aaxx,len(tmp)+2,len(aaxx))
  'wscript.echo aaxx
  tfo.write aaxx & chr(13) & chr(10)

 tfo.write chr(13) & chr(13) & chr(10) & chr(3)
 tfo.write chr(13) & chr(10)

 end if 'if ogimet_dane(i)<>"" then
next

'wscript.quit

'tfo.write chr(13) & chr(13) & chr(10) & chr(3)
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
