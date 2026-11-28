
----
### Bool Test Write (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3292.67 | 0.0455419 | 34.2625ms | 905 | 1280 | 18.2404 | 262.12 | 0.0256389 | 0.678662 | 1(Win) | true |
| simdjson (reflection) | 2544.94 | 0.238982 | 39.2403ms | 905 | 30 | 19.7057 | 339.133 | 0.384805 | 0.894328 | 2(Loss) | true |
| Glaze | 1113.51 | 0.168131 | 86.3142ms | 905 | 160 | 271.721 | 775.094 | 0.823564 | 2.1478 | 3(Loss) | true |
