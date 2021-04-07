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
            this.PlayersGrid = new System.Windows.Forms.DataGridView();
            this.CharactersGrid = new System.Windows.Forms.DataGridView();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.UpdateButton = new System.Windows.Forms.Button();
            this.RefreshButton = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize) (this.PlayersGrid)).BeginInit();
            ((System.ComponentModel.ISupportInitialize) (this.CharactersGrid)).BeginInit();
            this.SuspendLayout();
            // 
            // PlayersGrid
            // 
            this.PlayersGrid.AllowUserToAddRows = false;
            this.PlayersGrid.AllowUserToDeleteRows = false;
            this.PlayersGrid.Location = new System.Drawing.Point(12, 35);
            this.PlayersGrid.Name = "PlayersGrid";
            this.PlayersGrid.ReadOnly = true;
            this.PlayersGrid.Size = new System.Drawing.Size(546, 150);
            this.PlayersGrid.TabIndex = 0;
            // 
            // CharactersGrid
            // 
            this.CharactersGrid.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.CharactersGrid.Location = new System.Drawing.Point(12, 266);
            this.CharactersGrid.Name = "CharactersGrid";
            this.CharactersGrid.Size = new System.Drawing.Size(546, 150);
            this.CharactersGrid.TabIndex = 1;
            // 
            // label1
            // 
            this.label1.Location = new System.Drawing.Point(12, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(100, 23);
            this.label1.TabIndex = 2;
            this.label1.Text = "Players";
            // 
            // label2
            // 
            this.label2.Location = new System.Drawing.Point(12, 240);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(100, 23);
            this.label2.TabIndex = 3;
            this.label2.Text = "Characters";
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
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.CharactersGrid);
            this.Controls.Add(this.PlayersGrid);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize) (this.PlayersGrid)).EndInit();
            ((System.ComponentModel.ISupportInitialize) (this.CharactersGrid)).EndInit();
            this.ResumeLayout(false);
        }

        private System.Windows.Forms.Button RefreshButton;

        private System.Windows.Forms.Button UpdateButton;

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;

        private System.Windows.Forms.DataGridView CharactersGrid;

        private System.Windows.Forms.DataGridView PlayersGrid;

        #endregion
    }
}