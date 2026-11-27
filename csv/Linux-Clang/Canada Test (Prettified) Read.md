
----
### Canada Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1800.06 | 0.0405042 | 8604.38ms | 5212421 | 40 | 5.00454e+07 | 2.76155e+06 | 0.350336 | 1.37538 | 1(Win) | true |
| simdjson (ondemand) | 1678.42 | 0.133354 | 9227.47ms | 5212421 | 80 | 1.2479e+09 | 2.96169e+06 | 0.278263 | 1.47506 | 2(Loss) | true |
