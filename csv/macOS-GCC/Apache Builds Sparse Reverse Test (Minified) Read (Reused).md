
----
### Apache Builds Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1783.62 | 0.216631 | 6201.63ms | 94653 | 160 | 1.92321e+06 | 50609.6 | 0.205918 | 1(Win) | true |
| simdjson (ondemand) | 1017.82 | 0.224999 | 9623.81ms | 94653 | 2560 | 1.01936e+08 | 88687.6 | 1.19738 | 2(Loss) | true |
