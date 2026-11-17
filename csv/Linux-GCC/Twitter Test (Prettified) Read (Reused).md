
----
### Twitter Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2732.13 | 0.0912829 | 6638.95ms | 631514 | 640 | 2.59132e+07 | 220435 | 0.19166 | 1.83471 | 6.07353 | 0.832336 | 0.00962768 | 0.0122253 | 0.000119262 | 1(Win) | true |
| simdjson (reflection) | 2414.35 | 0.105703 | 7308.36ms | 631514 | 1280 | 8.89919e+07 | 249449 | 0.134444 | 2.06916 | 7.11025 | 0.966537 | 0.0067528 | 0.020916 | 0.000130771 | 2(Loss) | true |
| Jsonifier | 2315.97 | 0.0544039 | 7510.11ms | 631514 | 640 | 1.28097e+07 | 260046 | 0.239088 | 2.18495 | 6.23778 | 1.09628 | 0.00793855 | 0.00538403 | 0.000234122 | 3(Loss) | true |
| Glaze | 2218.45 | 0.0982879 | 7810.33ms | 631514 | 640 | 4.55667e+07 | 271477 | 0.100195 | 2.26886 | 8.22899 | 1.47596 | 0.0062035 | 0.00227214 | 8.51847e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1763.3 | 0.112464 | 9671.33ms | 631514 | 320 | 4.72162e+07 | 341551 | 0.0229026 | 2.8594 | 9.11251 | 1.82909 | 0.00797345 | 0.0176792 | 0.00016555 | 5(Loss) | true |
