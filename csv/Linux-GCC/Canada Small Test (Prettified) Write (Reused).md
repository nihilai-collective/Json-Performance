
----
### Canada Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 5532.84 | 0.144047 | 990.26ms | 14795 | 160 | 2159.04 | 2550.16 | 0.145612 | 0.929581 | 2.47279 | 0.120514 | 8.49104e-05 | 7.18148e-06 | 0 | 1(Win) | true |
| Glaze | 3929.52 | 0.100939 | 1090.63ms | 14795 | 640 | 8407.19 | 3590.67 | 0.0250152 | 1.30036 | 4.33721 | 0.474621 | 0.000128527 | 1.0033e-05 | 1.90098e-06 | 2(Loss) | true |
| simdjson (reflection) | 412.441 | 0.143207 | 4169.22ms | 14795 | 640 | 1.53609e+06 | 34210 | 0.18842 | 12.2528 | 43.0994 | 6.05914 | 0.00970767 | 0.000192738 | 0.000114481 | 3(Loss) | true |
