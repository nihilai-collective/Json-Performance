
----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1236.44 | 0.448111 | 7624.78ms | 360584 | 320 | 4.97036e+08 | 278121 | 0.319319 | 2.00197 | 1(Win) | true |
| simdjson (ondemand) | 1024.52 | 0.264966 | 9154.11ms | 360584 | 640 | 5.0621e+08 | 335648 | 0.853486 | 2.41616 | 2(Loss) | true |
