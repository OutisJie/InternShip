import Vue from "vue";
import App from "./App.vue";
import router from "./router";
import store from "./store";

Vue.config.productionTip = false;

Vue.component("user-name", {
  props: ["name"],
  template: `<h1>{{name}}</h1>`
}); 

// new Vue({
//   el: "#demo-app"
// })
new Vue({
  router,
  store,
  render: h => h(App)
}).$mount("#demo-app");