function count_lines_withCRLF(fname)
dim count, fs, tf,line
'count lines
set fs=CreateObject("Scripting.FileSystemObject")
count=0
set tf=fs.OpenTextFile(fname)
do 
 line=tf.ReadLine
  count=count+1
Loop Until tf.AtEndOfStream 
tf.close
count_lines_withCRLF=count
fs=null
end function
