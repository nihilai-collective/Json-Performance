
----
### Canada Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1113.22 | 0.125886 | 7183.43ms | 2251027 | 40 | 2.35729e+08 | 1.9284e+06 | 0.423725 | 4.53127 | 23.26 | 4.83302 | 0.0140062 | 0.0417914 | 0.000425961 | 1(Win) | true |
| Glaze | 1060.62 | 0.081017 | 7567.76ms | 2251027 | 160 | 4.30242e+08 | 2.02404e+06 | 0.0413048 | 4.71311 | 25.3565 | 4.46548 | 0.00895958 | 0.0395393 | 0.000524244 | 2(Loss) | true |
| simdjson (reflection) | 971.19 | 0.265617 | 8053.31ms | 2251027 | 30 | 1.03416e+09 | 2.21043e+06 | 0.0172802 | 5.19941 | 24.8459 | 4.27487 | 0.00910651 | 0.0773331 | 0.000489095 | 3(Loss) | true |
| simdjson (ondemand) | 928.465 | 0.0950884 | 8416.27ms | 2251027 | 30 | 1.45013e+08 | 2.31215e+06 | 0.056703 | 5.43239 | 25.8225 | 4.70766 | 0.011062 | 0.0759638 | 0.000486948 | 4(Loss) | true |
| Jsonifier (two-stage) | 921.407 | 0.165856 | 8436.1ms | 2251027 | 40 | 5.97282e+08 | 2.32986e+06 | 0.0558492 | 5.39821 | 26.6275 | 5.15798 | 0.0225172 | 0.0787801 | 0.000186482 | 5(Loss) | true |
