option explicit

dim fso,tf,tfo,i,j,lines,ogimet_dane,aaxx,aaxxdate,wdd
dim nrst,iw,tmp,header(2)
dim sourcefile,targetfile

Set fso = CreateObject("Scripting.FileSystemObject") 

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

'wscript.echo header(0)
'wscript.echo header(1)

for i=1 to lines-1
 ogimet_dane(i)=tf.ReadLine
 nrst=split(ogimet_dane(i)," ")(3)
 iw(i)=split(ogimet_dane(i)," ")(2)
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
 nrst=split(ogimet_dane(i)," ")(3)
 if isnumeric(nrst) then

 tfo.write chr(1) & chr(13) & chr(13) & chr(10)
 tfo.write header(0) & chr(10)

 if nrst>=12100 and nrst<=12695 then
  tfo.write "SNPL40 SOWR " & Mid(aaxxdate,1,4) & chr(10)
  tfo.write "AAXX" & " " & aaxxdate & chr(10)
 else
  tfo.write header(1) & chr(10)
  tfo.write "AAXX" & " " & aaxxdate & chr(10)
 end if
  'wscript.echo ogimet_dane(i)

  'aaxx=split(ogimet_dane(i),",")(6)
  'wscript.echo aaxx
  'aaxxdate=split(aaxx, " ")(1)
  if split(aaxx," ")(0)="AAXX" then
   tfo.write Mid(aaxx,12,len(aaxx)) & chr(10)
  end if
 tfo.write chr(13) & chr(13) & chr(10) & chr(3)
 tfo.write chr(13) & chr(10)
 end if 'if isnumeric(nrst) then
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
