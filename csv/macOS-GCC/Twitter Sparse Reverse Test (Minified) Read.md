
----
### Twitter Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2975.79 | 0.112913 | 8893.46ms | 264040 | 4890 | 4.46409e+07 | 84618.9 | 0.945503 | 1(Win) | true |
| simdjson (ondemand) | 2591.15 | 0.0943312 | 5082.42ms | 264040 | 640 | 5.37829e+06 | 97180 | 0.0575918 | 2(Loss) | true |
