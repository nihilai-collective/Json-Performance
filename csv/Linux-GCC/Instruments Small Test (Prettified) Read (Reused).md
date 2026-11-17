
----
### Instruments Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2611.33 | 0.0476317 | 1011.57ms | 7932 | 2560 | 4873.87 | 2896.82 | 0.34742 | 2.02059 | 9.06833 | 1.38591 | 0.000728753 | 1.5759e-05 | 4.72769e-06 | 1(Win) | true |
| Jsonifier (generic) | 2547.85 | 0.0456496 | 1016.88ms | 7932 | 2560 | 4702.55 | 2968.99 | 0.113409 | 2.05138 | 8.26929 | 1.57249 | 0.00110505 | 1.63007e-05 | 2.61008e-06 | 2(Loss) | true |
