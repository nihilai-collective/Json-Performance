
----
### Instruments Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2993.15 | 0.0907581 | 5932.59ms | 183677 | 1280 | 3.61104e+06 | 58522.9 | 0.0372325 | 0.826796 | 1(Win) | true |
| simdjson (ondemand) | 2768.23 | 0.120355 | 6378.64ms | 183677 | 640 | 3.71208e+06 | 63278.1 | 0.328484 | 0.894001 | 2(Loss) | true |
