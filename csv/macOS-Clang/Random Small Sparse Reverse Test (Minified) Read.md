
----
### Random Small Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1437.58 | 0.344488 | 330.716ms | 4926 | 640 | 81106.2 | 3267.85 | 0.491641 | 1(Win) | true |
| simdjson (ondemand) | 1000.77 | 0.0333498 | 478.381ms | 4926 | 640 | 1568.51 | 4694.2 | 0.0121811 | 2(Loss) | true |
