
----
### Marine IK Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 7639 | 0.39258 | 6181.79ms | 1834197 | 40 | 3.23247e+07 | 228986 | 0.406246 | 0.669309 | 2.9649 | 0.213713 | 0.00590114 | 0.0377107 | 2.16716e-06 | 1(Win) | true |
| simdjson (stage-1) | 7382.61 | 0.0628084 | 6285.15ms | 1834197 | 640 | 1.41738e+07 | 236939 | 0.0412805 | 0.69607 | 3.30201 | 0.160353 | 0.00399388 | 0.0376738 | 2.50535e-06 | 2(Loss) | true |
