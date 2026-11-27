
----
### Apache Builds Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2647.83 | 0.0853224 | 4654.78ms | 94653 | 1280 | 1.08299e+06 | 34091.3 | 0.00758475 | 0.934327 | 1(Win) | true |
| Jsonifier (two-stage) | 2051.27 | 0.525868 | 5746.7ms | 94653 | 40 | 2.14209e+06 | 44006 | 0.0887915 | 1.20626 | 2(Loss) | true |
| Glaze | 2001.74 | 0.230797 | 5800.46ms | 94653 | 160 | 1.73314e+06 | 45094.9 | 0.00413035 | 1.23611 | 3(Loss) | true |
| simdjson (ondemand) | 1429.91 | 0.0562828 | 8364ms | 94653 | 2560 | 3.23178e+06 | 63128.5 | 0.114478 | 1.73068 | 4(Loss) | true |
