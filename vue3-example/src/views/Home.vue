<template>
<div class="home">
    <user-name name="A Vue Tree Browser"></user-name>
    <TreeBrowser :node="root" @onClick="onfileClick"> </TreeBrowser>
</div>
</template>

<script>
// @ is an alias to /src
import HelloWorld from "@/components/HelloWorld.vue";
import  TreeBrowser from "@/components/TreeBrowser.vue";
import root from "../assets/root.json"

export default {
    name: "home",
    components: {
        HelloWorld,
        TreeBrowser
    },
    data: ()=> {
        return {
            //name: this.getName(),
            textDecoration: 'underline',
            textWeight: 'bold',
            root
        }
    },
    methods: {
      getName: function(){
        return "wujie"
      },
      onfileClick: function(node){
        alert(node.name);
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
