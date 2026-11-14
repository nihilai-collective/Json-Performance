
----
### Discord Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2777.04 | 0.104828 | 191.939ms | 4857 | 160 | 489.156 | 1667.96 | 0.110043 | 1(Win) | true |
| Glaze | 1847.49 | 0.123809 | 266.687ms | 4857 | 2560 | 24667 | 2507.18 | 0.166424 | 2(Loss) | true |
| Jsonifier (two-stage) | 1708.1 | 0.0785572 | 329.864ms | 4857 | 80 | 363.056 | 2711.79 | 0.168531 | 3(Loss) | true |
| simdjson (ondemand) | 729.442 | 0.181389 | 655.46ms | 4857 | 40 | 5306.82 | 6350.05 | 0.325705 | 4(Loss) | true |
