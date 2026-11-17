
----
### Discord Test (Prettified) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 19014.2 | 0.0276564 | 422.215ms | 83958 | 30 | 40.6897 | 4211 | 0.015829 | 0.129322 | 1(Win) | true |
| simdjson (stage-1) | 15858.5 | 0.0555591 | 526.655ms | 83958 | 30 | 236.064 | 5048.93 | 0.0402888 | 0.155262 | 2(Loss) | true |
