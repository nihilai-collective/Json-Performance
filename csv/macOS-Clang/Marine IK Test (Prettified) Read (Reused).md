
----
### Marine IK Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1639.74 | 0.162202 | 6915.82ms | 7351818 | 80 | 3.84807e+09 | 4.27582e+06 | 0.136674 | 1(Win) | true |
| simdjson (ondemand) | 1563.11 | 0.361227 | 7266.18ms | 7351818 | 40 | 1.05009e+10 | 4.48543e+06 | 0.0767696 | 2(Loss) | true |
