
----
### Twitter Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7912.5 | 0.080802 | 3183.23ms | 264040 | 2560 | 1.69277e+06 | 31824.1 | 0.133535 | 0.312623 | 1(Win) | true |
| simdjson (ondemand) | 6721.01 | 0.122357 | 3764.28ms | 264040 | 1280 | 2.68991e+06 | 37465.8 | 0.401112 | 0.368087 | 2(Loss) | true |
