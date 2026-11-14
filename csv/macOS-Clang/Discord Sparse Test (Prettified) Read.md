
----
### Discord Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2771.61 | 0.0662523 | 2957.46ms | 83958 | 2560 | 937782 | 28888.9 | 0.0206893 | 1(Win) | true |
| simdjson (ondemand) | 2457.96 | 0.132486 | 3500.17ms | 83958 | 640 | 1.19205e+06 | 32575.2 | 0.0417478 | 2(Loss) | true |
