var app = angular.module("appModule", []);

app.directive("gqTabContainer", function(){
    return{
        restrict: "E",
        transclude: true,
        scope: {},
        //directive做容器，那么就可以为其所包含的元素引入一个controller，传入$scope,定义域未知
        controller: ['$scope', function($scope){
            var panes = $scope.panes = [];

            //选中
            $scope.select = function(pane){
                angular.forEach(panes, function (pane) {
                    pane.selected = false;
                });

                pane.selected = true;
            }

            //注册
            this.addPane = function(pane){
                if(panes.length === 0){
                    $scope.select(pane);//如果面板数为0，那么选中。。。意义不明,可能是想在第一个条目加入的时候默认选中
                }
                panes.push(pane);
            }
        }],
        templateUrl: "gqTabList"
    }
})

app.directive('gqTabContent', function(){
    return{
        //寻找gqTabContainer
        require: '^gqTabContainer',
        restrict: 'E',
        transclude: true,
        scope: {
            title: '@'
        },
        //第四个参数是获取到的Directive
        link: function(scope, element, attrs, tabContainer){
            tabContainer.addPane(scope);
        },
        templateUrl: 'gqTabContent'
    }
})