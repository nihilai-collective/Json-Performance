
----
### Instruments Test (Prettified) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 13100.2 | 0.0267463 | 2065.75ms | 183677 | 2560 | 32743.2 | 13371.4 | 0.0189368 | 0.391869 | 2.07013 | 0.181601 | 1.26709e-05 | 9.08099e-07 | 2.2543e-07 | 1(Win) | true |
| simdjson (stage-1) | 12694.1 | 0.136848 | 2098.79ms | 183677 | 160 | 57056.7 | 13799.2 | 0.0152159 | 0.401933 | 2.12612 | 0.082313 | 3.40612e-05 | 2.07565e-06 | 7.48597e-07 | 2(Loss) | true |
