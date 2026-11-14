
----
### Twitter Test (Prettified) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 21976.7 | 0.126486 | 2758.26ms | 631514 | 2560 | 3.07586e+06 | 27404.4 | 0.13779 | 0.112542 | 1(Win) | true |
| simdjson (stage-1) | 19455.8 | 0.176918 | 3253.15ms | 631514 | 1280 | 3.839e+06 | 30955.2 | 0.0176698 | 0.127125 | 2(Loss) | true |
