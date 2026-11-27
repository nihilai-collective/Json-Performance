
----
### Random Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2773.84 | 0.0604073 | 7248.04ms | 409725 | 1280 | 9.26855e+06 | 140868 | 0.00860311 | 0.892285 | 1(Win) | true |
| simdjson (ondemand) | 2386.32 | 0.0928144 | 8501.19ms | 409725 | 320 | 7.3911e+06 | 163744 | 0.0423253 | 1.03725 | 2(Loss) | true |
