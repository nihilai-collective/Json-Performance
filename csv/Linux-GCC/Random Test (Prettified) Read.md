
----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1879.58 | 0.0983349 | 8884.9ms | 676745 | 320 | 3.64833e+07 | 343372 | 0.262206 | 1.31702 | 1(Win) | true |
| simdjson (ondemand) | 1844.87 | 0.149033 | 9230.89ms | 676745 | 40 | 1.08728e+07 | 349832 | 0.0508842 | 1.34182 | 2(Loss) | true |
