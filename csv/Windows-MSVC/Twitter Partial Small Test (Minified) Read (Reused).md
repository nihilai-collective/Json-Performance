
----
### Twitter Partial Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5510.33 | 0 | 54.6901ms | 2889 | 30 | 0 | 500 | 0 | 0.531233 | 1(Win) | true |
| Jsonifier (two-stage) | 5374.27 | 0.39073 | 54.6922ms | 2889 | 4890 | 19620.9 | 512.658 | 0.130139 | 0.544027 | 2(Loss) | true |
| simdjson (ondemand) | 4172.27 | 0.227043 | 69.3063ms | 2889 | 2560 | 5754.47 | 660.352 | 0.183715 | 0.707069 | 3(Loss) | true |
| Glaze | 3133.65 | 0.265596 | 92.7775ms | 2889 | 1280 | 6979.84 | 879.219 | 0.464203 | 0.939967 | 4(Loss) | true |
