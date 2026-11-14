
----
### Instruments Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 870.263 | 0.021165 | 1594.74ms | 7932 | 4890 | 16550.4 | 8692.25 | 0.0402075 | 5.93239 | 23.9007 | 4.77156 | 0.00637195 | 2.4776e-05 | 3.22269e-06 | 1(Win) | true |
| simdjson (ondemand) | 428.092 | 0.0207309 | 2492.72ms | 7932 | 4890 | 65620.1 | 17670.4 | 0.072652 | 12.0488 | 55.2282 | 11.1699 | 0.030397 | 2.15791e-05 | 2.99066e-06 | 2(Loss) | true |
