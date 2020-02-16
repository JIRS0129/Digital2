Imports System
Imports System.Threading
Imports System.IO.Ports
Imports System.ComponentModel

<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()>
Public Class Form1
    Inherits System.Windows.Forms.Form

    'Form reemplaza a Dispose para limpiar la lista de componentes.
    <System.Diagnostics.DebuggerNonUserCode()>
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        Try
            If disposing AndAlso components IsNot Nothing Then
                components.Dispose()
            End If
        Finally
            MyBase.Dispose(disposing)
        End Try
    End Sub

    'Requerido por el Diseñador de Windows Forms
    Private components As System.ComponentModel.IContainer

    'NOTA: el Diseñador de Windows Forms necesita el siguiente procedimiento
    'Se puede modificar usando el Diseñador de Windows Forms.  
    'No lo modifique con el editor de código.
    <System.Diagnostics.DebuggerStepThrough()>
    Private Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container()
        Me.counterTxtb = New System.Windows.Forms.TextBox()
        Me.Label1 = New System.Windows.Forms.Label()
        Me.SendCounterBtn = New System.Windows.Forms.Button()
        Me.baudrateCmb = New System.Windows.Forms.ComboBox()
        Me.GroupBox1 = New System.Windows.Forms.GroupBox()
        Me.GroupBox2 = New System.Windows.Forms.GroupBox()
        Me.comCmb = New System.Windows.Forms.ComboBox()
        Me.ConnectBtn = New System.Windows.Forms.Button()
        Me.GroupBox3 = New System.Windows.Forms.GroupBox()
        Me.s2Valuelbl = New System.Windows.Forms.Label()
        Me.s1Valuelbl = New System.Windows.Forms.Label()
        Me.Label3 = New System.Windows.Forms.Label()
        Me.Label2 = New System.Windows.Forms.Label()
        Me.SerialPort = New System.IO.Ports.SerialPort(Me.components)
        Me.GroupBox1.SuspendLayout()
        Me.GroupBox2.SuspendLayout()
        Me.GroupBox3.SuspendLayout()
        Me.SuspendLayout()
        '
        'counterTxtb
        '
        Me.counterTxtb.Location = New System.Drawing.Point(32, 79)
        Me.counterTxtb.Name = "counterTxtb"
        Me.counterTxtb.Size = New System.Drawing.Size(123, 22)
        Me.counterTxtb.TabIndex = 1
        '
        'Label1
        '
        Me.Label1.AutoSize = True
        Me.Label1.Location = New System.Drawing.Point(39, 46)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(95, 17)
        Me.Label1.TabIndex = 2
        Me.Label1.Text = "Value to send"
        '
        'SendCounterBtn
        '
        Me.SendCounterBtn.Location = New System.Drawing.Point(211, 79)
        Me.SendCounterBtn.Name = "SendCounterBtn"
        Me.SendCounterBtn.Size = New System.Drawing.Size(75, 23)
        Me.SendCounterBtn.TabIndex = 3
        Me.SendCounterBtn.Text = "Send"
        Me.SendCounterBtn.UseVisualStyleBackColor = True
        '
        'baudrateCmb
        '
        Me.baudrateCmb.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
        Me.baudrateCmb.FormattingEnabled = True
        Me.baudrateCmb.Items.AddRange(New Object() {"9600", "115200"})
        Me.baudrateCmb.Location = New System.Drawing.Point(18, 77)
        Me.baudrateCmb.Name = "baudrateCmb"
        Me.baudrateCmb.Size = New System.Drawing.Size(172, 24)
        Me.baudrateCmb.TabIndex = 4
        '
        'GroupBox1
        '
        Me.GroupBox1.Controls.Add(Me.counterTxtb)
        Me.GroupBox1.Controls.Add(Me.Label1)
        Me.GroupBox1.Controls.Add(Me.SendCounterBtn)
        Me.GroupBox1.Location = New System.Drawing.Point(324, 12)
        Me.GroupBox1.Name = "GroupBox1"
        Me.GroupBox1.Size = New System.Drawing.Size(306, 124)
        Me.GroupBox1.TabIndex = 5
        Me.GroupBox1.TabStop = False
        Me.GroupBox1.Text = "Counter"
        '
        'GroupBox2
        '
        Me.GroupBox2.Controls.Add(Me.comCmb)
        Me.GroupBox2.Controls.Add(Me.ConnectBtn)
        Me.GroupBox2.Controls.Add(Me.baudrateCmb)
        Me.GroupBox2.Location = New System.Drawing.Point(12, 12)
        Me.GroupBox2.Name = "GroupBox2"
        Me.GroupBox2.Size = New System.Drawing.Size(306, 124)
        Me.GroupBox2.TabIndex = 6
        Me.GroupBox2.TabStop = False
        Me.GroupBox2.Text = "Connection"
        '
        'comCmb
        '
        Me.comCmb.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
        Me.comCmb.FormattingEnabled = True
        Me.comCmb.Location = New System.Drawing.Point(18, 46)
        Me.comCmb.Name = "comCmb"
        Me.comCmb.Size = New System.Drawing.Size(172, 24)
        Me.comCmb.TabIndex = 6
        '
        'ConnectBtn
        '
        Me.ConnectBtn.Location = New System.Drawing.Point(212, 77)
        Me.ConnectBtn.Name = "ConnectBtn"
        Me.ConnectBtn.Size = New System.Drawing.Size(75, 23)
        Me.ConnectBtn.TabIndex = 3
        Me.ConnectBtn.Text = "Connect"
        Me.ConnectBtn.UseVisualStyleBackColor = True
        '
        'GroupBox3
        '
        Me.GroupBox3.Controls.Add(Me.s2Valuelbl)
        Me.GroupBox3.Controls.Add(Me.s1Valuelbl)
        Me.GroupBox3.Controls.Add(Me.Label3)
        Me.GroupBox3.Controls.Add(Me.Label2)
        Me.GroupBox3.Location = New System.Drawing.Point(12, 142)
        Me.GroupBox3.Name = "GroupBox3"
        Me.GroupBox3.Size = New System.Drawing.Size(618, 157)
        Me.GroupBox3.TabIndex = 6
        Me.GroupBox3.TabStop = False
        Me.GroupBox3.Text = "Sensors"
        '
        's2Valuelbl
        '
        Me.s2Valuelbl.AutoSize = True
        Me.s2Valuelbl.Location = New System.Drawing.Point(351, 100)
        Me.s2Valuelbl.Name = "s2Valuelbl"
        Me.s2Valuelbl.Size = New System.Drawing.Size(0, 17)
        Me.s2Valuelbl.TabIndex = 5
        '
        's1Valuelbl
        '
        Me.s1Valuelbl.AutoSize = True
        Me.s1Valuelbl.Location = New System.Drawing.Point(39, 100)
        Me.s1Valuelbl.Name = "s1Valuelbl"
        Me.s1Valuelbl.Size = New System.Drawing.Size(0, 17)
        Me.s1Valuelbl.TabIndex = 4
        '
        'Label3
        '
        Me.Label3.AutoSize = True
        Me.Label3.Location = New System.Drawing.Point(351, 46)
        Me.Label3.Name = "Label3"
        Me.Label3.Size = New System.Drawing.Size(69, 17)
        Me.Label3.TabIndex = 3
        Me.Label3.Text = "Sensor 2:"
        '
        'Label2
        '
        Me.Label2.AutoSize = True
        Me.Label2.Location = New System.Drawing.Point(39, 46)
        Me.Label2.Name = "Label2"
        Me.Label2.Size = New System.Drawing.Size(73, 17)
        Me.Label2.TabIndex = 2
        Me.Label2.Text = "Sensor 1: "
        '
        'SerialPort
        '
        '
        'Form1
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(8.0!, 16.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(958, 311)
        Me.Controls.Add(Me.GroupBox3)
        Me.Controls.Add(Me.GroupBox2)
        Me.Controls.Add(Me.GroupBox1)
        Me.Name = "Form1"
        Me.Text = "Form1"
        Me.GroupBox1.ResumeLayout(False)
        Me.GroupBox1.PerformLayout()
        Me.GroupBox2.ResumeLayout(False)
        Me.GroupBox3.ResumeLayout(False)
        Me.GroupBox3.PerformLayout()
        Me.ResumeLayout(False)

    End Sub
    Friend WithEvents counterTxtb As TextBox
    Friend WithEvents Label1 As Label
    Friend WithEvents SendCounterBtn As Button
    Friend WithEvents baudrateCmb As ComboBox
    Friend WithEvents GroupBox1 As GroupBox
    Friend WithEvents GroupBox2 As GroupBox
    Friend WithEvents ConnectBtn As Button

    Friend WithEvents GroupBox3 As GroupBox
    Friend WithEvents s2Valuelbl As Label
    Friend WithEvents Label3 As Label
    Friend WithEvents Label2 As Label


    Dim myPort As Array
    Dim startReceived As Boolean
    Dim receivedCounter As Integer
    Dim sensor1 As String
    Dim sensor2 As String
    Dim a As Boolean
    Dim inData As String
    Dim inDataNum As Integer
    Dim inDataNumTemp As Integer
    Dim inDataNumTemp2 As Integer
    Dim caracter As String
    Delegate Sub SetTextCallBack(ByVal [text] As String)


    Private Sub Form1_Load(sender As Object, e As EventArgs) Handles MyBase.Load

        myPort = IO.Ports.SerialPort.GetPortNames()
        comCmb.Items.AddRange(myPort)
        SendCounterBtn.Enabled = False
        ConnectBtn.Enabled = False

    End Sub

    Private Sub ConnectBtn_Click(sender As Object, e As EventArgs) Handles ConnectBtn.Click
        SerialPort.PortName = comCmb.Text
        SerialPort.BaudRate = baudrateCmb.Text
        SerialPort.Open()

        ConnectBtn.Enabled = False
        SendCounterBtn.Enabled = True

    End Sub

    Private Sub SendCounterbtn_Click(sender As Object, e As EventArgs) Handles SendCounterBtn.Click
        SerialPort.Write(Chr(counterTxtb.Text))
    End Sub

    Public WithEvents SerialPort As IO.Ports.SerialPort
    Friend WithEvents comCmb As ComboBox

    Private Sub comCmb_SelectedIndexChanged(sender As Object, e As EventArgs) Handles comCmb.SelectedIndexChanged
        ConnectBtn.Enabled = True
    End Sub

    Private Sub baudrateCmb_SelectedIndexChanged(sender As Object, e As EventArgs) Handles baudrateCmb.SelectedIndexChanged
        ConnectBtn.Enabled = True
    End Sub

    Private Sub SerialPort_DataReceived(sender As Object, e As SerialDataReceivedEventArgs) Handles SerialPort.DataReceived
        ReceivedText(Int(Asc(SerialPort.ReadExisting())))
    End Sub

    Private Sub ReceivedText(ByVal text As String)

        If Me.s1Valuelbl.InvokeRequired And Me.s2Valuelbl.InvokeRequired Then
            Dim x As New SetTextCallBack(AddressOf ReceivedText)
            Me.Invoke(x, New Object() {(text)})
        Else
            If text = 101 Then
                startReceived = True
                receivedCounter = 1
            Else
                If receivedCounter <> 0 Then
                    receivedCounter += 1
                    Select Case receivedCounter
                        Case 2
                            sensor1 = Str(text)
                        Case 3
                            sensor1 += "." + Str(text)
                            s1Valuelbl.Text = sensor1
                        Case 4
                            sensor2 = Str(text)
                        Case 5
                            sensor2 += "." + Str(text)
                            s2Valuelbl.Text = sensor2
                    End Select

                End If
            End If
        End If

    End Sub

    Public WithEvents s1Valuelbl As Label
End Class
