using System;
using System.Diagnostics;

class Program
{
    static void Main(string[] args)
    {
        try
        {
            // Start a new process to run the "whoami" command.
            Process process = new Process();
            process.StartInfo.FileName = "whoami";
            process.StartInfo.UseShellExecute = false;
            process.StartInfo.RedirectStandardOutput = true;

            // Start the process and read the output.
            process.Start();

            // Read and display the output of the "whoami" command.
            string output = process.StandardOutput.ReadToEnd();
            Console.WriteLine("Output of whoami command: " + output);

            // Wait for the process to exit
            process.WaitForExit();

            // Display current process ID
            Console.WriteLine("\nProcess ID is: " + Process.GetCurrentProcess().Id);
        }
        catch (Exception ex)
        {
            // Handle any potential exceptions
            Console.WriteLine("Error: " + ex.Message);
        }
    }
}
