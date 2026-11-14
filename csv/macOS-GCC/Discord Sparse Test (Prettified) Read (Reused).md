
----
### Discord Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2855.76 | 0.29536 | 3684.48ms | 83958 | 320 | 2.1945e+06 | 28037.6 | 0.0826776 | 1(Win) | true |
| simdjson (ondemand) | 2068.49 | 0.297629 | 4558.64ms | 83958 | 640 | 8.49473e+06 | 38708.8 | 2.0113 | 2(Loss) | true |
