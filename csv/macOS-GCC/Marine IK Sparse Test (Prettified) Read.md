
----
### Marine IK Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 5807.02 | 0.583201 | 8310.8ms | 7351818 | 40 | 1.98326e+09 | 1.20737e+06 | 0.92588 | 1(Win) | true |
| simdjson (ondemand) | 5158.7 | 0.506065 | 9014.3ms | 7351818 | 80 | 3.78453e+09 | 1.35911e+06 | 0.000941801 | 2(Loss) | true |
