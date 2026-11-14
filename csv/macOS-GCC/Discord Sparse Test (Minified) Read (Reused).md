
----
### Discord Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2282.92 | 0.0923004 | 2989.3ms | 56369 | 2560 | 1.20934e+06 | 23547.8 | 0.054328 | 1(Win) | true |
| simdjson (ondemand) | 1560.26 | 0.571348 | 4129.45ms | 56369 | 160 | 6.20027e+06 | 34454.4 | 0.0649712 | 2(Loss) | true |
