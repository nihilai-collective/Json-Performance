
----
### Twitter Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2837.08 | 0.0637906 | 7336.37ms | 360584 | 1280 | 7.65232e+06 | 121209 | 0.0370211 | 1.7879 | 6.99195 | 1.17014 | 0.0054779 | 4.4574e-05 | 5.2129e-06 | 1(Win) | true |
| simdjson (ondemand) | 2526 | 0.0732564 | 8116.85ms | 360584 | 1280 | 1.27306e+07 | 136136 | 0.0948065 | 1.99288 | 7.22621 | 1.12869 | 0.00830203 | 7.25819e-05 | 1.12881e-05 | 2(Loss) | true |
