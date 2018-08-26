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

## 简单的Vue组件

一般来说，一个.vue文件就代表一个组件，这个是依赖于webpack的配置，所以，这种模式不适用于single-page app。

有个非常重要的观念：组件是可以复用的，也是可以递归调用的，即在组件内引用自己。因为组件是可复用的，所以他们的data、computed、wath、methods以及生命钩子都是相同的，各个实例各自维护一份属于自己的拷贝。

### data

无论如何，data需要声明为一个方法。因为方法会返回一个对象，所以每个实例可以在拿到返回的对象的时候创建一份独立的拷贝。

```javascript
export default {
  data: () => {//箭头函数，对匿名函数/行内行数的this指向问题做了修改。箭头函数this指向声明当前函数的上下文所在的域，行内行数指向的是该上下文父级域（这段总结来自某次阿里面试，对面那个大佬教的=_=），其实vue的官方文档里说了最好不要用箭头函数
    return {
      name: "wujie"
    }
  }
}
```

### CSS

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



## 指令

#### v-text： 

v-text="name"和使用{{name}}的效果一样，主要用于操作元素中的纯文本

1. 这里的双引号不是字符串的意思，而是vue自定义的划定界限的符号。如果需要输出字符串，就需要在里面再添加单引号。
2. {{}}代表的就是“”
3. 当网速很慢或者js报错的时候，{{name}}会直接在页面上渲染出来，而使用v-text时，如果出错是不会显示的
4. 如果你想用unicode的特殊字符，比如说&#9660；&#9658; 这种图标的话，那么v-text是不管用的，只能用{{}}才能正常渲染出来。我不知道这是不是vue的一个缺陷。

#### v-html:

主要用于操作元素中的HTML标签，v-text会将元素当成HTML标签解析后输出

```html
<div id="app" v-html="message"></div>
var app = new Vue({
	el: "#app",
data: {
	message: "<img src='img/a.jpg' width='200px'>"//显示图片
}
})
```

过多的使用v-html可能会导致XSS攻击，所以尽量少用。

##### XSS攻击是什么？

	跨站脚本攻击（Cross Site Scripting）, XSS攻击通常指的是通过利用网页开发是留下的漏洞，恶意攻击者往Web页面插入恶意Script代码，当用户浏览时，嵌入其中Web里面的script代码会被执行，从而达到恶意攻击用户的目的。

危害：

- 流量劫持
- 获取用户的cookie信息，盗取账号
- 篡改、删除页面信息
- 配合CSRF攻击，实施进一步的攻击
- 。。。

其余就不去了解了，先回头看vue

#### v-bind:

绑定标签属性， ：符号后面是标签属性名

```html
<div id = "app">
  <span v-bind:title = 'message'>鼠标悬停查看动态绑定的信息</span>
</div>
var app = new Vue({
	el: '#app,
    data: {
		message: '加载于' + new Date()
    }
})
```

#### v-once:

页面元素和组件只会渲染一次，每次页面重新渲染的时候，该组件以及它所有的子节点都会被视为静态内容并跳过：

```html
<div id='app'>
  <span v-once>this will never change:{{message}}</span>
  <!--包含子元素-->
  <div v-once>
    <hi>{{message}}</hi>
    <p>
      {{name}}
    </p>
  </div>
</div>
<script>
  var app = new Vue({
    el: "#app",
    data: {
      message: "nihao",
      name: "wujie"
    }
  })
</script>
```

#### v-modal:

双向绑定，懒得写了

#### v-for:

我好困啊

```html
<li v-for="(param1, param2) in list">param1表示元素，param2表示index</li>
```

#### v-on:

```
v-on:click="handleClick('test')"
```

#### v-if/v-show:

区别在于if会只把显示的组件加到DOM文件中，之后不会再出现；show会添加到DOM中，只不过隐藏了起来，之后可以再通过交互显示出来。



## 事件修饰符

vue提供了一些可选的事件修饰符，可以和v-on一起使用，使你所绑定的事件执行某些事先规定的操作。

这些东西适用于：方法只有纯粹的数据逻辑，而不是去处理DOM事件细节。

这些修饰符包括：

- .stop
- .prevent
- .capture
- .self
- .once
- .passive

举例：

