
----
### Marine IK Reverse Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4952.46 | 0.204027 | 6064.34ms | 10018896 | 80 | 1.23955e+09 | 1.9293e+06 | 0.672252 | 0.499901 | 1(Win) | true |
| Glaze | 2729.1 | 0.180969 | 5338.1ms | 9930228 | 80 | 3.15484e+09 | 3.47008e+06 | 0.162735 | 0.907177 | 2(Loss) | true |
