
----
### Twitter Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2307.03 | 0.418746 | 7353.68ms | 360584 | 40 | 1.55837e+07 | 149058 | 0.339592 | 1.07282 | 1(Win) | true |
| Jsonifier (generic) | 2200.37 | 0.346962 | 7780.64ms | 360584 | 80 | 2.35221e+07 | 156283 | 0.742965 | 1.1249 | 2(Loss) | true |
