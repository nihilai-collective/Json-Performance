
----
### Github Events Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16462.4 | 0.114285 | 1195.42ms | 78778 | 640 | 17409.3 | 4563.63 | 0.0224551 | 0.309045 | 0.85223 | 0.122877 | 2.66374e-05 | 6.58496e-06 | 2.2611e-06 | 1(Win) | true |
| Glaze | 4856.6 | 0.116311 | 2284.21ms | 78778 | 2560 | 828752 | 15469.4 | 0.367408 | 1.05137 | 2.87243 | 0.44906 | 7.89402e-05 | 1.79748e-05 | 8.01798e-06 | 2(Loss) | true |
| simdjson (reflection) | 641.178 | 0.156274 | 6358.24ms | 78778 | 1280 | 4.2918e+07 | 117173 | 0.44197 | 7.88962 | 29.3666 | 6.6069 | 0.0369063 | 0.00956688 | 0.000209142 | 3(Loss) | true |
