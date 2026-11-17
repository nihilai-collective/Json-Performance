
----
### Twitter Partial Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 9340.31 | 0.0471099 | 7268.68ms | 631514 | 2560 | 2.36216e+06 | 64479.5 | 0.0883145 | 0.536645 | 2.6823 | 0.298926 | 0.000617421 | 4.71894e-06 | 3.15833e-06 | 1(Win) | true |
| Jsonifier | 9327.72 | 0.0461907 | 7281.79ms | 631514 | 2560 | 2.27701e+06 | 64566.6 | 0.22016 | 0.537252 | 2.68276 | 0.299054 | 0.000633018 | 5.52739e-06 | 3.29008e-06 | 2(Loss) | true |
| simdjson (ondemand) | 8306.59 | 0.042627 | 8062.69ms | 631514 | 2560 | 2.44529e+06 | 72503.7 | 0.221383 | 0.605801 | 2.87319 | 0.289481 | 0.000615272 | 2.36634e-05 | 1.43801e-05 | 3(Loss) | true |
| Glaze | 4065.35 | 0.031597 | 7970.71ms | 631514 | 1280 | 2.8046e+06 | 148144 | 0.0321363 | 1.24177 | 5.31388 | 0.937515 | 0.00122872 | 1.97888e-05 | 1.21707e-05 | 4(Loss) | true |
