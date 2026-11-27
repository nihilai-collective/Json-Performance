
----
### Bool Test Read (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 374.144 | 0.138666 | 233.148ms | 905 | 1280 | 13096.8 | 2306.8 | 1.24469 | 8.05371 | 1(Win) | true |
| simdjson (ondemand) | 185.608 | 0.199672 | 480.613ms | 905 | 30 | 2586.21 | 4650 | 0.071736 | 16.3174 | 2(Loss) | true |