```html
<a v-on:clicl.stop = 'dothis'>阻止单击事件继续传播</a>
<form v-on:submit.prevent = "formSubmitted">提交事件而不再重载页面</form>
<a v-on:click.stop.prevent='dothis'>修饰符之间可以串联</a>

<!-- 添加事件监听器时使用事件捕获模式 -->
<!-- 即元素自身触发的事件先在此处理，然后才交由内部元素进行处理 -->
<div v-on:click.capture="doThis">...</div>

<!-- 只当在 event.target 是当前元素自身时触发处理函数 -->
<!-- 即事件不是从内部元素触发的（内部元素通过$emit('click')可以触发） -->
<div v-on:click.self="doThat">...</div>

<!-- 点击事件将只会触发一次 -->
<a v-on:click.once="doThis"></a>

<!-- 滚动事件的默认行为 (即滚动行为) 将会立即触发 -->
<!-- 而不会等待 `onScroll` 完成  -->
<!-- 这其中包含 `event.preventDefault()` 的情况 -->
<div v-on:scroll.passive="onScroll">...</div>
```

使用修饰符时，顺序很重要；相应的代码会以同样的顺序产生。因此，用 v-on:click.prevent.self会阻止**所有的点击**，而 `v-on:click.self.prevent` 只会阻止对元素自身的点击。

如果.passive和.prevent一起使用，.prevent将会被忽略，.passive会告诉浏览器你不想阻止事件的默认行为。

##  按键修饰符

在监听键盘事件的时候，可以通过keyCode来检测。不过要记住所有的keyCode比较困难，所以Vue为最常用的按键提供了别名，全部的按键包括：

`.enter .tab .delete .esc .space .up .down .left .right`

```html
<!--只有在‘keyCode’是13的时候调用‘vm.submit()’-->
<input v-on:keyup.13="submit">

<input v-on:keyup.enter="submit">

<!--缩写语法-->
<input @keyup.enter="submit">
```

我们也可以通过全局`config.keyCode`对象来自定义按键修饰符的别名：

```vue
Vue.config.keyCodes.f1 = 12
```

如果想使用类似于ctrl+C这种组合键，Vue提供了四个修饰符来实现仅在按下相应按键时才会触发鼠标或键盘事件的监听器：

`.ctrl .alt .shift .meta`

```html
<!--Alt+C-->
<input @keyup.alt.67="clear">

<!--Ctrl+Click-->
<div @click.ctrl="doSomething">
    do something
</div>
```

### .exact修饰符

如果使用普通的按键修饰符来监听组合键，那么当多余的按键被按下时也会触发，.exact 解决了这个问题

```html
<!--即使Alt或Shift被一同按下的时候也会触发-->
<button @click.ctrl='onClick'>A</button>

<!--当且仅当ctrl被按下的时候会触发-->
<button @click.ctrl='onClick'>A</button>

<!-- 没有任何系统修饰符被按下的时候才触发 -->
<button @click.exact="onClick">A</button>
```

### 鼠标按钮修饰符

- .left
- .right
- .middle



## V-model

### 表单

可以使用v-model指令在表单<input>、<textare>、<select>元素上创建双向的数据绑定，它会根据控件的类型自动选取正确的方法来更新元素。v-model本质上是语法糖，它有如下的缺点：

- v-model会忽略所有的表单元素的value、checked、selected特性的初始值，而是将Vue实例的数据对象作为数据来源更新页面。所以初始值需要在data属性中事先声明
- 在使用输入法编辑的时候，在输入法组合文字的过程中，页面不会得到更新。不过input事件好像可以实现

### 文本、复选框、单选框、选择框

这部分的内容比较简单而且很难总结，所以我就直接贴一个链接得了，[啦啦啦😂](https://cn.vuejs.org/v2/guide/forms.html)

### 修饰符

- .lazy：默认情况下，v-model在每次input事件触发后将输入框的值与数据进行同步。使用lazy后可以变为change事件触发才进行同步

  ```html
  <!--在change时而非input时更新（大概效果是你输入完之后才会更新）-->
  <input v-model.lazy="msg">
  ```

- .number：可以将输入的值转换为数值类型，因为即使是使用type="number"，输入的数字还是会被转换为字符串。

  ```html
  <input v-model.number="age" type="number">
  ```

- .trim：可以自动过滤掉用户输入的首位空白字符

  ```html
  <input v-model.trim="msg">
  ```
