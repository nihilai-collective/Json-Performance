
----
### Random Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1492.16 | 0.268413 | 7328.92ms | 409725 | 320 | 1.58093e+08 | 261865 | 0.733348 | 1(Win) | true |
| simdjson (ondemand) | 984.758 | 0.197622 | 5404.32ms | 409725 | 160 | 9.83827e+07 | 396792 | 0.82655 | 2(Loss) | true |
