
----
### Random Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2248.75 | 0.343476 | 7287.85ms | 676745 | 40 | 3.88706e+07 | 287002 | 0.334855 | 1(Win) | true |
| simdjson (ondemand) | 1659.26 | 0.253192 | 9959.88ms | 676745 | 320 | 3.10363e+08 | 388965 | 0.0735772 | 2(Loss) | true |
