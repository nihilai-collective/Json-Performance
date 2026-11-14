
----
### Marine IK Test (Prettified) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 22862.9 | 0.11686 | 7965.19ms | 7351818 | 320 | 4.10967e+07 | 306665 | 0.00336268 | 0.108281 | 1(Win) | true |
| simdjson (stage-1) | 20317.4 | 0.259332 | 8973.29ms | 7351818 | 160 | 1.2814e+08 | 345085 | 0.45972 | 0.121848 | 2(Loss) | true |
