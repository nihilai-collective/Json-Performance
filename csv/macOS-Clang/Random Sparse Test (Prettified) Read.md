
----
### Random Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2591.82 | 0.0968923 | 6404.57ms | 676745 | 1280 | 7.45127e+07 | 249012 | 0.153628 | 1(Win) | true |
| simdjson (ondemand) | 2022.44 | 0.219078 | 8200.33ms | 676745 | 40 | 1.95505e+07 | 319117 | 0.118703 | 2(Loss) | true |
