

# vue3-example

## Project setup
```
npm install
```

### Compiles and hot-reloads for development
```
npm run serve
```

### Compiles and minifies for production
```
npm run build
```

### Lints and fixes files
```
npm run lint
```

### Run your unit tests
```
npm run test:unit
```



## plugins

Once a project is created, you can add more plugins by using `vue add`:

```
vue add @vue/cli-plugin-babel
```

All those plugins are used in the latest version available. You can force Vue CLI to use a specific version by passing the version property:

```
"@vue/cli-plugin-eslint": {
  "version": "^3.0.0"
}
```

This is useful if a new version has a breaking change or a bug, and you need to wait a little bit before using it.



## another use of the vue-cli: rapid prototyping

For really quick prototyping, you can create a really simple Vue application (even one that’s self-contained in a single .vue file) and serve that, without having to download all the dependencies in the `node_modules` folder.

How? First install the `cli-service-global` global package:

```
npm install -g @vue/cli-service-global
```

```
//or
```

```
yarn global add @vue/cli-service-global
```

Create an app.vue file:

```
<template>
    <div>
        <h2>Hello world!</h2>
        <marquee>Heyyy</marquee>
    </div>
</template>
```

and then run

```
vue serve app.vue
```

You can serve more organized projects, composed by JavaScript and HTML files as well. Vue CLI by default uses `main.js / index.js `as its entry point, and you can have a `package.json` and any tool configuration set up. `vue serve` will pick it up.

Since this uses global dependencies, it’s not an optimal approach for anything more than a demonstration or quick testing.



## vue.config.js

vue-cli 3.0使用的是webpack, 但是cli在构建项目的时候去掉了config文件，所以默认的配置文件不能修改。但是通过vue inspect命令可以看到配置的内容。

```
resolve: {
	alias: {
		'@': 'E:\\TONGJI\\InternShip\\vue3-example\\src',
		vue$: 'vue/dist/vue.runtime.esm.js'
    }
}
```

正是因为这个问题，我声明一个全局/局部组件的时候遇到了一个错误：“ You are using the runtime-only build of Vue where the template compiler is not available. Either pre-compile the templates into render functions, or use the compiler-included build. ” 这是由于runtime版本和full版本是有差别的：

- **full**: 包含编译器(compiler)和运行时(runtime)的构建版本
- **compile**: 负责将模板字符串编译成 JavaScript render 函数的代码（所以如果用template声明组件就会报错）。
- **运行时(Runtime)**：负责创建 Vue 实例(creating Vue instances)、渲染(rendering)和修补虚拟 DOM(patching virtual DOM) 等的代码。基本上，等同于完整版本减去编译器。 

```vue
// 这种情况需要编译器(compiler)
new Vue({
  template: '<div>{{ hi }}</div>'
})

// 这种情况不需要
new Vue({
  render (h) {
    return h('div', this.hi)
  }
})
```

在使用 `vue-loader` 或 `vueify` 时，`*.vue` 文件中的模板会 在构建时(build time)预编译(pre-compile)为 JavaScript。最终生成的 bundle 中你不再需要编译器(compiler)，因此可以直接使用只含有运行时的构建版本(runtime-only)。

所以解决的办法就是通过新建一个vue.config.js文件来合并/替换掉默认的配置：

```javascript
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
```

重启serve之后再vue inspect就能看到vue的版本变了。

当然，在一个完整的vue项目里面，用这个是ok的，但是如果只是运行了一个单页面，就是上一个小标题所说的，在声明组件的时候用template也会报错，但是如果我在单页面所在的目录下加上vue.config.js文件之后，vue serve app.vue会报错说无法找到入口，暂时不知道该怎么解决，还需要进一步学习render的用法。。。。

## 单页面组件

一般来说，一个.vue文件就代表一个组件，这个是依赖于webpack的配置，所以，这种模式不适用于single-page app。

在单个页面里面使用CSS的时候，可能会影响到别的组件的CSS，这个可以用<style scoped>标签来解决。如果不声明作用于，那么定义的CSS是全局的，声明scope之后，Vue会自动的为当前组件添加一个类，这个类包含所有声明的样式，类似less.

特别的，如果想将js和css单独拿出来作为文件，可以使用以下的方法：

```html
<template>
  <p>
      {{hello}}
  </p>
</template>
<script src="./hello.js"></script>
<script src="./hello.css"></script>
```

对于单页面组件，data需要声明为一个方法

```javascript
export default {
  data: () => {//箭头函数，对匿名函数/行内行数的this指向问题做了修改。箭头函数this指向声明当前函数的上下文所在的域，行内行数指向的是该上下文父级域（这段总结来自某次阿里面试，对面那个大佬教的=_=），其实vue的官方文档里说了最好不要用箭头函数
    return {
      name: "wujie"
    }
  }
}
```

对于CSS，还可以使用computed来声明

```vue
<template>
<div class="home">
    <p :style="styling">Hi Wujie</p>
</div>
</template>

<script>
export default {
    name: "home",
    data: function() {
        return {
            name: this.getName(),
            textDecoration: 'underline',
            textWeight: 'bold'
        }
    },
    methods: {
      getName: function(){
        return "wujie"
      }
    },
    computed: {
      styling: function() {
        return {
          textDecoration: this.textDecoration,
          textWeight: this.textWeight
        }
      }
    }
};
</script>
```

有没有发现这里的data是一个普通函数，this指向当前组件，没问题，但是换成箭头函数会报错！！为什么呢，因为如果使用箭头函数，就不能获取到methods的getName()方法，console.log(this)居然是undefined！！其实在methods中使用箭头函数声明函数也是undefined

等等，这跟阿里大佬说的不太一样啊，这里句柄不是data吗？那箭头函数的this不是指向data所在的域也就是当前组件吗？

好的接下来是个人推测，鬼知道是对是错=_=

在Vue里面，data和methods一样，在创建的时候都会被混入到Vue实例中，里面的属性和方法可以直接通过this访问，而data和methods方法中的this会被自动的绑定为Vue实例。

官方文档：“注意，**不应该使用箭头函数来定义 method 函数** (例如 `plus: () => this.a++`)。理由是箭头函数**绑定了父级作用域的上下文**，所以 `this` 将不会按照期望指向 Vue 实例，`this.a` 将是 undefined。”

这里的箭头函数，会返回一个绑定当前执行上下文中的this（要不干脆理解为data或者methods的内部域），而且这个this，Vue无法识别并自动绑定到实例中，所以会是undefined。

啊，天啊，受不了了，头痛