
----
### Canada Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 6435.43 | 0.263047 | 9921.16ms | 5212421 | 40 | 1.65139e+08 | 772435 | 0.021848 | 1(Win) | true |
| simdjson (ondemand) | 5460.08 | 0.162659 | 5830.82ms | 5212421 | 160 | 3.50878e+08 | 910417 | 0.0417903 | 2(Loss) | true |
