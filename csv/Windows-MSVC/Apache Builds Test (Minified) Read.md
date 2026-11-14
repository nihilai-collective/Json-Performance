
----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 744.273 | 0.454658 | 6204.44ms | 94653 | 2560 | 7.78419e+08 | 121284 | 1.12141 | 4.08227 | 1(Win) | true |
| simdjson (ondemand) | 645.583 | 0.431484 | 7161.11ms | 94653 | 2560 | 9.31825e+08 | 139824 | 0.310445 | 4.7065 | 2(Loss) | true |
