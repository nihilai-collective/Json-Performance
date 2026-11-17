
----
### Bool Test Read (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 220.172 | 0.189485 | 404.155ms | 905 | 30 | 1655.17 | 3920 | 0.170358 | 11.1517 | 1(Win) | true |
| simdjson (ondemand) | 70.0981 | 0.152006 | 1269.82ms | 905 | 2560 | 896701 | 12312.4 | 0.150473 | 35.1862 | 2(Loss) | true |
