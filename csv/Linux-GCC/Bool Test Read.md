
----
### Bool Test Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 987.605 | 0.177482 | 795.107ms | 905 | 1280 | 3079.27 | 873.907 | 0.0699492 | 5.54591 | 28.4133 | 2.51271 | 0.00474448 | 0.000155387 | 3.36671e-05 | 1(Win) | true |
| simdjson (stage-1) | 345.843 | 0.0315887 | 957.4ms | 905 | 4890 | 3038.88 | 2495.57 | 0.0549592 | 15.1308 | 76.4975 | 5.79563 | 0.00227864 | 0.000138065 | 1.51397e-05 | 2(Loss) | true |
