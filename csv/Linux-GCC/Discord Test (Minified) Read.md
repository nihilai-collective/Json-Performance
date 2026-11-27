
----
### Discord Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 21088.3 | 0.0453785 | 259.772ms | 56369 | 30 | 40.1437 | 2549.17 | 0.0248385 | 0.116323 | 1(Win) | true |
| simdjson (stage-1) | 16791.4 | 0.0745621 | 324.325ms | 56369 | 30 | 170.948 | 3201.5 | 0.0823208 | 0.146289 | 2(Loss) | true |
