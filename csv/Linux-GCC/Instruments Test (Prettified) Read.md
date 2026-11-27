
----
### Instruments Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 13687.3 | 0.0866474 | 1991.86ms | 183677 | 320 | 39349 | 12797.8 | 0.15725 | 0.374135 | 1.98065 | 0.113117 | 2.21346e-05 | 9.35746e-07 | 2.21176e-07 | 1(Win) | true |
| simdjson (stage-1) | 12937.8 | 0.0408806 | 2104.94ms | 183677 | 4890 | 149808 | 13539.3 | 0.035498 | 0.398744 | 2.13402 | 0.0823457 | 3.08657e-05 | 2.15658e-06 | 1.11114e-06 | 2(Loss) | true |
