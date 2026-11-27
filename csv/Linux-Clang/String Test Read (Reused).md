
----
### String Test Read (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 959.902 | 0.305309 | 457.188ms | 4215 | 1280 | 209234 | 4187.65 | 0.00830262 | 2.56325 | 1(Win) | true |
| Jsonifier (generic) | 804.715 | 0.0602616 | 594.028ms | 4215 | 30 | 271.84 | 4995.23 | 0.00800699 | 3.06135 | 2(Loss) | true |
