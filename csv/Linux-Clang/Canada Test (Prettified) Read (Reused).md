
----
### Canada Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2090.56 | 0.156474 | 8615.34ms | 5212421 | 30 | 4.15297e+08 | 2.37781e+06 | 0.0405671 | 2.42975 | 11.5101 | 2.08515 | 0.00982394 | 0.0505505 | 0.000571187 | 1(Win) | true |
| simdjson (ondemand) | 2049.33 | 0.0955179 | 8739.32ms | 5212421 | 160 | 8.58901e+08 | 2.42564e+06 | 0.191661 | 2.46616 | 11.3279 | 1.78361 | 0.0100336 | 0.0516215 | 0.00119774 | 2(Loss) | true |
