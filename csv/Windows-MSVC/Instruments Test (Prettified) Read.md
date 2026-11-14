
----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1491.53 | 0.0944424 | 6083.92ms | 183677 | 2560 | 3.14933e+07 | 117442 | 0.26389 | 1.65945 | 1(Win) | true |
| simdjson (ondemand) | 1209.88 | 0.231173 | 7402.91ms | 183677 | 320 | 3.58466e+07 | 144781 | 0.0291473 | 2.04589 | 2(Loss) | true |
