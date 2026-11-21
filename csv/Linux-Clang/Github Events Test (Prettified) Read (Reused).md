
----
### Github Events Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2923.96 | 0.468109 | 2661.15ms | 65103 | 80 | 790394 | 21233.9 | 0.434858 | 0.845679 | 1(Win) | true |
| Jsonifier | 2026.37 | 0.0714482 | 3688.45ms | 65103 | 4890 | 2.34346e+06 | 30639.6 | 0.186185 | 1.22075 | 2(Loss) | true |
| Glaze | 1975.77 | 0.103925 | 3655.27ms | 65103 | 2560 | 2.73028e+06 | 31424.2 | 0.140746 | 1.25202 | 3(Loss) | true |
| simdjson (ondemand) | 1362.12 | 0.0792883 | 5105.75ms | 65103 | 2560 | 3.34372e+06 | 45581.2 | 0.026133 | 1.8165 | 4(Loss) | true |
