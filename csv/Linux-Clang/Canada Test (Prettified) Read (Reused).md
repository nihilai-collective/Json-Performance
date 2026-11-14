
----
### Canada Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1957.04 | 0.0471545 | 9333.55ms | 5212421 | 160 | 2.29533e+08 | 2.54003e+06 | 0.0414589 | 1.26506 | 1(Win) | true |
| simdjson (ondemand) | 1852.3 | 0.12207 | 10068.2ms | 5212421 | 80 | 8.58544e+08 | 2.68366e+06 | 0.107318 | 1.33659 | 2(Loss) | true |
