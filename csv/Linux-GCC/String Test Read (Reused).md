
----
### String Test Read (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1938.92 | 0.179124 | 245.386ms | 4215 | 4890 | 67436.2 | 2073.19 | 0.0305478 | 1.2605 | 1(Win) | true |
| Glaze STATISTICAL TIE | 1299.28 | 0.191451 | 350.346ms | 4215 | 4890 | 171559 | 3093.82 | 0.0253854 | 1.88953 | 2(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 1296.36 | 0.0448943 | 345.322ms | 4215 | 80 | 155.03 | 3100.79 | 0.239284 | 1.8946 | 2(Tie) | true |
| simdjson (ondemand) | 864.274 | 0.149996 | 500.526ms | 4215 | 30 | 1460.07 | 4651 | 0.137076 | 2.84834 | 4(Loss) | true |
