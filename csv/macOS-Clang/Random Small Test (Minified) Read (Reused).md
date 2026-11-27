
----
### Random Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1236.81 | 0.0471863 | 419.222ms | 4926 | 320 | 1027.93 | 3798.31 | 0.16116 | 1(Win) | true |
| simdjson (ondemand) | 920.86 | 0.0738163 | 547.328ms | 4926 | 80 | 1134.48 | 5101.54 | 0.0296391 | 2(Loss) | true |
