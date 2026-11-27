
----
### Double Test Write Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 363.831 | 0.0294213 | 520.942ms | 1997 | 30 | 71.154 | 5234.53 | 0.0496948 | 6.76835 | 1(Win) | true |
| simdjson (reflection) | 305.076 | 0.0238415 | 629.824ms | 1997 | 80 | 177.214 | 6242.66 | 0.0194266 | 8.07988 | 2(Loss) | true |
| Glaze | 271.968 | 0.0486716 | 640.386ms | 1798 | 80 | 753.327 | 6304.8 | 0.312669 | 9.06219 | 3(Loss) | true |
