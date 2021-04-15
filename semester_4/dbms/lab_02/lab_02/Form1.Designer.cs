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
            this.ParentGrid = new System.Windows.Forms.DataGridView();
            this.ChildGrid = new System.Windows.Forms.DataGridView();
            this.ParentLabel = new System.Windows.Forms.Label();
            this.ChildLabel = new System.Windows.Forms.Label();
            this.UpdateButton = new System.Windows.Forms.Button();
            this.RefreshButton = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize) (this.ParentGrid)).BeginInit();
            ((System.ComponentModel.ISupportInitialize) (this.ChildGrid)).BeginInit();
            this.SuspendLayout();
            // 
            // ParentGrid
            // 
            this.ParentGrid.AllowUserToAddRows = false;
            this.ParentGrid.AllowUserToDeleteRows = false;
            this.ParentGrid.Location = new System.Drawing.Point(12, 35);
            this.ParentGrid.Name = "ParentGrid";
            this.ParentGrid.ReadOnly = true;
            this.ParentGrid.Size = new System.Drawing.Size(546, 150);
            this.ParentGrid.TabIndex = 0;
            // 
            // ChildGrid
            // 
            this.ChildGrid.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.ChildGrid.Location = new System.Drawing.Point(12, 266);
            this.ChildGrid.Name = "ChildGrid";
            this.ChildGrid.Size = new System.Drawing.Size(546, 150);
            this.ChildGrid.TabIndex = 1;
            // 
            // ParentLabel
            // 
            this.ParentLabel.Location = new System.Drawing.Point(12, 9);
            this.ParentLabel.Name = "ParentLabel";
            this.ParentLabel.Size = new System.Drawing.Size(100, 23);
            this.ParentLabel.TabIndex = 2;
            this.ParentLabel.Text = "Parent";
            // 
            // ChildLabel
            // 
            this.ChildLabel.Location = new System.Drawing.Point(12, 240);
            this.ChildLabel.Name = "ChildLabel";
            this.ChildLabel.Size = new System.Drawing.Size(100, 23);
            this.ChildLabel.TabIndex = 3;
            this.ChildLabel.Text = "Child";
            // 
            // UpdateButton
            // 
            this.UpdateButton.Location = new System.Drawing.Point(12, 447);
            this.UpdateButton.Name = "UpdateButton";
            this.UpdateButton.Size = new System.Drawing.Size(93, 32);
            this.UpdateButton.TabIndex = 4;
            this.UpdateButton.Text = "UPDATE";
            this.UpdateButton.UseVisualStyleBackColor = true;
            this.UpdateButton.Click += new System.EventHandler(this.UpdateButton_Click);
            // 
            // RefreshButton
            // 
            this.RefreshButton.Location = new System.Drawing.Point(111, 447);
            this.RefreshButton.Name = "RefreshButton";
            this.RefreshButton.Size = new System.Drawing.Size(93, 32);
            this.RefreshButton.TabIndex = 5;
            this.RefreshButton.Text = "REFRESH";
            this.RefreshButton.UseVisualStyleBackColor = true;
            this.RefreshButton.Click += new System.EventHandler(this.RefreshButton_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(570, 491);
            this.Controls.Add(this.RefreshButton);
            this.Controls.Add(this.UpdateButton);
            this.Controls.Add(this.ChildLabel);
            this.Controls.Add(this.ParentLabel);
            this.Controls.Add(this.ChildGrid);
            this.Controls.Add(this.ParentGrid);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize) (this.ParentGrid)).EndInit();
            ((System.ComponentModel.ISupportInitialize) (this.ChildGrid)).EndInit();
            this.ResumeLayout(false);
        }

        private System.Windows.Forms.Button RefreshButton;

        private System.Windows.Forms.Button UpdateButton;

        private System.Windows.Forms.Label ParentLabel;
        private System.Windows.Forms.Label ChildLabel;

        private System.Windows.Forms.DataGridView ChildGrid;

        private System.Windows.Forms.DataGridView ParentGrid;

        #endregion
    }
}