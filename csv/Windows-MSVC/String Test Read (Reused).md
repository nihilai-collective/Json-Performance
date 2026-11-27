
----
### String Test Read (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 612.648 | 0.0633662 | 786.43ms | 4215 | 160 | 2765.72 | 6561.25 | 0.0571211 | 4.0185 | 1(Win) | true |
| simdjson (ondemand) | 512.722 | 0.144722 | 890.924ms | 4215 | 30 | 3862.07 | 7840 | 0.0851064 | 4.79881 | 2(Loss) | true |
