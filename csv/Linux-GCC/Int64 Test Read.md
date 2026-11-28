
----
### Int64 Test Read Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1699.48 | 0.126417 | 77.3339ms | 1313 | 30 | 26.0276 | 736.8 | 0.135538 | 1.40454 | 1(Win) | true |
| simdjson (reflection) | 985.473 | 0.112096 | 132.312ms | 1313 | 30 | 60.8609 | 1270.63 | 0.201592 | 2.45669 | 2(Loss) | true |
| Glaze | 901.83 | 0.0709314 | 142.839ms | 1313 | 160 | 155.195 | 1388.48 | 0.182636 | 2.69321 | 3(Loss) | true |
| simdjson (ondemand) | 336.281 | 0.0508509 | 377.205ms | 1313 | 30 | 107.559 | 3723.6 | 0.11651 | 7.30942 | 4(Loss) | true |
