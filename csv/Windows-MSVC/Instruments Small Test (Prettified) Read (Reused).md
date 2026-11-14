
----
### Instruments Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2553.38 | 0.0899401 | 314.285ms | 7932 | 4890 | 34717.5 | 2962.56 | 0.104854 | 1.18126 | 1(Win) | true |
| Jsonifier | 2267.17 | 0.16453 | 352.554ms | 7932 | 640 | 19287.1 | 3336.56 | 0.270876 | 1.33412 | 2(Loss) | true |
| Glaze | 1971.86 | 0.148415 | 400.751ms | 7932 | 80 | 2593.35 | 3836.25 | 0.227568 | 1.53722 | 3(Loss) | true |
| simdjson (ondemand) | 1590.3 | 0.193452 | 502.378ms | 7932 | 30 | 2540.23 | 4756.67 | 0.626741 | 1.91139 | 4(Loss) | true |
