
----
### String Test Read (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1858.73 | 0.0851449 | 257.062ms | 4215 | 80 | 271.25 | 2162.62 | 0.0866251 | 1.31539 | 1(Win) | true |
| Glaze | 1255.42 | 0.0271314 | 364.353ms | 4215 | 320 | 241.498 | 3201.92 | 0.0240148 | 1.95539 | 2(Loss) | true |
| simdjson (ondemand) | 952.291 | 0.175307 | 472.787ms | 4215 | 40 | 2190.37 | 4221.12 | 0.12166 | 2.5841 | 3(Loss) | true |
