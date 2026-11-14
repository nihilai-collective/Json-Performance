
----
### Discord Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1590.5 | 0.0736675 | 5497.99ms | 83958 | 1280 | 1.76043e+06 | 50341.8 | 0.009157 | 1.91004 | 1(Win) | true |
| simdjson (ondemand) | 1458.32 | 0.0454676 | 5948.67ms | 83958 | 2560 | 1.59538e+06 | 54904.7 | 0.0804014 | 2.0833 | 2(Loss) | true |
