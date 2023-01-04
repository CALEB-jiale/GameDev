# game_dev

## Dependencies

SDL2 安装地址：

> /Library/Frameworks/SDL2.framework

SDL2 配置过程：

1. 在 Xcode 左侧栏点击项目进入项目管理界面
2. 进入 Build Phases 界面
3. 在 Link Binary With Libraries 一栏点击添加符号
4. 在弹出界面中选择 Add Files
5. 将 SDL2 文件添加

## Settings

### Xcode 读取相对路径

1. 在 Xcode 顶端菜单栏选择 Product -> Scheme -> Edit Scheme
2. 在弹出页面选择 Run -> Options
3. 在 Working Dictionary 选项里面，勾选 Using cusom working dictionary

## Xcode 修改默认生成路径

1. 在 Xcode 顶端菜单栏选择 Xcode -> Settings
2. 在弹出页面选择 Locations -> Advanced
3. 在弹出页面选择 Custome，然后在下拉菜单选择 Relative to Workspace