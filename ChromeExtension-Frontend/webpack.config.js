const path = require('path');
const HtmlWebpackPlugin = require('html-webpack-plugin');
const CopyWebpackPlugin = require('copy-webpack-plugin');

module.exports = {
    devtool: "cheap-module-source-map",
    entry: {
        popup :path.resolve("./frontend/Pages/PopupPage/popup.jsx"),
        options:path.resolve("./frontend/Pages/OptionsPage/options.jsx"),
        background:path.resolve("./frontend/Background/background.js"),
        content:path.resolve("./frontend/ContentScript/content.js"),
      },
      mode: 'development',
      output: {
        path: path.resolve(__dirname, './dist'),
        filename: '[name].js',
        publicPath: '/'
      },
      optimization: {
        splitChunks:{
          chunks : 'all'
        }
      },
      performance: {
        hints: false,
        maxEntrypointSize: 512000,
        maxAssetSize: 512000
    },
    resolve: {
      extensions: ['.js', '.jsx', '.json'],
    },
      module: {
        rules: [
          { //Open .js and .jsx files
            test: /\.(js|jsx)$/,
            exclude: /node_modules/,
            use: {
                loader : 'babel-loader',
                options: {
                    presets:['@babel/preset-env', '@babel/preset-react']
                }
            },
          }]
      },
      plugins: [
        ...GetHTMLPlugins([
            'popup',
            'options'
        ]),
        new CopyWebpackPlugin({
            patterns: [
                {from : path.resolve('public'), to: path.resolve('dist')}
            ]
        })
      ],
}

function GetHTMLPlugins(chunks)
{
    return chunks.map(chunk => new HtmlWebpackPlugin({
        title: 'React Extension',
        filename : `${chunk}.html`,
        chunks:[chunk]
    }))
}