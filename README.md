<div align="center">
<h1>✨ AntiPython Colab Compiler for AI</h1>
  
<a href="https://github.com/Fileforma/AntiPython-AI-Club/" target="_blank" title="GitHub stars">
<img src = "https://api.visitorbadge.io/api/daily?path=https%3A%2F%2Fgithub.com%2FFileforma%2FAntiPython-AI-Compiler-Colab&label=Online%20Visitors&countColor=%23263759&style=flat-square"
 alt="Visitor Count" />
<img src="https://img.shields.io/github/stars/Fileforma" alt="GitHub stars"/>
</a>

**Google Colab GPU access** in `your favorite programming language`

Receive [project updates](https://antipythonai.substack.com/)

Contribute [1$ towards your favorite language](https://opencollective.com/fileforma)


<img src="https://res.cloudinary.com/dcrelr5e7/image/upload/v1706581854/Virtual_Assistant_Promotion_of_Services_Facebook_Cover_Photo_kxqr4d.png" alt="Banner"/>

</div>


## What's this?
AntiPython Colab is a source to source compiler that let's you **build AI in Java, Rust, JavaScript, Flutter, C#, Go, Ocaml(and etc...)** utilizing free Google Colab GPUs!

It's blazingly fast and very robust as it uses websockets and the Treesitter C library under the hood.

✔ Web GUI for ease of access

✔ No language lock-in! Free and opensource language servers available!

✔ Super secure language servers running on your personal device.


### Motivation
AI is super interesting but Python is a bore. We built a compiler that translates programming languages to Python!

AntiPython Colab is built for:

-   Programmers interested in free GPU access and AI - just without the Python.
-   Developers keen on accessing Python's *vast AI tooling* without touching Python. 
-   Companies that seek to add AI to their products without needing to hire Python devs.
-   Hobbyists who realize they spend more time setting up Python environments than actual coding.

## Development Status!
This is a work in progress. Send direct feeback here - murage@fileforma.com

25th Jan - Built Chrome extension interface.

29th Jan - Java imports working. 

[Sponsor your favorite language here🙏](https://opencollective.com/fileforma)

Join the [mailing list](https://antipythonai.substack.com/)

<div align="center">
<h1>✨ Getting started ✨</h1>
<h3>Java demo showing Java to Python imports available</h3>
<p> <b>Node JS and GCC<b> needed to compile Javascript and C</p>
</div>
  
[Watch the video tutorial](https://youtu.be/mmfHCCA0IHE)

1. Clone the repo to your personal computer
   ```
   git clone https://github.com/Fileforma/AntiPython-AI-Compiler-Colab.git
   ```
2. Open the folder `AntiPython-AI-Compiler-Colab`
   ```
   cd AntiPython-AI-Compiler-Colab
   ```

3. Open the folder `ChromeExtension-Frontend`
   ```
   cd ChromeExtension-Frontend
   ```
4. Install node modules using npm
   ```
   npm install
   ```
5. Build the Chrome Extension. A new folder `dist` is created inside **ChromeExtension-Frontend**
   ```
   npm run build
   ```
6. Open Google Chrome and visit `chrome://extensions` in a new tab. Enable Developer Mode.
7. Click the `Load unpacked button` and select the folder **dist** created in `Step 5`.
8. Visit the Google Colab webpage `https://colab.research.google.com/` and create a new notebook.

9. Go back to the folder `AntiPython-AI-Compiler-Colab`. Open a *new* terminal window.
10. Open the folder `Compiler-Backend` and open the folder `Translator`
   ```
   cd Compiler-Backend && cd Translator
   ```
11. Start the Language Server
    ```
    clear && gcc main.c mongoose.c cJSON.c ../SupportedLanguages/tree-sitter-java/src/parser.c ../TreeSitterLibrary/libtree-sitter.a -o main.o && ./main.o
    ```
13. Go back to the folder `ChromeExtension-Frontend` from Step 3. Open another *new* terminal window. Start the extension server.
    ```
    npm start
    ```
14. Go to the Google Colab page and have fun with the Java Demo!
    *Only imports working at the moment. This is a demo showing the Chrome interface*
    Try these Java examples
    ```
    import math;
    import com.fileforma.tensorflow;
    import com.fileforma.numpy as numpy;
    ```

## Our other products
[Making VS Code Extensions for Engineering Managers and CTOs](https://www.udemy.com/course/vscode-extensions)

[FFmpeg Data Structures in the C language](https://www.udemy.com/course/part-1-video-coding-with-ffmpeg-and-c-in-replit-online-ide)  



## Financial Supporters

🙏 Get Lifetime Support [for Early Backers](https://opencollective.com/fileforma)

🏢 Corporate Sponsor [support](https://opencollective.com/fileforma)

Join the [mailing list](https://antipythonai.substack.com/)


[<img src="https://img.shields.io/twitter/follow/murage_kibicho" alt="Follow for updates"/>](https://twitter.com/murage_kibicho)


