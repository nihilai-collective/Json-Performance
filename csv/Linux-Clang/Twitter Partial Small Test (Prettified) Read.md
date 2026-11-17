
----
### Twitter Partial Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 6543.26 | 0.136853 | 787.245ms | 3808 | 640 | 369.23 | 555.013 | 0.123156 | 0.832453 | 3.18724 | 0.345326 | 0.000779198 | 2.01057e-05 | 1.23096e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 6333.02 | 0.199094 | 787.649ms | 3808 | 80 | 104.275 | 573.438 | 0.317079 | 0.854605 | 3.28624 | 0.405987 | 0.000265888 | 3.93908e-05 | 3.28256e-06 | 2(Loss) | true |
| Jsonifier | 6228.08 | 0.183543 | 789.366ms | 3808 | 4890 | 5601.06 | 583.1 | 0.152039 | 0.869687 | 3.28624 | 0.405987 | 0.000267814 | 2.57235e-05 | 5.79987e-06 | 3(Loss) | true |
| Glaze | 3378.06 | 0.15476 | 841.304ms | 3808 | 640 | 1771.55 | 1075.05 | 0.0353306 | 1.55388 | 6.48057 | 1.20746 | 0.000267939 | 9.43737e-06 | 0 | 4(Loss) | true |
