
----
### Marine IK Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 6246.29 | 0.0597518 | 9614.06ms | 9930848 | 160 | 1.31326e+08 | 1.51623e+06 | 0.00657387 | 0.80625 | 2.51578 | 0.147539 | 0.00033375 | 0.0250597 | 0.00019738 | 1(Win) | true |
| Glaze | 4088.26 | 0.244189 | 7264.11ms | 9930228 | 30 | 9.59879e+08 | 2.31644e+06 | 0.210595 | 1.23453 | 4.414 | 0.474254 | 0.000774766 | 0.0224352 | 0.000407483 | 2(Loss) | true |
| simdjson (reflection) | 342.338 | 1.50942 | 8423.93ms | 10018896 | 30 | 5.32444e+12 | 2.79104e+07 | 0.487766 | 12.8897 | 38.772 | 5.80014 | 0.0233653 | 0.289008 | 0.146556 | 3(Loss) | true |
