
----
### Marine IK Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 5923.95 | 0.155274 | 7532.28ms | 7351818 | 160 | 5.40362e+08 | 1.18354e+06 | 0.0183033 | 1(Win) | true |
| simdjson (ondemand) | 5433.26 | 0.336974 | 8274.21ms | 7351818 | 30 | 5.6726e+08 | 1.29043e+06 | 0.084881 | 2(Loss) | true |
