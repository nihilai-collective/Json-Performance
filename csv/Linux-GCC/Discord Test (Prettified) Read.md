
----
### Discord Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2173.28 | 0.139904 | 3760.8ms | 83958 | 640 | 1.70034e+06 | 36842.2 | 0.0641684 | 1.13839 | 1(Win) | true |
| simdjson (ondemand) | 2108.3 | 0.0866116 | 3842.21ms | 83958 | 2560 | 2.76982e+06 | 37977.8 | 0.144386 | 1.17351 | 2(Loss) | true |
