
----
### Random Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1975.3 | 0.361425 | 8762.98ms | 676745 | 30 | 4.18352e+07 | 326733 | 0.201507 | 1(Win) | true |
| simdjson (ondemand) | 1430.31 | 0.152196 | 5852.35ms | 676745 | 80 | 3.77298e+07 | 451226 | 0.342069 | 2(Loss) | true |
