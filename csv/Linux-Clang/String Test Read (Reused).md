
----
### String Test Read (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2015.28 | 0.154487 | 238.994ms | 4215 | 30 | 284.861 | 1994.63 | 0.247944 | 1.21249 | 1(Win) | true |
| Glaze | 1322.53 | 0.0488448 | 347.761ms | 4215 | 80 | 176.323 | 3039.43 | 0.185546 | 1.85628 | 2(Loss) | true |
| simdjson (ondemand) | 982.693 | 0.17836 | 442.375ms | 4215 | 2560 | 136268 | 4090.53 | 0.0813036 | 2.50358 | 3(Loss) | true |
