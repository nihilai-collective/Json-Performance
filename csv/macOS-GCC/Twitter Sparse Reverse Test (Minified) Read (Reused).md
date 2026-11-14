
----
### Twitter Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3127 | 0.172787 | 8073.44ms | 264040 | 2560 | 4.95618e+07 | 80527.1 | 1.42463 | 1(Win) | true |
| simdjson (ondemand) | 2653.16 | 0.213905 | 5018.09ms | 264040 | 160 | 6.5944e+06 | 94908.8 | 0.0707547 | 2(Loss) | true |
