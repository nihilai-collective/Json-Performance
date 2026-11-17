
----
### Canada Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4853.67 | 0.0804105 | 1025.53ms | 14795 | 4890 | 26719.3 | 2907 | 0.327315 | 1.05283 | 2.94829 | 0.270903 | 0.000280369 | 1.49556e-05 | 1.86599e-06 | 1(Win) | true |
| Glaze | 4028.09 | 0.0918233 | 1088.56ms | 14795 | 4890 | 50587.8 | 3502.8 | 0.0677759 | 1.26883 | 4.24475 | 0.486786 | 0.00097315 | 1.14171e-05 | 6.63464e-07 | 2(Loss) | true |
