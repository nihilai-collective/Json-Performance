
----
### Discord Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2741.37 | 0.215996 | 2322.7ms | 56369 | 1280 | 2.2964e+06 | 19609.8 | 0.0258109 | 0.901824 | 1(Win) | true |
| Jsonifier (two-stage) | 2139.92 | 0.151401 | 2886.03ms | 56369 | 1280 | 1.85161e+06 | 25121.3 | 0.0242632 | 1.15565 | 2(Loss) | true |
| Glaze | 1881.75 | 0.0916382 | 3219.19ms | 56369 | 2560 | 1.75448e+06 | 28567.9 | 0.00967773 | 1.3144 | 3(Loss) | true |
| simdjson (ondemand) | 904.329 | 0.0662183 | 6298.86ms | 56369 | 2560 | 3.96666e+06 | 59444.8 | 0.12988 | 2.73633 | 4(Loss) | true |
