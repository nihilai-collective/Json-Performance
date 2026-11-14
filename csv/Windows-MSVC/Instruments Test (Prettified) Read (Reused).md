
----
### Instruments Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2780.11 | 0.124156 | 6586.77ms | 183677 | 80 | 489563 | 63007.5 | 0.15846 | 1.09282 | 1(Win) | true |
| Jsonifier | 2543.62 | 0.0418176 | 7158.72ms | 183677 | 4890 | 4.05539e+06 | 68865.6 | 0.0534001 | 1.19448 | 2(Loss) | true |
| Glaze | 2125.15 | 0.116029 | 8581.76ms | 183677 | 320 | 2.92696e+06 | 82426.2 | 0.171072 | 1.42975 | 3(Loss) | true |
| simdjson (ondemand) | 1597.99 | 0.0591475 | 5732.84ms | 183677 | 2560 | 1.07616e+07 | 109618 | 0.0221343 | 1.9016 | 4(Loss) | true |
