<template>
<div class="home">
    <img alt="Vue logo" src="../assets/logo.png">
    <HelloWorld msg="Welcome to Your Vue.js App" />
    <p :style="styling">Hi Wujie</p>
</div>
</template>

<script>
// @ is an alias to /src
import HelloWorld from "@/components/HelloWorld.vue";

export default {
    name: "home",
    components: {
        HelloWorld
    },
    data: ()=> {
      console.log(this);
        return {
            //name: this.getName(),
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
