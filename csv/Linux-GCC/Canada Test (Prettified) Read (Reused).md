
----
### Canada Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2173.58 | 0.172521 | 8304.2ms | 5212421 | 30 | 4.67018e+08 | 2.28699e+06 | 0.00193125 | 2.33939 | 10.857 | 1.78264 | 0.0100166 | 0.0507182 | 0.000333127 | 1(Win) | true |
| Jsonifier (generic) | 1990.14 | 0.0786359 | 8959.39ms | 5212421 | 80 | 3.08633e+08 | 2.49779e+06 | 0.589722 | 2.54711 | 11.2235 | 2.09727 | 0.00984016 | 0.0507796 | 0.000827588 | 2(Loss) | true |
