
----
### Twitter Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3826 | 0.0507966 | 9064.27ms | 360584 | 4890 | 1.0193e+07 | 89879.8 | 0.000600034 | 1(Win) | true |
| simdjson (ondemand) | 2993.44 | 0.134563 | 5933.82ms | 360584 | 640 | 1.52934e+07 | 114878 | 0.0180798 | 2(Loss) | true |
