
extern Jahley::App* Jahley::CreateApplication();


int main (int argc, char** argv)
{
    {
       // libassert::enable_virtual_terminal_processing_if_needed();
        libassert::set_failure_handler (custom_fail);

        ScopedStopWatch sw (_FN_);

        Jahley::App* app = Jahley::CreateApplication();
        if (app->isWindowApp())
        {
            app->run();
        }

        delete app;
    }

    std::cout << "Press ENTER to continue...";
    std::cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
}