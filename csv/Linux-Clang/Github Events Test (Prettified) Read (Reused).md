
----
### Github Events Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2835.9 | 0.227263 | 3531.52ms | 65103 | 1280 | 3.16875e+06 | 21893.2 | 0.187445 | 1.79967 | 5.95525 | 1.11296 | 0.00661183 | 4.54088e-05 | 1.53603e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 2201.68 | 0.154915 | 4162.11ms | 65103 | 1280 | 2.44282e+06 | 28199.8 | 0.174374 | 2.29242 | 8.1162 | 1.26123 | 0.00977377 | 6.52212e-05 | 3.79687e-05 | 2(Loss) | true |
| Glaze | 1962.3 | 0.173713 | 4520.81ms | 65103 | 640 | 1.93339e+06 | 31640 | 0.293468 | 2.5824 | 9.06014 | 1.68007 | 0.0162462 | 3.27846e-05 | 1.55763e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1371.34 | 0.191598 | 5837.17ms | 65103 | 320 | 2.40793e+06 | 45274.8 | 0.0399319 | 3.70795 | 11.3507 | 1.90469 | 0.00887642 | 5.87051e-05 | 3.02405e-05 | 4(Loss) | true |
