
----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2323.64 | 0.0433702 | 2379.41ms | 56369 | 30 | 3020.27 | 23135.1 | 0.532698 | 1.06426 | 1(Win) | true |
| Jsonifier (two-stage) | 1903.03 | 0.119444 | 2871.55ms | 56369 | 640 | 728618 | 28248.5 | 0.131129 | 1.29977 | 2(Loss) | true |
| Glaze | 1663.65 | 0.114366 | 3264.03ms | 56369 | 1280 | 1.74809e+06 | 32313.1 | 0.20808 | 1.48697 | 3(Loss) | true |
| simdjson (ondemand) | 858.872 | 0.180192 | 6382.02ms | 56369 | 320 | 4.07048e+06 | 62591 | 0.174286 | 2.88142 | 4(Loss) | true |
