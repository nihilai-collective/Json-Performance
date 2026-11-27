
----
### Discord Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2858.28 | 0.126213 | 2832.54ms | 83958 | 640 | 800016 | 28012.8 | 0.0605828 | 1(Win) | true |
| simdjson (ondemand) | 2486.83 | 0.0403814 | 3348.25ms | 83958 | 40 | 6761.69 | 32197 | 0.085329 | 2(Loss) | true |
