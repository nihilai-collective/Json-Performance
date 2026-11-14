
----
### Instruments Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2607.7 | 0.0602131 | 1013.35ms | 7932 | 2560 | 7810.4 | 2900.85 | 0.276536 | 2.00327 | 9.06732 | 1.38691 | 0.00063548 | 2.07821e-05 | 4.82618e-06 | 1(Win) | true |
| Jsonifier (generic) | 2525.22 | 0.0500993 | 1020.84ms | 7932 | 4890 | 11013.9 | 2995.6 | 0.0564838 | 2.07268 | 8.27005 | 1.57249 | 0.00141979 | 3.43152e-05 | 1.3329e-05 | 2(Loss) | true |
