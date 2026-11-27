
----
### Bool Test Read Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 880.835 | 0.0622184 | 102.789ms | 905 | 80 | 29.7328 | 979.837 | 0.00893085 | 2.73776 | 1(Win) | true |
| simdjson (ondemand) | 515.412 | 0.0725335 | 169.44ms | 905 | 30 | 44.2575 | 1674.53 | 0.0795608 | 4.73145 | 2(Loss) | true |
