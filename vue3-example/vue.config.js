const path = require('path')

module.exports = {
    devServer: {
        port: 3000
    },
    configureWebpack: config => {//webpack配置，值为对象时会合并配置，为方法时会改写配置
        Object.assign(config, {
            resolve: {
                alias: {
                    '@': path.resolve(__dirname, './src'),
                    'vue$': 'vue/dist/vue.esm.js'
                }
            }
        })

    }
}