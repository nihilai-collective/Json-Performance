
----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 868.304 | 0.154495 | 7133.75ms | 1834197 | 160 | 1.54987e+09 | 2.01453e+06 | 0.388034 | 2.85123 | 1(Win) | true |
| Jsonifier (two-stage) | 813.249 | 0.174645 | 7520.93ms | 1834197 | 80 | 1.12888e+09 | 2.15091e+06 | 0.763595 | 3.04428 | 2(Loss) | true |
| Glaze | 692.552 | 0.146886 | 8664.52ms | 1834197 | 160 | 2.20225e+09 | 2.52577e+06 | 0.253664 | 3.57476 | 3(Loss) | true |
| simdjson (ondemand) | 645.776 | 0.164457 | 9346.12ms | 1834197 | 30 | 5.95327e+08 | 2.70872e+06 | 0.0247928 | 3.83379 | 4(Loss) | true |
