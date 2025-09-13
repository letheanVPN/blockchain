# MCP-CMake: CMakeプロジェクト管理ツール

[View in English (英語のドキュメントはこちら)](./README.md)

MCP-CMakeは、Model Context Protocol (MCP) を通じてCMakeベースのプロジェクトを管理するための一連のツールを提供します。これにより、CMakeプロジェクトの設定、ビルド、テストをプログラム的に実行できます。

## 🚀 はじめに

### サーバーのセットアップ

MCP-CMakeサーバーを起動するには、CMakeプロジェクトのルートディレクトリのパスを指定する必要があります。このディレクトリには `CMakePresets.json` ファイルが含まれている必要があります。

```bash
python -m mcp_cmake.server -w /path/to/your/cmake/project
```

サーバーが起動すると、最初のヘルスチェックが実行されます。成功すると、サーバーは `Healthy` 状態になり、ツール呼び出しを受け入れる準備が整います。

### サーバーの状態

サーバーは2つの内部状態を維持します：
-   `WORKING_DIRECTORY`: 管理対象のCMakeプロジェクトへの絶対パス。
-   `IS_HEALTHY`: サーバーの準備ができているかを示すブール値のフラグ。ほとんどのツールが機能するには、これが `true` である必要があります。

## 🛠️ 利用可能なツール

### 1. `health_check`

開発環境を検証し、成功した場合にサーバーを `Healthy` 状態に設定します。このツールは、作業ディレクトリを新しいプロジェクトに切り替えるためにも使用できます。

-   **引数:**
    -   `working_dir` (Optional[str]): CMakeプロジェクトディレクトリへの絶対パス。指定された場合、サーバーはこのディレクトリに切り替わります。
-   **戻り値:** チェック結果を含む辞書。

**例:**
```python
# 現在の作業ディレクトリでヘルスチェックを実行
client.call_tool("health_check")

# 新しいプロジェクトに切り替えて、そのヘルスチェックを実行
client.call_tool("health_check", {"working_dir": "/path/to/another/project"})
```

### 2. `list_presets`

現在の作業ディレクトリの `CMakePresets.json` ファイルから、利用可能な `configurePresets` を一覧表示します。

-   **引数:** なし
-   **戻り値:** プリセット名の文字列のリスト。

**例:**
```python
presets = client.call_tool("list_presets")
print(presets.text)
# 出力: ['default', 'ninja-multi-config', 'windows-msvc']
```

### 3. `create_project`

指定されたプリセットを使用してCMakeプロジェクトを設定します。このツールはコンパイラを自動検出し、構造化された診断ロギング（GCC/Clangの場合はJSON、MSVCの場合はSARIF）を有効にします。

-   **引数:**
    -   `preset` (str): 使用するコンフィグプリセットの名前。
    -   `cmake_defines` (Optional[dict]): `-D` フラグで渡すCMake定義の辞書（例： `{"MY_VAR": "VALUE"}`）。
-   **戻り値:** 成功または失敗のレスポンス。

**例:**
```python
client.call_tool("create_project", {"preset": "default"})
```

### 4. `build_project`

指定されたビルドプリセットを使用してプロジェクトをビルドします。ビルドが失敗した場合、コンパイラの出力から解析された構造化エラーレポートを返します。

-   **引数:**
    -   `preset` (str): 使用するビルドプリセットの名前。
    -   `targets` (Optional[list[str]]): ビルドする特定のターゲットのリスト。
    -   `verbose` (Optional[bool]): `True` の場合、詳細なビルド出力を有効にします。
    -   `parallel_jobs` (Optional[int]): ビルドに使用する並列ジョブの数。
-   **戻り値:** 詳細なエラー情報を含む成功または失敗のレスポンス。

**例:**
```python
# デフォルトターゲットをビルド
client.call_tool("build_project", {"preset": "default"})

# 4つの並列ジョブで特定のターゲットをビルド
client.call_tool("build_project", {"preset": "default", "targets": ["my_executable"], "parallel_jobs": 4})
```

### 5. `test_project`

指定されたテストプリセットを使用してプロジェクトのテストを実行します。

-   **引数:**
    -   `preset` (str): 使用するテストプリセットの名前。
    -   `test_filter` (Optional[str]): 実行するテストをフィルタリングするための正規表現。
    -   `verbose` (Optional[bool]): `True` の場合、詳細なテスト出力を有効にします。
    -   `parallel_jobs` (Optional[int]): 実行する並列テストの数。
-   **戻り値:** 成功または失敗のレスポンス。

**例:**
```python
# すべてのテストを実行
client.call_tool("test_project", {"preset": "default"})

# 特定の名前に一致するテストを実行
client.call_tool("test_project", {"preset": "default", "test_filter": "MyTest*"})
```
