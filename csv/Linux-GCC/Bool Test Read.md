
----
### Bool Test Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 660.593 | 0.0213866 | 135.001ms | 905 | 320 | 24.9841 | 1306.52 | 0.103938 | 3.66768 | 1(Win) | true |
| simdjson (stage-1) | 327.645 | 0.0570393 | 278.142ms | 905 | 40 | 90.3019 | 2634.18 | 0.0332283 | 7.48028 | 2(Loss) | true |
