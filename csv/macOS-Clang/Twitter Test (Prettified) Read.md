
----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2147.98 | 0.460437 | 7428.49ms | 631514 | 160 | 2.66666e+08 | 280384 | 1.81931 | 1(Win) | true |
| Jsonifier (two-stage) | 1947.58 | 0.356989 | 7962.69ms | 631514 | 640 | 7.79945e+08 | 309234 | 0.557574 | 2(Loss) | true |
| Glaze | 1799.65 | 0.234369 | 8874.59ms | 631514 | 160 | 9.84259e+07 | 334653 | 1.15014 | 3(Loss) | true |
| simdjson (ondemand) | 975.028 | 0.798499 | 7910.27ms | 631514 | 30 | 7.29796e+08 | 617683 | 0.0362183 | 4(Loss) | true |
