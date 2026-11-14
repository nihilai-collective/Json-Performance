
----
### Random Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 3431.87 | 0.0713002 | 9682.5ms | 676745 | 1280 | 2.30134e+07 | 188059 | 0.0216362 | 0.721264 | 1(Win) | true |
| Jsonifier (generic) | 3383.1 | 0.127589 | 9757.57ms | 676745 | 1280 | 7.58329e+07 | 190770 | 0.128378 | 0.731631 | 2(Loss) | true |
