
----
### String Test Read (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1784.99 | 0.17321 | 264.642ms | 4215 | 30 | 456.447 | 2251.97 | 0.0755466 | 1.3698 | 1(Win) | true |
| Glaze | 1219.69 | 0.0639173 | 371.104ms | 4215 | 40 | 177.497 | 3295.7 | 0.752853 | 2.01276 | 2(Loss) | true |
| simdjson (reflection) | 1192.72 | 0.114279 | 383.267ms | 4215 | 30 | 445.013 | 3370.23 | 0.0247202 | 2.05901 | 3(Loss) | true |
| simdjson (ondemand) | 815.687 | 0.232818 | 530.474ms | 4215 | 1280 | 168497 | 4928.04 | 0.00456551 | 3.01871 | 4(Loss) | true |
