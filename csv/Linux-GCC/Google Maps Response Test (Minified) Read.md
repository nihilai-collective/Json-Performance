
----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1394.49 | 0.10317 | 1534.16ms | 11812 | 80 | 5556.65 | 8078.07 | 0.115612 | 3.70613 | 17.673 | 3.32509 | 0.00474623 | 7.51355e-05 | 6.24365e-05 | 1(Win) | true |
| simdjson (ondemand) | 1084.45 | 0.0314161 | 1766.39ms | 11812 | 1280 | 13631.5 | 10387.6 | 0.00954322 | 4.7657 | 19.5475 | 3.64241 | 0.00630662 | 3.07553e-05 | 1.17068e-05 | 2(Loss) | true |
