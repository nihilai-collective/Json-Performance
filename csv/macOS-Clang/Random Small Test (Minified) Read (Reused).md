
----
### Random Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1236.73 | 0.0883215 | 438.162ms | 4926 | 4890 | 55040.1 | 3798.56 | 0.0454915 | 1(Win) | true |
| simdjson (ondemand) | 810.275 | 0.265499 | 601.77ms | 4926 | 2560 | 606583 | 5797.78 | 1.60623 | 2(Loss) | true |
