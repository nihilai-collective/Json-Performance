
----
### Marine IK Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 6132.31 | 0.21212 | 7672.59ms | 7351818 | 40 | 2.35268e+08 | 1.14333e+06 | 0.415666 | 1(Win) | true |
| simdjson (ondemand) | 5185.19 | 0.186096 | 8122.72ms | 7351818 | 30 | 1.89957e+08 | 1.35217e+06 | 0.390902 | 2(Loss) | true |
