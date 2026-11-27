
----
### Random Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1637.73 | 0.170681 | 6388.54ms | 409725 | 320 | 5.30667e+07 | 238589 | 0.281793 | 1(Win) | true |
| simdjson (ondemand) | 1046.57 | 0.18175 | 9931.98ms | 409725 | 320 | 1.47349e+08 | 373357 | 0.0569974 | 2(Loss) | true |
