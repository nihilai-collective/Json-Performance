
----
### Twitter Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 2228.48 | 0.0638483 | 142.795ms | 2889 | 640 | 398.801 | 1236.34 | 0.0539938 | 1(Win) | true |
| Jsonifier | 2189.51 | 0.80613 | 115.826ms | 2889 | 40 | 4115.98 | 1258.35 | 0.107168 | 2(Loss) | true |
| Glaze | 1915.34 | 0.229511 | 161.705ms | 2889 | 4890 | 53299.1 | 1438.48 | 0.380656 | 3(Loss) | true |
| simdjson (ondemand) | 908.306 | 0.166467 | 351.011ms | 2889 | 30 | 764.907 | 3033.3 | 0.0010989 | 4(Loss) | true |
