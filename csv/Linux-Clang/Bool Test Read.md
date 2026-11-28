
----
### Bool Test Read Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1750.3 | 0.158987 | 48.9981ms | 905 | 30 | 18.4379 | 493.1 | 0 | 1.33385 | 1(Win) | true |
| Glaze | 1376.76 | 0.087999 | 64.5357ms | 905 | 160 | 48.6917 | 626.888 | 0.0858146 | 1.72026 | 2(Loss) | true |
| simdjson (ondemand) | 436.257 | 0.215075 | 203.398ms | 905 | 4890 | 88532.1 | 1978.36 | 0.415361 | 5.59728 | 3(Loss) | true |
