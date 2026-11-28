
----
### Bool Test Read (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 643.823 | 0.284893 | 138.011ms | 905 | 2560 | 37339.3 | 1340.55 | 0.309833 | 3.77168 | 1(Win) | true |
| Glaze | 592.415 | 0.26959 | 149.312ms | 905 | 160 | 2468.16 | 1456.88 | 0.560828 | 4.09608 | 2(Loss) | true |
| simdjson (ondemand) | 166.056 | 0.0481 | 531.371ms | 905 | 40 | 250 | 5197.5 | 0.0480769 | 14.7962 | 3(Loss) | true |
