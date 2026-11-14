
----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2318.44 | 0.12849 | 1044.7ms | 25388 | 4890 | 880462 | 10443.2 | 0.0859029 | 1.30817 | 1(Win) | true |
| Jsonifier | 2209.24 | 0.143696 | 1096.31ms | 25388 | 640 | 158723 | 10959.4 | 0.0456022 | 1.3727 | 2(Loss) | true |
| Glaze | 1510.77 | 0.0729755 | 1600.37ms | 25388 | 4890 | 668843 | 16026.2 | 0.0247766 | 2.00847 | 3(Loss) | true |
| simdjson (ondemand) | 1211.88 | 0.1116 | 1994.77ms | 25388 | 2560 | 1.27266e+06 | 19978.8 | 0.177847 | 2.50502 | 4(Loss) | true |
