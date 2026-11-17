
----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 2493.6 | 0.0594696 | 149.346ms | 3808 | 160 | 120.019 | 1456.36 | 0.0557586 | 0.971837 | 1(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 2488.37 | 0.114681 | 149.48ms | 3808 | 80 | 224.096 | 1459.42 | 0.140269 | 0.976513 | 1(Tie) | true |
| Glaze | 2233.93 | 0.0960461 | 167.135ms | 3808 | 40 | 97.5154 | 1625.65 | 0.150482 | 1.09019 | 3(Loss) | true |
| Jsonifier | 2055.35 | 0.111783 | 180.872ms | 3808 | 40 | 156.041 | 1766.9 | 0.137528 | 1.18612 | 4(Loss) | true |
| simdjson (ondemand) | 1436.36 | 0.159278 | 258.015ms | 3808 | 40 | 648.687 | 2528.32 | 0.00560287 | 1.70554 | 5(Loss) | true |
