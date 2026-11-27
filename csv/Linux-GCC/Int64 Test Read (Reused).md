
----
### Int64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1903.4 | 0.103562 | 68.7946ms | 1313 | 80 | 37.1328 | 657.862 | 0.249533 | 1.24891 | 1(Win) | true |
| simdjson (reflection) | 1039.29 | 0.0817575 | 124.124ms | 1313 | 30 | 29.1092 | 1204.83 | 0.0165971 | 2.32734 | 2(Loss) | true |
| Glaze | 952.305 | 0.0859601 | 137.825ms | 1313 | 80 | 102.202 | 1314.89 | 0.260203 | 2.54666 | 3(Loss) | true |
| simdjson (ondemand) | 342.241 | 0.0267786 | 373.469ms | 1313 | 40 | 38.3974 | 3658.75 | 0.0068334 | 7.18355 | 4(Loss) | true |
