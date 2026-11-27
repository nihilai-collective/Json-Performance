
----
### Instruments Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2528.5 | 0.0382337 | 1020.83ms | 7932 | 4890 | 6397.94 | 2991.71 | 0.021906 | 2.06739 | 9.61624 | 1.34065 | 0.00113011 | 2.53948e-05 | 9.02353e-06 | 1(Win) | true |
| Jsonifier (generic) | 2445.57 | 0.0971431 | 1032.65ms | 7932 | 640 | 5778.41 | 3093.16 | 0.124927 | 2.13479 | 8.84329 | 1.58233 | 0.00105762 | 2.87601e-05 | 8.47044e-06 | 2(Loss) | true |
