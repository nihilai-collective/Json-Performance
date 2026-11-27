
----
### String Test Read (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2094.05 | 0.0953597 | 235.062ms | 4215 | 80 | 268.066 | 1919.6 | 0.270316 | 1.16605 | 1(Win) | true |
| Glaze | 1309.84 | 0.197013 | 355.631ms | 4215 | 4890 | 178756 | 3068.89 | 0.0645047 | 1.87431 | 2(Loss) | true |
| simdjson (ondemand) | 921.973 | 0.195371 | 470.019ms | 4215 | 2560 | 185746 | 4359.93 | 0.188431 | 2.66945 | 3(Loss) | true |
