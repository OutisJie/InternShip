<template>
<div class="myself">
    <div class="node" :style="{'margin-left': `${depth * 20}px`}" @click="open">
        <span v-if="hasChildren">{{isExpanded? "&#9660;": "&#9658;"}}</span>
        <span v-else>&#9633;</span>
        <span :style="getFileStyle(node)"> {{node.name}}</span>
    </div>
    <tree-browser 
        v-if="isExpanded" 
        v-for="child in node.children" 
        :node="child" 
        :key="child.name" 
        :depth="depth + 1"
        @onClick="(node) => $emit('onClick', node)"></tree-browser>
</div>
</template>

<script>
import * as ColorHash from 'color-hash';
const colorHash = new ColorHash();
export default {
    name: 'tree-browser',
    props: {
        node: Object,
        depth: {
            type: Number,
            default: 0
        }
    },
    data: function () {
        return {
            isExpanded: false
        }
    },
    methods: {
        open: function () {
            this.isExpanded = !this.isExpanded;
            if(!this.hasChildren){
                this.$emit('onClick', this.node);

            }
        }, 
        getFileStyle: function(node){
            let color = 'red';
            if(node.children.length === 0){
                color = colorHash.hex(node.name.split('.')[1])
            }
            return {color}
        }
    },
    computed: {
        hasChildren: function () {
            return this.node.children.length !== 0 ? true : false
        }
    }

}
</script>

<style scoped>
.node {
    text-align: left;
    font-size: 18px;
}

/* .myself{
    margin-left: 20px;
} */
</style>
