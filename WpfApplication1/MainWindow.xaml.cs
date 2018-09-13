using Microsoft.Win32;
using OpenCvSharp;
using OpenCvSharp.Extensions;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace WpfApplication1
{
    /// <summary>
    /// MainWindow.xaml에 대한 상호 작용 논리
    /// </summary>
    public partial class MainWindow : System.Windows.Window
    {
        [DllImport("mfclibrary1.dll")]
        public static extern int addValue(int a, int b, ref int c);
        [DllImport("mfclibrary1.dll")]
        public static extern void addValue2(IntPtr p, int a, int b, ref int c);
        [DllImport("mfclibrary1.dll")]
        public static extern IntPtr initClassDll();
        [DllImport("mfclibrary1.dll")]
        public static extern IntPtr endClassDll(IntPtr p);
        IntPtr m_ClassPointer;
        public MainWindow()
        {
            InitializeComponent();

            m_ClassPointer = initClassDll();
        }

        private void button_Click(object sender, RoutedEventArgs e)
        {
            int a, b, c;

            a = 1;
            b = 2;
            c = 0;
            addValue2(m_ClassPointer, a, b, ref c);

        }

        private void button1_Click(object sender, RoutedEventArgs e)
        {
            int a,b,c,d;

            a = 5;
            b = 5;
            c = 0;
            d=addValue(a, b, ref c);

            OpenFileDialog fDlg= new OpenFileDialog();
            string strFileName="";

            fDlg.DefaultExt = "BMP";
            fDlg.Filter = "그림파일(*.bmp, *.jpg, *.png)|*.bmp;*.jpg;*.png;|모든파일 *.*|*.*";
            
            if(fDlg.ShowDialog()==true)
            {
                strFileName = fDlg.FileName;
                
                Mat imgSrc = new Mat(strFileName, ImreadModes.Color);
                WriteableBitmap bitImg = new WriteableBitmap(imgSrc.Width, imgSrc.Height, 96, 96, PixelFormats.Bgr24, null);
                
                unsafe
                {
                    Byte* pBuffer = (Byte *)imgSrc.Data;
                    for (a = 0; a < imgSrc.Height; a++)
                    {
                        for (b = 0; b < imgSrc.Width; b++)
                        {
                            for (c = 0; c < imgSrc.Channels(); c++)
                            {
                                pBuffer[a * imgSrc.Width * imgSrc.Channels() + b * imgSrc.Channels() + c] = (Byte)((a * b + c) % 255); //흑백물결무늬
                                pBuffer[a * imgSrc.Width * imgSrc.Channels() + b * imgSrc.Channels() + c] = (Byte)((a + b + c) % 255); //흑백사선무늬
                                pBuffer[a * imgSrc.Width * imgSrc.Channels() + b * imgSrc.Channels() + c] = (Byte)((a + b * c) % 255); //칼라줄무늬
                            }
                            //칼러격자무늬
                            pBuffer[a * imgSrc.Width * imgSrc.Channels() + b * imgSrc.Channels() + 0] = (Byte)((a) % 255);
                            pBuffer[a * imgSrc.Width * imgSrc.Channels() + b * imgSrc.Channels() + 1] = (Byte)((b) % 255);
                            pBuffer[a * imgSrc.Width * imgSrc.Channels() + b * imgSrc.Channels() + 2] = (Byte)((a + b) % 255);
                        }
                    }
                }
                WriteableBitmapConverter.ToWriteableBitmap(imgSrc, bitImg);
                image.Source = bitImg;
                
            }
            
        }

        private void Window_Closed(object sender, EventArgs e)
        {
            if( m_ClassPointer != IntPtr.Zero)
            {
                endClassDll(m_ClassPointer);
                m_ClassPointer = IntPtr.Zero;
            }
            
        }
        ~MainWindow()
        {
            if (m_ClassPointer != IntPtr.Zero)
            {
                endClassDll(m_ClassPointer);
                m_ClassPointer = IntPtr.Zero;
            }
        }
    }
}
