
----
### Random Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2000.05 | 0.0658217 | 8286.97ms | 676745 | 320 | 1.44363e+07 | 322689 | 0.0415978 | 1.23771 | 1(Win) | true |
| simdjson (ondemand) | 1857 | 0.0735893 | 8938.99ms | 676745 | 320 | 2.09318e+07 | 347547 | 0.0914973 | 1.33307 | 2(Loss) | true |
