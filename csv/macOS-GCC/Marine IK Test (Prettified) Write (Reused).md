
----
### Marine IK Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 6636.59 | 0.231708 | 9475.54ms | 10018896 | 320 | 3.56109e+09 | 1.43971e+06 | 1.21242 | 1(Win) | true |
| Glaze | 3065.15 | 0.532493 | 10196.8ms | 9930228 | 160 | 4.33074e+10 | 3.08964e+06 | 3.29059 | 2(Loss) | true |
| simdjson (reflection) | 326.186 | 0.0934611 | 9048.28ms | 10018896 | 30 | 2.2485e+10 | 2.92924e+07 | 1.65739 | 3(Loss) | true |
