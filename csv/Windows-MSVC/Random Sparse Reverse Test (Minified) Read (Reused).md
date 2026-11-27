
----
### Random Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1382.3 | 0.18717 | 7864.05ms | 409725 | 1280 | 3.58313e+08 | 282676 | 0.267138 | 2.19858 | 1(Win) | true |
| simdjson (ondemand) | 1101.22 | 0.207186 | 9802.18ms | 409725 | 320 | 1.72944e+08 | 354828 | 0.121332 | 2.75983 | 2(Loss) | true |
