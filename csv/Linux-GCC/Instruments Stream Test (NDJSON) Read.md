
----
### Instruments Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1738.35 | 0.126179 | 7449.59ms | 4197496 | 40 | 3.37709e+08 | 2.30278e+06 | 0.0254023 | 2.92316 | 14.6094 | 2.8874 | 0.000515945 | 0.080757 | 0.000988262 | 1(Win) | true |
| simdjson (ondemand) | 1465.54 | 0.0775658 | 8817.92ms | 4197496 | 80 | 3.59102e+08 | 2.73145e+06 | 0.718669 | 3.47119 | 16.5291 | 2.70204 | 0.00539609 | 0.0813066 | 0.000523369 | 2(Loss) | true |
