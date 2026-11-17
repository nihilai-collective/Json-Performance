
----
### Random Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1242.34 | 0.0387309 | 1351.87ms | 8150 | 2560 | 15031.2 | 6256.32 | 0.0092086 | 4.16961 | 17.4361 | 3.47657 | 0.00596832 | 3.42216e-05 | 9.63382e-06 | 1(Win) | true |
| simdjson (ondemand) | 814.369 | 0.0663734 | 1673.98ms | 8150 | 320 | 12841.4 | 9544.13 | 0.0411078 | 6.34753 | 27.7521 | 5.46871 | 0.0132431 | 7.05521e-05 | 4.29448e-05 | 2(Loss) | true |
