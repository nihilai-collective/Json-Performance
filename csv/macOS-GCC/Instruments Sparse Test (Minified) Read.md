
----
### Instruments Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3183.41 | 0.245865 | 3333.27ms | 108313 | 40 | 254582 | 32448 | 0.144851 | 1(Win) | true |
| simdjson (ondemand) | 2718.07 | 0.053663 | 3940.73ms | 108313 | 40 | 16636.1 | 38003.2 | 0.0112284 | 2(Loss) | true |
