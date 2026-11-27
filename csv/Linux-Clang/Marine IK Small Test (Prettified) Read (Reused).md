
----
### Marine IK Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2966.83 | 0.0606374 | 1421.21ms | 18245 | 4890 | 61843.3 | 5864.78 | 0.565309 | 1.7269 | 7.27646 | 1.35045 | 0.0014515 | 1.28786e-05 | 3.84451e-06 | 1(Win) | true |
| Jsonifier | 2593.72 | 0.0846466 | 1500.25ms | 18245 | 4890 | 157677 | 6708.43 | 0.736368 | 1.97561 | 7.79003 | 1.77704 | 0.00200568 | 2.05115e-05 | 9.87468e-06 | 2(Loss) | true |
| Glaze | 2130.37 | 0.0512807 | 1639.32ms | 18245 | 4890 | 85781.6 | 8167.5 | 0.137003 | 2.40398 | 10.4569 | 2.0786 | 0.0032198 | 2.0534e-05 | 8.54087e-06 | 3(Loss) | true |
| simdjson (ondemand) | 2025.17 | 0.0514707 | 1698.97ms | 18245 | 4890 | 95629.9 | 8591.76 | 0.114761 | 2.52141 | 10.4149 | 1.69075 | 0.00169802 | 1.88191e-05 | 7.07256e-06 | 4(Loss) | true |
