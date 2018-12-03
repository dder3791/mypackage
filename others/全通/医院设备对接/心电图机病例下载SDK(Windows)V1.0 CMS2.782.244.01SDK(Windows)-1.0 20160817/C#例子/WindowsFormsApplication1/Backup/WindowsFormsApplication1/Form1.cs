using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.Management;

namespace WindowsFormsApplication1
{
    [UnmanagedFunctionPointer(CallingConvention.StdCall)]
    public delegate void CallBack_DownloadMessage(int emDLM, int nPercent);     // 声明回调函数的委托函数类型
    
    public partial class Form1 : Form
    {
        public delegate void DownloadMessageEventHandler(Object sender, DMEventArgs e);     // 服务状态的事件的委托函数类型
        public static event DownloadMessageEventHandler DownloadMessageControl;             // 服务状态的事件

        private delegate void UpdateLBX(string str);                // 更新Listbox内容的跨线程函数
        private delegate void UpdatePRG(int nPercent);              // 更新Progressbar进度的跨线程函数

        // 启动下载数据服务
        [DllImport("Sync_CaseDownload.dll")]
        public static extern int StartDownloadCase(int nCommNum, int nInterval, string pPath, CallBack_DownloadMessage fcbDownloadMessage);

        // 停止下载数据服务
        [DllImport("Sync_CaseDownload.dll")]
        public static extern void StopDownloadCase();

        // 检查端口是否连接了ECG设备
        [DllImport("Sync_CaseDownload.dll")]
        public static extern int CheckPort(int nCommNum);

        public static CallBack_DownloadMessage myDownloadMessage;   // 回调函数指针

        public static GCHandle gch;

		public static bool Running;
		public static bool StopDownload;

        public Form1()
        {
            InitializeComponent();

            progressBar1.Maximum = 100;
            progressBar1.Minimum = 0;

			Running = false;

            // 需要监听事件
            DownloadMessageControl += new DownloadMessageEventHandler(this.Download_Message);
        }
        
        ~Form1()
        {

        }

		// 回调函数，用于接收并处理下载过程中的状态和消息
        public static void fnDownloadMessage(int emDLM, int nPercent)
        {
            // 触发事件
            DownloadMessageControl(new Form1(), new DMEventArgs(emDLM, nPercent));	
        }

        //事件处理函数，用来更新控件内容
        public void Download_Message(Object o, DMEventArgs e)
        {
            int emDLM = e.DLM;
            int nPercent = e.Percent;

            string message = "未知消息";
            switch (emDLM)
            {
                case 0:				// 0  已下载新病例
					message = "已下载新病例";
                    break;
                case 1:				// 1  端口打开失败
					message = "端口打开失败";
                    break;
				case 2:				// 2  获取设备版本号失败
					message = "获取设备版本号失败";
					break;
				case 3:				// 3  获取设备标识失败
					message = "获取设备标识失败";
					break;
				case 4:				// 4  获取病例数失败
					message = "获取病例数失败";
					break;
				case 5:				// 5  未检测到新病例
					message = "未检测到新病例";
					break;
				case 6:				// 6  获取病例信息失败
                    message = "获取病例信息失败";
					break;
				case 7:				// 7  获取病例数据失败
					message = "获取病例数据失败";
					break;
				case 8:				// 8  删除病例失败
					message = "删除病例失败";
					break;
				case 9:				// 9  磁盘空间不足
					message = "磁盘空间不足";
					break;
				case 10:			// 10 中止下载
					message = "中止下载";
					break;
                case 11:
                    message = "正在下载数据...";
                    MyUpdatePRG(nPercent);          // 更新下载进度条
                    break;
                default:
                    break;
            }

            // 更新Listbox内容
            MyUpdateLBX(message);
        }

        // 更新Listbox内容
        private void MyUpdateLBX(string str)
        {
            if (this.listBox1.InvokeRequired)       //等待异步
            {
                // 通过代理添加列表项
                UpdateLBX uc = new UpdateLBX(MyUpdateLBX);
                this.BeginInvoke(uc, str);
            }
            else
            {
                listBox1.Items.Add(str);
                listBox1.TopIndex = listBox1.Items.Count - 1;
            }
        }

        // 更新下载进度条
        private void MyUpdatePRG(int nPercent)
        {
            if (this.progressBar1.InvokeRequired)   //等待异步
            {
                // 通过代理调用更新进度条
                UpdatePRG uc = new UpdatePRG(MyUpdatePRG);
                this.BeginInvoke(uc, nPercent);
            }
            else
            {
                progressBar1.Value = nPercent;
            } 
        }

		// Start按钮单击响应
        private void button1_Click(object sender, EventArgs e)
        {
			if (Running)
			{
				MessageBox.Show("Download Service is running!", "Information");
				return;
			}
			
			this.listBox1.Items.Clear();
			Running = true;
			StopDownload = false;
			
            int port = 0;
			
			// 检查是否有设备连接到某个端口
            for (int i = 1; i < 100; ++i)
            {
                if (CheckPort(i) != 0)
                {
					// 找到设备，保存连接端口
                    port = i;

                    this.listBox1.Items.Add(String.Format("找到设备端口 {0:d}", i));
                    break;
                }
                this.listBox1.Items.Add(String.Format("端口 {0:d} 没有连接设备", i));
            }
			
            if (port > 0)
            {
				// 找到已连接设备，开始下载服务
				int time_interval = 1000;		        // 轮询间隔 1000 单位毫秒
				string save_path = "C:\\zzzTest";		// 病例文件保存路径 

                gch = GCHandle.Alloc(new CallBack_DownloadMessage(fnDownloadMessage));

                Running = StartDownloadCase(port, time_interval, save_path, (CallBack_DownloadMessage)gch.Target/*myDownloadMessage*/) != 0;

                if (!Running)
                {
                    MessageBox.Show("Start download service failed!", "Error");
                }
            }
            else 
            {
                MessageBox.Show("Not found device!", "Error");
            }
        }

		// Stop按钮单击响应
        private void button2_Click(object sender, EventArgs e)
        {
			StopDownloadCase();         // 注意，阻塞式函数
            Running = false;
            gch.Free();
        }
    }

    public class DMEventArgs : EventArgs            // 用于传递服务状态的自定义事件参数
    {
        private readonly int m_emDLM;
        private readonly int m_nPercent;
        public DMEventArgs(int emDLM, int nPercent)
        {
            m_emDLM = emDLM;
            m_nPercent = nPercent;
        }

        public int DLM { get { return m_emDLM; } }
        public int Percent { get { return m_nPercent; } }
    }
}