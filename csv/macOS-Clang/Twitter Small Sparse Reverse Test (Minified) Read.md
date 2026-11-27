
----
### Twitter Small Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3069.67 | 0.0821212 | 91.0351ms | 2821 | 320 | 165.761 | 876.419 | 0.0769587 | 1(Win) | true |
| simdjson (ondemand) | 2396.94 | 0.0618438 | 116.62ms | 2821 | 640 | 308.365 | 1122.4 | 0.0229646 | 2(Loss) | true |
