
----
### Discord Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3367.3 | 0.0571997 | 2717.23ms | 83958 | 4890 | 904600 | 23778.3 | 0.0449723 | 0.734398 | 1(Win) | true |
| Jsonifier | 2555.28 | 0.0944346 | 3470.29ms | 83958 | 1280 | 1.12078e+06 | 31334.6 | 0.123135 | 0.968109 | 2(Loss) | true |
| Glaze | 2446.7 | 0.0605931 | 3596.88ms | 83958 | 2560 | 1.00658e+06 | 32725.1 | 0.0337476 | 1.0111 | 3(Loss) | true |
| simdjson (ondemand) | 1444.65 | 0.0508319 | 5896.89ms | 83958 | 2560 | 2.03195e+06 | 55424.4 | 0.031526 | 1.71289 | 4(Loss) | true |
