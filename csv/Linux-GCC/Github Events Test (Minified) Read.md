
----
### Github Events Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 22824.6 | 0.153938 | 225.548ms | 53331 | 4890 | 57538.3 | 2228.32 | 0.0141786 | 0.107095 | 1(Win) | true |
| simdjson (stage-1) | 17515.6 | 0.30138 | 293.723ms | 53331 | 1280 | 98027.7 | 2903.72 | 0.0158765 | 0.140011 | 2(Loss) | true |
