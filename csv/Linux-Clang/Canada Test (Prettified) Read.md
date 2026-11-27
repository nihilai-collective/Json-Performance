
----
### Canada Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 23275.3 | 0.107095 | 5660.12ms | 5373214 | 160 | 8.89483e+06 | 220160 | 0.0261673 | 0.106356 | 1(Win) | true |
| simdjson (stage-1) | 20241.3 | 0.134862 | 6502.76ms | 5373214 | 80 | 9.32531e+06 | 253161 | 0.0139457 | 0.122301 | 2(Loss) | true |
