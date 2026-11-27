
----
### Double Test Read Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 3067.82 | 0.0805593 | 59.3249ms | 1811 | 80 | 16.4551 | 562.975 | 0.0711016 | 0.769616 | 1(Win) | true |
| simdjson (stage-1) | 1246.08 | 0.0569793 | 140.458ms | 1811 | 40 | 24.9481 | 1386.03 | 0.184922 | 1.9467 | 2(Loss) | true |
