
----
### Random Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1716.11 | 0.184292 | 7066.02ms | 409725 | 80 | 1.40863e+07 | 227691 | 0.0143856 | 2.94313 | 15.1515 | 2.85795 | 0.00613591 | 0.0108359 | 2.37964e-06 | 1(Win) | true |
| simdjson (ondemand) | 1171.42 | 0.113114 | 9877.59ms | 409725 | 160 | 2.27778e+07 | 333565 | 0.0761808 | 4.35575 | 17.0956 | 3.14278 | 0.0126493 | 0.0215549 | 1.33169e-05 | 2(Loss) | true |
