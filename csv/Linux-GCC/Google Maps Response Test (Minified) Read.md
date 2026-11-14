
----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2494.38 | 0.0712099 | 1181.49ms | 11812 | 1280 | 13237.8 | 4516.08 | 0.0608737 | 2.05387 | 10.1043 | 1.61179 | 0.00251545 | 2.74483e-05 | 8.06912e-06 | 1(Win) | true |
| Glaze | 1915.76 | 0.0641108 | 1319.73ms | 11812 | 1280 | 18190.2 | 5880.08 | 0.0420869 | 2.66604 | 13.1048 | 2.62318 | 0.0015412 | 4.09409e-05 | 1.508e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1807.81 | 0.0661231 | 1365.98ms | 11812 | 1280 | 21729.9 | 6231.19 | 0.0237158 | 2.81275 | 13.5533 | 2.14396 | 0.00647646 | 3.4856e-05 | 1.7924e-05 | 3(Loss) | true |
| simdjson (reflection) | 1501.82 | 0.0494262 | 1488.16ms | 11812 | 160 | 2199.11 | 7500.77 | 0.0658699 | 3.38538 | 13.4896 | 2.16128 | 0.00432293 | 1.64028e-05 | 4.23298e-06 | 4(Loss) | true |
| simdjson (ondemand) | 1114.57 | 0.0463406 | 1756.26ms | 11812 | 2560 | 56156.2 | 10106.9 | 0.0727085 | 4.56556 | 17.7466 | 3.1963 | 0.00840694 | 7.69543e-05 | 4.34873e-05 | 5(Loss) | true |
