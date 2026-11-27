
----
### Canada Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2226.21 | 0.0538055 | 1317.48ms | 11579 | 2560 | 18234.8 | 4960.26 | 0.0408727 | 2.30281 | 11.4869 | 1.90172 | 0.000999891 | 3.70755e-05 | 2.34463e-05 | 1(Win) | true |
| Jsonifier (generic) | 2077.24 | 0.0829119 | 1362.34ms | 11579 | 40 | 777.077 | 5316 | 0.0745619 | 2.49928 | 11.3795 | 2.13317 | 0.00217204 | 1.94317e-05 | 2.15908e-06 | 2(Loss) | true |
