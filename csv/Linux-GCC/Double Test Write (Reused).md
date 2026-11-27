
----
### Double Test Write (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 876.332 | 0.0495299 | 224.747ms | 1997 | 40 | 46.3462 | 2173.25 | 0.135926 | 2.78938 | 1(Win) | true |
| simdjson (reflection) | 724.085 | 0.0522333 | 273.253ms | 1997 | 40 | 75.4974 | 2630.2 | 0.0671234 | 3.3831 | 2(Loss) | true |
| Glaze | 558.118 | 0.0975177 | 323.889ms | 1798 | 160 | 1436.2 | 3072.3 | 0.197344 | 4.3972 | 3(Loss) | true |
