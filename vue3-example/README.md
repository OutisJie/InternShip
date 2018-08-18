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