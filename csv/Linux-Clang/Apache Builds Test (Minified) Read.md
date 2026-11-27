
----
### Apache Builds Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1762.22 | 0.064726 | 5133.16ms | 94653 | 4890 | 5.37545e+06 | 51224.1 | 0.16359 | 1.40421 | 1(Win) | true |
| Jsonifier (two-stage) | 1495.58 | 0.177284 | 6104.44ms | 94653 | 160 | 1.83192e+06 | 60356.5 | 0.0312524 | 1.65468 | 2(Loss) | true |
| Glaze | 1483.59 | 0.12853 | 6163.85ms | 94653 | 320 | 1.95703e+06 | 60844.3 | 0.152527 | 1.66807 | 3(Loss) | true |
| simdjson (ondemand) | 1127.13 | 0.156049 | 8038.21ms | 94653 | 320 | 4.99792e+06 | 80086.4 | 0.0339827 | 2.19583 | 4(Loss) | true |
