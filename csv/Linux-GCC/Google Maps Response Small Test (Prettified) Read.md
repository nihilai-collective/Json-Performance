
----
### Google Maps Response Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2720.38 | 0.139884 | 1048.51ms | 9378 | 160 | 3383.9 | 3287.62 | 0.0271927 | 1.91661 | 8.79399 | 1.55118 | 0.00042853 | 5.66485e-05 | 3.06569e-05 | 1(Win) | true |
| simdjson (ondemand) | 2239.01 | 0.0934476 | 1125.99ms | 9378 | 320 | 4458.57 | 3994.43 | 0.0236322 | 2.32218 | 9.66347 | 1.68927 | 0.00171912 | 1.033e-05 | 2.33259e-06 | 2(Loss) | true |
