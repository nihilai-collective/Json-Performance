
----
### Instruments Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2694.79 | 0.0279058 | 7397.15ms | 183677 | 2560 | 842345 | 65002.5 | 0.0245784 | 1.88224 | 8.07297 | 1.5183 | 0.00190185 | 1.57588e-05 | 1.20647e-05 | 1(Win) | true |
| simdjson (ondemand) | 2584.2 | 0.0603117 | 7698.5ms | 183677 | 1280 | 2.1393e+06 | 67784.3 | 0.165544 | 1.96526 | 9.11225 | 1.37512 | 0.00377757 | 1.16713e-05 | 7.03936e-06 | 2(Loss) | true |
