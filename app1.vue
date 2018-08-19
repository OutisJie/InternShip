<template>
    <div>
        <h2>Hello world!</h2>
        <marquee>Wujie</marquee>
        <user-name name="Hello"></user-name>
    </div>
</template>

<script>
import Vue from 'vue'

Vue.component('user-name',{
    props: ['name'],
    render: h => h(()=>{return {template: `<h1>nihao</h1>`}})
})

export default {
    
}
</script>


<style>
    marquee{
        color: yellowgreen;
        font-size: 30px;
    }
</style>
