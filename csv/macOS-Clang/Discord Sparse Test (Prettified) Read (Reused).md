
----
### Discord Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3075.1 | 0.0935797 | 2664.46ms | 83958 | 4890 | 2.90321e+06 | 26037.7 | 0.0921621 | 1(Win) | true |
| simdjson (ondemand) | 2650.33 | 0.0877656 | 3091.74ms | 83958 | 2560 | 1.79976e+06 | 30210.8 | 0.187858 | 2(Loss) | true |
