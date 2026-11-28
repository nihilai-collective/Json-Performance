
----
### Double Test Write Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 372.86 | 0.0639556 | 521.59ms | 1997 | 80 | 853.714 | 5107.79 | 0.22295 | 6.60525 | 1(Win) | true |
| simdjson (reflection) | 305.758 | 0.040476 | 622.997ms | 1997 | 30 | 190.685 | 6228.73 | 0.349603 | 8.06164 | 2(Loss) | true |
| Glaze | 271.757 | 0.1429 | 634.989ms | 1798 | 2560 | 208124 | 6309.7 | 0.0998406 | 9.07127 | 3(Loss) | true |
