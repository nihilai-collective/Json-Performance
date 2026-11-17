
----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1862.79 | 0.115777 | 8593.53ms | 5373214 | 160 | 1.62295e+09 | 2.75087e+06 | 0.0421285 | 2.68279 | 14.3202 | 2.70056 | 0.00458096 | 0.0624249 | 0.00113462 | 1(Win) | true |
| simdjson (ondemand) | 1801.49 | 0.0768182 | 8917.35ms | 5373214 | 160 | 7.63931e+08 | 2.84448e+06 | 0.118888 | 2.80219 | 13.7965 | 2.30358 | 0.00641135 | 0.0650309 | 0.000882912 | 2(Loss) | true |
| Jsonifier | 1771.07 | 0.0908244 | 9061.62ms | 5373214 | 160 | 1.1049e+09 | 2.89334e+06 | 0.523043 | 2.85062 | 15.2522 | 3.24726 | 0.00320161 | 0.0381593 | 0.00151652 | 3(Loss) | true |
| Glaze | 1615.01 | 0.072694 | 9898.85ms | 5373214 | 160 | 8.51204e+08 | 3.17292e+06 | 0.0304174 | 3.11997 | 16.0017 | 2.99619 | 0.00493304 | 0.0406137 | 0.00688521 | 4(Loss) | true |
