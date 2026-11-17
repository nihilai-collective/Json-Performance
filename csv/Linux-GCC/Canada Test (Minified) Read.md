
----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 802.146 | 0.162454 | 7756.44ms | 2090234 | 40 | 6.51936e+08 | 2.48509e+06 | 0.11019 | 6.32798 | 30.3516 | 5.61815 | 0.0232553 | 0.105551 | 0.00100216 | 1(Win) | true |
| Jsonifier (generic) | 762.829 | 0.443205 | 8117.71ms | 2090234 | 160 | 2.14618e+10 | 2.61317e+06 | 0.0593681 | 6.65966 | 30.981 | 6.39269 | 0.0224095 | 0.103286 | 0.000866895 | 2(Loss) | true |
