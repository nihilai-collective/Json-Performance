
----
### Double Test Read (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 559.259 | 0.622361 | 323.175ms | 1811 | 1280 | 472832 | 3088.2 | 0.078362 | 5.38513 | 1(Win) | true |
| simdjson (ondemand) | 289.866 | 0.125467 | 617.035ms | 1811 | 1280 | 71534.2 | 5958.28 | 0.909493 | 10.4394 | 2(Loss) | true |
