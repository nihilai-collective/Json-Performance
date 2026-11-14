
----
### Instruments Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1835.87 | 0.151636 | 5041.32ms | 183677 | 160 | 3.34929e+06 | 95414.4 | 0.0896597 | 1.65503 | 1(Win) | true |
| simdjson (ondemand) | 1634.76 | 0.148282 | 5655.53ms | 183677 | 320 | 8.07843e+06 | 107152 | 0.124958 | 1.85876 | 2(Loss) | true |
