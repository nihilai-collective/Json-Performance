
----
### Twitter Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 16794 | 0.0437825 | 4360.09ms | 631514 | 160 | 39443.9 | 35861.6 | 0.0373345 | 0.30692 | 1.63181 | 0.0839744 | 1.75273e-05 | 6.45275e-06 | 5.70059e-06 | 1(Win) | true |
| simdjson (stage-1) | 15465.5 | 0.07044 | 4605.95ms | 631514 | 80 | 60195.7 | 38942 | 0.0237476 | 0.333135 | 1.78296 | 0.0659448 | 0.000154252 | 6.19543e-06 | 4.92863e-06 | 2(Loss) | true |
