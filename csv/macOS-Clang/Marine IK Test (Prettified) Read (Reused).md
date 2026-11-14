
----
### Marine IK Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1608.34 | 0.414462 | 7104.92ms | 7351818 | 40 | 1.30575e+10 | 4.35929e+06 | 2.61022 | 1(Win) | true |
| simdjson (ondemand) | 1550.13 | 0.100053 | 7387.4ms | 7351818 | 30 | 6.14378e+08 | 4.52301e+06 | 0.271875 | 2(Loss) | true |
