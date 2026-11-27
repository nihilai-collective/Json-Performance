
----
### Random Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 22110.3 | 0.143504 | 3646.61ms | 837491 | 2560 | 6.87921e+06 | 36123.1 | 0.0553795 | 0.111841 | 1(Win) | true |
| Glaze | 4021.39 | 0.182926 | 5043.48ms | 837491 | 320 | 4.22384e+07 | 198611 | 0.623342 | 0.61557 | 2(Loss) | true |
| simdjson (reflection) | 544.648 | 0.251157 | 9249.27ms | 837491 | 40 | 5.42601e+08 | 1.46644e+06 | 0.548052 | 4.54544 | 3(Loss) | true |
