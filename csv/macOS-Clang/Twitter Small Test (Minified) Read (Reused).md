
----
### Twitter Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2882.37 | 0.086737 | 114.797ms | 2889 | 640 | 439.931 | 955.867 | 0.106302 | 1(Win) | true |
| Jsonifier (two-stage) | 2250.53 | 0.0700176 | 143.487ms | 2889 | 640 | 470.239 | 1224.23 | 0.0311518 | 2(Loss) | true |
| Glaze | 2123.94 | 0.123634 | 158.31ms | 2889 | 640 | 1646.13 | 1297.2 | 0.353597 | 3(Loss) | true |
| simdjson (ondemand) | 894.625 | 0.143935 | 322.872ms | 2889 | 2560 | 50302.1 | 3079.69 | 0.325737 | 4(Loss) | true |
