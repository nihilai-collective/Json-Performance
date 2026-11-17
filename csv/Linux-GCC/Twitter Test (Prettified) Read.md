
----
### Twitter Test (Prettified) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14744.1 | 0.0225598 | 4804.36ms | 631514 | 4890 | 415251 | 40847.5 | 0.050461 | 0.342132 | 1.6894 | 0.0621333 | 8.56351e-06 | 1.09906e-06 | 6.80677e-07 | 1(Win) | true |
| simdjson (stage-1) | 14612.3 | 0.0152691 | 4850.06ms | 631514 | 4890 | 193670 | 41215.7 | 0.00553006 | 0.350376 | 1.77513 | 0.0659353 | 3.52932e-05 | 6.42789e-07 | 1.49283e-07 | 2(Loss) | true |
