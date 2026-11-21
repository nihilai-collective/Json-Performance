
----
### Twitter Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2833.85 | 0.426108 | 123.051ms | 2889 | 30 | 514.875 | 972.233 | 0.725213 | 1(Win) | true |
| Jsonifier (two-stage) | 2328.28 | 0.109418 | 150.325ms | 2889 | 320 | 536.479 | 1183.35 | 0.0522607 | 2(Loss) | true |
| Glaze | 2219.36 | 0.130415 | 142.199ms | 2889 | 320 | 838.778 | 1241.42 | 0.0229124 | 3(Loss) | true |
| simdjson (ondemand) | 900.469 | 0.192229 | 355.705ms | 2889 | 30 | 1037.8 | 3059.7 | 0.135994 | 4(Loss) | true |
