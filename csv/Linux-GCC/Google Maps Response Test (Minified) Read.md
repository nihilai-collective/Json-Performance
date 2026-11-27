
----
### Google Maps Response Test (Minified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1468.35 | 0.0716173 | 1505.03ms | 11812 | 320 | 9659.92 | 7671.74 | 0.195385 | 3.52466 | 16.866 | 3.2144 | 0.00455152 | 1.34926e-05 | 2.64561e-06 | 1(Win) | true |
| simdjson (ondemand) | 1089.27 | 0.0877506 | 1766.56ms | 11812 | 80 | 6588.23 | 10341.6 | 0.578385 | 4.66901 | 19.215 | 3.59736 | 0.0095422 | 2.85726e-05 | 1.37572e-05 | 2(Loss) | true |
