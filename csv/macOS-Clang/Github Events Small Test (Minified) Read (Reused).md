
----
### Github Events Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2073.9 | 0.28508 | 95.1999ms | 1691 | 80 | 393.129 | 777.6 | 0.336441 | 1(Win) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1801.22 | 0.135984 | 107.435ms | 1691 | 1280 | 1897.32 | 895.32 | 0.0381469 | 2(Tie) | true |
| Glaze STATISTICAL TIE | 1794.21 | 0.193612 | 108.937ms | 1691 | 320 | 969.072 | 898.816 | 0.157747 | 2(Tie) | true |
| simdjson (ondemand) | 1263.97 | 0.0450881 | 143.801ms | 1691 | 2560 | 847.181 | 1275.87 | 0.186686 | 4(Loss) | true |
