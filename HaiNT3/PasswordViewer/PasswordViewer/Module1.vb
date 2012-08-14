Imports System.IO
Module Module1

    Sub Main()
        Dim CurrentPath As String = Directory.GetCurrentDirectory()
        Dim strFileName As String = CurrentPath + "\\pass.txt"

        Dim FileReader As StreamReader
        FileReader = New StreamReader(strFileName)

        Dim strFileNameToViewPass As String

        strFileNameToViewPass = FileReader.ReadToEnd()
        FileReader.Close()


        Dim Obj As New Object
        Dim strPassword As String
        Obj = CreateObject("NirSoft.AccessPassView")
        strPassword = Obj.GetPassword(strFileNameToViewPass)


        Dim FileWriter As StreamWriter
        FileWriter = New StreamWriter(strFileName, False)
        FileWriter.Write(strPassword)
        FileWriter.Close()

    End Sub

End Module
