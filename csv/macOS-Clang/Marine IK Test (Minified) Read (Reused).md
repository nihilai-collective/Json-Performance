
----
### Marine IK Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 757.518 | 0.295003 | 8505.55ms | 1834197 | 30 | 1.39213e+09 | 2.30915e+06 | 0.39892 | 1(Win) | true |
| Jsonifier (two-stage) | 644.314 | 0.228533 | 9662.64ms | 1834197 | 30 | 1.15482e+09 | 2.71487e+06 | 0.115539 | 2(Loss) | true |
| Glaze | 517.483 | 0.104624 | 5806.18ms | 1834197 | 30 | 3.75216e+08 | 3.38026e+06 | 0.0995747 | 3(Loss) | true |
| simdjson (ondemand) | 442.392 | 0.11493 | 6760.85ms | 1834197 | 30 | 6.19533e+08 | 3.95402e+06 | 0.0136931 | 4(Loss) | true |
