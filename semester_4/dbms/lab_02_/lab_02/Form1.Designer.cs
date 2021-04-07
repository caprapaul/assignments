namespace lab_02
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }

            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.EmployeesGrid = new System.Windows.Forms.DataGridView();
            this.ReportsToGrid = new System.Windows.Forms.DataGridView();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.UpdateButton = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize) (this.EmployeesGrid)).BeginInit();
            ((System.ComponentModel.ISupportInitialize) (this.ReportsToGrid)).BeginInit();
            this.SuspendLayout();
            // 
            // EmployeesGrid
            // 
            this.EmployeesGrid.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.EmployeesGrid.Location = new System.Drawing.Point(27, 38);
            this.EmployeesGrid.Name = "EmployeesGrid";
            this.EmployeesGrid.Size = new System.Drawing.Size(355, 150);
            this.EmployeesGrid.TabIndex = 0;
            this.EmployeesGrid.Tag = "";
            // 
            // ReportsToGrid
            // 
            this.ReportsToGrid.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.ReportsToGrid.Location = new System.Drawing.Point(27, 254);
            this.ReportsToGrid.Name = "ReportsToGrid";
            this.ReportsToGrid.Size = new System.Drawing.Size(355, 150);
            this.ReportsToGrid.TabIndex = 1;
            // 
            // label1
            // 
            this.label1.Location = new System.Drawing.Point(27, 12);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(100, 23);
            this.label1.TabIndex = 2;
            this.label1.Text = "Employees";
            // 
            // label2
            // 
            this.label2.Location = new System.Drawing.Point(27, 228);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(100, 23);
            this.label2.TabIndex = 3;
            this.label2.Text = "Reports to";
            // 
            // UpdateButton
            // 
            this.UpdateButton.Location = new System.Drawing.Point(535, 214);
            this.UpdateButton.Name = "UpdateButton";
            this.UpdateButton.Size = new System.Drawing.Size(75, 23);
            this.UpdateButton.TabIndex = 4;
            this.UpdateButton.Text = "UPDATE";
            this.UpdateButton.UseVisualStyleBackColor = true;
            this.UpdateButton.Click += new System.EventHandler(this.UpdateButton_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.UpdateButton);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.ReportsToGrid);
            this.Controls.Add(this.EmployeesGrid);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize) (this.EmployeesGrid)).EndInit();
            ((System.ComponentModel.ISupportInitialize) (this.ReportsToGrid)).EndInit();
            this.ResumeLayout(false);
        }

        private System.Windows.Forms.Button UpdateButton;

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;

        private System.Windows.Forms.DataGridView ReportsToGrid;

        private System.Windows.Forms.DataGridView EmployeesGrid;

        #endregion
    }
}