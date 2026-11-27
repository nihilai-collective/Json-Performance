
----
### Random Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2667.66 | 0.343971 | 7007.5ms | 676745 | 80 | 5.54018e+07 | 241933 | 0.0951424 | 1(Win) | true |
| simdjson (ondemand) | 1840.22 | 0.165013 | 9854.95ms | 676745 | 80 | 2.67943e+07 | 350717 | 0.00456229 | 2(Loss) | true |
