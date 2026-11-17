
----
### Canada Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1007.99 | 0.649556 | 8148.04ms | 5212421 | 80 | 8.20895e+10 | 4.93153e+06 | 0.253937 | 3.01487 | 1(Win) | true |
| simdjson (ondemand) | 953.215 | 0.70624 | 8699.12ms | 5212421 | 80 | 1.08516e+11 | 5.21494e+06 | 0.915663 | 3.18817 | 2(Loss) | true |
