
----
### Random Small Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2483.07 | 0.104151 | 317.389ms | 8150 | 80 | 850.273 | 3130.18 | 0.0999344 | 1(Win) | true |
| simdjson (ondemand) | 2115.66 | 0.0683846 | 374.758ms | 8150 | 160 | 1009.86 | 3673.76 | 0.0514043 | 2(Loss) | true |
