
----
### Canada Small Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 6857.08 | 0.0719753 | 165.979ms | 11579 | 320 | 429.913 | 1610.39 | 0.031058 | 1(Win) | true |
| simdjson (ondemand) | 6701.98 | 0.0757517 | 171.748ms | 11579 | 320 | 498.506 | 1647.66 | 0.032253 | 2(Loss) | true |
